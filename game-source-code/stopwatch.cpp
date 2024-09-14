#include "stopwatch.h"

StopWatch::StopWatch(){}

std::chrono::time_point<std::chrono::high_resolution_clock> StopWatch::currentTime()
{
    auto time = std::chrono::high_resolution_clock::now();
    return time;
}

float StopWatch::elapsedTime()
{
    stopTimer();
	auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(finalTime-initialTime);
	auto TimePassed = static_cast<float> (elapsedTime.count())/1000000.0f;
	return TimePassed;
}

void StopWatch::stopTimer()
{

}

void StopWatch::restartTimer()
{

}