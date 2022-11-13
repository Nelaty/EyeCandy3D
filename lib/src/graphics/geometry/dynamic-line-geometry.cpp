#include "ec3/graphics/geometry/dynamic-line-geometry.h"
#include "ec3/node.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace ec
{
	DynamicLineGeometry::DynamicLineGeometry(Node* start, Node* end, const float lineWidth)
		: m_start{start},
		  m_end{end},
		  m_lineWidth{lineWidth}
	{
		init();
	}

	DynamicLineGeometry::~DynamicLineGeometry()
	= default;

	void DynamicLineGeometry::setStart(Node* start)
	{
		m_start = start;
	}

	ec::Node* DynamicLineGeometry::getStart() const
	{
		return m_start;
	}

	void DynamicLineGeometry::setEnd(Node* end)
	{
		m_end = end;
	}

	ec::Node* DynamicLineGeometry::getEnd() const
	{
		return m_end;
	}

	void DynamicLineGeometry::setLineWidth(float lineWidth)
	{
		m_lineWidth = lineWidth;
	}

	float DynamicLineGeometry::getLineWidth() const
	{
		return m_lineWidth;
	}

	void DynamicLineGeometry::onRender()
	{
		if (!initVertices())
		{
			return;
		}
		recalculateNormals();
		m_data.updateVertexData();

		m_data.bind();
		DynamicGeometry::onRender();

		/*glLineWidth(m_lineWidth);
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
		glVertex3f(startPos.x, startPos.y, startPos.z);
		glVertex3f(endPos.x, endPos.y, endPos.z);
		glEnd();
		glLineWidth(1.0f);*/
	}

	void DynamicLineGeometry::init()
	{
		m_data.resizeBuffers(8, 36);

		initVertices();
		initTexCoords();
		initIndices();

		recalculateNormals();
		m_data.initBufferObjects();
	}

	bool DynamicLineGeometry::initVertices()
	{
		if(!m_start || !m_end) return false;

		auto startPos = m_start->getGlobalPosition();
		auto endPos = m_end->getGlobalPosition();

		if(startPos == endPos) return false;

		const glm::vec3 distanceVec = endPos - startPos;

		/// \todo fix initialization 
		glm::vec3 tempY = glm::normalize(distanceVec);

		glm::vec3 tempX(1.0f, 0.0f, 0.0f);
		glm::vec3 tempZ;
		if(glm::dot(tempX, tempY) == 0.0f)
		{
			tempX = glm::vec3(0.0f, 0.0f, 1.0f);
		}
		tempZ = glm::normalize(glm::cross(tempY, tempX));
		tempX = glm::cross(tempY, tempZ);



		glm::vec3 halfSizes = glm::vec3{0.5f * m_lineWidth, 0.5f * glm::length(distanceVec), 0.5f * m_lineWidth};
		//const glm::vec3 mid = startPos + 0.5f * normal;

		auto& vertices = m_data.m_vertices;

		glm::vec3 positions[3];
		positions[0] = halfSizes.x * tempX;
		positions[1] = halfSizes.y * tempY;
		positions[2] = halfSizes.z * tempZ;

		glm::vec3 offset = -0.5f *  distanceVec;

		//offset = glm::vec3(0.0f);

		vertices[0].m_position = offset + (-positions[0] - positions[1] + positions[2]);
		vertices[1].m_position = offset + (positions[0] - positions[1] + positions[2]);
		vertices[2].m_position = offset + (positions[0] + positions[1] + positions[2]);
		vertices[3].m_position = offset + (-positions[0] + positions[1] + positions[2]);
		vertices[4].m_position = offset + (-positions[0] - positions[1] - positions[2]);
		vertices[5].m_position = offset + (positions[0] - positions[1] - positions[2]);
		vertices[6].m_position = offset + (positions[0] + positions[1] - positions[2]);
		vertices[7].m_position = offset + (-positions[0] + positions[1] - positions[2]);

		// x coordinates are flipped ???
		// introduces new problem: indices now wrong
		for(int i = 0; i < 8; ++i)
		{
			vertices[i].m_position.x *= -1.0f;
		}

		return true;
	}

	void DynamicLineGeometry::initTexCoords()
	{
		auto& vertices = m_data.m_vertices;

		vertices[0].m_texCoords = glm::vec2(0.0f, 0.0f);
		vertices[1].m_texCoords = glm::vec2(1.0f, 0.0f);
		vertices[2].m_texCoords = glm::vec2(1.0f, 1.0f);
		vertices[3].m_texCoords = glm::vec2(0.0f, 1.0f);

		vertices[4].m_texCoords = glm::vec2(1.0f, 1.0f);
		vertices[5].m_texCoords = glm::vec2(0.0f, 1.0f);
		vertices[6].m_texCoords = glm::vec2(0.0f, 0.0f);
		vertices[7].m_texCoords = glm::vec2(1.0f, 0.0f);
	}

	void DynamicLineGeometry::initIndices()
	{
		auto& indices = m_data.m_indices;

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
	}
}
