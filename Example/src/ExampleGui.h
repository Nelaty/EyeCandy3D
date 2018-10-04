#pragma once
#include "Agui/Gui.hpp"
#include "Agui/Widgets/Button/Button.hpp"
#include "Agui/Widgets/Button/ButtonListener.hpp"
#include "Agui/FlowLayout.hpp"
#include "Agui/Widgets/Slider/Slider.hpp"
#include "Agui/Widgets/ScrollBar/VScrollBar.hpp"
#include "Agui/Widgets/ImageWidget/ImageWidget.hpp"
#include "Agui/Widgets/Frame/Frame.hpp"

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

	agui::Frame* m_frame;
	agui::FlowLayout* m_flowLayout;
	agui::Slider* m_slider;
	agui::ImageWidget* m_imageWidget;

	agui::VScrollBar* m_verticalScrollBar;
};
