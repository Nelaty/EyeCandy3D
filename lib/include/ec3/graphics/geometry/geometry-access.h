#pragma once
#include "ec3/common/common.h"

#include <glm/glm.hpp>

namespace ec
{
	class Shader;

	/**
	* \brief Base class for all kinds of geometry.
	*/
	class EC3D_DECLSPEC IGeometryAccess
	{
	public:
		virtual ~IGeometryAccess();

		/**
		 * \brief Render this geometry.
		 */
		virtual void render();

	protected:
		/** 
		 * \brief Called at the beginning of the rendering routine. 
		 */
		virtual void beginRender() = 0;
		/** 
		 * \brief The actual drawing of the object. 
		 */
		virtual void onRender() = 0;
		/** 
		 * \brief Called at the end of the rendering routine. 
		 */
		virtual void endRender() = 0;

		explicit IGeometryAccess();
	};
}