#ifndef STOPWATCH
#define STOPWATCH

#include <chrono>

class StopWatch
{
    public:
        StopWatch();
        float elapsedTime();
        void stopTimer();
        void restartTimer();
    
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> currentTime();
        std::chrono::time_point<std::chrono::high_resolution_clock> initialTime;
        std::chrono::time_point<std::chrono::high_resolution_clock> finalTime;

};
#endif