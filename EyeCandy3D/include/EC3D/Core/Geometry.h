#pragma once
#include "Vertex.h"
#include "Texture.h"

#include <glm/glm.hpp>

#include <vector>
#include <gl/glew.h>

/*
* Base class for all kinds of geometry.
*/
namespace ec
{
	class Shader;

	class Geometry
	{
	public:
		virtual ~Geometry();

		/* Render this geometry with a given matrix */
		virtual void Render(Shader* shader, const glm::mat4& model);

	protected:
		/** Called at the beginning of the rendering routine. */
		virtual void BeginRender() = 0;
		/** The actual rendering of the object. */
		virtual void OnRender() = 0;
		/** Called at the end of the rendering routine. */
		virtual void EndRender() = 0;
		
		explicit Geometry();
	};
}