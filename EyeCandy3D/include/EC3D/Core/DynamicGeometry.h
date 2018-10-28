#pragma once
#include "EC3D/Core/Geometry.h"
#include "EC3D/Common/Common.h"

namespace ec
{
	/**
	 * \brief Kind of geometry that can be changed for every rendering.
	 */
	class EC3D_DECLSPEC DynamicGeometry : public Geometry
	{
	public:
		virtual ~DynamicGeometry();

	protected:
		explicit DynamicGeometry();

		/**
		 * \brief Update the geometry before rendering.
		 */
		void beginRender() override;

		/**
		 * \brief Update function gets called once at the start of every
		 * render cycle.
		 */
		virtual void update();
	};
}