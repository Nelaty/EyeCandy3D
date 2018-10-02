#pragma once
#include "EC3D/Core/StaticGeometry.h"

namespace ec
{
	class CircleGeometry : public StaticGeometry
	{
	public:
		explicit CircleGeometry(float radius = 1.0f, int sectionCount = 20);
		~CircleGeometry();

		/**
		 * \brief Change the circle geometry
		 * \param radius Needs to be > 0.0f
		 * \param sectionCount Needs to be > 2
		 */
		void init(float radius, int sectionCount);

		/** Get the radius of the circle */
		float getRadius() const;
		/** Get the number of sections used to approximate the circle */
		int getSectionCount() const;

	private:
		float m_radius;
		int m_sectionCount;
	};
}
