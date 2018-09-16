#include "EC3D/Core/Application.h"
#include "EC3D/Core/Window.h"
#include "EC3D/Utilities/Random.h"
#include "EC3D/Gui/MiniAgui.h"

#include <glm/glm.hpp>



namespace ec
{
	Application::Application(const unsigned int windowWidth, 
							 const unsigned int windowHeight,
							 const std::string& windowTitle,
							 const std::string& windowName)
		: m_running{true}
	{
		utl::Random::seed();
	}

	Application::~Application() = default;

	void Application::startMainLoop()
	{
		while(m_running)
		{
			mainLoopImpl();
		}
		cleanup();
	}

	void Application::tick()
	{
		for(auto& it : m_windows)
		{
			it.second->tickMeta();
		}
	}

	void Application::render()
	{
		for(auto& it : m_windows)
		{
			it.second->render();
		}
	}

	void Application::init()
	{
		const auto initSuccessful = initImpl();
		printVersions();
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

	void Application::printVersions() const
	{
		auto major = 0;
		auto minor = 0;

		sscanf_s(reinterpret_cast<const char*>(glGetString(GL_VERSION)), "%d.%d",
				 &major, &minor);

		printf("LIBRARY VERSIONS\n\n");
		printf("OpenGL v%d.%d\n", major, minor);
		printf("GLEW v%s\n", glewGetString(GLEW_VERSION));
		printf("GLFW v%d.%d.%d\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
	}
}
