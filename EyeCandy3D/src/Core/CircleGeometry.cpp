#include "EC3D/Core/CircleGeometry.h"

#include <corecrt_math_defines.h>

namespace ec
{
	CircleGeometry::CircleGeometry(const float radius, const int sectionCount)
	{
		init(radius, sectionCount);
		StaticGeometry::setupMesh();
	}

	CircleGeometry::~CircleGeometry()
	= default;

	float CircleGeometry::getRadius() const
	{
		return m_radius;
	}

	int CircleGeometry::getSectionCount() const
	{
		return m_sectionCount;
	}

	void CircleGeometry::init(const float radius, const int sectionCount)
	{
		assert(sectionCount > 2);
		assert(radius > 0.0f);

		m_radius = radius;
		m_sectionCount = sectionCount;

		m_data.resizeBuffers(sectionCount + 1, sectionCount * 3);

		auto& vertices = m_data.m_vertices;
		auto& indices = m_data.m_indices;

		const glm::vec3 normal(0.0f, 0.0f, 1.0f);

		// Init vertices
		vertices[0].m_position = glm::vec3(0.0f, 0.0f, 0.0f);
		vertices[0].m_normal = normal;
		vertices[0].m_texCoords = glm::vec2(0.5f, 0.5f);

		const float circleStep = 2 * M_PI / sectionCount;
		const float oneOnverRadius = 0.5f * (1.0f / radius);
		for(int i = 1; i <= sectionCount; ++i)
		{
			const auto angle = i * circleStep;

			glm::vec2 position(cos(angle) * radius,
							   sin(angle) * radius);

			vertices[i].m_position.x = cos(angle) * radius;
			vertices[i].m_position.y = sin(angle) * radius;

			vertices[i].m_normal = normal;
			vertices[i].m_texCoords = oneOnverRadius * position + 0.5f;
		}

		// Init indices
		int index = 1;
		for(int i = 0; i < sectionCount; ++i)
		{
			int pos = i * 3;
			indices[pos] = 0;
			indices[pos + 1] = index;
			index = index + 1 > sectionCount ? 1 : index + 1;
			indices[pos + 2] = index;
		}		
	}
}
