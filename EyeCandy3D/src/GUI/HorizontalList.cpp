#include "EC3D/GUI/HorizontalList.h"

#include <glm/glm.hpp>

namespace ec_gui
{
	HorizontalList::HorizontalList(Widget* parent, const int hspace)
		: Widget(parent),
		m_hspace{hspace}
	{
	}

	HorizontalList::~HorizontalList()
	= default;

	void HorizontalList::setHorizontalSpace(const int hspace)
	{
		m_hspace = hspace;
		alignChildren();
	}

	void HorizontalList::addChild(Widget* widget)
	{
		alignChild(widget, m_children.size());
	
		__super::addChild(widget);
	}

	void HorizontalList::alignChildren()
	{
		for(size_t i = 0; i < m_children.size(); ++i)
		{
			alignChild(m_children[i], i);
		}
	}

	void HorizontalList::alignChild(Widget* widget, const int pos) const
	{
		const glm::ivec2 widgetPos(pos * m_hspace, 0);
		widget->setPosition(widgetPos);
	}
}