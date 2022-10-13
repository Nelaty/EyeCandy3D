#include "ec3/Application.h"
#include "ec3/Window/Window.h"
#include "ec3/Utilities/Random.h"
#include "ec3/Gui/MiniAgui.h"

#include <ec3/Common/EyeCandy3dInitializer.h>

#include <glm/glm.hpp>

namespace ec
{
	Application::Application()
		: m_running{true}
	{
		ec::Random::seed();
		EyeCandy3dInitializer::initEyeCandy3D();
	}
	Application::~Application() = default;

	void Application::startMainLoop()
	{
		while (m_running)
		{
			mainLoopImpl();
			closeDeadWindows();
		}
		cleanup();
	}

	void Application::kill()
	{
		m_running = false;
	}

	void Application::tick()
	{
		for (auto& it : m_windows)
		{
			it.second->tickMeta();
		}
	}

	void Application::render()
	{
		for (auto& it : m_windows)
		{
			it.second->render();
		}
	}

	void Application::closeDeadWindows()
	{
        for(auto it = m_windows.begin(); it != m_windows.end();)
        {
            if(!it->second->shouldClose())
            {
                ++it;
                continue;
            }
            it->second->destroy();
            it = m_windows.erase(it);
        }
	}

	void Application::monitorCallback(GLFWmonitor* monitor, const int event)
	{
		if(event == GLFW_CONNECTED)
		{
			if(s_monitorConnectedCallback)
			{
				s_monitorConnectedCallback(monitor);
			}			
		}
		else if(event == GLFW_DISCONNECTED)
		{
			if(s_monitorDisconnectedCallback)
			{
				s_monitorDisconnectedCallback(monitor);
			}
		}	
	}

	void Application::init()
	{
		const auto initSuccessful = initImpl();
		printVersions();
	
		glfwSetMonitorCallback(Application::monitorCallback);
	}

	void Application::cleanup()
	{
		glfwTerminate();
	}

	bool Application::initImpl()
	{
		initOpenGl();

		return true;
	}

	void Application::mainLoopImpl()
	{
		tick();
		render();

		// Poll & process events
		glfwPollEvents();
	}

	void Application::initOpenGl()
	{
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT, GL_LINE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Application::printVersions()
	{
		auto major = 0;
		auto minor = 0;

		sscanf(reinterpret_cast<const char*>(glGetString(GL_VERSION)), "%d.%d",
		         &major, &minor);

		printf("LIBRARY VERSIONS\n\n");
		printf("OpenGL v%d.%d\n", major, minor);
		printf("GLEW v%s\n", glewGetString(GLEW_VERSION));
		printf("GLFW v%d.%d.%d\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
	}

	void Application::setMonitorConnectedCallback(const std::function<void(GLFWmonitor*)>& cb)
	{
		s_monitorConnectedCallback = cb;
	}

	void Application::setMonitorDisconnectedCallback(const std::function<void(GLFWmonitor*)>& cb)
	{
		s_monitorDisconnectedCallback = cb;
	}

	std::function<void(GLFWmonitor*)> Application::s_monitorConnectedCallback = nullptr;
	std::function<void(GLFWmonitor*)> Application::s_monitorDisconnectedCallback = nullptr;
}
