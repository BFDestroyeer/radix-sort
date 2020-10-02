#include "logger.h"

Logger::Logger()
{
    file_stream.open("./latest.md", std::ios_base::out);
    file_stream << "|Name|1 000 000|100 000 000|1 000 000 000|" << std::endl;
    file_stream << "|-|-|-|-|" << std::endl;
}

Logger::~Logger()
{
    file_stream.close();
}

Logger& Logger::instance()
{
    static Logger logger;
    return logger;
}

void Logger::log(std::string name, std::chrono::nanoseconds time_10m, std::chrono::nanoseconds time_100m,
    std::chrono::nanoseconds time_1000m)
{
    file_stream << "|" << name << "|" <<
        std::chrono::duration_cast<std::chrono::milliseconds>(time_10m).count() << "ms|" <<
        std::chrono::duration_cast<std::chrono::milliseconds>(time_100m).count() << "ms|" <<
        std::chrono::duration_cast<std::chrono::milliseconds>(time_1000m).count() << "ms|" << std::endl;
}