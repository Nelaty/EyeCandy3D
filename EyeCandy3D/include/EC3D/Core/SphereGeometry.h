#pragma once
#include "EC3D/Core/StaticGeometry.h"
#include "EC3D/Common/Common.h"

namespace ec
{
	/**
	 * \brief Geometry that represents a sphere.
	 */
	class EC3D_DECLSPEC SphereGeometry : public StaticGeometry
	{
	public:
		/**
		 * \brief SphereGeometry constructor.
		 * \param radius The radius of the sphere.
		 * \param latitude Number of vertical sections.
		 * \param longitude Number of horizontal sections.
		 */
		explicit SphereGeometry(float radius = 1.0f, 
								int latitude = 20, 
								int longitude = 20);
		~SphereGeometry();

		/**
		 * \brief Re-initialize the sphere with different parameters.
		 * \param radius The radius of the sphere.
		 * \param latitude Number of vertical sections.
		 * \param longitude Number of horizontal sections.
		 */
		void resize(float radius,
					int latitude = 20, 
					int longitude = 20);

		float getRadius() const;
		int getLatitude() const;
		int getLongitude() const;

	private:
		/**
		 * \brief Initialize the geometry data.
		 * \param radius The radius of the sphere.
		 * \param latitude Number of vertical sections.
		 * \param longitude Number of horizontal sections.
		 */
		void init(float radius,
				  int latitude,
				  int longitude);

		/**
		 * \brief Initialize vertex data and texture coordinates.
		 */
		void initVerticesAndTexCoords();
		/**
		 * \brief Initialize index data.
		 */
		void initIndices();

		float m_radius;
		int m_latitude;
		int m_longitude;
	};
}