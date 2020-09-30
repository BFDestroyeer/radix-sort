#pragma once

#include <fstream>
#include <string>

class Logger
{
    protected:
    std::ofstream file_stream;

    public:
    Logger();
    ~Logger();

    void log(std::string name, long long time_10m, long long time_100m, long long time_1000m);
};