#pragma once
#include "ec3/Graphics/Lighting/Light.h"

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