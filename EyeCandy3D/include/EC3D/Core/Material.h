#pragma once
#include "Texture.h"

#include <vector>

#include <glm/glm.hpp>

/*
* A material contains all relevant information to color an object
*/
namespace ec
{
	class Shader;

	class Material
	{
	public:
		explicit Material();
		virtual ~Material();

		/* Add a texture to this material */
		void AddTexture(const Texture& texture);

		/* Remove a specific texture associated with this material */
		void RemoveTexture(const Texture& texture);

		/* Try to get a texture at the specified index */
		Texture* GetTexture(const unsigned int index);

		/* Get all textures associated with this material */
		const std::vector<Texture>& GetTextures() const;

		/* */
		void SetHasTexture(const bool hasTexture);
		bool HasTexture() const;

		/* 
		* Comfort functions to create and add specific texture types to this material 
		* If a texture is supposed to be used by different materials, it should be created
		* outside this class and added via AddTexture
		* return: true -> successfully added
		*/
		bool AddDiffuseTextureFromPath(const char* path);
		bool AddSpecularTextureFromPath(const char* path);
		bool AddBumpTextureFromPath(const char* path);

		/* Flat color manipulation functions */
		void SetColorAmbient(const glm::vec4& color);
		void SetColorAmbient(const float r, const float g, const float b, const float a);
		void SetColorDiffuse(const glm::vec4& color);
		void SetColorDiffuse(const float r, const float g, const float b, const float a);
		void SetColorSpecular(const glm::vec4& color);
		void SetColorSpecular(const float r, const float g, const float b, const float a);
		void SetColorEmissive(const glm::vec4& color);
		void SetColorEmissive(const float r, const float g, const float b, const float a);

		/* Flat color getter */
		const glm::vec4& GetColorAmbient() const;
		const glm::vec4& GetColorDiffuse() const;
		const glm::vec4& GetColorSpecular() const;
		const glm::vec4& GetColorEmissive() const;

		/* Shininess access (specular attribute) */
		void SetShininess(const float shininess);
		float GetShininess() const;

	private:
		/* Flat colors */
		glm::vec4 m_colorAmbient;
		glm::vec4 m_colorDiffuse;
		glm::vec4 m_colorSpecular;
		glm::vec4 m_colorEmissive;

		/* Additional attributes */
		float m_shininess;

		/* Textures */
		std::vector<Texture> m_textures;
		bool m_hasTexture;
	};
}