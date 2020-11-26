#pragma once
#include <string>

class TestConfig
{
public:
    static std::string getTexturePath(std::string_view name);

    static const std::string s_resourceDir;
};