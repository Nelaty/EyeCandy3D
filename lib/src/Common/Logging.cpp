#include "ec3/Common/Logging.h"

#include "spdlog/spdlog.h"

namespace ec {

void Logger::trace(const std::string& message)
{
    spdlog::trace(message);
}
void Logger::debug(const std::string& message)
{
    spdlog::debug(message);
}
void Logger::info(const std::string& message)
{
    spdlog::info(message);
}
void Logger::warn(const std::string& message)
{
    spdlog::warn(message);
}
void Logger::error(const std::string& message)
{
    spdlog::error(message);
}
void Logger::critical(const std::string& message)
{
    spdlog::critical(message);
}
}