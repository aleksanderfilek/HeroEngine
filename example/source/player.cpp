#include"player.hpp"

Player::Player(unsigned int _modelLoc)
{
    this->position = {0.0f, 0.0f, 0.0f};

    this->modelLoc = _modelLoc;

    this->mesh = new Hero::Mesh();
    this->mesh->Load("example/resources/models/player.daebin");

    this->texture = new Hero::Texture();
    this->texture->Load("example/resources/textures/player.png");

        Hero::matrix_identity(root.matrix);
        Hero::matrix_scale(root.matrix, root.scale);
        Hero::matrix_rotate(root.matrix, root.rotation);
        Hero::matrix_translate(root.matrix, root.position);

        Hero::matrix_identity(child.matrix);
        Hero::matrix_scale(child.matrix, child.scale);
        Hero::matrix_rotate(child.matrix, child.rotation);
        Hero::matrix_translate(child.matrix, child.position);


}

Player::~Player()
{

}

void Player::Start()
{
    Skeleton* skeleton = new Skeleton();

    skeleton->AddBone(&root, 0);
    skeleton->AddBone(&child, 0);

    animator = new Animator(skeleton);

    animator->AddAnimation("example/resources/anims/player_idle.anim");
    animator->Play("player_idle", true);

}

void Player::Update()
{

    animator->Update();
    
    Hero::float3 mouseRay = this->camera->ScreenToWorldVector();
    Hero::float3 cameraPos = this->camera->GetPosition();

    float x = cameraPos.x - (mouseRay.x/mouseRay.y)*cameraPos.y;
    float y = 0.0f;
    float z = cameraPos.z - (mouseRay.z/mouseRay.y)*cameraPos.y;
    
    Hero::float3 bVec = Hero::substract({x,y,z}, this->position);
    Hero::normalize(bVec);

    float dotProduct = bVec.x;
    float aLength = 1.0f;
    float bLength = Hero::length(bVec);
    float cos = dotProduct/(aLength * bLength);
    float alpha = acosf(cos);
    alpha *= (z>this->position.z)?-1.0f:1.0f;
    alpha -= PI/2.0f;

    Hero::float3 forward = bVec;
    Hero::float3 right = Hero::normalized(Hero::cross_product(forward, {0.0f, 1.0f, 0.0f}));


    Hero::float3 deltaPosition = {0.0f, 0.0f, 0.0f};
    if(Hero::Input::keyPressed(Hero::Input::W))
    {
        deltaPosition = Hero::add(deltaPosition, forward);
    }
    else if(Hero::Input::keyPressed(Hero::Input::S))
    {
        deltaPosition = Hero::substract(deltaPosition, forward);
    }
    if(Hero::Input::keyPressed(Hero::Input::D))
    {
        deltaPosition = Hero::substract(deltaPosition, right);
    }
    else if(Hero::Input::keyPressed(Hero::Input::A))
    {
        deltaPosition = Hero::add(deltaPosition, right);
    }

    deltaPosition = Hero::multiply(deltaPosition, 5.0f*Hero::Time::GetDeltaTime());
    Hero::float3 newPos = Hero::add(deltaPosition, this->position);

    this->position = newPos;

    Hero::matrix_identity(this->modelMatrix);
    //Hero::matrix_scale(this->modelMatrix, {0.5f, 0.5f, 0.5f});
    Hero::matrix_rotateAxisY(this->modelMatrix, alpha);
    Hero::matrix_translate(this->modelMatrix, {position.x, 0.0f, position.z});
}

void Player::Draw()
{
    this->texture->Bind();

    glUniformMatrix4fv(this->modelLoc, 1, GL_FALSE, &this->root.matrix.v[0].x);  
    glCheckError();
    this->mesh->Draw();

    glUniformMatrix4fv(this->modelLoc, 1, GL_FALSE, &this->child.matrix.v[0].x);  
    glCheckError();
    this->mesh->Draw();
}

void Player::Close()
{
    delete mesh;
    delete texture;
    delete animator;
}