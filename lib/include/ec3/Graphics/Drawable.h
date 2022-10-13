#pragma once
#include <GL/glew.h>
#include "ec3/Common/Common.h"

#include <glm/glm.hpp>


namespace ec
{
	class IGeometryAccess;
	class Material;
	class Shader;

	/**
	 * \brief Core class for rendering geometry data with a certain material and
	 * shader.
	 */
	class EC3D_DECLSPEC Drawable
	{
	public:
		explicit Drawable();
		/**
		 * \brief Drawable constructor.
		 * \param geometry The geometry to render onto.
		 * \param material Color information.
		 * \param shader The shader used for drawing.
		 */
		explicit Drawable(IGeometryAccess* geometry, Material* material, Shader* shader);
		virtual ~Drawable();

		/** 
		 * \brief Initialize this drawable. Comfort function. 
		 * \param geometry The geometry to render onto.
		 * \param material Color information.
		 * \param shader The shader used for drawing.
		 */
		void init(IGeometryAccess* geometry, Material* material, Shader* shader);

		/** 
		 * \brief Render this drawable. 
		 * \param model Transformation of the object to draw.
		 */
		virtual void render(const glm::mat4& model);

		/** 
		 * \brief Set the current geometry. 
		 */
		void setGeometry(IGeometryAccess* geometry);
		/**
		 * \brief Get the current geometry. 
		 */
		IGeometryAccess* getGeometry() const;

		/** 
		 * \brief Set the current material. 
		 */
		void setMaterial(Material* material);
		/**
		 * \brief Get the current material. 
		 */
		Material* getMaterial() const;

		/**
		 * \brief Set the current shader. 
		 */
		void setShader(Shader* shader);
		/** 
		 * \brief Get the current shader. 
		 */
		Shader* getShader() const;

	protected:
		/** 
		 * \brief Prepare drawable for rendering. 
		 */
		virtual void beginRender(const glm::mat4& model);
		/** 
		 * \brief Render the drawable. 
		 */
		virtual void render();
		/** 
		 * \brief Finalize the rendering. 
		 */
		virtual void endRender();

		/**
		 * \brief Transfer material data to the shader. 
		 * \param shader The shader to pass the data to.
		 * \param material The material data to pass.
		 */
		static void setMaterialUniforms(Shader* shader, Material* material);

		IGeometryAccess* m_geometry;
		Material* m_material;
		Shader* m_shader;
	};
}