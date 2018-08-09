#pragma once
#include "Geometry.h"

/*
* Specialized geometry for rectangles
*/
namespace ec
{
	class RectangleMesh : public Geometry
	{
	public:
		explicit RectangleMesh(const float uniform = 1.0f);
		explicit RectangleMesh(const float width, const float height);
		virtual ~RectangleMesh();

	private:
		void Init(const float width, const float height);
	};
}