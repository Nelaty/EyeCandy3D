#pragma once
#include "Vertex.h"
#include "Texture.h"

#include <glm/glm.hpp>

#include <vector>
#include <gl/glew.h>

/*
* Base class for all kinds of geometry.
*/
namespace ec
{
	class Shader;

	class Geometry
	{
	public:
		virtual ~Geometry();

		/* Render this geometry with a given matrix */
		virtual void Render(Shader* shader, const glm::mat4& model);

		/* Recalculate vertex normals */
		virtual void RecalculateNormals();

		/* Geometry buffer access */
		GLuint GetVAO() const;
		GLuint GetVBO() const;
		GLuint GetEBO() const;

	protected:
		/* Initialize the geometry */
		virtual void SetupMesh();

		/* Buffers */
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_EBO;

		/* Vertex and index data */
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;

		explicit Geometry();
	};
}