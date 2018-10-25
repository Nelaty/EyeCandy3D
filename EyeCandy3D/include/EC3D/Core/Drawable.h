#pragma once
#include <GL/glew.h>
#include "EC3D/Common/Common.h"

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
		 * \param shader 
		 */
		explicit Drawable(IGeometryAccess* geometry, Material* material, Shader* shader);
		virtual ~Drawable();

		/** Initialize this drawable. Comfort function. */
		void init(IGeometryAccess* geometry, Material* material, Shader* shader);

		/** Render this drawable. */
		virtual void render(const glm::mat4& model);

		/** Set the current geometry. */
		void setGeometry(IGeometryAccess* geometry);
		/** Get the current geometry. */
		IGeometryAccess* getGeometry() const;

		/** Set the current material. */
		void setMaterial(Material* material);
		/** Get the current material. */
		Material* getMaterial() const;

		/** Set the current shader. */
		void setShader(Shader* shader);
		/** Get the current shader. */
		Shader* getShader() const;

	protected:
		/** Prepare drawable for rendering. */
		virtual void beginRender(const glm::mat4& model);
		/** Render the drawable. */
		virtual void render();
		/** Finalize the rendering. */
		virtual void endRender();

		/** Transfer material data to the shader. */
		static void setMaterialUniforms(Shader* shader, Material* material);

		IGeometryAccess* m_geometry;
		Material* m_material;
		Shader* m_shader;
	};
}