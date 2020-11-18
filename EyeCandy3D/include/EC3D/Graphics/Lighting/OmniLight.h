#pragma once
#include "Light.h"

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