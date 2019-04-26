#include "EC3D/Core/Geometry/Geometry.h"

#include <glm/glm.hpp>

namespace ec
{
	Geometry::~Geometry()
	= default;

	void Geometry::recalculateNormals()
	{
		auto& vertices = m_data.m_vertices;
		auto& indices = m_data.m_indices;

		for(auto& it : vertices)
		{
			it.m_normal = glm::vec3(0.0f);
		}

		for(size_t i = 0; i < indices.size();)
		{
			const auto edge1 = vertices[indices[i]].m_position - vertices[indices[i + 1]].m_position;
			const auto edge2 = vertices[indices[i]].m_position - vertices[indices[i + 2]].m_position;

			const auto faceNormal = glm::normalize(glm::cross(edge2, edge1));
			vertices[indices[i]].m_normal += faceNormal;
			vertices[indices[i + 1]].m_normal += faceNormal;
			vertices[indices[i + 2]].m_normal += faceNormal;

			i += 3;
		}
		for(auto& it : vertices)
		{
			it.m_normal = glm::normalize(it.m_normal);
		}
	}

	GLuint Geometry::getVao() const
	{
		return m_data.getVao();
	}

	GLuint Geometry::getVbo() const
	{
		return m_data.getVbo();
	}

	GLuint Geometry::getEbo() const
	{
		return m_data.getEbo();
	}

	const ec::GeometryData& Geometry::getData() const
	{
		return m_data;
	}

	void Geometry::beginRender()
	{
		m_data.bind();
	}

	void Geometry::onRender()
	{
		glDrawElements(m_mode, m_data.m_indices.size(), m_type, nullptr);
	}

	void Geometry::endRender()
	{
		m_data.unbind();
	}

	void Geometry::setMode(const GLenum mode)
	{
		m_mode = mode;
	}

	void Geometry::setType(const GLenum type)
	{
		m_type = type;
	}

	Geometry::Geometry(const GLenum mode, const GLenum type)
		: m_mode{mode},
		m_type{type}
	{		
	}
}