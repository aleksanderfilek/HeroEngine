#ifndef HERO_LEVEL_CORE_HPP
#define HERO_LEVEL_CORE_HPP

namespace Hero
{

class ILevel
{
private:
    bool enable = true;

public:
    void Init()
    {
        if(this->enable)
        {
            this->OnInit();
        }
    }

    void Update()
    {
        if(this->enable)
        {
            this->OnUpdate();
        }
    }

    void Close()
    {
        if(this->enable)
        {
            this->OnClose();
        }
    }

    bool GetEnable(){ return this->enable; }
    void SetEnable(bool _enable){ this->enable = _enable; }

    virtual void OnInit(){};
    virtual void OnUpdate(){};
    virtual void OnClose(){};
};

}

#endif