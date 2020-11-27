#pragma once
#include "EC3D/ThirdParty/easyloggingpp/easylogging++.h"

class Logging
{
public:

    static el::Logger* getDefaultLogger();
    static el::Logger* getDebugLogger();

private:
    static constexpr const char* s_loggerDefault = "default";
    static constexpr const char* s_loggerDebug = "debug";
};
