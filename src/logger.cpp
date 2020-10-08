#include "logger.h"

Logger::Logger()
{
    file_stream.open("./latest.md", std::ios_base::out);
    file_stream.close();
    #ifdef _WIN32
    std::system("wmic cpu get name | find /v \"Name\" > ./latest.md");
    #endif
    file_stream.open("./latest.md", std::ios::app);
    file_stream << "|Name|Threads count|10 000 000 items|100 000 000 items|1 000 000 000 items|" << std::endl;
    file_stream << "|-|-|-|-|-|" << std::endl;
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

void Logger::log(std::string name, size_t threads_count, std::chrono::nanoseconds time_10m,
    std::chrono::nanoseconds time_100m, std::chrono::nanoseconds time_1000m)
{
    file_stream << "|" << name << "|"
        << threads_count << "|"
        << std::chrono::duration_cast<std::chrono::milliseconds>(time_10m).count() << "ms|"
        << std::chrono::duration_cast<std::chrono::milliseconds>(time_100m).count() << "ms|"
        << std::chrono::duration_cast<std::chrono::milliseconds>(time_1000m).count() << "ms|" << std::endl;
}
