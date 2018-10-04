#pragma once
#include "EC3D/Common/Common.h"
#include "EC3D/Core/Texture.h"

#include <vector>

#include <glm/glm.hpp>

/*
* A material contains all relevant information to color an object
*/
namespace ec
{
	class Shader;

	class EC3D_DECLSPEC Material
	{
	public:
		explicit Material();
		virtual ~Material();

		/* Add a texture to this material */
		void addTexture(const Texture& texture);

		/* Remove a specific texture associated with this material */
		void removeTexture(const Texture& texture);

		/* Try to get a texture at the specified index */
		Texture* getTexture(unsigned int index);

		/* Get all textures associated with this material */
		const std::vector<Texture>& getTextures() const;

		/* */
		bool hasTexture() const;

		/* 
		* Comfort functions to create and add specific texture types to this material 
		* If a texture is supposed to be used by different materials, it should be created
		* outside this class and added via AddTexture
		* return: true -> successfully added
		*/
		bool addDiffuseTextureFromPath(const char* path);
		//bool addSpecularTextureFromPath(const char* path);
		//bool addBumpTextureFromPath(const char* path);

		/* Flat color manipulation functions */
		void setColorAmbient(const glm::vec4& color);
		void setColorAmbient(float r, float g, float b, float a);
		void setColorDiffuse(const glm::vec4& color);
		void setColorDiffuse(float r, float g, float b, float a);
		void setColorSpecular(const glm::vec4& color);
		void setColorSpecular(float r, float g, float b, float a);
		void setColorEmission(const glm::vec4& color);
		void setColorEmission(float r, float g, float b, float a);
	
		/* Flat color getter */
		const glm::vec4& getColorAmbient() const;
		const glm::vec4& getColorDiffuse() const;
		const glm::vec4& getColorSpecular() const;
		const glm::vec4& getColorEmission() const;

		/* Shininess access (specular attribute) */
		void setShininess(float shininess);
		float getShininess() const;

	private:
		/* Flat colors */
		glm::vec4 m_colorAmbient;
		glm::vec4 m_colorDiffuse;
		glm::vec4 m_colorSpecular;
		glm::vec4 m_colorEmission;

		/* Additional attributes */
		float m_shininess;

		/* Textures */
		std::vector<Texture> m_textures;
		bool m_hasTexture;
	};
}