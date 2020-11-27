#include "EC3D/Common/Logging.h"

el::Logger* Logging::getDefaultLogger()
{
    return el::Loggers::getLogger(s_loggerDefault);
}

el::Logger* Logging::getDebugLogger()
{
    return el::Loggers::getLogger(s_loggerDebug);
}
