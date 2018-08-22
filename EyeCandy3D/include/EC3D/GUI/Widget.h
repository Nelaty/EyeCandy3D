#pragma once

#include <glm/glm.hpp>

#include <vector>
#include <string>

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
	class GuiRenderer;
	class GuiRenderingContext;
	class Theme;

	class Widget
	{
	public:
		explicit Widget(Widget* parent);
		virtual ~Widget();

		/* 
		* Render this widget. Uses visitor pattern. 
		*/
		virtual void render(GuiRenderer& renderer, GuiRenderingContext& context);

		/* Drawable access */
		virtual void setDrawable(ec::Drawable* drawable);
		virtual ec::Drawable* getDrawable();

		/* Parent access */
		virtual const Widget* getParent() const;
		virtual Widget* getParent();
		virtual void setParent(Widget* widget);

		/* Remove and add children*/
		virtual void addChild(Widget* widget);
		virtual void removeChild(Widget* widget);
		virtual void removeChildAtIndex(unsigned int index);

		/* Get child at a specified index or get them all */
		virtual const std::vector<Widget*>& getChildren() const;
		virtual unsigned int getIndexOfChild(Widget* widget);
		virtual const Widget* getChildAtIndex(unsigned int index) const;
		virtual Widget* getChildAtIndex(unsigned int index);

		/* Activation */
		virtual bool isEnabled() const;
		virtual void enable(bool enable);

		/* Visibility */
		virtual bool isVisible() const;
		virtual void setVisible(bool visible);

		/* Check if the position is contained in this widget */
		virtual bool contains(const glm::ivec2& position) const;

		/* Focus */
		virtual bool isFocused() const;
		virtual void setFocus(bool focused);
		virtual void moveFocus();

		/* Dragging */
		virtual bool isDragged() const;
		virtual void setDragged(bool dragged);

		/* Position */
		virtual void setPosition(const glm::ivec2& position);
		virtual void setPosition(int x, int y);
		virtual void setPositionX(int x);
		virtual void setPositionY(int y);
		virtual const glm::ivec2& getPosition() const;

		/* Size */
		virtual void setSize(const glm::ivec2& size);
		virtual void setSize(int sx, int sy);
		virtual void setSizeX(int sx);
		virtual void setSizeY(int sy);
		virtual const glm::ivec2& getSize() const;

		/* Theme */
		static void setTheme(Theme* theme);
		static Theme* getTheme();

		/* Events */
		virtual bool onMouseButton(const glm::ivec2& position, int button, int mods, bool pressed);
		virtual bool onMouseMove(const glm::ivec2& position);
		virtual bool onMouseDrag(const glm::ivec2& position, const glm::ivec2& offset, int button, int mods);
		virtual bool onMouseScroll(const glm::ivec2& position, const glm::vec2& offset);

		virtual bool onFocus(bool focused);

		virtual bool onKey(int key, int scancode, int mods, bool pressed);
		virtual bool onText(unsigned int codepoint, int mods);

		virtual bool onDrop(const glm::ivec2& position, int count, const char** paths);
		virtual bool onResize(const glm::ivec2& size);

	protected:
		static Theme* s_theme;

		Widget* m_parent;
		std::vector<Widget*> m_children;
		ec::Drawable* m_drawable = nullptr;

		glm::ivec2 m_position{0};
		glm::ivec2 m_size{100};

		std::string m_tooltip = "";

		/* Flags */
		bool m_enabled = true;
		bool m_visible = true;
		bool m_focused = false;
		bool m_drag = false;
	};
}