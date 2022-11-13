#pragma once
#include "ec3/graphics/lighting/light.h"

namespace ec
{
	/// Ambient lighting that acts everywhere.
	/// \todo: implement
	class OmniLight : public Light
	{
	public:
		explicit OmniLight();
		~OmniLight();
		
	private:

	};
}