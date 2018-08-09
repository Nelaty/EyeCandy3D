#pragma once
#include "Widget.h"

#include <vector>

/*
* Automatically aligns child widget in a horizontal order
*/
namespace ec_gui
{
	class HorizontalList : public Widget
	{
	public:
		explicit HorizontalList(Widget* parent, int hspace = 1);
		~HorizontalList();

		/* Set horizontal space between child widgets */
		void SetHorizontalSpace(int hspace);

		/* Automatically align new children */
		virtual void AddChild(Widget* widget) override;

	private:
		/* Align all child */
		void AlignChilds();
		/* Align widget */
		void AlignChild(Widget* widget, int pos);

		int m_hspace;
	};
}