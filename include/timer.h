#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
private:

    Timer();

    static Timer* instance;

    std::chrono::system_clock::time_point startTime;

    std::chrono::system_clock::time_point gameStartTime;

    std::chrono::duration<float> pausedTime = std::chrono::duration<float>(0);

    std::chrono::system_clock::time_point pauseStart;

    bool paused = false;

    std::chrono::duration<float> deltaTime;

public:

    float speed; // normal speed : 1

    static Timer* getInstance();

    void reset();

    float getSpeed();

    float getDeltaTime();

    float getWorldDeltaTime();

    int getPlayedTime();

    void pause();

    void resume();

    void tick();

    ~Timer();

};

#endif