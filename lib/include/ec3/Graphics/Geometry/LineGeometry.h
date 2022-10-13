#pragma once
#include "StaticGeometry.h"

#include <glm/glm.hpp>

namespace ec
{
	/**
	 * \brief Describes the geometry of a single line.
	 */
	class LineGeometry : public StaticGeometry
	{
	public:
		/**
		 * \brief LineGeometry constructor.
		 * \param start The start point of the line.
		 * \param end The end point of the line.
		 */
		explicit LineGeometry(const glm::vec3& start,
							  const glm::vec3& end);
		~LineGeometry();

		/**
		 * \brief Get the start point of the line.
		 */
		const glm::vec3& getStart() const;
		/**
		 * \brief Get the end point of the line.
		 */
		const glm::vec3& getEnd() const;

		/**
		 * \brief Recalculate the vertex normals of the line.
		 */
		void recalculateNormals() override;

	private:
		/**
		 * \brief Initialize geometry data.
		 * \param start The start point of the line.
		 * \param end The end point of the line.
		 */
		void init(const glm::vec3& start, const glm::vec3& end);

		glm::vec3 m_start;
		glm::vec3 m_end;
	};
}
