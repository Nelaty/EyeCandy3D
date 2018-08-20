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
	};
}