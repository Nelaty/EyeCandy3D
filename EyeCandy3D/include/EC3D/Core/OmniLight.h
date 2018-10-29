#pragma once
#include "EC3D/Core/Light.h"

namespace ec
{
	/**
	 * \brief Ambient lighting that acts everywhere.
	 * \todo: implement
	 */
	class OmniLight : public Light
	{
	public:
		explicit OmniLight();
		~OmniLight();
		
	private:

	};
}