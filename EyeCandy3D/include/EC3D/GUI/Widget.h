#pragma once

#include <vector>
#include <memory>
#include <string>

#include <glm/glm.hpp>

struct GLFWwindow;

namespace ec
{
	struct InputEvent;

	class Drawable;
}

/*
* Base for all GUI elements
* A gui element can have multiple child widget and it can receive 
* input events.
*/
namespace ec_gui
{
	class GUIRenderer;
	class GUIRenderingContext;
	class Theme;

	class Widget
	{
	public:
		explicit Widget(Widget* parent);
		virtual ~Widget();

		/* 
		* Render this widget. Uses visitor pattern. 
		*/
		virtual void Render(GUIRenderer& renderer, GUIRenderingContext& context);

		/* Drawable access */
		virtual void SetDrawable(ec::Drawable* drawable);
		virtual ec::Drawable* GetDrawable();

		/* Parent access */
		virtual const Widget* GetParent() const;
		virtual Widget* GetParent();
		virtual void SetParent(Widget* widget);

		/* Remove and add children*/
		virtual void AddChild(Widget* widget);
		virtual void RemoveChild(Widget* widget);
		virtual void RemoveChildAtIndex(unsigned int index);

		/* Get child at a specified index or get them all */
		virtual const std::vector<Widget*>& GetChildren() const;
		virtual unsigned int GetIndexOfChild(Widget* widget);
		virtual const Widget* GetChildAtIndex(const unsigned int index) const;
		virtual Widget* GetChildAtIndex(const unsigned int index);

		/* Activation */
		virtual bool IsEnabled() const;
		virtual void Enable(const bool enable);

		/* Visibility */
		virtual bool IsVisible() const;
		virtual void SetVisible(const bool visible);

		/* Check if the position is contained in this widget */
		virtual bool Contains(const glm::ivec2& position) const;

		/* Focus */
		virtual bool IsFocused() const;
		virtual void SetFocus(const bool focused);
		virtual void MoveFocus();

		/* Dragging */
		virtual bool IsDragged() const;
		virtual void SetDragged(const bool dragged);

		/* Position */
		virtual void SetPosition(const glm::ivec2& position);
		virtual void SetPosition(const int x, const int y);
		virtual void SetPositionX(const int x);
		virtual void SetPositionY(const int y);
		virtual const glm::ivec2& GetPosition() const;

		/* Size */
		virtual void SetSize(const glm::ivec2& size);
		virtual void SetSize(const int sx, const int sy);
		virtual void SetSizeX(const int sx);
		virtual void SetSizeY(const int sy);
		virtual const glm::ivec2& GetSize() const;

		/* Theme */
		static void SetTheme(Theme* theme);
		static Theme* GetTheme();

		/* Events */
		virtual bool OnMouseButton(const glm::ivec2& position, int button, int mods, bool pressed);
		virtual bool OnMouseMove(const glm::ivec2& position);
		virtual bool OnMouseDrag(const glm::ivec2& position, const glm::ivec2& offset, int button, int mods);
		virtual bool OnMouseScroll(const glm::ivec2& position, const glm::vec2& offset);

		virtual bool OnFocus(bool focused);

		virtual bool OnKey(int key, int scancode, int mods, bool pressed);
		virtual bool OnText(unsigned int codepoint, int mods);

		virtual bool OnDrop(const glm::ivec2& position, int count, const char** paths);
		virtual bool OnResize(const glm::ivec2& size);

	protected:
		static Theme* s_theme;

		Widget* m_parent;
		std::vector<Widget*> m_children;
		ec::Drawable* m_drawable;

		glm::ivec2 m_position;
		glm::ivec2 m_size;

		std::string m_tooltip;

		/* Flags */
		bool m_enabled;
		bool m_visible;
		bool m_focused;
		bool m_drag;
	};
}