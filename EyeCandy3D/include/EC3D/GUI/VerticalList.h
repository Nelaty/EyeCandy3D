#pragma once
#include "Widget.h"

/*
* Automatically aligns child widget in a vertical order
*/
namespace ec_gui
{
	class VerticalList : public Widget
	{
	public:
		explicit VerticalList(Widget* parent, int vspace = 1);
		~VerticalList();

		/* Set the vertical space between children */
		void setVerticalSpace(int vspace);

		/* Add and align new children */
		void addChild(Widget* widget) override;

	private:
		/* Align all children */
		void alignChilds();
		/* Align a widget */
		void alignChild(Widget* widget, int pos) const;

		int m_vspace;
	};
}