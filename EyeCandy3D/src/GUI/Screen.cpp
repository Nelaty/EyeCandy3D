#include "EC3D/GUI/Screen.h"
#include "EC3D/GUI/GUIRenderer.h"

namespace ec_gui
{
	Screen::Screen()
		: Widget(nullptr), 
		m_focusedWidget(nullptr)
	{
	}

	Screen::~Screen()
	= default;

	void Screen::render(GuiRenderer& renderer, GuiRenderingContext& context)
	{
		renderer.render(this, context);
	}

	void Screen::setFocusedWidget(Widget* widget)
	{
		/* Remove the focus of the previously focused widget if existent */
		if(m_focusedWidget)
		{
			m_focusedWidget->onFocus(false);
			m_focusedWidget->setFocus(false);
			m_focusedWidget->setDragged(false);
		}

		/* Give focus to the new widget */
		m_focusedWidget = widget;
		if(m_focusedWidget)
		{
			m_focusedWidget->onFocus(true);
			m_focusedWidget->setFocus(true);
		}
	}

	ec_gui::Widget* Screen::getFocusedWidget() const
	{
		return m_focusedWidget;
	}

	bool Screen::onMouseButton(const glm::ivec2& position, int button, int mods, bool pressed)
	{
		return __super::onMouseButton(position, button, mods, pressed);
	}

	bool Screen::onMouseMove(const glm::ivec2& position)
	{
		return __super::onMouseMove(position);
	}

	bool Screen::onMouseDrag(const glm::ivec2& position, const glm::ivec2& offset, int button, int mods)
	{
		//return __super::OnMouseDrag(position, offset, button, mods);

		const auto result = true;

		if(m_focusedWidget)
		{
			m_focusedWidget->onMouseDrag(position, offset, button, mods);
		}
		return result;
	}

	bool Screen::onMouseScroll(const glm::ivec2& position, const glm::vec2& offset)
	{
		const auto result =__super::onMouseScroll(position, offset);

		if(m_focusedWidget)
		{
			m_focusedWidget->onMouseScroll(position, offset);
		}
		return result;
	}

	bool Screen::onFocus(bool focused)
	{
		return __super::onFocus(focused);
	}

	bool Screen::onKey(int key, int scancode, int mods, bool pressed)
	{
		const auto result = __super::onKey(key, scancode, mods, pressed);
		
		if(m_focusedWidget)
		{
			m_focusedWidget->onKey(key, scancode, mods, pressed);
		}
		return result;
	}

	bool Screen::onText(unsigned int codepoint, int mods)
	{
		const auto result = true;// __super::OnText(codepoint, mods);

		if(m_focusedWidget)
		{
			m_focusedWidget->onText(codepoint, mods);
		}
		return result;
	}

	bool Screen::onDrop(const glm::ivec2& position, int count, const char** paths)
	{
		return __super::onDrop(position, count, paths);
	}

	bool Screen::onResize(const glm::ivec2& size)
	{
		return __super::onResize(size);
	}

	void Screen::moveFocus()
	{
	}

	bool Screen::contains(const glm::ivec2& position) const
	{
		return m_enabled;
	}

}