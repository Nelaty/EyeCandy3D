#pragma once
#include "spdlog/spdlog.h"

#include <iostream>

namespace ec {
class Logger
{
public:
    enum class LogLevel
    {
        trace = 0,
        debug,
        info,
        warn,
        error,
        critical,
    };

    static void log(const std::string& message, LogLevel level)
    {
        if(level >= logLevel())
            std::cout << message;
    }

    static void trace(const std::string& message)
    {
        Logger::log(message, LogLevel::trace);
    }
    static void debug(const std::string& message)
    {
        Logger::log(message, LogLevel::debug);
    }
    static void info(const std::string& message)
    {
        Logger::log(message, LogLevel::info);
    }
    static void warn(const std::string& message)
    {
        Logger::log(message, LogLevel::warn);
    }
    static void error(const std::string& message)
    {
        Logger::log(message, LogLevel::error);
    }
    static void critical(const std::string& message)
    {
        Logger::log(message, LogLevel::critical);
    }

    static LogLevel logLevel()
    {
        return LogLevel::trace;
    }
};
}