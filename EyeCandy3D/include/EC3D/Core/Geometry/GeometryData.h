#pragma once
#include <GL/glew.h>
#include "EC3D/Common/Common.h"

#include "Vertex.h"

#include <vector>

namespace ec
{
	/**
	 * \brief Encapsulates vertex and index data and knows how to
	 * create, update and delete OpenGL buffers.
	 */
	class EC3D_DECLSPEC GeometryData
	{
	public:
		GeometryData();
		~GeometryData();

		/**
		 * \brief Notify OpenGL to use this geometry data.
		 */
		void bind();
		/**
		 * \brief Notify OpenGL to stop using any geometry data.
		 */
		void unbind();

		/** 
		 * \brief Resize vertex and index containers.
		 * \param vertexCount The size of the vertex buffer.
		 * \param indexCount The size of the index buffer.
		 */
		void resizeBuffers(unsigned int vertexCount, unsigned int indexCount);

		/**
		 * \brief Initializes VAO, VBO and EBO. 
		 * Passes vertex and index data to the GPU. 
		 * \return False if buffers are already initialized, true otherwise.
		 */
		bool initBufferObjects(GLenum usage = GL_STATIC_DRAW);

		/** 
		 * \brief Check if buffer objects are initialized.
		 * \return True if they are initialized, false otherwise.
		 */
		bool buffersInitialized() const;

		/**
		 * \brief Clears containers and releases memory on the GPU. After 
		 * calling this function, this data object won't be initialized
		 * any more.
		 * \return True if buffers are initialized, false otherwise.
		 */
		bool releaseMemory();

		/**
		 * \brief Should be called if vertex data has changed. Updates vertices 
		 * on the GPU.
		 */
		void updateVertexData();

		/**
		* \brief Should be called if index data has changed. Updates indices
		* on the GPU.
		*/
		void updateIndexData();

		/**
		* \brief Should be called if vertex and index data changed. Updates
		* vertices and indices on the GPU.
		*/
		void update();

		/**
		 * \brief Get usage 
		 */
		GLenum getUsage() const;
		/**
		 * \brief Get the vao buffer id. 
		 */
		GLuint getVao() const;
		/** 
		 * \brief Get the vbo buffer id.
		 */
		GLuint getVbo() const;
		/** 
		 * \brief Get the ebo buffer id. 
		 */
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
