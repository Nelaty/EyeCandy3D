#include "ExampleGui.h"

ExampleGui::ExampleGui()
{
}

ExampleGui::~ExampleGui()
= default;

void ExampleGui::init()
{
	initListener();

	auto flowLayout = new agui::FlowLayout();
	flowLayout->setVerticalSpacing(120);
	flowLayout->setHorizontalSpacing(20);
	this->add(flowLayout);

	auto button = new agui::Button();
	button->setSize(50, 100);
	button->addButtonListener(m_buttonListener);
	flowLayout->add(button);

	auto button2 = new agui::Button();
	button2->setSize(100, 50);
	button2->addButtonListener(m_buttonListener);
	flowLayout->add(button2);

	for (int i = 0; i < 20; ++i)
	{
		auto b = new agui::Button();
		b->setSize(50, 50);
		b->addButtonListener(m_buttonListener);
		flowLayout->add(b);
	}
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