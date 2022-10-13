#include "ec3/Common/Config.h"

#include "spdlog/spdlog.h"
#include "SimpleIni.h"

namespace ec
{
    Config::Config()
    {
        loadDefaultConfig();
    }

    Config* Config::s_config = nullptr;

    bool Config::loadDefaultConfig()
    {
        return loadConfig(Config::s_configPath);
    }

    bool Config::loadConfig(std::string_view path)
    {
        m_initialized = m_ini.Load(path.data());
    }
    bool Config::isInitialized() const
    {
        return m_initialized;
    }

    int Config::readInt(std::string_view key, std::string_view section, int defaultValue)
    {
        return defaultValue;
    }

    double Config::readDouble(std::string_view key, std::string_view section, double defaultValue)
    {
        return defaultValue;
    }

    float Config::readFloat(std::string_view key, std::string_view section, float defaultValue)
    {
        return defaultValue;
    }

    std::string Config::readString(std::string_view key, std::string_view section, std::string_view defaultValue)
    {
        return defaultValue.data();
    }

    bool Config::readBool(std::string_view key, std::string_view section, bool defaultValue)
    {
        return defaultValue;
    }

    /*
        glm::vec2 Config::getVec2(std::string_view key, std::string_view section) const
    {
        CSimpleIniA::TNamesDepend values;

        bool iniResult = m_ini.GetAllValues(section.data(), key.data(), values);
        if(!iniResult)
        {
            LOG(INFO) << "Config::getVec2 import error. Section: " << section << "; Key: " << key;
            return glm::vec2(0);
        }
        return strIt2vecf<glm::vec2, 2>(values);
    }

    glm::vec3 Config::getVec3(std::string_view key, std::string_view section) const
    {
        CSimpleIniA::TNamesDepend values;

        bool iniResult = m_ini.GetAllValues(section.data(), key.data(), values);
        if(!iniResult)
        {
            LOG(INFO) << "Config::getVec3 import error. Section: " << section << "; Key: " << key;
            return glm::vec3(0);
        }
        return strIt2vecf<glm::vec3, 3>(values);
    }
    glm::vec4 Config::getVec4(std::string_view key, std::string_view section) const
    {     CSimpleIniA::TNamesDepend values;

        bool iniResult = m_ini.GetAllValues(section.data(), key.data(), values);
        if(!iniResult)
        {
            LOG(INFO) << "Config::getVec4 import error. Section: " << section << "; Key: " << key;
            return glm::vec4(0);
        }
        return strIt2vecf<glm::vec4, 4>(values);
    }
    */
}