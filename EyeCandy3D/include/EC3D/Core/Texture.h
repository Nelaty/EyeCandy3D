#pragma once
#include <gl/glew.h>

#include <map>
#include <string>

namespace ec
{
	/*
	* Encapsulates texture specific structures
	*/
	struct TextureTypes
	{
	public:
		enum class Type
		{
			texture_diffuse,
			texture_specular,
			texture_bump
		};
		enum class Dimensions : int
		{
			texture_2D = GL_TEXTURE_2D,
			texture_3D = GL_TEXTURE_3D
		};

		static const std::string& GetTypeString(const Type type);

	private:
		static const std::map<Type, std::string> s_textureTypes;
	};

	/*
	* Create and destroy textures on the GPU and enable them for OpenGL
	*/
	class Texture
	{
	public:
		explicit Texture();
		~Texture();

		/* Buffer Id access*/
		void SetId(const unsigned int id);
		unsigned int GetId() const;

		/* Texture type access */
		void SetType(const std::string& type);
		const std::string& GetType() const;

		/* Texture dimension access */
		TextureTypes::Dimensions GetDimensions() const;

		/* Create 2D texture */
		bool TextureFromFile(const char* path, const std::string& type);
	
		/* Create a 3D texture */
		bool CubeMapFromFile(const char* path, const std::string& type);

	private:
		unsigned int m_id;
		std::string m_type;

		TextureTypes::Dimensions m_dimension;
	};
}