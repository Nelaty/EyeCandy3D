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
		explicit CubeMesh(const float uniformSize = 1.0f);
		explicit CubeMesh(const float width, const float height, const float depth);
		~CubeMesh();

		void Resize(float width, float height, float depth);

	private:
		void Init(const float width, const float height, const float depth);
	};
}