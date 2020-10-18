#pragma once

#include <cstdlib>

#include <chrono>
#include <fstream>
#include <string>

/**
 * @brief Class providing test result recording function
 * 
 */
class Logger
{
    protected:
    std::ofstream file_stream;

    public:
    /**
     * @brief Construct a new Logger object
     * 
     */
    Logger();
    
    /**
     * @brief Destroy the Logger object
     * 
     */
    ~Logger();

    /**
     * @brief Returns static Logger instance
     * 
     * @return Logger&
     */
    static Logger& instance();

    /**
     * @brief Recording test result
     * 
     * @param name Name of test
     * @param threads_count Count of threads used for test
     * @param time_10m Time for 10 000 000 items
     * @param time_100m Time for 100 000 000 items
     * @param time_1000m Time for 1 000 000 000 items
     */
    void log(std::string name, size_t threads_count,std::chrono::nanoseconds time_10m, std::chrono::nanoseconds time_100m,
        std::chrono::nanoseconds time_1000m);
};
