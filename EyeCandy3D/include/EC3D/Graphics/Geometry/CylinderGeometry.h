#pragma once
#include "StaticGeometry.h"

namespace ec
{
	/**
	 * \brief Kind of static geometry that represents a cylinder.
	 */
	class CylinderGeometry : public StaticGeometry
	{
	public:
		/**
		 * \brief CylinderGeometry constructor.
		 * \param radius Top and bottom circle radii.
		 * \param height The height of the cylinder.
		 * \param latitude Number of rows.
		 * \param longitude Number of columns.
		 */
		explicit CylinderGeometry(float radius = 0.5f,
								  float height = 1.0f,
								  int latitude = 2,
								  int longitude = 20);
		~CylinderGeometry();

		/**
		 * \brief Change the dimensions of the cylinder.
		 * \param radius Top and bottom circle radii.
		 * \param height The height of the cylinder.
		 * \param latitude Number of rows.
		 * \param longitude Number of columns.
		 */
		void resize(float radius,
					float height,
					int latitude,
					int longitude);

		/**
		 * \brief Get the radius of top/bottom shape
		 * \return The radius
		 */
		float getRadius() const;

		/**
		 * \brief Get the vertical dimension.
		 * \return The height.
		 */
        float getHeight() const;

        /**
         * \brief Get the number of circles around the y-axis.
         * \return The latitude.
         */
        int getLatitude() const;

        /**
         * \brief Get resolution of top/bottom circle
         * (number of vertices per circle).
         * \return The longitude.
         */
        int getLongitude() const;

	private:
		/**
		 * \brief Initialize the cylinder geometry data.
		 * \param radius Top and bottom circle radii.
		 * \param height The height of the cylinder.
		 * \param latitude Number of rows.
		 * \param longitude Number of columns.
		 */
		void init(float radius = 0.5f,
				  float height = 1.0f,
				  int latitude = 15,
				  int longitude = 15);

		/**
		 * \brief Initialize vertices and texture coordinates.
		 */
		void initVerticesAndTexCoords();
		/**
		 * \brief Initialize indices.
		 */
		void initIndices();

		float m_radius;
		float m_height;
		int m_latitude;
		int m_longitude;
	};
}