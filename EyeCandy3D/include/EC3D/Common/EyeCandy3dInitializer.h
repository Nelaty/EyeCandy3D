//
// Created by nelaty on 30.11.20.
//

#pragma once
#include <cstdint>

class EyeCandy3dInitializer
{
public:
    enum class InitializationResult
    {
        ok = 0,
        already_initialized = 1,
        error = 2
    };

    static InitializationResult initEyeCandy3D();

    static bool isInitialized();

private:
    static bool s_initializationSuccessful;
};
