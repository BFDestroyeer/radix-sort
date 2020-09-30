#include "logger.h"

Logger::Logger()
{
    file_stream.open("./latest.md", std::ios_base::out);
    file_stream << "|Name|10m|100m|1000m|" << std::endl;
    file_stream << "|-|-|-|-|" << std::endl;
}

Logger::~Logger()
{
    file_stream.close();
}

void Logger::log(std::string name, long long time_10m, long long time_100m, long long time_1000m)
{
    file_stream << "|" << name << "|" << time_10m << "|" << time_100m << "|" << time_1000m << "|" << std::endl;
}