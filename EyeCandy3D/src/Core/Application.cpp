#include "EC3D/Core/Application.h"
#include "EC3D/Core/Window.h"

namespace ec
{
	Application::Application(const unsigned int windowWidth, 
							 const unsigned int windowHeight,
							 const std::string& windowTitle,
							 const std::string& windowName)
		: m_running{true}
	{
		init();

		for(auto i = 0; i < 1; ++i)
		{
			const char c = i + '0';
			createWindow<Window>(windowWidth,
								 windowHeight,
								 windowTitle,
								 windowName + c);
		}

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
		printf("\n");
		printf("##############################\n");
		printf("INITIALIZING APPLICATION\n\n");

		const auto initSuccessful = initImpl();

		if(initSuccessful)
		{
			printf("\nINITIALIZATION SUCCESSFUL\n");
		}
		else
		{
			printf("\nERROR: INITIALIZATION UNSUCCESSFUL");
		}
		printf("##############################\n");

		printVersions();

		if(!initSuccessful)
		{
			throw(std::exception("Error: Couldn't initialize application!\n"));
		}
	}

	void Application::cleanup()
	{
		glfwTerminate();
	}

	bool Application::initImpl()
	{
		glewExperimental = GL_TRUE;
		/* Init GLFW */
		printf("Initializing GLFW...\n");
		if(!glfwInit())
		{
			printf("ERROR: Couldn't initialize GLFW!\n");
			return false;
		}
		
		createWindow<Window>(1024, 1024, "asd", "asdf");

		/* Init GLEW */
		printf("Initializing GLEW...\n");
		const auto glewError = glewInit();
		if(glewError != GLEW_OK)
		{
			printf("ERROR: Couldn't init GLEW: \n");
			printf("Error: %p\n", glewGetErrorString(glewError));
			return false;
		}

		initOpenGl();
		initAgui();

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

	void Application::initAgui()
	{
	}

	void Application::printVersions() const
	{
		int major = 0;
		int minor = 0;

		sscanf_s(reinterpret_cast<const char*>(glGetString(GL_VERSION)), "%d.%d",
				 &major, &minor);

		printf("LIBRARY VERSIONS\n\n");
		printf("OpenGL v%d.%d\n", major, minor);
		printf("GLEW v%s\n", glewGetString(GLEW_VERSION));
		printf("GLFW v%d.%d.%d\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
	}
}