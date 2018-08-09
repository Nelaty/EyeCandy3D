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

		static const glm::vec3 g_coordinate_system_up = glm::vec3(0.0f, 1.0f, 0.0f);
		static const glm::vec3 g_coordinate_system_orientation = glm::vec3(0.0f, 0.0f, -1.0f);

	#else 
	#ifdef EC3D_LEFT_HANDED_COORDINATE_SYSTEM
	
		static const glm::vec3 g_coordinate_system_up = glm::vec3(0.0f, 1.0f, 0.0f);
		static const glm::vec3 g_coordinate_system_orientation = glm::vec3(0.0f, 0.0f, 1.0f);

	#endif
	#endif
}

namespace conf_shader
{
	static const char* g_material_ambient = "material_ambient";
	static const char* g_material_diffuse = "material_diffuse";
	static const char* g_material_specular = "material_specular";
	static const char* g_material_emissive = "material_emissive";
	static const char* g_material_shininess = "material_shininess";
	static const char* g_material_has_texture = "material_has_texture";
	
	const glm::vec4 g_material_ambient_default = glm::vec4(0.0f);
	const glm::vec4 g_material_diffuse_default = glm::vec4(1.0f);
	const glm::vec4 g_material_specular_default = glm::vec4(0.0f);
	const glm::vec4 g_material_emissive_default = glm::vec4(0.0f);
	constexpr float g_material_shininess_default = 0.1f;
	constexpr bool g_material_has_texture_default = false;

	static const char* g_texture_diffuse = "texture_diffuse";
	static const char* g_texture_specular = "texture_specular";
	static const char* g_texture_bump = "texture_bump";

	static const char* g_basicKey = "basic";
	static const char* g_guiKey = "gui";
	static const char* g_textKey = "text";

	static const char* g_projectionKey = "projection";
	static const char* g_modelKey = "model";
	static const char* g_viewKey = "view";
}



	