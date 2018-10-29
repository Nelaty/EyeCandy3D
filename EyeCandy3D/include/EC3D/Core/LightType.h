#pragma once

namespace ec
{
	/**
	 * \brief Contains all different types of light sources.
	 */
	enum class LightType
	{
		point,
		directional,
		omni,
		spot,

		count
	};
}