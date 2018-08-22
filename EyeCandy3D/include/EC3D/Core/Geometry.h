#pragma once
#include <glm/glm.hpp>

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
		virtual void render(Shader* shader, const glm::mat4& model);

	protected:
		/** Called at the beginning of the rendering routine. */
		virtual void beginRender() = 0;
		/** The actual rendering of the object. */
		virtual void onRender() = 0;
		/** Called at the end of the rendering routine. */
		virtual void endRender() = 0;
		
		explicit Geometry() = default;
	};
}