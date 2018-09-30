#include "EC3D/Gui/GuiSystem.h"
#include "EC3D/Core/Camera.h"
#include "EC3D/Core/Scene.h"
#include "EC3D/Core/SceneSystem.h"
#include "EC3D/Core/Window.h"
#include "EC3D/Core/EventSystem.h"
#include "EC3D/Core/InputObservable.h"

#include "EC3D/Gui/Backend/OpenGLInput.h"
#include "EC3D/Gui/Backend/OpenGLGraphics.h"

#include "EC3D/Gui/GuiRenderContext.h"

#include "Agui/Gui.hpp"
#include "Agui/Widgets/Button/Button.hpp"
#include "Agui/Widgets/Button/ButtonListener.hpp"
#include "Agui/FlowLayout.hpp"

#include <iostream>

class SimpleActionListener : public agui::ButtonListener
{
public:
	void buttonStateChanged(agui::Button* button, agui::Button::ButtonStateEnum type) override
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
	}
	void toggleStateChanged(agui::Button* button, bool) override
	{
		std::cout << "Button: toggleStateChanged!\n";
	}
	void isToggleButtonChanged(agui::Button* button, bool) override
	{
		std::cout << "Button: isToggleButtonChanged!\n";
	}
	void textAlignmentChanged(agui::Button* button, agui::AreaAlignmentEnum type) override
	{
		std::cout << "Button: textAlignmentChanged!\n";
	}
};


namespace ec
{

	GuiSystem::GuiSystem(Camera* camera)
		: m_camera(camera)
	{
		m_window = Window::getCurrentWindow();

		// Instance a new gui
		m_model = std::make_unique<agui::Gui>();
	
		//Set the input handler
		m_inputListener = std::make_unique<Controller_Type>();
		m_model->setInput(m_inputListener.get());
		registerInputListener();

		// Set the graphics handler
		m_graphicsHandler = std::make_unique<GraphicsHandler_Type>(camera);
		m_model->setGraphics(m_graphicsHandler.get());

		initTestGui();
	}

	GuiSystem::~GuiSystem()
	= default;

	void GuiSystem::render(const GuiRenderContext& context) const
	{
		m_graphicsHandler->setRenderContext(context);
		m_model->render();
	}

	void GuiSystem::setModel(Gui_Ptr gui)
	{
		m_model = std::make_unique<agui::Gui>();

		m_model->setInput(m_inputListener.get());
	}

	GuiSystem::Gui_Type* GuiSystem::getModel() const
	{
		return m_model.get();
	}

	GuiSystem::GraphicsHandler_Type* GuiSystem::getGraphicsHandler() const
	{
		return m_graphicsHandler.get();
	}

	void GuiSystem::registerInputListener() const
	{
		auto& eventSystem = m_window->getEventSystem();
		eventSystem.registerInputListener(m_inputListener.get());
	}

	void GuiSystem::unregisterInputListener() const
	{
		auto& eventSystem = m_window->getEventSystem();
		eventSystem.unregisterInputListener(m_inputListener.get());
	}

	void GuiSystem::initTestGui()
	{
		static int i = 0;
		if(i >= 1) return;
		++i;

		const auto listener = new SimpleActionListener();

		auto flowLayout = new agui::FlowLayout();
		flowLayout->setVerticalSpacing(120);
		flowLayout->setHorizontalSpacing(20);
		m_model->add(flowLayout);

		auto button = new agui::Button();
		button->setSize(50, 100);
		button->addButtonListener(listener);
		flowLayout->add(button);

		auto button2 = new agui::Button();
		button2->setSize(100, 50);
		button2->addButtonListener(listener);
		flowLayout->add(button2);

		for(int i = 0; i < 20; ++i)
		{
			auto b = new agui::Button();
			b->setSize(50, 50);
			b->addButtonListener(listener);
			flowLayout->add(b);
		}
	}
}
