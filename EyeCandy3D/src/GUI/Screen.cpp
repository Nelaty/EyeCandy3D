#include "EC3D/GUI/Screen.h"
#include "EC3D/GUI/GUIRenderer.h"

namespace ec_gui
{
	Screen::Screen()
		: Widget(nullptr)
	{
	}

	Screen::~Screen()
	{
	}

	void Screen::Render(GUIRenderer& renderer, GUIRenderingContext& context)
	{
		renderer.Render(this, context);
	}

	void Screen::SetFocusedWidget(Widget* widget)
	{
		/* Remove the focus of the previously focused widget if existent */
		if(m_focusedWidget)
		{
			m_focusedWidget->OnFocus(false);
			m_focusedWidget->SetFocus(false);
			m_focusedWidget->SetDragged(false);
		}

		/* Give focus to the new widget */
		m_focusedWidget = widget;
		if(m_focusedWidget)
		{
			m_focusedWidget->OnFocus(true);
			m_focusedWidget->SetFocus(true);
		}
	}

	ec_gui::Widget* Screen::GetFocusedWidget()
	{
		return m_focusedWidget;
	}

	bool Screen::OnMouseButton(const glm::ivec2& position, int button, int mods, bool pressed)
	{
		return __super::OnMouseButton(position, button, mods, pressed);
	}

	bool Screen::OnMouseMove(const glm::ivec2& position)
	{
		return __super::OnMouseMove(position);
	}

	bool Screen::OnMouseDrag(const glm::ivec2& position, const glm::ivec2& offset, int button, int mods)
	{
		//return __super::OnMouseDrag(position, offset, button, mods);
	
		bool result = true;

		if(m_focusedWidget)
		{
			m_focusedWidget->OnMouseDrag(position, offset, button, mods);
		}
		return result;
	}

	bool Screen::OnMouseScroll(const glm::ivec2& position, const glm::vec2& offset)
	{
		bool result =__super::OnMouseScroll(position, offset);

		if(m_focusedWidget)
		{
			m_focusedWidget->OnMouseScroll(position, offset);
		}
		return result;
	}

	bool Screen::OnFocus(bool focused)
	{
		return __super::OnFocus(focused);
	}

	bool Screen::OnKey(int key, int scancode, int mods, bool pressed)
	{
		bool result = __super::OnKey(key, scancode, mods, pressed);
		
		if(m_focusedWidget)
		{
			m_focusedWidget->OnKey(key, scancode, mods, pressed);
			result = result && true;
		}
		return result;
	}

	bool Screen::OnText(unsigned int codepoint, int mods)
	{
		bool result = true;// __super::OnText(codepoint, mods);

		if(m_focusedWidget)
		{
			m_focusedWidget->OnText(codepoint, mods);
			result = result && true;
		}
		return result;
	}

	bool Screen::OnDrop(const glm::ivec2& position, int count, const char** paths)
	{
		return __super::OnDrop(position, count, paths);
	}

	bool Screen::OnResize(const glm::ivec2& size)
	{
		return __super::OnResize(size);
	}

	void Screen::MoveFocus()
	{
	}

	bool Screen::Contains(const glm::ivec2& position) const
	{
		return m_enabled;
	}

}