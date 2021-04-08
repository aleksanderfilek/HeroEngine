#ifndef ANIM_HPP
#define ANIM_HPP

#include<string>
#include<vector>
#include<fstream>

#include"Hero.hpp"

#include"components.hpp"
#include"emath.hpp"

struct Bone
{
    unsigned int parentId;
    Transform* transform;
};

class KeyFrame
{
private:
    float time = 0.0f;
    std::vector<Transform> transforms;
public:
    KeyFrame(float _time, const std::vector<Transform>& _transforms);
    ~KeyFrame();

    inline Transform GetTransform(unsigned int id){ return this->transforms[id]; }
    inline float GetTime(){ return this->time; }
};

class Skeleton
{
private:
    std::vector<Bone> bones;
public:
    ~Skeleton();

    void AddBone(Transform* transform, unsigned int parendId);

    bool Update(KeyFrame* previousFrame, KeyFrame* nextFrame, float time);
};


class Animation
{
private:
    std::string name;
    std::vector<KeyFrame*> keyFrames;
public:
    ~Animation();

    bool Load(const std::string& path);

    inline bool CheckName(const std::string& _name){ return this->name.compare(_name) == 0; }
    inline unsigned int FrameCount(){ return this->keyFrames.size(); }
    inline KeyFrame* GetFrame(unsigned int id){ return this->keyFrames[id]; }
    float GetLength();
};

class Animator
{
private:
    std::vector<Animation*> animations;
    Skeleton* skeleton;

    bool isPlaying = false;
    float time = 0.0f;
    unsigned int currentAnimId = 0;
    unsigned int currentFrameId = 0;
    bool loop = false;
public:
    Animator(Skeleton* _skeleton);
    ~Animator();

    void AddAnimation(const std::string& path);
    void RemoveAnimation(const std::string& name);

    void Play(const std::string& name, bool _loop = false);
    void Stop();

    void Update();
};

#endif