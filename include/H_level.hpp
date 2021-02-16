#ifndef H_LEVEL_HPP
#define H_LEVEL_HPP

namespace Hero
{

class Level
{
public:
    Level(){};
    virtual ~Level(){};
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void Draw() = 0;
    virtual void Close() = 0;
};

}

#endif