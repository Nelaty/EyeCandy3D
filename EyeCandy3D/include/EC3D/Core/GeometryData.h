#pragma once
#include <GL/glew.h>
#include "EC3D/Common/Common.h"

#include "EC3D/Core/Vertex.h"

#include <vector>

namespace ec
{
	class EC3D_DECLSPEC GeometryData
	{
	public:
		GeometryData();
		~GeometryData();

		void bind();
		void unbind();

		/** Resize vertex and index containers. */
		void resizeBuffers(unsigned int vertexCount, unsigned int indexCount);

		/**
		 * Initializes VAO, VBO and EBO. 
		 * Passes vertex and index data to the GPU. 
		 * \return False if buffers are already initialized, true otherwise.
		 */
		bool initBufferObjects(GLenum usage = GL_DYNAMIC_COPY);

		/** 
		 * Check if buffer objects are initialized.
		 * \return True if they are initialized, false otherwise.
		 */
		bool buffersInitialized() const;

		/**
		 * Clears containers and releases memory on the GPU. After 
		 * calling this function, this data object won't be initialized
		 * any more.
		 * \return True if buffers are initialized, false otherwise.
		 */
		bool releaseMemory();

		/**
		 * Should be called if vertex data has changed. Updates vertices 
		 * on the GPU.
		 */
		void updateVertexData();

		/**
		* Should be called if index data has changed. Updates indices
		* on the GPU.
		*/
		void updateIndexData();

		/**
		* Should be called if vertex and index data changed. Updates
		* vertices and indices on the GPU.
		*/
		void update();

		/** Get usage */
		GLenum getUsage() const;
		/** Get the vao buffer id. */
		GLuint getVao() const;
		/** Get the vbo buffer id. */
		GLuint getVbo() const;
		/** Get the ebo buffer id. */
		GLuint getEbo() const;

		std::vector<Vertex> m_vertices;
		std::vector<unsigned int> m_indices;

	private:
		bool m_initialized;

		GLenum m_usage;

		GLuint m_vao;
		GLuint m_vbo;
		GLuint m_ebo;
	};
}