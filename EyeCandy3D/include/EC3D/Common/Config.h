#pragma once
#define EC3D_CUDA_SUPPORTED
#define EC3D_RIGHT_HANDED_COORDINATE_SYSTEM

#include <glm/glm.hpp>

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
	static const char* g_materialAmbient = "material_ambient";
	static const char* g_materialDiffuse = "material_diffuse";
	static const char* g_materialSpecular = "material_specular";
	static const char* g_materialEmissive = "material_emissive";
	static const char* g_materialShininess = "material_shininess";
	static const char* g_materialHasTexture = "material_has_texture";
	
	const glm::vec4 g_materialAmbientDefault = glm::vec4(0.0f);
	const glm::vec4 g_materialDiffuseDefault = glm::vec4(1.0f);
	const glm::vec4 g_materialSpecularDefault = glm::vec4(0.0f);
	const glm::vec4 g_materialEmissiveDefault = glm::vec4(0.0f);
	constexpr float g_materialShininessDefault = 0.1f;
	constexpr bool g_materialHasTextureDefault = false;

	static const char* g_textureDiffuse = "texture_diffuse";
	static const char* g_textureSpecular = "texture_specular";
	static const char* g_textureBump = "texture_bump";

	static const char* g_basicKey = "basic";
	static const char* g_guiKey = "gui";
	static const char* g_textKey = "text";

	static const char* g_projectionKey = "projection";
	static const char* g_modelKey = "model";
	static const char* g_viewKey = "view";
}