#pragma once

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

		void Init(Geometry* geometry, Material* material, Shader* shader);

		/* Rendering */
		virtual void Render(const glm::mat4& model);

		/* Geometry access */
		void SetGeometry(Geometry* geometry);
		Geometry* GetGeometry();

		/* Material access */
		void SetMaterial(Material* material);
		Material* GetMaterial();

		/* Shader access */
		void SetShader(Shader* shader);
		Shader* GetShader();

	protected:
		/* Prepare drawable for rendering */
		virtual void BeginRender(const glm::mat4& model);
		/* Render the drawable */
		virtual void Render(Shader* shader, const glm::mat4& model);
		/* Finalize the rendering */
		virtual void EndRender();

		/* Transfer material data to the shader */
		void SetMaterialUniforms(Shader* shader, Material* material);

		Geometry* m_geometry;
		Material* m_material;
		Shader* m_shader;
	};
}