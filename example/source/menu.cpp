#include"menu.hpp"

event(prymityw)
{
    extern unsigned int DrawType;
    if(Hero::Input::keyPressed(Hero::Input::F1))
    {
        DrawType = GL_LINE_STRIP;
    }
    else
    {
        DrawType = GL_TRIANGLES;
    }
    
}

void Menu::Start()
{
    this->fontBig = new Hero::Font("example/resources/arial.ttf", 100);
    this->fontSmall = new Hero::Font("example/resources/arial.ttf", 28);

    this->shader = new Hero::Shader();
    this->shader->Load("example/resources/shaders/uiShader.glslbin");
    Hero::Renderer2D::SetShader(this->shader);

    this->btnTexture = new Hero::Texture();
    this->btnTexture->Load("example/resources/textures/button.png");

    this->uiGroup = new Hero::Group();

    Hero::Text* text = new Hero::Text();
    text->SetFont(this->fontBig);
    text->SetText("DEMO");
    text->Apply();
    Hero::int2 textSize = text->GetSize();
    Hero::int2 textPosition = (Hero::int2){640 - (int)(textSize.x/2), 100};
    text->SetRelativePosition(textPosition);

    this->uiGroup->Add(text);

    Hero::Button* startButton = new Hero::Button();
    startButton->SetFont(this->fontSmall);
    startButton->SetText("START");
    startButton->SetTexture(this->btnTexture);
    startButton->Apply();
    startButton->SetSize({100, 30});
    Hero::int2 startBtnPos = (Hero::int2){640 - (int)(100/2), 360};
    startButton->SetRelativePosition(startBtnPos);
    startButton->AddClickEvent(EventFromClass(StartBtn_Click));

    this->uiGroup->Add(startButton);

    Hero::Button* quitButton = new Hero::Button();
    quitButton->SetFont(this->fontSmall);
    quitButton->SetText("QUIT");
    quitButton->SetTexture(this->btnTexture);
    quitButton->Apply();
    quitButton->SetSize({100, 30});
    Hero::int2 quitBtnPos = (Hero::int2){640 - (int)(100/2), 400};
    quitButton->SetRelativePosition(quitBtnPos);
    quitButton->AddClickEvent(EventFromClass(QuitBtn_Click));

    this->uiGroup->Add(quitButton);

    glClearColor(0.39f, 0.58f, 0.92f, 1.0f);

    Hero::Game::RuntimeInject(prymityw);

}

void Menu::Update()
{

    this->uiGroup->Update();
}

void Menu::Draw()
{
    Hero::ClearRenderer();

    this->uiGroup->Draw();
}

void Menu::Close()
{
    delete this->fontBig;
    delete this->fontSmall;
    delete this->shader;
    delete this->uiGroup;
    delete this->btnTexture;
}

event(Menu::StartBtn_Click)
{
    World* worldLevel = new World();
    Hero::Game::SetLevel(worldLevel);
}

event(Menu::QuitBtn_Click)
{
    SDL_Event quitEvent;
    quitEvent.type = SDL_QUIT;
    SDL_PushEvent(&quitEvent);
 
}