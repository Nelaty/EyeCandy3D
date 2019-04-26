#include "EC3D/Core/Geometry/RectangleGeometry.h"
#include "EC3D/Core/Shader/Shader.h"

namespace ec
{
	RectangleGeometry::RectangleGeometry(const float uniform)
	{
		init(uniform, uniform);
		StaticGeometry::setupMesh();
	}

	RectangleGeometry::RectangleGeometry(const float width, const float height)
	{
		init(width, height);
	}

	RectangleGeometry::~RectangleGeometry()
	= default;

	void RectangleGeometry::init(const float width, const float height)
	{
		m_width = width;
		m_height = height;

		m_data.resizeBuffers(4, 6);

		const auto halfWidth = 0.5f * width;
		const auto halfHeight = 0.5f * height;

		auto& vertices = m_data.m_vertices;
		auto& indices = m_data.m_indices;

		// Initialize vertices
		vertices[0].m_position = glm::vec3(-halfWidth, -halfHeight, 0.0f);
		vertices[0].m_normal = glm::vec3(0.0f, 0.0f, 1.0f);
		vertices[0].m_texCoords = glm::vec2(0.0f, 1.0f);

		vertices[1].m_position = glm::vec3(halfWidth, -halfHeight, 0.0f);
		vertices[1].m_normal = glm::vec3(0.0f, 0.0f, 1.0f);
		vertices[1].m_texCoords = glm::vec2(1.0f, 1.0f);

		vertices[2].m_position = glm::vec3(halfWidth, halfHeight, 0.0f);
		vertices[2].m_normal = glm::vec3(0.0f, 0.0f, 1.0f);
		vertices[2].m_texCoords = glm::vec2(1.0f, 0.0f);

		vertices[3].m_position = glm::vec3(-halfWidth, halfHeight, 0.0f);
		vertices[3].m_normal = glm::vec3(0.0f, 0.0f, 1.0f);
		vertices[3].m_texCoords = glm::vec2(0.0f, 0.0f);

		// Initialize index list
		indices.push_back(0);
		indices.push_back(1);
		indices.push_back(2);

		indices.push_back(2);
		indices.push_back(3);
		indices.push_back(0);
	}

	float RectangleGeometry::getWidth() const
	{
		return m_width;
	}

	float RectangleGeometry::getHeight() const
	{
		return m_height;
	}
}
