#include "EC3D/GUI/GUI.h"
#include "EC3D/GUI/Widget.h"
#include "EC3D/GUI/Screen.h"

#include <GLFW/glfw3.h>


namespace ec_gui
{
	GUI::GUI(const std::string& guiName)
		: m_name{guiName}
	{
		m_widgetRoot = std::make_unique<Screen>();
	}

	GUI::~GUI()
	{
	}
	
	void GUI::Enable(bool enabled)
	{
		m_widgetRoot->Enable(enabled);
	}

	bool GUI::IsEnabled() const
	{
		return m_widgetRoot->IsEnabled();
	}

	Widget* GUI::GetWidget()
	{
		return m_widgetRoot.get();
	}

	void GUI::SetRoot(std::unique_ptr<Widget> root)
	{
		m_widgetRoot = std::move(root);
	}

	ec_gui::Widget* GUI::GetRoot()
	{
		return m_widgetRoot.get();
	}

	const std::string& GUI::GetName() const
	{
		return m_name;
	}

	void GUI::SetName(const std::string& guiName)
	{
		m_name = guiName;
	}
}