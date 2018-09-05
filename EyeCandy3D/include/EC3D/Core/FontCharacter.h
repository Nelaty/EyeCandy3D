#pragma once
#include "EC3D/Common/Common.h"

namespace ec
{
	/**
	* A font character holds information to a specific character of a
	* specific font.
	*/
	struct EC3D_DECLSPEC FontCharacter
	{
		float m_advanceX;
		float m_advanceY;

		float m_bitmapWidth;
		float m_bitmapHeight;

		float m_bitmapLeft;
		float m_bitmapTop;

		float m_uvOffsetX;
		float m_uvOffsetY;
	};
}