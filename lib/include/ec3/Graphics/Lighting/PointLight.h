#pragma once
#include "ec3/Graphics/Lighting/Light.h"

namespace ec
{
	/// Light source, which emits light omnidirectional from
	/// a given position.
	/// \todo: implement
	class PointLight : public Light
	{
	public:
		explicit PointLight(float falloff);
		~PointLight();

		/**
		 * \brief Set the current falloff.
		 */
		void setFalloff(float falloff);
		/** 
		 * \brief Get the current falloff.
		 */
		float getFalloff() const;

	private:
		float m_falloff;
	};
}