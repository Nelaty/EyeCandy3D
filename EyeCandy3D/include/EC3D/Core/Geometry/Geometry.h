#pragma once
#include "IGeometryAccess.h"
#include "GeometryData.h"

#include "EC3D/Common/Common.h"

namespace ec
{
	/**
	 * \brief Geometry 
	 */
	class EC3D_DECLSPEC Geometry : public IGeometryAccess
	{
	public:
		virtual ~Geometry();

		/** 
		 * \brief Recalculate vertex normals. 
		 */
		virtual void recalculateNormals();

		/** \brief Get the vertex array object id. */
		GLuint getVao() const;
		/** \brief Get the vertex buffer object id. */
		GLuint getVbo() const;
		/** \brief Get the element buffer object id. */
		GLuint getEbo() const;

		/** \brief Get the raw geometry data. */
		const GeometryData& getData() const;

	protected:
		/**
		 * \brief Geometry constructor.
		 * \param mode The kind of primitive to render.
		 * \param type The data size used for geometry data.
		 */
		explicit Geometry(GLenum mode = GL_TRIANGLES, GLenum type = GL_UNSIGNED_INT);

		/**
		* \brief Called at the beginning of the rendering routine.
		*/
		void beginRender() override;
		/**
		* \brief The actual drawing of the object.
		*/
		void onRender() override;
		/**
		* \brief Called at the end of the rendering routine.
		*/
		void endRender() override;

		GeometryData m_data;

		/**
		 * \brief Set type of primitive to render
		 */
		void setMode(GLenum mode);
		/**
		 * \brief Set the data size used for geometry data.
		 */
		void setType(GLenum type);

	private:
		GLenum m_mode;
		GLenum m_type;
	};
}