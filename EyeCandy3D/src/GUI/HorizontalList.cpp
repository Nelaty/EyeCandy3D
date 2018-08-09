#include "EC3D/GUI/HorizontalList.h"

#include <glm/glm.hpp>

namespace ec_gui
{
	HorizontalList::HorizontalList(Widget* parent, int hspace)
		: Widget(parent),
		m_hspace{hspace}
	{
	}

	HorizontalList::~HorizontalList()
	{
	}

	void HorizontalList::SetHorizontalSpace(int hspace)
	{
		m_hspace = hspace;
		AlignChilds();
	}

	void HorizontalList::AddChild(Widget* widget)
	{
		AlignChild(widget, m_children.size());
	
		__super::AddChild(widget);
	}

	void HorizontalList::AlignChilds()
	{
		for(int i = 0; i < m_children.size(); ++i)
		{
			AlignChild(m_children[i], i);
		}
	}

	void HorizontalList::AlignChild(Widget* widget, int pos)
	{
		glm::ivec2 widgetPos(pos * m_hspace, 0);
		widget->SetPosition(widgetPos);
	}
}