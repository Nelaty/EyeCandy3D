#pragma once
#include "ec3/graphics/geometry/static-geometry.h"

namespace ec
{
	struct Vertex;

	/**
	 * \brief Describes the geometry of a line strip.
	 */
	class LineStripGeometry : public StaticGeometry
	{
	public:
		explicit LineStripGeometry();
		~LineStripGeometry();

		/** 
		 * \brief Needs to be called after all vertices have been added.
		 */
		void init();
		/** 
		 * \brief Clear the temporary point list.
		 * \details This does not affect the existing geometry until 
		 * init is called!
		 */
		void reset();

		/**
		 * \brief Add a new point to this line strip.
		 * \details The first two points
		 * define the first section. Each other point builds another line
		 * with its predecessor.
		 */
		void addVertex(const glm::vec3& vertex);
		/**
		 * \brief Set the current point data. Removes existing points.
		 */
		void setData(glm::vec3* vertices, int count);

		void recalculateNormals() override;

	private:
		std::vector<glm::vec3> m_tempPoints;
	};
}
