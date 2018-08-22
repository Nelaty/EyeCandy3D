#pragma once
#include "Widget.h"

#include <memory>
#include <string>

struct GLFWwindow;

/*
* A GUI contains the root of a widget hierarchy and can be identified by a 
* name.
*/
namespace ec_gui
{
	class Widget;

	class Gui
	{
	public:
		using Widget_TP = std::unique_ptr<Widget>;

	public:
		explicit Gui(std::string guiName);
		virtual ~Gui();

		/* Enable and disable this GUI */
		void enable(bool enabled) const;
		bool isEnabled() const;

		/* Widget access */
		Widget* getWidget() const;

		/* Root widget access */
		void setRoot(std::unique_ptr<Widget> root);
		Widget* getRoot() const;

		/* GUI name access */
		const std::string& getName() const;
		void setName(const std::string& guiName);

	protected:
		std::string m_name;

		Widget_TP m_widgetRoot;
	};
}