#include "ec3/graphics/geometry/cube-geometry.h"
#include "ec3/graphics/geometry/vertex.h"

#include <vector>
#include <stdexcept>

namespace ec
{
	CubeGeometry::CubeGeometry(const float uniformSize)
	{
		init(uniformSize, uniformSize, uniformSize);
	}

	CubeGeometry::CubeGeometry(const float width, const float height, const float depth)
	{
		init(width, height, depth);
	}

	CubeGeometry::~CubeGeometry()
	= default;

	void CubeGeometry::resize(const float width, const float height, const float depth)
	{
		init(width, height, depth);
	}

	float CubeGeometry::getWidth() const
	{
		return m_width;
	}

	float CubeGeometry::getHeight() const
	{
		return m_height;
	}

	float CubeGeometry::getDepth() const
	{
		return m_depth;
	}

	void CubeGeometry::init(const float width, const float height, const float depth)
	{
	    if(width <= 0.0f) throw std::domain_error("width must be > 0!");
	    if(height <= 0.0f) throw std::domain_error("height must be > 0!");
	    if(depth <= 0.0f) throw std::domain_error("depth must be > 0!");

		m_width = width;
		m_height = height;
		m_depth = depth;

		m_data.resizeBuffers(8, 36);

		auto& vertices = m_data.m_vertices;
		auto& indices = m_data.m_indices;

		const glm::vec3 halfSizes(0.5f * width, 0.5f * height, 0.5f * depth);

		// Vertex positions
		vertices[0].m_position = glm::vec3(-halfSizes.x, -halfSizes.y, halfSizes.z);
		vertices[1].m_position = glm::vec3(halfSizes.x, -halfSizes.y, halfSizes.z);
		vertices[2].m_position = glm::vec3(halfSizes.x, halfSizes.y, halfSizes.z);
		vertices[3].m_position = glm::vec3(-halfSizes.x, halfSizes.y, halfSizes.z);

		vertices[4].m_position = glm::vec3(-halfSizes.x, -halfSizes.y, -halfSizes.z);
		vertices[5].m_position = glm::vec3(halfSizes.x, -halfSizes.y, -halfSizes.z);
		vertices[6].m_position = glm::vec3(halfSizes.x, halfSizes.y, -halfSizes.z);
		vertices[7].m_position = glm::vec3(-halfSizes.x, halfSizes.y, -halfSizes.z);

		// Vertex texture coordinates
		vertices[0].m_texCoords = glm::vec2(0.0f, 0.0f);
		vertices[1].m_texCoords = glm::vec2(1.0f, 0.0f);
		vertices[2].m_texCoords = glm::vec2(1.0f, 1.0f);
		vertices[3].m_texCoords = glm::vec2(0.0f, 1.0f);

		vertices[4].m_texCoords = glm::vec2(1.0f, 1.0f);
		vertices[5].m_texCoords = glm::vec2(0.0f, 1.0f);
		vertices[6].m_texCoords = glm::vec2(0.0f, 0.0f);
		vertices[7].m_texCoords = glm::vec2(1.0f, 0.0f);

		// Front
		indices[0] = 0;
		indices[1] = 1;
		indices[2] = 2;
		indices[3] = 0;
		indices[4] = 2;
		indices[5] = 3;

		// Left
		indices[6] = 4;
		indices[7] = 0;
		indices[8] = 3;
		indices[9] = 4;
		indices[10] = 3;
		indices[11] = 7;


		// Right
		indices[12] = 1;
		indices[13] = 5;
		indices[14] = 6;
		indices[15] = 1;
		indices[16] = 6;
		indices[17] = 2;

		// Top
		indices[18] = 3;
		indices[19] = 2;
		indices[20] = 6;
		indices[21] = 3;
		indices[22] = 6;
		indices[23] = 7;

		// Bottom
		indices[24] = 4;
		indices[25] = 5;
		indices[26] = 1;
		indices[27] = 4;
		indices[28] = 1;
		indices[29] = 0;

		// Back
		indices[30] = 5;
		indices[31] = 4;
		indices[32] = 7;
		indices[33] = 5;
		indices[34] = 7;
		indices[35] = 6;

		recalculateNormals();
		setupMesh();
	}
}