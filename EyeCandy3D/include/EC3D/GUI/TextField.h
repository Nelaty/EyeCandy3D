#pragma once
#include "Text.h"

/*
 * Can hold a text string, which can be manipulated
 */
namespace ec_gui
{
	class Widget;

	class TextField : public Text
	{
	public:
		explicit TextField(Widget* parent);
		~TextField();

		bool onText(unsigned int codepoint, int mods) override;
	};
}