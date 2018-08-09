#pragma once

/*
* A font character holds information to a specific character of a
* specific font.
*/
namespace ec
{
	struct FontCharacter
	{
		float advanceX;
		float advanceY;

		float bitmapWidth;
		float bitmapHeight;

		float bitmapLeft;
		float bitmapTop;

		float uvOffsetX;
		float uvOffsetY;
	};
}