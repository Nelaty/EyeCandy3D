#pragma once
#include "EC3D/Core/Geometry.h"
#include "EC3D/Common/Common.h"

namespace ec
{
	class EC3D_DECLSPEC DynamicGeometry : public Geometry
	{
	public:
		virtual ~DynamicGeometry();

	protected:
		explicit DynamicGeometry();

		void beginRender() override;

		/**
		 * Update function gets called once at the start of every
		 * render cycle.
		 */
		virtual void update();
	};
}