#include "ec3/graphics/geometry/rectangle-geometry.h"
#include "ec3/graphics/shader/shader.h"

#include <stdexcept>

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
	    if(width <= 0.0) throw std::domain_error("width must be > 0!");
	    if(height <= 0.0) throw std::domain_error("height must be > 0!");

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
