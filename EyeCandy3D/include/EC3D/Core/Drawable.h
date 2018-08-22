#pragma once
#include <GL/glew.h>

#include <glm/glm.hpp>

/*
* Core class for rendering geometry data with a certain material and 
* shader.
*/
namespace ec
{
	class Geometry;
	class Material;
	class Shader;

	class Drawable
	{
	public:
		explicit Drawable();
		explicit Drawable(Geometry* geometry, Material* material, Shader* shader);
		virtual ~Drawable();

		void init(Geometry* geometry, Material* material, Shader* shader);

		/* Rendering */
		virtual void render(const glm::mat4& model);

		/* Geometry access */
		void setGeometry(Geometry* geometry);
		Geometry* getGeometry();

		/* Material access */
		void setMaterial(Material* material);
		Material* getMaterial();

		/* Shader access */
		void setShader(Shader* shader);
		Shader* getShader();

	protected:
		/* Prepare drawable for rendering */
		virtual void beginRender(const glm::mat4& model);
		/* Render the drawable */
		virtual void render(Shader* shader, const glm::mat4& model);
		/* Finalize the rendering */
		virtual void endRender();

		/* Transfer material data to the shader */
		void setMaterialUniforms(Shader* shader, Material* material);

		Geometry* m_geometry;
		Material* m_material;
		Shader* m_shader;
	};
}