#pragma once
#include <GL/glew.h>
#include "EC3D/Common/Common.h"

#include <map>
#include <string>

namespace ec
{
	/**
	* \brief Encapsulates texture specific structures
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

		/**
		 * \brief Convert a texture type to its string representation.
		 */
		static const std::string& getTypeString(Type type);

	private:
		static const std::map<Type, std::string> s_textureTypes;
	};

	/**
	* \brief Create and destroy textures on the GPU and enable them
	* for OpenGL
	*/
	class EC3D_DECLSPEC Texture
	{
	public:
		explicit Texture();
		~Texture();

		/** 
		 * \brief Check if both texture ids are the same. 
		 */
		bool operator==(const Texture& texture) const;

		/**
		 * \brief Activate this texture. 
		 */
		void bind() const;
		/** 
		 * Deactivate this texture.
		 */
		void unbind() const;

		/**
		 * \brief Get the texture id.
		 */
		int getId() const;

		/** 
		 * \brief Set the type of this texture. 
		 */
		void setType(const std::string& type);
		/**
		 * \brief Get the type of this texture.
		 */
		const std::string& getType() const;

		/** 
		 * \brief Get the dimension of this texture.
		 */
		TextureTypes::Dimensions getDimensions() const;

		/**
		 * \brief Create a 2D texture.
		 * \return True if creation was successful, false otherwise.
		 * \todo Remove type
		 */
		bool textureFromFile(std::string_view path, std::string_view type);
	
		/** 
		 * \brief Create a 3D texture.
		 * \return True if creation was successful, false otherwise.
		 * \todo Remove type
		 */
		bool cubeMapFromFile(std::string_view path, std::string_view type);

		/** 
		 * \brief Get the texture height in pixels. 
		 */
		int getWidth() const;
		/** 
		 * \brief Get the texture width in pixels. 
		 */
		int getHeight() const;
		/** 
		 * \brief Get the number of bytes used per pixel.
		 */
		int getComponentNum() const;

		/** 
		 * \brief Check if this texture has been initialized.
		 */
		bool isInitialized() const;

		/** 
		 * \brief Deallocate texture memory.
		 */
		void free();

	private:
		bool m_initialized;

		GLuint m_id;
		std::string m_type;

		int m_width;
		int m_height;
		int m_componentNum;

		TextureTypes::Dimensions m_dimension;
	};
}