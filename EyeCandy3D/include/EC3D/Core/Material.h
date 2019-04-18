#pragma once
#include "EC3D/Common/Common.h"
#include "EC3D/Core/Texture.h"
#include "EC3D/Core/Color.h"

#include <vector>

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

		/** Create a new material with a given diffuse color. */
		static Material createFromColor(const Color& color);
		/** Create a new material with a given texture. */
		static Material createFromTexture(const Texture& texture);

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
		bool addDiffuseTextureFromPath(const char* path);

		/** 
		 * \brief Color manipulation function.
		 */
		/// @{
		void setColorAmbient(const Color& color);
		void setColorAmbient(float r, float g, float b, float a);
		void setColorDiffuse(const Color& color);
		void setColorDiffuse(float r, float g, float b, float a);
		void setColorSpecular(const Color& color);
		void setColorSpecular(float r, float g, float b, float a);
		void setColorEmission(const Color& color);
		void setColorEmission(float r, float g, float b, float a);
		/// @}

		/**
		 * \brief Get color function.
		 */
		/// @[
		const Color& getColorAmbient() const;
		const Color& getColorDiffuse() const;
		const Color& getColorSpecular() const;
		const Color& getColorEmission() const;
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
		Color m_colorAmbient;
		Color m_colorDiffuse;
		Color m_colorSpecular;
		Color m_colorEmission;

		/* Additional attributes */
		float m_shininess;

		/* Textures */
		std::vector<Texture> m_textures;
	};
}