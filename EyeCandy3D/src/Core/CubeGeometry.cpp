#include "EC3D/Core/CubeGeometry.h"
#include "EC3D/Core/Vertex.h"

#include <vector>

namespace ec
{
	CubeGeometry::CubeGeometry(const float uniformSize)
	{
		init(uniformSize, uniformSize, uniformSize);
	}

	CubeGeometry::CubeGeometry(float sxHalf, float syHalf, float szHalf)
	{
		init(sxHalf, syHalf, szHalf);
	}

	CubeGeometry::~CubeGeometry()
	= default;

	void CubeGeometry::resize(float sxHalf, float syHalf, float szHalf)
	{
		init(sxHalf, syHalf, szHalf);
	}

	const glm::vec3& CubeGeometry::getHalfSizes() const
	{
		return m_halfSizes;
	}

	float CubeGeometry::getWidth() const
	{
		return 2 * m_halfSizes.x;
	}

	float CubeGeometry::getHalfWidth() const
	{
		return m_halfSizes.x;
	}

	float CubeGeometry::getHeight() const
	{
		return 2 * m_halfSizes.y;
	}

	float CubeGeometry::getHalfHeight() const
	{
		return m_halfSizes.y;
	}

	float CubeGeometry::getDepth() const
	{
		return 2 * m_halfSizes.z;
	}

	float CubeGeometry::getHalfDepth() const
	{
		return m_halfSizes.z;
	}

	void CubeGeometry::init(float sxHalf, float syHalf, float szHalf)
	{
		m_data.resizeBuffers(8, 36);

		auto& vertices = m_data.m_vertices;
		auto& indices = m_data.m_indices;

		m_halfSizes = glm::vec3(sxHalf, syHalf, szHalf);

		// Vertex positions
		vertices[0].m_position = glm::vec3(-m_halfSizes.x, -m_halfSizes.y, m_halfSizes.z);
		vertices[1].m_position = glm::vec3(m_halfSizes.x, -m_halfSizes.y, m_halfSizes.z);
		vertices[2].m_position = glm::vec3(m_halfSizes.x, m_halfSizes.y, m_halfSizes.z);
		vertices[3].m_position = glm::vec3(-m_halfSizes.x, m_halfSizes.y, m_halfSizes.z);

		vertices[4].m_position = glm::vec3(-m_halfSizes.x, -m_halfSizes.y, -m_halfSizes.z);
		vertices[5].m_position = glm::vec3(m_halfSizes.x, -m_halfSizes.y, -m_halfSizes.z);
		vertices[6].m_position = glm::vec3(m_halfSizes.x, m_halfSizes.y, -m_halfSizes.z);
		vertices[7].m_position = glm::vec3(-m_halfSizes.x, m_halfSizes.y, -m_halfSizes.z);

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