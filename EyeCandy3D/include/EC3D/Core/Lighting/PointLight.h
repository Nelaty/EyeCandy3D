#pragma once
#include "Light.h"

namespace ec
{
	/**
	 * \brief Light source, which emits light omni-directional from
	 * a given position.
	 * \todo: implement
	 */
	class PointLight : public Light
	{
	public:
		explicit PointLight(float falloff);
		~PointLight();

		float m_falloff;
	};
}