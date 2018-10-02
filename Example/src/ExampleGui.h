#pragma once
#include "Agui/Gui.hpp"
#include "Agui/Widgets/Button/Button.hpp"
#include "Agui/Widgets/Button/ButtonListener.hpp"
#include "Agui/FlowLayout.hpp"

#include "EC3D/Gui/Listener/GenericButtonListener.h"

#include <iostream>

class ExampleGui : public agui::Gui
{
public:
	explicit ExampleGui();
	~ExampleGui();

	void init();
private:
	void initListener();

	ec::GenericButtonListener* m_buttonListener;
};
