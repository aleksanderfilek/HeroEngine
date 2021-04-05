#include"player.hpp"

Player::Player(unsigned int _modelLoc)
{
    this->modelLoc = _modelLoc;

    this->mesh = new Hero::Mesh();
    this->mesh->Load("example/resources/models/player.daebin");

    this->texture = new Hero::Texture();
    this->texture->Load("example/resources/textures/player.png");
}

Player::~Player()
{
    delete this->mesh;
    delete this->texture;
}

void Player::Start()
{

}

void Player::Update()
{
    Hero::float3 deltaPosition = {0.0f, 0.0f, 0.0f};
    if(Hero::Input::keyPressed(Hero::Input::W))
    {
        Hero::float3 f = {0.0f, 0.0f, 1.0f};
        deltaPosition = Hero::add(deltaPosition, f);
    }
    else if(Hero::Input::keyPressed(Hero::Input::S))
    {
        Hero::float3 f = {0.0f, 0.0f, 1.0f};
        deltaPosition = Hero::substract(deltaPosition, f);
    }
    if(Hero::Input::keyPressed(Hero::Input::D))
    {
        Hero::float3 f = {1.0f, 0.0f, 0.0f};
        deltaPosition = Hero::add(deltaPosition, f);
    }
    else if(Hero::Input::keyPressed(Hero::Input::A))
    {
        Hero::float3 f = {1.0f, 0.0f, 0.0f};
        deltaPosition = Hero::substract(deltaPosition, f);
    }

    deltaPosition = Hero::multiply(deltaPosition, 5.0f*Hero::Time::GetDeltaTime());
    Hero::float3 newPos = Hero::add(deltaPosition, this->position);

    this->position = newPos;

    Hero::matrix_identity(this->modelMatrix);
    //Hero::matrix_scale(this->modelMatrix, {0.5f, 0.5f, 0.5f});
    Hero::matrix_translate(this->modelMatrix, {position.x, 0.0f, position.z});
}

void Player::Draw()
{
    glUniformMatrix4fv(this->modelLoc, 1, GL_FALSE, &this->modelMatrix.v[0].x);  
    glCheckError();
    this->texture->Bind();
    this->mesh->Draw();
}

void Player::Close()
{

}