#pragma once
#include "EC3D/Core/StaticGeometry.h"

/*
* Specialized geometry for rectangles
*/
namespace ec
{
	class RectangleMesh : public StaticGeometry
	{
	public:
		explicit RectangleMesh(float uniform = 1.0f);
		explicit RectangleMesh(float width, float height);
		virtual ~RectangleMesh();

	private:
		void init(float width, float height);
	};
}