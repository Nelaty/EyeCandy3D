#pragma once
#include "Widget.h"

#include <vector>

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
		void SetVerticalSpace(int vspace);

		/* Add and align new children */
		virtual void AddChild(Widget* widget) override;

	private:
		/* Align all children */
		void AlignChilds();
		/* Align a widget */
		void AlignChild(Widget* widget, int pos);

		int m_vspace;
	};
}