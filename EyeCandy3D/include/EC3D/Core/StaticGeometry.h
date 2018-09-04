#pragma once
#include <GL/glew.h>

#include "EC3D/Core/Geometry.h"


namespace ec
{
	class StaticGeometry : public Geometry
	{
	public:
		virtual ~StaticGeometry();

	protected:
		/* Initialize the geometry */
		virtual void setupMesh();

		explicit StaticGeometry();
	};
}