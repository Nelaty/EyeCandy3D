#pragma once
#include "EC3D/Core/StaticGeometry.h"

#include <glm/glm.hpp>

namespace ec
{
	class LineGeometry : public StaticGeometry
	{
	public:
		explicit LineGeometry(const glm::vec3& start,
							  const glm::vec3& end);
		~LineGeometry();

		const glm::vec3& getStart() const;
		const glm::vec3& getEnd() const;

		void recalculateNormals() override;

	private:
		void init(const glm::vec3& start, const glm::vec3& end);

		glm::vec3 m_start;
		glm::vec3 m_end;
	};
}
