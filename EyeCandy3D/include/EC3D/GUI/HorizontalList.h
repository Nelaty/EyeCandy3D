#pragma once
#include "Widget.h"

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
		void setHorizontalSpace(int hspace);

		/* Automatically align new children */
		void addChild(Widget* widget) override;

	private:
		/* Align all child */
		void alignChildren();
		/* Align widget */
		void alignChild(Widget* widget, int pos) const;

		int m_hspace;
	};
}