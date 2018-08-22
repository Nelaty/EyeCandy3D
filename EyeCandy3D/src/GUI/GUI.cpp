#include "EC3D/GUI/Gui.h"
#include "EC3D/GUI/Widget.h"
#include "EC3D/GUI/Screen.h"

#include <utility>

namespace ec_gui
{
	Gui::Gui(std::string guiName)
		: m_name{std::move(guiName)}
	{
		m_widgetRoot = std::make_unique<Screen>();
	}
	
	Gui::~Gui()
	= default;

	void Gui::enable(const bool enabled) const
	{
		m_widgetRoot->enable(enabled);
	}

	bool Gui::isEnabled() const
	{
		return m_widgetRoot->isEnabled();
	}

	Widget* Gui::getWidget() const
	{
		return m_widgetRoot.get();
	}

	void Gui::setRoot(std::unique_ptr<Widget> root)
	{
		m_widgetRoot = std::move(root);
	}

	ec_gui::Widget* Gui::getRoot() const
	{
		return m_widgetRoot.get();
	}

	const std::string& Gui::getName() const
	{
		return m_name;
	}

	void Gui::setName(const std::string& guiName)
	{
		m_name = guiName;
	}
}