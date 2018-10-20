#pragma once
#include "EC3D/Core/Light.h"

namespace ec
{
	class PointLight : public Light
	{
	public:
		explicit PointLight(float falloff);
		~PointLight();

		/** Set the current falloff */
		void setFalloff(float falloff);
		/** Get the current falloff */
		float getFalloff() const;

	private:
		float m_falloff;
	};
}