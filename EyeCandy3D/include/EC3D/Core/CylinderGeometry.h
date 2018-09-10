#pragma once
#include "EC3D/Core/StaticGeometry.h"

namespace ec
{
	class CylinderGeometry : public StaticGeometry
	{
	public:
		explicit CylinderGeometry(float radius = 0.5f, 
								  float height = 1.0f,
								  int latitude = 15, 
								  int longitude = 15);
		~CylinderGeometry();

		void init(float radius = 0.5f,
				  float height = 1.0f,
				  int latitude = 15,
				  int longitude = 15);

	private:
		void initVerticesAndTexCoords();
		void initIndices();

		float m_radius;
		float m_height;
		int m_latitude;
		int m_longitude;
	};
}