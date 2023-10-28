#include "Timer.h"
#include <iostream>

Timer* Timer::instance = nullptr;

Timer::Timer()
{
    speed = 1;
    gameStartTime = std::chrono::system_clock::now();
}

float Timer::getSpeed() {
    return speed;
}

Timer* Timer::getInstance()
{
    if (instance == nullptr)
    {
        instance = new Timer();
    }
    return instance;
}

void Timer::reset()
{
    startTime = std::chrono::system_clock::now();
}

float Timer::getDeltaTime()
{
    return deltaTime.count();
}

float Timer::getWorldDeltaTime()
{
    return deltaTime.count() * speed;
}


void Timer::tick()
{
    deltaTime = std::chrono::system_clock::now() - startTime;
}

int Timer::getPlayedTime()
{
    if (paused) {
		return (int)((std::chrono::system_clock::now() - gameStartTime - pausedTime - (std::chrono::system_clock::now() - pauseStart)).count() / 10000000);
	}

    return (int)((std::chrono::system_clock::now() - gameStartTime - pausedTime).count() / 10000000);
}

void Timer::pause()
{
	pauseStart = std::chrono::system_clock::now();
    paused = true;
}

void Timer::resume()
{
	pausedTime += std::chrono::system_clock::now() - pauseStart;
    paused = false;
}

Timer::~Timer()
{
    delete instance;
    instance = nullptr;
}