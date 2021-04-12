#include"player.hpp"

Player::Player(unsigned int _modelLoc):modelLoc(_modelLoc)
{
    this->meshes[0].Load("example/resources/models/player/player_hips.daebin");
    this->meshes[1].Load("example/resources/models/player/player_stomach.daebin");
    this->meshes[2].Load("example/resources/models/player/player_chest.daebin");
    this->meshes[3].Load("example/resources/models/player/player_neck.daebin");
    this->meshes[4].Load("example/resources/models/player/player_head.daebin");
    this->meshes[5].Load("example/resources/models/player/player_lupperleg.daebin");
    this->meshes[6].Load("example/resources/models/player/player_llowerleg.daebin");
    this->meshes[7].Load("example/resources/models/player/player_lfoot.daebin");
    this->meshes[8].Load("example/resources/models/player/player_rupperleg.daebin");
    this->meshes[9].Load("example/resources/models/player/player_rlowerleg.daebin");
    this->meshes[10].Load("example/resources/models/player/player_rfoot.daebin");
    this->meshes[11].Load("example/resources/models/player/player_lupperarm.daebin");
    this->meshes[12].Load("example/resources/models/player/player_llowerarm.daebin");
    this->meshes[13].Load("example/resources/models/player/player_rupperarm.daebin");
    this->meshes[14].Load("example/resources/models/player/player_rlowerarm.daebin");    

    this->skeleton = new Skeleton();
    this->skeleton->AddBone(&this->bones[0], 0);
    this->skeleton->AddBone(&this->bones[1], 0);
    this->skeleton->AddBone(&this->bones[2], 1);
    this->skeleton->AddBone(&this->bones[3], 2);
    this->skeleton->AddBone(&this->bones[4], 3);
    this->skeleton->AddBone(&this->bones[5], 0);
    this->skeleton->AddBone(&this->bones[6], 5);
    this->skeleton->AddBone(&this->bones[7], 6);
    this->skeleton->AddBone(&this->bones[8], 0);
    this->skeleton->AddBone(&this->bones[9], 8);
    this->skeleton->AddBone(&this->bones[10], 9);
    this->skeleton->AddBone(&this->bones[11], 2);
    this->skeleton->AddBone(&this->bones[12], 11);
    this->skeleton->AddBone(&this->bones[13], 2);
    this->skeleton->AddBone(&this->bones[14], 13);

    this->animator = new Animator(this->skeleton);
    this->animator->AddAnimation("example/resources/anims/player_idle.anim");

    this->texture = new Hero::Texture();
    this->texture->Load("example/resources/textures/player.png");

    this->currentSpeed = this->moveSpeed;
    this->sprintTime = this->maxSprintTime;
    
    this->root.position = {0.0f, 0.0f, 0.0f};
    this->root.scale = {0.4f, 0.4f, 0.4f};
}

Player::~Player()
{
    delete this->texture;
    delete this->skeleton;
    delete this->animator;
}

void Player::Start()
{

    this->animator->Play("player_idle", true);

}

void Player::Update()
{
    this->animator->Update();
/*
    if(this->sprintTime <= 0.0f)
    {
        this->sprintRestoring = true;
    }
    if(this->sprintRestoring == true)
    {
        this->sprintTime += this->sprintRestorationSpeed 
                                * Hero::Time::GetDeltaTime();
        if(this->sprintTime >= this->maxSprintTime)
        {
            this->sprintRestoring = false;
        }
    }

    if(this->sprintRestoring == false 
            && Hero::Input::keyPressed(Hero::Input::KeyCode::LSHIFT))
    {
        this->targetSpeed = this->runSpeed;
        this->sprintTime -= this->sprintLostSpeed 
                            * Hero::Time::GetDeltaTime();
    }
    else
    {
        this->targetSpeed = this->moveSpeed;
    }
*/
    this->currentSpeed = lerp(this->currentSpeed, this->targetSpeed, 
                                4.0f*Hero::Time::GetDeltaTime());

    Hero::float3 moveVector = {0.0f, 0.0f, 0.0f};

    if(Hero::Input::keyPressed(Hero::Input::KeyCode::W))
    {
        Hero::float3 dir = {0.0f, 0.0f, 1.0f};
        moveVector = Hero::add(moveVector, dir);
    }
    else if(Hero::Input::keyPressed(Hero::Input::KeyCode::S))
    {
        Hero::float3 dir = {0.0f, 0.0f, -1.0f};
        moveVector = Hero::add(moveVector, dir);
    }

    if(Hero::Input::keyPressed(Hero::Input::KeyCode::A))
    {
        Hero::float3 dir = {-1.0f, 0.0f, 0.0f};
        moveVector = Hero::add(moveVector, dir);
    }
    else if(Hero::Input::keyPressed(Hero::Input::KeyCode::D))
    {
        Hero::float3 dir = {1.0f, 0.0f, 0.0f};
        moveVector = Hero::add(moveVector, dir);
    }


    Hero::normalize(moveVector);

    float moveVecLength = Hero::length(moveVector);
    if(moveVecLength != 0.0f)
    {
        float cos = moveVector.x/moveVecLength;
        float alpha = acosf(cos);
        alpha *= (moveVector.z > 0.0f)?-1.0f:1.0f;
        alpha -= PI/2.0f;

        this->root.rotation.y = alpha;
    }

    const float speed = this->moveSpeed * Hero::Time::GetDeltaTime();
    moveVector = Hero::multiply(moveVector, speed);

    this->root.position = Hero::add(this->root.position, moveVector);

    Hero::matrix_identity(this->root.matrix);
    Hero::matrix_scale(this->root.matrix, this->root.scale);
    Hero::matrix_rotate(this->root.matrix, this->root.rotation);
    Hero::matrix_translate(this->root.matrix, this->root.position);

    for(int i = 0; i < 15; i++)
    {
        this->bones[i].matrix = 
            matrix_matrix(this->root.matrix, this->bones[i].matrix);
    }


    /*
    this->transform.position = Hero::add(this->transform.position, moveVector);

    Hero::matrix4x4& matrix = this->transform.matrix;
    Hero::matrix_identity(matrix);
    Hero::matrix_scale(matrix, this->transform.scale);
    Hero::matrix_rotate(matrix, this->transform.rotation);
    Hero::matrix_translate(matrix, this->transform.position);
    */
}

void Player::Draw()
{
    this->texture->Bind();

    for(int i = 0; i < 15; i++)
    {
        glUniformMatrix4fv(this->modelLoc, 1, GL_FALSE, &this->bones[i].matrix.v[0].x);
        glCheckError();
        this->meshes[i].Draw();
    }
}

void Player::Close()
{
    
}