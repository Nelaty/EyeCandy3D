#pragma once
#include "EC3D/Core/StaticGeometry.h"

namespace ec
{
	class SphereMesh : public StaticGeometry
	{
	public:
		explicit SphereMesh(float radius = 1.0f, int latitude = 20, int longitude = 20);
		~SphereMesh();

		void Resize(float radius, int latitude = 20, int longitude = 20);

		float GetRadius() const;
		float GetLatitude() const;
		float GetLongitude() const;

	private:
		void Init(float radius, int latitude, int longitude);

		void InitVerticesAndTexCoords();
		void InitIndices();

		float m_radius;
		float m_latitude;
		float m_longitude;
	};
}