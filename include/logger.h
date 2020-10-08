#pragma once

#include <cstdlib>

#include <chrono>
#include <fstream>
#include <string>

class Logger
{
    protected:
    std::ofstream file_stream;

    public:
    Logger();
    ~Logger();

    static Logger& instance();

    void log(std::string name, size_t threads_count,std::chrono::nanoseconds time_10m, std::chrono::nanoseconds time_100m,
        std::chrono::nanoseconds time_1000m);
};
