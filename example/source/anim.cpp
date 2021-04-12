#include"anim.hpp"

Skeleton::~Skeleton()
{
    this->bones.clear();
}

void Skeleton::AddBone(Transform* transform, unsigned int parentId)
{
    Bone bone = { parentId, transform };
    this->bones.push_back(bone);
}

bool Skeleton::Update(KeyFrame* previousFrame, KeyFrame* nextFrame, float time)
{
    
    float dt = time - previousFrame->GetTime();
    dt /= nextFrame->GetTime() - previousFrame->GetTime();

    unsigned int length = this->bones.size();
    for(int i = 0; i < length; i++)
    {
        Transform previousTransform = previousFrame->GetTransform(i);
        Transform nextTransform = nextFrame->GetTransform(i);

        Hero::float3 position = 
            Float3Lerp(previousTransform.position, nextTransform.position, dt);
        Hero::float3 rotation = 
            Float3Lerp(previousTransform.rotation, nextTransform.rotation, dt);
        Hero::float3 scale = 
            Float3Lerp(previousTransform.scale, nextTransform.scale, dt);

        Transform transform;
        transform.position = position;
        transform.rotation = rotation;
        transform.scale = scale;

        *this->bones[i].transform = transform;
    }


    for(int i = 0; i < length; i++)
    {
        Transform& transform = *this->bones[i].transform;
        Hero::matrix_identity(transform.matrix);
        Hero::matrix_scale(transform.matrix, transform.scale);
        Hero::matrix_rotate(transform.matrix, transform.rotation);
        Hero::matrix_translate(transform.matrix, transform.position);

        if(i > 0)
        {
            Hero::matrix4x4& parentMatrix = 
                this->bones[this->bones[i].parentId].transform->matrix;

            Hero::matrix4x4 matrix = matrix_matrix(parentMatrix, transform.matrix);

            transform.matrix = matrix;
        }
        
    }

    return dt >= 1.0f;
}

KeyFrame::KeyFrame(float _time, const std::vector<Transform>& _transforms)
{
    this->time = _time;

    for(Transform t: _transforms)
    {
        this->transforms.push_back(t);
    }
}

KeyFrame::~KeyFrame()
{
    this->transforms.clear();
}

Animation::~Animation()
{
    this->keyFrames.clear();
}

bool Animation::Load(const std::string& path)
{
    std::ifstream file(path);
    if(!file.is_open())
    {
        std::cout<<"Could not open animaiton file: "<<path<<std::endl;
        return false;
    }

    file>>this->name;
    unsigned int bones_count;
    file>>bones_count;
    unsigned int frames_count;
    file>>frames_count;

    for(int i = 0; i < frames_count; i++)
    {
        float time;
        file>>time;
        std::vector<Transform> transforms;

        for(int j = 0; j < bones_count; j++)
        {
            Hero::float3 position;
            file>>position.x>>position.y>>position.z;
            Hero::float3 rotation;
            file>>rotation.x>>rotation.y>>rotation.z;
            Hero::float3 scale;
            file>>scale.x>>scale.y>>scale.z;

            Transform transform;
            transform.position = position;
            transform.rotation = {Hero::deg2rad(rotation.x),
                                    Hero::deg2rad(rotation.y),
                                    Hero::deg2rad(rotation.z)};
            transform.scale = scale;

            transforms.push_back(transform);
        }

        KeyFrame* frame = new KeyFrame(time, transforms);
        this->keyFrames.push_back(frame);
    }

    file.close();

    return true;
}

float Animation::GetLength()
{
    float sum = 0.0f;

    for(KeyFrame* f: this->keyFrames)
    {
        sum += f->GetTime();
    }

    return sum;
}

Animator::Animator(Skeleton* _skeleton)
{
    this->skeleton = _skeleton;
}

Animator::~Animator()
{
    for(int i = 0; i < this->animations.size(); i++)
    {
        delete this->animations[i];
        this->animations[i] = nullptr;
    }
    this->animations.clear();

    delete this->skeleton;
}

void Animator::AddAnimation(const std::string& path)
{
    Animation* anim = new Animation();

    if(!anim->Load(path))
    {
        delete anim;
        return;
    }

    for(int f = 0; f<anim->FrameCount(); f++)
    {
        KeyFrame* frame = anim->GetFrame(f);
        std::vector<Transform> newTransform;
        for(int b = 1; b < this->skeleton->GetBonesCount(); b++)
        {
            Transform transform = frame->GetTransform(b);
            Transform parentTransform = 
                frame->GetTransform(this->skeleton->GetBone(b).parentId);
            Hero::float3 newPosition = Hero::substract(transform.position, parentTransform.position);
            transform.position = newPosition;
            newTransform.push_back(transform);
        }
        for(int i = 1; i <= newTransform.size(); i++)
        {
            frame->SetTransform(i, newTransform[i-1]);
        }
    }

    this->animations.push_back(anim);

}

void Animator::RemoveAnimation(const std::string& name)
{
    int i;
    for(i = 0; i < this->animations.size(); i++)
    {
        if(this->animations[i]->CheckName(name))
        {
            break;            
        }
    }

    if(i == this->animations.size())
    {
        std::cout<<"Animaiton: "<<name<<" does not exists."<<std::endl;
        return;
    }

    Animation* anim = this->animations[i];
    this->animations.erase(this->animations.begin() + i);
    delete anim;
}

void Animator::Play(const std::string& name, bool _loop)
{
    int i;
    for(i = 0; i < this->animations.size(); i++)
    {
        if(this->animations[i]->CheckName(name))
        {
            break;            
        }
    }

    if(i == this->animations.size())
    {
        std::cout<<"Animaiton: "<<name<<" does not exists."<<std::endl;
        return;
    }

    this->currentAnimId = i;
    this->currentFrameId = 1;
    this->loop = _loop;
    this->isPlaying = true;
    this->time = 0.0f;
}

void Animator::Stop()
{
    this->isPlaying = false;
    this->currentAnimId = 0;
    this->currentFrameId = 1;
    this->time = 0.0f;
}

void Animator::Update()
{
    if(!this->isPlaying)
    {
        return;
    }

    this->time += Hero::Time::GetDeltaTime();

    Animation* animation = this->animations[this->currentAnimId];

    KeyFrame* previousFrame = animation->GetFrame(this->currentFrameId - 1);

    KeyFrame* nextFrame = animation->GetFrame(this->currentFrameId);


    bool result = this->skeleton->Update(previousFrame, nextFrame, this->time);

    if(result)
    {
        this->currentFrameId++;
        if(animation->FrameCount() == this->currentFrameId)
        {
            if(loop == true)
            {
                this->currentFrameId = 1;
                this->time -= animation->GetLength();
            }
            else
            {
                Stop();
            }
        }
    }
    
}