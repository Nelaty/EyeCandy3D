#include "EC3D/Core/Window.h"
#include "EC3D/Common/Config.h"
#include "EC3D/Core/InputEvent.h"

#include "EC3D/Core/EventQueue.h"
#include "EC3D/Core/EventSource.h"

#include "EC3D/Utilities/Profiler.h"

#include <gl/glew.h>
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
		m_deviceRegistry{this},
		m_clearColor{0.5,0.5,0.5,1.0},
		m_initSuccessful{false}
	{
		init();

		m_eventQueue = std::make_unique<EventQueue>();
		m_eventSource = std::make_unique<EventSource>();

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

		printVersions();

		if(!m_initSuccessful)
		{
			throw(std::exception("Error: Couldn't initialize window!\n"));
		}
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

	void Window::errorCallback(int error, const char* description)
	{
		printf("ERROR: %s\n", description);
	}

	void Window::resizeWindow(GLFWwindow* window, int width, int height)
	{
		m_windowWidth = width;
		m_windowHeight = height;
	}

	ec::InputObservable& Window::getInputObserver()
	{
		return m_inputObservable;
	}

	ec::ShaderManager& Window::getShaderManager()
	{
		return m_shaderManager;
	}

	ec::SceneSystem& Window::getSceneSystem()
	{
		return m_sceneSystem;
	}

	ec::EventQueue* Window::getEventQueue()
	{
		return m_eventQueue.get();
	}

	void Window::switchToFaceMode()
	{
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void Window::switchToWireframeMode()
	{
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void Window::switchToPointMode()
	{
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}

	void Window::goWindowed()
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
		glfwMakeContextCurrent(m_window);

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
		glfwPollEvents();
	}

	void Window::initCallbacks()
	{
		printf("Initializing Callbacks...\n");
		glfwSetWindowUserPointer(m_window, this);

		// Error callback
		glfwSetErrorCallback(Window::errorCallback);

		// Install all other devices (keyboard, mouse etc.)
		m_deviceRegistry.installAll();

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

		auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->getInputObserver();
		inputObserver.receiveEvent(inputEvent);
	}

	void Window::resizeCallback(GLFWwindow* window, int width, int height)
	{
		static_cast<Window*>(glfwGetWindowUserPointer(window))->resizeWindow(window, width, height);

		InputEvent inputEvent(InputType::resize);
		auto& displayEvent = inputEvent.m_event.m_display;

		displayEvent = DisplayEvent(window, 0, 0, width, height);

		auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->getInputObserver();
		inputObserver.receiveEvent(inputEvent);
	}

	void Window::focusCallback(GLFWwindow* window, int focused)
	{
		InputEvent inputEvent;
		auto& displayEvent = inputEvent.m_event.m_display;

		displayEvent = DisplayEvent(window, 0, 0, 0, 0);

		auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->getInputObserver();
		if(focused == GLFW_TRUE)
		{
			inputEvent.m_type = InputType::gained_focus;
		}
		else if(focused == GLFW_FALSE)
		{
			inputEvent.m_type = InputType::lost_focus;
		}
		inputObserver.receiveEvent(inputEvent);
	}

	void Window::closeCallback(GLFWwindow* window)
	{
		InputEvent inputEvent(InputType::closed);
			auto& displayEvent = inputEvent.m_event.m_display;

			displayEvent = DisplayEvent(window, 0, 0, 0, 0);
		
			auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->getInputObserver();
			inputObserver.receiveEvent(inputEvent);
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

	void Window::printVersions() const
	{
		auto major = 0;
		auto minor = 0;

		sscanf_s(reinterpret_cast<const char*>(glGetString(GL_VERSION)), "%d.%d", &major, &minor);
		
		printf("LIBRARY VERSIONS\n\n");
		printf("OpenGL v%d.%d\n", major, minor);
		printf("GLEW v%p\n", glewGetString(GLEW_VERSION));
		printf("GLFW v%d.%d.%d\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
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

	void ec::Window::windowTick(float timeDelta)
	{
		m_inputObservable.informAll();
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

	void Window::closeWindow()
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

	ec::EventSource* Window::getEventSource() const
	{
		return m_eventSource.get();
	}

}