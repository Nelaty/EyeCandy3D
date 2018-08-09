#pragma once
#include "Widget.h"

/*
* Used as the root of a gui graph
* Holds a reference to the currently focused widget if any
*/

namespace ec_gui
{
	class GUIRenderer;
	class GUIRenderingContext;

	class Screen : public Widget
	{
	public:
		explicit Screen();
		~Screen();

		/* Render visitor function */
		virtual void Render(GUIRenderer& renderer, GUIRenderingContext& context) override;

		/* Access functions for the currently focused widget */
		void SetFocusedWidget(Widget* widget);
		Widget* GetFocusedWidget();

		/* A screen can't be focused */
		virtual void MoveFocus() override;

		/* Will always return true */
		virtual bool Contains(const glm::ivec2& position) const override;

		/* 
		*  Events
		*  If there's a focused widget, inform it about 
		*  a new event.
		*/
		virtual bool OnMouseButton(const glm::ivec2& position, int button, int mods, bool pressed) override;
		virtual bool OnMouseMove(const glm::ivec2& position) override;
		virtual bool OnMouseDrag(const glm::ivec2& position, const glm::ivec2& offset, int button, int mods) override;
		virtual bool OnMouseScroll(const glm::ivec2& position, const glm::vec2& offset) override;

		virtual bool OnFocus(bool focused) override;

		virtual bool OnKey(int key, int scancode, int mods, bool pressed) override;
		virtual bool OnText(unsigned int codepoint, int mods) override;

		virtual bool OnDrop(const glm::ivec2& position, int count, const char** paths) override;
		virtual bool OnResize(const glm::ivec2& size) override;


		
	private:
		Widget* m_focusedWidget;
	};
}