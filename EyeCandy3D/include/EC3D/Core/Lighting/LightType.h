#pragma once

namespace ec
{
	/**
	 * \brief Contains all different types of light sources.
	 */
	enum class LightType : int
	{
		point = 0,
		directional,
		omni,
		spot,

		count
	};
}