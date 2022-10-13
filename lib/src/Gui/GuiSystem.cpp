#include "ec3/Gui/GuiSystem.h"
#include "ec3/Graphics/Camera.h"
#include "ec3/Scene.h"
#include "ec3/Window/Window.h"
#include "ec3/Input/EventSystem.h"
#include "ec3/Input/InputObservable.h"

#include "ec3/Gui/Backend/OpenGLInput.h"
#include "ec3/Gui/Backend/OpenGLGraphics.h"

#include "ec3/Gui/GuiRenderContext.h"

#include "Agui/Gui.hpp"

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
		m_model = std::move(gui);

		m_model->setInput(m_inputListener.get());
		m_model->setGraphics(m_graphicsHandler.get());
	}

	GuiSystem::Gui_Type* GuiSystem::getModel() const
	{
		return m_model.get();
	}

	GuiSystem::GraphicsHandler_Type* GuiSystem::getGraphicsHandler() const
	{
		return m_graphicsHandler.get();
	}

	GuiSystem::Controller_Type* GuiSystem::getInputHandler() const
	{
		return m_inputListener.get();
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
}
