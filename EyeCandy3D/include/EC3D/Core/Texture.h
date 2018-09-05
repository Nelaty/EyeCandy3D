#pragma once
#include <GL/glew.h>
#include "EC3D/Common/Common.h"

#include <map>
#include <string>

namespace ec
{
	/**
	* Encapsulates texture specific structures
	*/
	struct EC3D_DECLSPEC TextureTypes
	{
	public:
		enum class Type
		{
			texture_diffuse,
			texture_specular,
			texture_bump
		};
		enum Dimensions : GLenum
		{
			texture_2d = GL_TEXTURE_2D,
			texture_3d = GL_TEXTURE_3D
		};

		static const std::string& getTypeString(Type type);

	private:
		static const std::map<Type, std::string> s_textureTypes;
	};

	/**
	* Create and destroy textures on the GPU and enable them for OpenGL
	*/
	class EC3D_DECLSPEC Texture
	{
	public:
		explicit Texture();
		~Texture();

		/** Activate this texture. */
		void bind() const;
		/** Deactivate this texture. */
		void unbind() const;

		/** Buffer Id access*/
		void setId(unsigned int id);
		int getId() const;

		/** Texture type access */
		void setType(const std::string& type);
		const std::string& getType() const;

		/** Texture dimension access */
		TextureTypes::Dimensions getDimensions() const;

		/** Create 2D texture */
		bool textureFromFile(const char* path, const std::string& type);
	
		/** Create a 3D texture */
		bool cubeMapFromFile(const char* path, const std::string& type);

		/** Check if this texture has been initialized */
		bool isInitialized() const;

		/** Deallocation of texture memory */
		void free();

	private:
		bool m_initialized;

		GLuint m_id;
		std::string m_type;

		TextureTypes::Dimensions m_dimension;
	};
}