#include "EC3D/Gui/Widget.h"
#include "EC3D/Gui/Screen.h"
#include "EC3D/Gui/GuiRenderer.h"
#include "EC3D/Gui/Theme.h"

#include "EC3D/Core/Drawable.h"

#include <algorithm>
#include <iterator>

namespace ec_gui
{
	Widget::Widget(Widget* parent)
		: m_parent{parent}
	{
	}

	Widget::~Widget()
	= default;

	void Widget::render(GuiRenderer& renderer, GuiRenderingContext& context)
	{
		renderer.render(this, context);
	}

	void Widget::setDrawable(ec::Drawable* drawable)
	{
		m_drawable = drawable;
	}

	ec::Drawable* Widget::getDrawable()
	{
		return m_drawable;
	}

	const ec_gui::Widget* Widget::getParent() const
	{
		return m_parent;
	}

	ec_gui::Widget* Widget::getParent()
	{
		return m_parent;
	}

	void Widget::setParent(Widget* widget)
	{
		m_parent = widget;
	}

	void Widget::addChild(Widget* widget)
	{
		widget->setParent(this);
		m_children.push_back(widget);
	}

	void Widget::removeChild(Widget* widget)
	{
		std::remove_if(m_children.begin(),
					   m_children.end(),
					   [&](const Widget* it)
		{
			return it == widget;
		});
	}

	void Widget::removeChildAtIndex(unsigned int index)
	{
		auto it = m_children.begin();
		std::advance(it, index);
		m_children.erase(it);
	}

	const std::vector<Widget*>& Widget::getChildren() const
	{
		return m_children;
	}

	unsigned int Widget::getIndexOfChild(Widget* widget)
	{
		const auto it = std::find_if(m_children.begin(),
									 m_children.end(),
									 [&](const Widget* it)
		{
			return it == widget;
		});
		
		return static_cast<unsigned int>(std::distance(m_children.begin(), it));
	}

	const ec_gui::Widget* Widget::getChildAtIndex(const unsigned int index) const
	{
		return m_children[index];
	}

	ec_gui::Widget* Widget::getChildAtIndex(const unsigned int index)
	{
		return m_children[index];
	}

	bool Widget::isEnabled() const
	{
		return m_enabled;
	}

	void Widget::enable(const bool enable)
	{
		m_enabled = enable;
	}

	bool Widget::isVisible() const
	{
		return m_visible;
	}

	void Widget::setVisible(const bool visible)
	{
		m_visible = visible;
	}

	bool Widget::contains(const glm::ivec2& position) const
	{
		const auto movedPos = position - m_position;
		return movedPos.x >= 0 && movedPos.y >= 0
			&& movedPos.x <= m_size.x && movedPos.y <= m_size.y;

	}

	bool Widget::isFocused() const
	{
		return m_focused;
	}

	void Widget::setFocus(const bool focused)
	{
		m_focused = focused;
	}

	void Widget::moveFocus()
	{
		auto* parent = m_parent;
		while(parent)
		{
			auto* nextParent = parent->getParent();
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

		auto* screen = dynamic_cast<Screen*>(parent);
		if(screen)
		{
			screen->setFocusedWidget(this);
		}
	}

	bool Widget::isDragged() const
	{
		return m_drag;
	}

	void Widget::setDragged(const bool dragged)
	{
		m_drag = dragged;
	}

	void Widget::setPosition(const glm::ivec2& position)
	{
		m_position = position;
	}

	void Widget::setPosition(const int x, const int y)
	{
		m_position.x = x;
		m_position.y = y;
	}

	void Widget::setPositionX(const int x)
	{
		m_position.x = x;
	}

	const glm::ivec2& Widget::getPosition() const
	{
		return m_position;
	}

	void Widget::setSize(const glm::ivec2& size)
	{
		m_size = size;
	}

	void Widget::setSize(const int sx, const int sy)
	{
		m_size.x = sx;
		m_size.y = sy;
	}

	void Widget::setSizeX(const int sx)
	{
		m_size.x = sx;
	}

	void Widget::setSizeY(const int sy)
	{
		m_size.y = sy;
	}

	const glm::ivec2& Widget::getSize() const
	{
		return m_size;
	}

	void Widget::setTheme(Theme* theme)
	{
		s_theme = theme;
	}

	ec_gui::Theme* Widget::getTheme()
	{
		return s_theme;
	}

	bool Widget::onMouseButton(const glm::ivec2& position, int button, int mods, bool pressed)
	{
		if(!(m_enabled && m_visible))
		{
			return false;
		}

		if(contains(position))
		{
			for(auto& it : m_children)
			{
				if(it->onMouseButton(position - m_position, button, mods, pressed))
				{
					if(!m_focused)
					{
						moveFocus();
					}
					return true;
				}
			}
		}
		return false;
	}

	bool Widget::onMouseMove(const glm::ivec2& position)
	{
		if(!(m_enabled && m_visible))
		{
			return false;
		}

		if(contains(position))
		{
			for(auto& it : m_children)
			{
				if(it->onMouseMove(position - m_position))
				{
					return true;
				}
			}
		}
		return false;
	}

	bool Widget::onMouseDrag(const glm::ivec2& position, const glm::ivec2& offset, int button, int mods)
	{
		return false;
	}

	bool Widget::onMouseScroll(const glm::ivec2& position, const glm::vec2& offset)
	{
		if(!(m_enabled && m_visible))
		{
			return false;
		}

		if(contains(position))
		{
			for(auto& it : m_children)
			{
				if(it->onMouseScroll(position - m_position, offset))
				{
					return true;
				}
			}
		}
		return false;
	}

	bool Widget::onFocus(bool focused)
	{
		return true;
	}

	bool Widget::onKey(int key, int scancode, int mods, bool pressed)
	{
		return false;
	}

	bool Widget::onText(unsigned int codepoint, int mods)
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

	bool Widget::onDrop(const glm::ivec2& position, int count, const char** paths)
	{
		return false;
	}

	bool Widget::onResize(const glm::ivec2& size)
	{
		return false;
		// TODO: Reevaluate position
	}

	void Widget::setPositionY(const int y)
	{
		m_position.y = y;
	}

	ec_gui::Theme* Widget::s_theme = nullptr;
}