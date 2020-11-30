#pragma once
#define EC3D_CUDA_SUPPORTED
#define EC3D_RIGHT_HANDED_COORDINATE_SYSTEM

#include "EC3D/ThirdParty/SimpleIni/SimpleIni.h"

#include <glm/glm.hpp>

namespace ec
{
    struct ConfigKeywordsWindow
    {
        static constexpr const char* SECTION = "Window";
        static constexpr const char* WIDTH_DEFAULT = "WIDTH_DEFAULT";
        static constexpr const char* HEIGHT_DEFAULT = "HEIGHT_DEFAULT";
    };

    struct ConfigKeywordsOpenGL
    {
        static constexpr const char* SECTION = "OpenGL";
        static constexpr const char* GL_MINOR = "GL_MINOR";
        static constexpr const char* GL_MAJOR = "GL_MAJOR";
    };

    struct ConfigKeywordShader
    {
        static constexpr const char* SECTION = "Shader";
        static constexpr const char* PROJECTION_KEY = "PROJECTION_KEY";
        static constexpr const char* MODEL_KEY = "MODEL_KEY";
        static constexpr const char* VIEW_KEY = "VIEW_KEY";
    };

    class Config
    {
    public:
        /** Initialize the singleton instance. */
        static bool init()
        {
            getInstance();
            return s_config != nullptr;
        }

        /** Get the singleton instance. */
        static Config* getInstance()
        {
            if(s_config) s_config = new Config();
            return s_config;
        }

        /** Check if the ini has successfully been initialized. */
        bool isInitialized() const;

        /** Read a bool value from the configuration file. */
        bool readBool(std::string_view key, std::string_view section) const;
        /** Read a int value from the configuration file. */
        int readInt(std::string_view key, std::string_view section) const;
        /** Read a float value from the configuration file. */
        float readFloat(std::string_view key, std::string_view section) const;
        /** Read a double value from the configuration file. */
        double readDouble(std::string_view key, std::string_view section) const;
        /** Read a string from the configuration file. */
        std::string_view readString(std::string_view key, std::string_view section) const;

        glm::vec2 getVec2(std::string_view key, std::string_view section) const;
        glm::vec3 getVec3(std::string_view key, std::string_view section) const;
        glm::vec4 getVec4(std::string_view key, std::string_view section) const;

    private:
        explicit Config();
        ~Config() = default;

        static Config* s_config;

        CSimpleIniA m_ini;
        bool m_initialized{false};

        bool loadDefaultConfig();
        bool loadConfig(const std::string_view path);

        static constexpr const char* s_configPath = "res_sample_0815/config.ini";
    };
}

namespace conf
{
	// OpenGL
	constexpr unsigned int g_glMajor = 3;
	constexpr unsigned int g_glMinor = 3;

	// CUDA
	constexpr unsigned int g_cuNumberOfBlocks = 1024;
	constexpr unsigned int g_cuThreadsPerBlock = 256;

	#ifdef EC3D_RIGHT_HANDED_COORDINATE_SYSTEM

		static const glm::vec3 g_coordinateSystemUp = glm::vec3(0.0f, 1.0f, 0.0f);
		static const glm::vec3 g_coordinateSystemOrientation = glm::vec3(0.0f, 0.0f, -1.0f);

	#else 
	#ifdef EC3D_LEFT_HANDED_COORDINATE_SYSTEM
	
		static const glm::vec3 g_coordinateSystemUp = glm::vec3(0.0f, 1.0f, 0.0f);
		static const glm::vec3 g_coordinateSystemOrientation = glm::vec3(0.0f, 0.0f, 1.0f);

	#endif
	#endif
}

namespace conf_shader
{
	static constexpr const char* g_materialAmbient = "material_ambient";
	static constexpr const char* g_materialDiffuse = "material_diffuse";
	static constexpr const char* g_materialSpecular = "material_specular";
	static constexpr const char* g_materialEmissive = "material_emissive";
	static constexpr const char* g_materialShininess = "material_shininess";
	static constexpr const char* g_materialHasTexture = "material_has_texture";
	
	const glm::vec4 g_materialAmbientDefault = glm::vec4(0.0f);
	const glm::vec4 g_materialDiffuseDefault = glm::vec4(1.0f);
	const glm::vec4 g_materialSpecularDefault = glm::vec4(0.0f);
	const glm::vec4 g_materialEmissiveDefault = glm::vec4(0.0f);
	constexpr float g_materialShininessDefault = 0.1f;
	constexpr bool g_materialHasTextureDefault = false;

	static constexpr const char* g_textureDiffuse = "texture_diffuse";
	static constexpr const char* g_textureSpecular = "texture_specular";
	static constexpr const char* g_textureBump = "texture_bump";

	static constexpr const char* g_basicKey = "basic";
	static constexpr const char* g_guiKey = "gui";
	static constexpr const char* g_textKey = "text";

	static constexpr const char* g_projectionKey = "projection";
	static constexpr const char* g_modelKey = "model";
	static constexpr const char* g_viewKey = "view";
}