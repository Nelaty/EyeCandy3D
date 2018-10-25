#pragma once
#include "EC3D/Core/StaticGeometry.h"
#include "EC3D/Common/Common.h"


namespace ec
{
	/**
	 * \brief Concrete static geometry that represents a cube.
	 */
	class EC3D_DECLSPEC CubeGeometry : public StaticGeometry
	{
	public:
		/**
		 * \brief CubeGeometry constructor.
		 * \param uniformSize Side length used for all sides.
		 */
		explicit CubeGeometry(float uniformSize = 1.0f);
		/**
		 * \brief CubeGeometry constructor.
		 * \param width The width of the cube.
		 * \param height The height of the cube.
		 * \param depth The depth of the cube.
		 */
		explicit CubeGeometry(float width, float height, float depth);
		~CubeGeometry();

		/**
		 * \brief Resize the side length of the cube.
		 * \param width The width of the cube.
		 * \param height The height of the cube.
		 * \param depth The depth of the cube.
		 */
		void resize(float width, float height, float depth);

		/**
		 * \brief Get the current width.
		 */
		float getWidth() const;
		/**
		 * \brief Get the current height.
		 */
		float getHeight() const;
		/**
		 * \brief Get the current depth.
		 */
		float getDepth() const;

	private:
		/**
		 * \brief Initialize the geometry data.
		 * \param width The width of the cube.
		 * \param height The height of the cube.
		 * \param depth The depth of the cube.
		 */
		void init(float width, float height, float depth);

		float m_width;
		float m_height;
		float m_depth;
	};
}