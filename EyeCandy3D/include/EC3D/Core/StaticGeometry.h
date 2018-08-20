#pragma once
#include "EC3D/Core/Geometry.h"
#include "EC3D/Core/Vertex.h"

#include <gl/glew.h>

#include <vector>

namespace ec
{
	class StaticGeometry : public Geometry
	{
	public:
		virtual ~StaticGeometry();

		/* Recalculate vertex normals */
		virtual void RecalculateNormals();

		/* Geometry buffer access */
		GLuint GetVAO() const;
		GLuint GetVBO() const;
		GLuint GetEBO() const;

	protected:
		virtual void BeginRender() override;
		virtual void OnRender() override;
		virtual void EndRender() override;

		/* Buffers */
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_EBO;

		/* Initialize the geometry */
		virtual void SetupMesh();

		/* Vertex and index data */
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;

		explicit StaticGeometry();
	};
}