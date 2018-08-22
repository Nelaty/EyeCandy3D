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
		float getLatitude() const;
		float getLongitude() const;

	private:
		void init(float radius, int latitude, int longitude);

		void initVerticesAndTexCoords();
		void initIndices();

		float m_radius;
		float m_latitude;
		float m_longitude;
	};
}