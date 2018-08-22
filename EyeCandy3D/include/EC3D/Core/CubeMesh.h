#pragma once
#include "EC3D/Core/StaticGeometry.h"

/*
* Specialized geometry
* Initializes vertices, normals and texture coordinates of a cube
*/
namespace ec
{
	class CubeMesh : public StaticGeometry
	{
	public:
		explicit CubeMesh(float uniformSize = 1.0f);
		explicit CubeMesh(float width, float height, float depth);
		~CubeMesh();

		void resize(float width, float height, float depth);

	private:
		void init(float width, float height, float depth);
	};
}