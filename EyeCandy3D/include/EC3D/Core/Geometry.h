#pragma once
#include "EC3D/Core/IGeometryAccess.h"
#include "EC3D/Common/Common.h"
#include "EC3D/Core/GeometryData.h"

namespace ec
{
	class EC3D_DECLSPEC Geometry : public IGeometryAccess
	{
	public:
		virtual ~Geometry();

		/** 
		 * \brief Recalculate vertex normals. 
		 */
		virtual void recalculateNormals();

		/** Get the vertex array object id. */
		GLuint getVao() const;
		/** Get the vertex buffer object id. */
		GLuint getVbo() const;
		/** Get the element buffer object id. */
		GLuint getEbo() const;

	protected:
		explicit Geometry(GLenum mode = GL_TRIANGLES, GLenum type = GL_UNSIGNED_INT);

		void beginRender() override;
		void onRender() override;
		void endRender() override;

		GeometryData m_data;

		void setMode(GLenum mode);
		void setType(GLenum type);

	private:
		GLenum m_mode;
		GLenum m_type;
	};
}