#pragma once
#include "EC3D/Core/StaticGeometry.h"

namespace ec
{
	/**
	 * \brief Concrete static geometry that represents a circle.
	 */
	class CircleGeometry : public StaticGeometry
	{
	public:
		/**
		 * \brief CircleGeometry constructor.
		 * \param radius The initial radius. [>0]
		 * \param sectionCount The initial number of triangles used
		 * to approximate this circle. [>2]
		 */
		explicit CircleGeometry(float radius = 1.0f, 
								int sectionCount = 20);
		~CircleGeometry();

		/**
		 * \brief Change the circle geometry
		 * \param radius The circle radius. [>0]
		 * \param sectionCount The number of triangles used
		 * to approximate this circle. [>2]
		 */
		void init(float radius, int sectionCount);

		/** 
		 * \brief Get the radius of the circle.
		 */
		float getRadius() const;
		/** 
		 * \brief Get the number of sections used to approximate the circle. 
		 */
		int getSectionCount() const;

	private:
		float m_radius;
		int m_sectionCount;
	};
}
