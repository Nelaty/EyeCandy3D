#pragma once
#include "EC3D/Core/StaticGeometry.h"

namespace ec
{
	struct Vertex;

	class LineStripGeometry : public StaticGeometry
	{
	public:
		explicit LineStripGeometry();
		~LineStripGeometry();

		/** Needs to be called after all vertices have been added. */
		void init();
		/** 
		 * Clear the temporary point list.
		 * This does not affect the existing geometry until init is called!
		 */
		void reset();

		/**
		 * Add a new point to this line strip. The first two points
		 * define the first section. Each other point builds another line
		 * with its predecessor.
		 */
		void addVertex(const glm::vec3& vertex);
		/**
		 * Set the current point data. 
		 * Removes existing points.
		 */
		void setData(glm::vec3* vertices, int count);

		void recalculateNormals() override;

	private:
		std::vector<glm::vec3> m_tempPoints;
	};
}
