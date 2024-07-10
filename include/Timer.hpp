#pragma once

#include <chrono>
#include <iostream>

class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_point;
    std::chrono::time_point<std::chrono::high_resolution_clock> end_time_point;

public:
    void start() { start_time_point = std::chrono::high_resolution_clock::now(); }
    
    void stop() { end_time_point = std::chrono::high_resolution_clock::now(); }
    
    void display()
    {
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(
                start_time_point).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(end_time_point).time_since_epoch().count();
        
        double duration = static_cast<double>(end - start) * 0.000001;
        
        std::cout << "Time taken: " << duration << " seconds." << std::endl << std::endl;
    }
};