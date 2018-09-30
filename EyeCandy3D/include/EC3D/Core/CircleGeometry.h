#pragma once
#include "EC3D/Core/StaticGeometry.h"

namespace ec
{
	class CircleGeometry : public StaticGeometry
	{
	public:
		explicit CircleGeometry(float radius = 1.0f, int sectionCount = 20);
		~CircleGeometry();

		float getRadius() const;
		int getSectionCount() const;

	private:
		void init(float radius, int sectionCount);

		float m_radius;
		int m_sectionCount;
	};
}
