#include "EC3D/Common/Config.h"
#include "EC3D/ThirdParty/easyloggingpp/easylogging++.h"

namespace ec
{
    namespace
    {
        template<class T, int count>
        T strIt2vecf(const CSimpleIniA::TNamesDepend& data)
        {
            T result(0);
            auto it = data.begin();
            for(int i = 0; i < count; ++i)
            {
                result[i] = atof(it->pItem);
                ++it;
            }
            return result;
        }
    }

    Config::Config()
    {
        loadDefaultConfig();
    }

    Config* Config::s_config = nullptr;

    bool Config::loadDefaultConfig()
    {
        return loadConfig(s_configPath);
    }

    bool Config::loadConfig(std::string_view path)
    {
        SI_Error rc = m_ini.LoadFile(path.data());
        m_initialized = rc >= 0;
        return m_initialized;
    }
    bool Config::isInitialized() const
    {
        return m_initialized;
    }

    int Config::readInt(std::string_view key, std::string_view section) const
    {
        return m_ini.GetLongValue(section.data(), key.data());
    }

    double Config::readDouble(std::string_view key, std::string_view section) const
    {
        return m_ini.GetDoubleValue(section.data(), key.data());
    }

    float Config::readFloat(std::string_view key, std::string_view section) const
    {
        return static_cast<float>(m_ini.GetDoubleValue(section.data(), key.data()));
    }

    std::string_view Config::readString(std::string_view key, std::string_view section) const
    {
        return m_ini.GetValue(section.data(), key.data());
    }

    bool Config::readBool(std::string_view key, std::string_view section) const
    {
        return m_ini.GetBoolValue(section.data(), key.data());
    }

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
}