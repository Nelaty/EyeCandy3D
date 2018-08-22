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
		virtual void recalculateNormals();

		/* Geometry buffer access */
		GLuint getVao() const;
		GLuint getVbo() const;
		GLuint getEbo() const;

	protected:
		void beginRender() override;
		void onRender() override;
		void endRender() override;

		/* Buffers */
		GLuint m_VAO{};
		GLuint m_VBO{};
		GLuint m_EBO{};

		/* Initialize the geometry */
		virtual void setupMesh();

		/* Vertex and index data */
		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;

		explicit StaticGeometry();
	};
}