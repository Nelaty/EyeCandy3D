#pragma once
#include "EC3D/Common/Common.h"
#include "EC3D/Core/Texture.h"

#include <vector>
#include <string>

#include <glm/glm.hpp>


namespace ec
{
	class Shader;

	/**
	 * \brief A material contains all relevant information to color an object
	 */
	class EC3D_DECLSPEC Material
	{
	public:
		explicit Material();
		virtual ~Material();

		/**
		 * \brief Add a new texture to this material.
		 */
		void addTexture(const Texture& texture);

		/**
		 * \brief Remove a given texture associated with this 
		 * material.
		 * \return True if the texture was found, false otherwise.
		 */
		bool removeTexture(const Texture& texture);

		/**
		 * \brief Try to get a texture at the specified index.
		 */
		Texture* getTexture(unsigned int index);

		/** 
		 * \brief Get all textures associated with this material. 
		 */
		const std::vector<Texture>& getTextures() const;

		/**
		 * \brief Check if this material is currently using any
		 * textures.
		 */
		bool hasTexture() const;

		/**
		* \brief Comfort functions to create and add specific texture
		* types to this material 
		* \details If a texture is supposed to be used by different 
		* materials, it should be created outside this class and
		* added via AddTexture
		* \return True if the texture was successfully added, false
		* otherwise.
		*/
		bool addDiffuseTextureFromPath(const std::string& path);

		/** 
		 * \brief Color manipulation function.
		 */
		/// @{
		void setColorAmbient(const glm::vec4& color);
		void setColorAmbient(float r, float g, float b, float a);
		void setColorDiffuse(const glm::vec4& color);
		void setColorDiffuse(float r, float g, float b, float a);
		void setColorSpecular(const glm::vec4& color);
		void setColorSpecular(float r, float g, float b, float a);
		void setColorEmission(const glm::vec4& color);
		void setColorEmission(float r, float g, float b, float a);
		/// @}

		/**
		 * \brief Get color function.
		 */
		/// @[
		const glm::vec4& getColorAmbient() const;
		const glm::vec4& getColorDiffuse() const;
		const glm::vec4& getColorSpecular() const;
		const glm::vec4& getColorEmission() const;
		/// @]

		/**
		 * \brief Set the currently used shininess coefficient.
		 */
		void setShininess(float shininess);
		/**
		 * \brief Get the currently used shininess coefficient.
		 */
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
	};
}