#pragma once
#include <iostream>
#include <string>
#include <mutex>

#define LOG(msg) Logger::instance().log(msg)
#define LOG_TTI(tti, msg) Logger::instance().logTti(tti, msg)

class Logger
{
private:
    std::mutex _mutex;

    Logger() = default;
    ~Logger() = default;

public:
    static Logger& instance()
    {
        static Logger logger;
        return logger;
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

    template <typename T>
    void log(const T& msg)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        std::cout << msg << "\n";
    }

    template <typename T>
    void logTti(int tti, const T& msg)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        std::cout << "[TTI " << tti << "] " << msg << "\n";
    }
};