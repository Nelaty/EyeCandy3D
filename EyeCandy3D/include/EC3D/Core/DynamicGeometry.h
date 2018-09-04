#pragma once
#include "EC3D/Core/Geometry.h"

namespace ec
{
	class DynamicGeometry : public Geometry
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