#include "EC3D/Gui/GuiSystem.h"
#include "EC3D/Core/Camera.h"
#include "EC3D/Core/Scene.h"
#include "EC3D/Core/SceneSystem.h"
#include "EC3D/Core/Window.h"
#include "EC3D/Core/EventSystem.h"
#include "EC3D/Core/InputObservable.h"

#include "EC3D/Gui/Backend/OpenGLInput.h"
#include "EC3D/Gui/Backend/OpenGLGraphics.h"

#include "Agui/Gui.hpp"

namespace ec
{

	GuiSystem::GuiSystem(Camera* camera)
	{
		m_camera = camera;

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

	void GuiSystem::render()
	{
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

	void GuiSystem::registerInputListener() const
	{
		auto& eventSystem = m_camera->getScene()->getSceneSystem()->getWindow()->getEventSystem();
		eventSystem.registerInputListener(m_inputListener.get());
	}

	void GuiSystem::unregisterInputListener() const
	{
		auto& eventSystem = m_camera->getScene()->getSceneSystem()->getWindow()->getEventSystem();
		eventSystem.unregisterInputListener(m_inputListener.get());
	}
}
