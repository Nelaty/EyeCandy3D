#include "EC3D/Graphics/Geometry/GeometryData.h"

namespace ec
{
	GeometryData::GeometryData()
		: m_initialized{false}
	{
	}

	GeometryData::~GeometryData()
	{
		releaseMemory();
	}

	void GeometryData::bind()
	{
		glBindVertexArray(m_vao);
	}

	void GeometryData::unbind()
	{
		glBindVertexArray(0);
	}

	void GeometryData::resizeBuffers(const unsigned vertexCount, const unsigned indexCount)
	{
		m_vertices.resize(vertexCount);
		m_indices.resize(indexCount);
	}

	bool GeometryData::initBufferObjects(const GLenum usage)
	{
		if(buffersInitialized())
		{
			return false;
		}
		m_usage = usage;

		glGenVertexArrays(1, &m_vao);
		glGenBuffers(1, &m_vbo);
		glGenBuffers(1, &m_ebo);
		
		glBindVertexArray(m_vao);

		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], usage);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], usage);


		// positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);
		// normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, m_normal)));
		// texture coordinates
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, m_texCoords)));

		glBindVertexArray(0);

		m_initialized = true;
		return true;
	}

	void GeometryData::updateVertexData()
	{
		assert(m_initialized);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], m_usage);
		glBindVertexArray(0);
	}

	void GeometryData::updateIndexData()
	{
		assert(m_initialized);

		glBindVertexArray(m_vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(unsigned int), &m_indices[0], m_usage);
		glBindVertexArray(0);
	}

	void GeometryData::update()
	{
		updateVertexData();
		updateIndexData();
	}

	GLenum GeometryData::getUsage() const
	{
		return m_usage;
	}

	GLuint GeometryData::getVao() const
	{
		return m_vao;
	}

	GLuint GeometryData::getVbo() const
	{
		return m_vbo;
	}

	GLuint GeometryData::getEbo() const
	{
		return m_ebo;
	}

	bool GeometryData::buffersInitialized() const
	{
		return m_initialized;
	}

	bool GeometryData::releaseMemory()
	{
		if(!m_initialized)
		{
			return false;
		}

		glDeleteBuffers(1, &m_vbo);
		glDeleteBuffers(1, &m_ebo);
		glDeleteVertexArrays(1, &m_vao);

		m_initialized = false;
		return true;
	}
}