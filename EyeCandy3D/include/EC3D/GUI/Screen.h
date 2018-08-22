#pragma once
#include "Widget.h"

/*
* Used as the root of a gui graph
* Holds a reference to the currently focused widget if any
*/

namespace ec_gui
{
	class GuiRenderer;
	class GuiRenderingContext;

	class Screen : public Widget
	{
	public:
		explicit Screen();
		~Screen();

		/* Render visitor function */
		void render(GuiRenderer& renderer, GuiRenderingContext& context) override;

		/* Access functions for the currently focused widget */
		void setFocusedWidget(Widget* widget);
		Widget* getFocusedWidget() const;

		/* A screen can't be focused */
		void moveFocus() override;

		/* Will always return true */
		bool contains(const glm::ivec2& position) const override;

		/* 
		*  Events
		*  If there's a focused widget, inform it about 
		*  a new event.
		*/
		bool onMouseButton(const glm::ivec2& position, int button, int mods, bool pressed) override;
		bool onMouseMove(const glm::ivec2& position) override;
		bool onMouseDrag(const glm::ivec2& position, const glm::ivec2& offset, int button, int mods) override;
		bool onMouseScroll(const glm::ivec2& position, const glm::vec2& offset) override;

		bool onFocus(bool focused) override;

		bool onKey(int key, int scancode, int mods, bool pressed) override;
		bool onText(unsigned int codepoint, int mods) override;

		bool onDrop(const glm::ivec2& position, int count, const char** paths) override;
		bool onResize(const glm::ivec2& size) override;


		
	private:
		Widget* m_focusedWidget;
	};
}