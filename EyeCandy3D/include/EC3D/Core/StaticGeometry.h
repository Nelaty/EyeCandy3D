#pragma once
#include <GL/glew.h>
#include "EC3D/Common/Common.h"

#include "EC3D/Core/Geometry.h"


namespace ec
{
	/**
	 * \brief Geometry that does not change itself over time.
	 */
	class EC3D_DECLSPEC StaticGeometry : public Geometry
	{
	public:
		virtual ~StaticGeometry();

	protected:
		/**
		 * \brief Initialize geometry buffers.
		 */
		virtual void setupMesh();

		explicit StaticGeometry();
	};
}