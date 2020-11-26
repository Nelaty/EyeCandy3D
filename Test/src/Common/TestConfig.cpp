#include "TestConfig.h"

const std::string TestConfig::s_resourceDir =
    "./TestResources/";

std::string TestConfig::getTexturePath(std::string_view name)
{
    return s_resourceDir + name.data();
}
