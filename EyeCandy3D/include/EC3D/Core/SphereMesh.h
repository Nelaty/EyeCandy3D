#pragma once
#include "EC3D/Core/StaticGeometry.h"

namespace ec
{
	class SphereMesh : public StaticGeometry
	{
	public:
		explicit SphereMesh(float radius = 1.0f, int latitude = 20, int longitude = 20);
		~SphereMesh();

		void resize(float radius, int latitude = 20, int longitude = 20);

		float getRadius() const;
		int getLatitude() const;
		int getLongitude() const;

	private:
		void init(float radius, int latitude, int longitude);

		void initVerticesAndTexCoords();
		void initIndices();

		float m_radius;
		int m_latitude;
		int m_longitude;
	};
}