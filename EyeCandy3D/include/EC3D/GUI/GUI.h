#pragma once
#include "Widget.h"

#include <memory>
#include <vector>
#include <string>

struct GLFWwindow;

/*
* A GUI contains the root of a widget hierarchy and can be identified by a 
* name.
*/
namespace ec_gui
{
	class Widget;

	class GUI
	{
	public:
		using Widget_TP = std::unique_ptr<Widget>;

	public:
		explicit GUI(const std::string& guiName);
		virtual ~GUI();

		/* Enable and disable this GUI */
		void Enable(bool enabled);
		bool IsEnabled() const;

		/* Widget access */
		Widget* GetWidget();

		/* Root widget access */
		void SetRoot(std::unique_ptr<Widget> root);
		Widget* GetRoot();

		/* GUI name access */
		const std::string& GetName() const;
		void SetName(const std::string& guiName);

	protected:
		std::string m_name;

		Widget_TP m_widgetRoot;
	};
}