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
	{
	}

	void VerticalList::SetVerticalSpace(int vspace)
	{
		m_vspace = vspace;
		AlignChilds();
	}

	void VerticalList::AddChild(Widget* widget)
	{
		AlignChild(widget, m_children.size());
		__super::AddChild(widget);
	}

	void VerticalList::AlignChilds()
	{
		for(size_t i = 0; i < m_children.size(); ++i)
		{
			AlignChild(m_children[i], i);
		}
	}

	void VerticalList::AlignChild(Widget* widget, int pos)
	{
		glm::ivec2 widgetPos(0, pos * m_vspace);
		widget->SetPosition(widgetPos);
	}

}