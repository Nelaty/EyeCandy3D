#pragma once

namespace ec
{
	/// Describe the type of a light source
	enum class LightType
	{
		point,
		directional,
		omni,
		spot,

		count
	};
}