#ifndef H_timer_HPP
#define H_timer_HPP

namespace Hero
{

class Time
{    
    private:
        static Time* _instance;

        double _deltaTime;
        double _timeScale;

        void SetDeltaTime(double value){ _instance->_deltaTime = value;}

        Time();

    public:

        static double GetDeltaTime(){ return _instance->_deltaTime*_instance->_timeScale; }
        static void SetScale(double value){ _instance->_timeScale = value; }
        static double GetScale(){ return _instance->_timeScale; }
};

}

#endif