#include "EC3D/Core/Window.h"
#include "EC3D/Common/Config.h"
#include "EC3D/Core/InputEvent.h"

#include "EC3D/Utilities/Profiler.h"

#include <utility>

namespace ec
{
	Window::Window(const unsigned int windowWidth,
				   const unsigned int windowHeight,
				   std::string windowTitle)
		: m_windowWidth{windowWidth},
		m_windowHeight{windowHeight},
		m_windowTitle{std::move(windowTitle)},
		m_sceneSystem{this},
		m_eventSystem{this},
		m_clearColor{0.5,0.5,0.5,1.0},
		m_initSuccessful{false}
	{
		init();

		m_frameInterval = 1.0 / 100.0;

		m_windowedResolutionLast = getWindowResolution();
		m_windowPositionLast = getWindowPosition();
	}

	Window::~Window()
	= default;

	void Window::init()
	{
		printf("\n");
		printf("##############################\n");
		printf("INITIALIZING WINDOW\n\n");

		m_initSuccessful = initImpl();
		
		if(m_initSuccessful)
		{
			printf("\nINITIALIZATION SUCCESSFUL\n");
		}
		else
		{
			printf("\nERROR: INITIALIZATION UNSUCCESSFUL");
		}
		printf("##############################\n");

		if(!m_initSuccessful)
		{
			throw(std::exception("Error: Couldn't initialize window!\n"));
		}
	}

	void Window::makeContextCurrent() const
	{
		glfwMakeContextCurrent(m_window);
	}

	void Window::startMainLoop()
	{
		if(!m_initSuccessful)
		{
			printf("The simulation hasn't been initialized!\n");
			return;
		}

		m_timer.reset();
		while(!glfwWindowShouldClose(m_window))
		{
			mainLoopImpl();
		}
		glfwTerminate();
	}

	void Window::tickMeta()
	{
		const auto timeDelta = static_cast<float>(m_timer.getTimeDelta());

		windowTick(timeDelta);
		tick(timeDelta);

		m_timer.resetTimeDelta();
	}

	void Window::render()
	{
		makeContextCurrent();

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND); // Enable blending for water transparency

		m_renderer.render(this);

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

		/* Swap front and back buffers */
		glfwSwapBuffers(m_window);
	}

	void Window::setFrameRate(const double fps)
	{
		m_frameRate = fps;
		m_frameInterval = 1.0 / fps;
	}

	void Window::errorCallback(const int error, const char* description)
	{
		printf("ERROR: (%d) %s\n", error, description);
	}

	void Window::resizeWindow(GLFWwindow* window, const int width, const int height)
	{
		m_windowWidth = width;
		m_windowHeight = height;
	}

	EventSystem& Window::getEventSystem()
	{
		return m_eventSystem;
	}

	ec::ShaderManager& Window::getShaderManager()
	{
		return m_shaderManager;
	}

	ec::SceneSystem& Window::getSceneSystem()
	{
		return m_sceneSystem;
	}

	void Window::switchToFaceMode() const
	{
		makeContextCurrent();
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void Window::switchToWireFrameMode() const
	{
		makeContextCurrent();
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void Window::switchToPointMode() const
	{
		makeContextCurrent();
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}

	void Window::goWindowed() const
	{
		glfwSetWindowMonitor(m_window, nullptr,
							 m_windowPositionLast.x, m_windowPositionLast.y,
							 m_windowedResolutionLast.x, m_windowedResolutionLast.y,
							 GLFW_DONT_CARE);
	}

	bool Window::initImpl()
	{
		m_initSuccessful = true;
		glewExperimental = GL_TRUE;
		/* Init GLFW */
		printf("Initializing GLFW...\n");
		if(!glfwInit())
		{
			printf("ERROR: Couldn't initialize GLFW!\n");
			m_initSuccessful = false;
			return m_initSuccessful;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, conf::g_glMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, conf::g_glMinor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Create a windowed mode window and its OpenGL context */
		printf("Initializing window...\n");
		m_window = glfwCreateWindow(m_windowWidth,
									m_windowHeight,
									m_windowTitle.c_str(), nullptr, nullptr);
		if(!m_window)
		{
			printf("ERROR: Couldn't create the window!\n");
			m_initSuccessful = false;
			glfwTerminate();
			return m_initSuccessful;
		}

		/* Make the window's context current */
		makeContextCurrent();

		/* Init GLEW */
		printf("Initializing GLEW...\n");
		const GLenum glewError = glewInit();
		if(glewError != GLEW_OK)
		{
			printf("ERROR: Couldn't init GLEW: \n");
			printf("Error: %p\n", glewGetErrorString(glewError));
			m_initSuccessful = false;
			return m_initSuccessful;
		}

		initCallbacks();
		initOpenGl();

		return m_initSuccessful;
	}

	void Window::mainLoopImpl()
	{
		const auto timeDelta = static_cast<float>(m_timer.getTimeDelta());

		windowTick(timeDelta);
		tick(timeDelta);
		m_timer.resetTimeDelta();
		render();

		/* Poll for and process events */
		m_eventSystem.pollEvents();
	}

	void Window::initCallbacks()
	{
		printf("Initializing Callbacks...\n");
		glfwSetWindowUserPointer(m_window, this);

		// Error callback
		glfwSetErrorCallback(Window::errorCallback);

		// Install all other devices (keyboard, mouse etc.)
		m_eventSystem.getDeviceRegistry().installAll();

		// Joystick
		/// \todo Create joystick device and add entry in DeviceRegistry

		// Window callbacks
		glfwSetDropCallback(m_window, Window::dropCallback);
		glfwSetFramebufferSizeCallback(m_window, Window::resizeCallback);
		glfwSetWindowFocusCallback(m_window, Window::focusCallback);
		glfwSetWindowCloseCallback(m_window, Window::closeCallback);
	}

	void Window::dropCallback(GLFWwindow* window, int count, const char** paths)
	{
		InputEvent inputEvent(InputType::drop);
		auto& dropEvent = inputEvent.m_event.m_drop;

		dropEvent = DropEvent(0, 0,
							  window,
							  count, paths);

		auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->getEventSystem();
		inputObserver.dispatchEvent(inputEvent);
	}

	void Window::resizeCallback(GLFWwindow* window, int width, int height)
	{
		static_cast<Window*>(glfwGetWindowUserPointer(window))->resizeWindow(window, width, height);

		InputEvent inputEvent(InputType::resize);
		auto& displayEvent = inputEvent.m_event.m_display;

		displayEvent = DisplayEvent(window, 0, 0, width, height);

		auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->getEventSystem();
		inputObserver.dispatchEvent(inputEvent);
	}

	void Window::focusCallback(GLFWwindow* window, int focused)
	{
		InputEvent inputEvent;
		auto& displayEvent = inputEvent.m_event.m_display;

		displayEvent = DisplayEvent(window, 0, 0, 0, 0);

		auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->getEventSystem();
		if(focused == GLFW_TRUE)
		{
			inputEvent.m_type = InputType::gained_focus;
		}
		else if(focused == GLFW_FALSE)
		{
			inputEvent.m_type = InputType::lost_focus;
		}
		inputObserver.dispatchEvent(inputEvent);
	}

	void Window::closeCallback(GLFWwindow* window)
	{
		InputEvent inputEvent(InputType::closed);
			auto& displayEvent = inputEvent.m_event.m_display;

			displayEvent = DisplayEvent(window, 0, 0, 0, 0);
		
			auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->getEventSystem();
			inputObserver.dispatchEvent(inputEvent);
	}


	void Window::initOpenGl()
	{
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT, GL_LINE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Window::initAgui()
	{
	}

	glm::ivec2 Window::getWindowResolution() const
	{
		glm::ivec2 resolution;
		glfwGetFramebufferSize(m_window, &resolution.x, &resolution.y);
		return resolution;
	}

	glm::ivec2 Window::getWindowPosition() const
	{
		glm::ivec2 position;
		glfwGetWindowPos(m_window, &position.x, &position.y);
		return position;
	}

	void Window::tick(const float timeDelta)
	{
	}

	void ec::Window::windowTick(const float timeDelta)
	{
		m_eventSystem.informAll();
		m_sceneSystem.tick(timeDelta);
	}

	void Window::goFullscreen()
	{
		auto* monitor = glfwGetPrimaryMonitor();
		if(!monitor)
		{
			return;
		}
		m_windowedResolutionLast = getWindowResolution();
		m_windowPositionLast = getWindowPosition();

		const auto mode = glfwGetVideoMode(monitor);
		const auto width = mode->width;
		const auto height = mode->height;
		glfwSetWindowMonitor(m_window, monitor, 0, 0, width, height, GLFW_DONT_CARE);
	}

	void Window::closeWindow() const
	{
		glfwSetWindowShouldClose(m_window, GLFW_TRUE);
	}

	void Window::setClearColor(const glm::vec4& clearColor)
	{
		m_clearColor = clearColor;
	}

	const glm::vec4& Window::getClearColor() const
	{
		return m_clearColor;
	}

	GLFWwindow* Window::getWindow() const
	{
		return m_window;
	}
}