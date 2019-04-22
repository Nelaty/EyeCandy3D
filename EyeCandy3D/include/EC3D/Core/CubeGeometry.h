#pragma once
#include "EC3D/Core/StaticGeometry.h"
#include "EC3D/Common/Common.h"

#include <glm/glm.hpp>

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
		explicit CubeGeometry(float sxHalf, float syHalf, float szHalf);
		~CubeGeometry();

		/**
		 * \brief Resize the side length of the cube.
		 * \param width The width of the cube.
		 * \param height The height of the cube.
		 * \param depth The depth of the cube.
		 */
		void resize(float sxHalf, float syHalf, float szHalf);

		/** \brief Get the cube dimensions as half sizes. */
		const glm::vec3& getHalfSizes() const;

		/** \brief Get the full width. */
		float getWidth() const;
		/** \brief Get the half width. */
		float getHalfWidth() const;

		/** \brief Get the full height. */
		float getHeight() const;
		/** \brief Get the half height. */
		float getHalfHeight() const;

		/** \brief Get the full depth. */
		float getDepth() const;
		/** \brief Get the half depth. */
		float getHalfDepth() const;

	private:
		/**
		 * \brief Initialize the geometry data.
		 * \param width The width of the cube.
		 * \param height The height of the cube.
		 * \param depth The depth of the cube.
		 */
		void init(float sxHalf, float syHalf, float szHalf);

		glm::vec3 m_halfSizes;
	};
}