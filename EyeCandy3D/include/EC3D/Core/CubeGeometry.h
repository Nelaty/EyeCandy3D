#pragma once
#include "EC3D/Core/StaticGeometry.h"

/*
* Specialized geometry
* Initializes vertices, normals and texture coordinates of a cube
*/
namespace ec
{
	class CubeGeometry : public StaticGeometry
	{
	public:
		explicit CubeGeometry(float uniformSize = 1.0f);
		explicit CubeGeometry(float width, float height, float depth);
		~CubeGeometry();

		void resize(float width, float height, float depth);

	private:
		void init(float width, float height, float depth);
	};
}