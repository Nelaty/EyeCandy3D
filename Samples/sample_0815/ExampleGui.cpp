#include "ExampleGui.h"
#include "EC3D/Gui/Backend/OpenGLImage.h"

ExampleGui::ExampleGui()
{
}

ExampleGui::~ExampleGui()
= default;

void ExampleGui::init()
{
	initListener();

	m_flowLayout = new agui::FlowLayout();
	this->add(m_flowLayout);

	auto image = new ec::OpenGLImage("res_sample_0815/widgetImage.png");
	auto empty = new agui::EmptyWidget();
	empty->setSize(500, 1000);
	m_flowLayout->add(empty);

	m_imageWidget = new agui::ImageWidget(image);
	//m_flowLayout->add(m_imageWidget);

	m_slider = new agui::Slider();
	m_slider->setSize(100, 36);
	m_slider->setMaxValue(255);
	m_slider->setMarkerSize(agui::Dimension(10, 30));
	//m_flowLayout->add(m_slider);
	
	m_verticalScrollBar = new agui::VScrollBar();
	m_verticalScrollBar->setSize(agui::Dimension(10, 200));
	m_verticalScrollBar->setMinValue(10);
	m_verticalScrollBar->setMinValue(200);
	m_verticalScrollBar->setValue(200);
	//m_flowLayout->add(m_verticalScrollBar);

	for(int i = 0; i < 2; ++i)
	{
		auto b = new agui::Button();
		b->setSize(50, 50);
		b->addButtonListener(m_buttonListener);
		b->setBackColor(agui::Color(255, 255, 0, (255 * i) / 4));
		m_flowLayout->add(b);
	}

	auto button = new agui::Button();
	button->setSize(50, 100);
	button->setBackColor(agui::Color(255, 0, 0, 120));
	button->addButtonListener(m_buttonListener);
	m_flowLayout->add(button);

	auto button2 = new agui::Button();
	button2->setSize(100, 50);
	button2->addButtonListener(m_buttonListener);
	m_flowLayout->add(button2);

	m_frame = new agui::Frame();
	m_frame->setSize(200, 200);
	m_frame->setLocation(50, -200);
	//this->add(m_frame);
}

void ExampleGui::initListener()
{
	m_buttonListener = new ec::GenericButtonListener();
	const auto stateChangedCallback = [](agui::Button* button, agui::Button::ButtonStateEnum type)
	{
		switch(type)
		{
			case agui::Button::DEFAULT:
				std::cout << "Button: buttonStateChanged (DEFAULT)!" << button << "\n";
				break;
			case agui::Button::HOVERED:
				std::cout << "Button: buttonStateChanged (HOVERED)!" << button << "\n";
				break;
			case agui::Button::CLICKED:
				std::cout << "Button: buttonStateChanged (CLICKED)!" << button << "\n";
				break;
			default: break;
		}
	};
	m_buttonListener->setButtonChangedCallback(stateChangedCallback);
}