#include "ec3/common/initializer.h"

#include "spdlog/spdlog.h"

#include <mutex>

namespace
{
    static std::mutex s_initializationMutex;
}

EyeCandy3dInitializer::InitializationResult EyeCandy3dInitializer::initEyeCandy3D()
{
    // Mutual exclusion necessary, since initialization should
    // happen only once.
    s_initializationMutex.lock();
    if(isInitialized())
    {
        s_initializationMutex.unlock();
        return InitializationResult::already_initialized;
    }

    // Set init state and unlock resource
    s_initializationSuccessful = true;
    s_initializationMutex.unlock();

    return InitializationResult::ok;
}

bool EyeCandy3dInitializer::isInitialized()
{
    return s_initializationSuccessful;
}

bool EyeCandy3dInitializer::s_initializationSuccessful = true;