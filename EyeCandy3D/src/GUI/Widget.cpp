#include "EC3D/GUI/Widget.h"
#include "EC3D/GUI/Screen.h"
#include "EC3D/GUI/GUIRenderer.h"
#include "EC3D/GUI/Theme.h"

#include "EC3D/Core/Drawable.h"

#include <algorithm>
#include <iterator>

#include <GLFW/glfw3.h>

namespace ec_gui
{
	Widget::Widget(Widget* parent)
		: m_parent{parent},
		m_position{0},
		m_size{100},
		m_tooltip{""},
		m_enabled{true},
		m_visible{true},
		m_focused{false},
		m_drag{false},
		m_drawable{nullptr}
	{
	}

	Widget::~Widget()
	{
	}

	void Widget::Render(GUIRenderer& renderer, GUIRenderingContext& context)
	{
		renderer.Render(this, context);
	}

	void Widget::SetDrawable(ec::Drawable* drawable)
	{
		m_drawable = drawable;
	}

	ec::Drawable* Widget::GetDrawable()
	{
		return m_drawable;
	}

	const ec_gui::Widget* Widget::GetParent() const
	{
		return m_parent;
	}

	ec_gui::Widget* Widget::GetParent()
	{
		return m_parent;
	}

	void Widget::SetParent(Widget* widget)
	{
		m_parent = widget;
	}

	void Widget::AddChild(Widget* widget)
	{
		widget->SetParent(this);
		m_children.push_back(std::move(widget));
	}

	void Widget::RemoveChild(Widget* widget)
	{
		std::remove_if(m_children.begin(),
					   m_children.end(),
					   [&](const Widget* it)
		{
			return it == widget;
		});
	}

	void Widget::RemoveChildAtIndex(unsigned int index)
	{
		auto it = m_children.begin();
		std::advance(it, index);
		m_children.erase(it);
	}

	const std::vector<Widget*>& Widget::GetChildren() const
	{
		return m_children;
	}

	unsigned int Widget::GetIndexOfChild(Widget* widget)
	{
		const auto it = std::find_if(m_children.begin(),
									 m_children.end(),
									 [&](const Widget* it)
		{
			return it == widget;
		});
		
		return static_cast<unsigned int>(std::distance(m_children.begin(), it));
	}

	const ec_gui::Widget* Widget::GetChildAtIndex(const unsigned int index) const
	{
		return m_children[index];
	}

	ec_gui::Widget* Widget::GetChildAtIndex(const unsigned int index)
	{
		return m_children[index];
	}

	bool Widget::IsEnabled() const
	{
		return m_enabled;
	}

	void Widget::Enable(const bool enable)
	{
		m_enabled = enable;
	}

	bool Widget::IsVisible() const
	{
		return m_visible;
	}

	void Widget::SetVisible(const bool visible)
	{
		m_visible = visible;
	}

	bool Widget::Contains(const glm::ivec2& position) const
	{
		glm::ivec2 movedPos = position - m_position;
		return movedPos.x >= 0 && movedPos.y >= 0
			&& movedPos.x <= m_size.x && movedPos.y <= m_size.y;

	}

	bool Widget::IsFocused() const
	{
		return m_focused;
	}

	void Widget::SetFocus(const bool focused)
	{
		m_focused = focused;
	}

	void Widget::MoveFocus()
	{
		auto* parent = m_parent;
		while(parent)
		{
			auto* nextParent = parent->GetParent();
			if(nextParent)
			{
				parent = nextParent;
			}
			else
			{
				 // Found the root widget
				break;
			}
		}

		auto* screen = static_cast<Screen*>(parent);
		if(screen)
		{
			screen->SetFocusedWidget(this);
		}
	}

	bool Widget::IsDragged() const
	{
		return m_drag;
	}

	void Widget::SetDragged(const bool dragged)
	{
		m_drag = dragged;
	}

	void Widget::SetPosition(const glm::ivec2& position)
	{
		m_position = position;
	}

	void Widget::SetPosition(const int x, const int y)
	{
		m_position.x = x;
		m_position.y = y;
	}

	void Widget::SetPositionX(const int x)
	{
		m_position.x = x;
	}

	const glm::ivec2& Widget::GetPosition() const
	{
		return m_position;
	}

	void Widget::SetSize(const glm::ivec2& size)
	{
		m_size = size;
	}

	void Widget::SetSize(const int sx, const int sy)
	{
		m_size.x = sx;
		m_size.y = sy;
	}

	void Widget::SetSizeX(const int sx)
	{
		m_size.x = sx;
	}

	void Widget::SetSizeY(const int sy)
	{
		m_size.y = sy;
	}

	const glm::ivec2& Widget::GetSize() const
	{
		return m_size;
	}

	void Widget::SetTheme(Theme* theme)
	{
		s_theme = theme;
	}

	ec_gui::Theme* Widget::GetTheme()
	{
		return s_theme;
	}

	bool Widget::OnMouseButton(const glm::ivec2& position, int button, int mods, bool pressed)
	{
		if(!(m_enabled && m_visible))
		{
			return false;
		}

		if(Contains(position))
		{
			for(auto& it : m_children)
			{
				if(it->OnMouseButton(position - m_position, button, mods, pressed))
				{
					if(!m_focused)
					{
						MoveFocus();
					}
					return true;
				}
			}
		}
		return false;
	}

	bool Widget::OnMouseMove(const glm::ivec2& position)
	{
		if(!(m_enabled && m_visible))
		{
			return false;
		}

		if(Contains(position))
		{
			for(auto& it : m_children)
			{
				if(it->OnMouseMove(position - m_position))
				{
					return true;
				}
			}
		}
		return false;
	}

	bool Widget::OnMouseDrag(const glm::ivec2& position, const glm::ivec2& offset, int button, int mods)
	{
		return false;
	}

	bool Widget::OnMouseScroll(const glm::ivec2& position, const glm::vec2& offset)
	{
		if(!(m_enabled && m_visible))
		{
			return false;
		}

		if(Contains(position))
		{
			for(auto& it : m_children)
			{
				if(it->OnMouseScroll(position - m_position, offset))
				{
					return true;
				}
			}
		}
		return false;
	}

	bool Widget::OnFocus(bool focused)
	{
		return true;
	}

	bool Widget::OnKey(int key, int scancode, int mods, bool pressed)
	{
		return false;
	}

	bool Widget::OnText(unsigned int codepoint, int mods)
	{
		if(m_focused && m_visible && m_enabled)
		{
			printf("Text: %d, %d", codepoint, mods);
		}
		else
		{
			return false;
		}		
	}

	bool Widget::OnDrop(const glm::ivec2& position, int count, const char** paths)
	{
		return false;
	}

	bool Widget::OnResize(const glm::ivec2& size)
	{
		return false;
		// TODO: Reevaluate position
	}

	void Widget::SetPositionY(const int y)
	{
		m_position.y = y;
	}

	ec_gui::Theme* Widget::s_theme = nullptr;
}