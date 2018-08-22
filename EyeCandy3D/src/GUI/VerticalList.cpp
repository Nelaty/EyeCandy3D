#include "EC3D/GUI/VerticalList.h"

#include <glm/glm.hpp>

namespace ec_gui
{
	VerticalList::VerticalList(Widget* parent, int vspace)
		: Widget(parent),
		m_vspace{vspace}
	{
	}

	VerticalList::~VerticalList()
	= default;

	void VerticalList::setVerticalSpace(int vspace)
	{
		m_vspace = vspace;
		alignChilds();
	}

	void VerticalList::addChild(Widget* widget)
	{
		alignChild(widget, m_children.size());
		__super::addChild(widget);
	}

	void VerticalList::alignChilds()
	{
		for(size_t i = 0; i < m_children.size(); ++i)
		{
			alignChild(m_children[i], i);
		}
	}

	void VerticalList::alignChild(Widget* widget, int pos) const
	{
		const glm::ivec2 widgetPos(0, pos * m_vspace);
		widget->setPosition(widgetPos);
	}

}