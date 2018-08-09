#include "EC3D/Core/Window.h"
#include "EC3D/Common/Config.h"
#include "EC3D/Core/InputEvent.h"

#include "EC3D/Utilities/Profiler.h"

#include <gl/glew.h>
#include <sstream>

namespace ec
{
	Window::Window(const unsigned int windowWidth,
				   const unsigned int windowHeight,
				   const char* windowTitle)
		: m_sceneSystem{this},
		m_windowWidth{windowWidth},
		m_windowHeight{windowHeight},
		m_windowTitle{windowTitle},
		m_initSuccessful{false},
		m_clearColor{0.5,0.5,0.5,1.0}
	{
		Init();

		m_frameInterval = 1.0 / 100.0;

		m_windowedResolutionLast = GetWindowResolution();
		m_windowPositionLast = GetWindowPosition();
	}

	Window::~Window()
	{
	}

	void Window::Init()
	{
		printf("\n");
		printf("##############################\n");
		printf("INITIALIZING WINDOW\n\n");

		m_initSuccessful = InitImpl();
		
		if(m_initSuccessful)
		{
			printf("\nINITIALIZATION SUCCESSFUL\n");
		}
		else
		{
			printf("\nERROR: INITIALIZATION UNSUCCESSFUL");
		}
		printf("##############################\n");

		PrintVersions();

		if(!m_initSuccessful)
		{
			throw(std::exception("Error: Couldn't initialize window!\n"));
		}
	}

	void Window::StartMainLoop()
	{
		if(!m_initSuccessful)
		{
			printf("The simulation hasn't been initialized!\n");
			return;
		}

		m_timer.Reset();
		while(!glfwWindowShouldClose(m_window))
		{
			MainLoopImpl();
		}
		glfwTerminate();
	}

	void Window::Render()
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND); // Enable blending for water transparency

		m_renderer.Render(this);

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

		/* Swap front and back buffers */
		glfwSwapBuffers(m_window);
	}

	void Window::SetFrameRate(const double fps)
	{
		m_frameRate = fps;
		m_frameInterval = 1.0 / fps;
	}

	void Window::ErrorCallback(int error, const char* description)
	{
		printf("ERROR: %s\n", description);
	}

	void Window::ResizeCallback(GLFWwindow* window, int width, int height)
	{
		m_windowWidth = width;
		m_windowHeight = height;
	}

	ec::InputObservable& Window::GetInputObserver()
	{
		return m_inputObservable;
	}

	ec::ShaderManager& Window::GetShaderManager()
	{
		return m_shaderManager;
	}

	ec::SceneSystem& Window::GetSceneSystem()
	{
		return m_sceneSystem;
	}

	void Window::SwitchToFaceMode()
	{
		glEnable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

	void Window::SwitchToWireframeMode()
	{
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}

	void Window::SwitchToPointMode()
	{
		glDisable(GL_CULL_FACE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
	}

	void Window::GoWindowed()
	{
		glfwSetWindowMonitor(m_window, nullptr,
							 m_windowPositionLast.x, m_windowPositionLast.y,
							 m_windowedResolutionLast.x, m_windowedResolutionLast.y,
							 GLFW_DONT_CARE);
	}

	bool Window::InitImpl()
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
									m_windowTitle.c_str(), NULL, NULL);
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
		GLenum glewError = glewInit();
		if(glewError != GLEW_OK)
		{
			printf("ERROR: Couldn't init GLEW: \n");
			printf("Error: %s\n", glewGetErrorString(glewError));
			m_initSuccessful = false;
			return m_initSuccessful;
		}

		InitCallbacks();
		InitOpenGL();

		return m_initSuccessful;
	}

	void Window::MainLoopImpl()
	{
		float timeDelta = static_cast<float>(m_timer.GetTimeDelta());

		Tick(timeDelta);
		m_timer.ResetTimeDelta();
		Render();

		/* Poll for and process events */
		glfwPollEvents();
	}

	void Window::InitCallbacks()
	{
		printf("Initializing Callbacks...\n");
		glfwSetWindowUserPointer(m_window, this);
		
		// Error
		glfwSetErrorCallback(Window::ErrorCallback);

		// Mouse
		auto cursorPosCallback = [](GLFWwindow* window, double xpos, double ypos)
		{	
			auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInputObserver();

			const auto& lastMouseButtonEvent = inputObserver.GetLastMouseButtonEvent();
			if(lastMouseButtonEvent.m_pressed)
			{
				glm::vec2 offset(xpos, ypos);
				offset -= inputObserver.GetLastMousePosition();
				inputObserver.SetLastMousePosition(glm::vec2(xpos, ypos));

				InputEvent inputEvent(InputType::mouse_drag);
				inputEvent.m_event.m_drag = MouseDragEvent(window, offset.x, offset.y, xpos, ypos, lastMouseButtonEvent.m_button, lastMouseButtonEvent.m_mods);
				inputObserver.ReceiveEvent(inputEvent);
			}
	
			InputEvent inputEvent(InputType::mouse_move);
			inputEvent.m_event.m_move = MouseMoveEvent(window, xpos, ypos);
			inputObserver.ReceiveEvent(inputEvent);	
		};
		glfwSetCursorPosCallback(m_window, cursorPosCallback);
		
		auto cursorEnterCallback = [](GLFWwindow* window, int entered)
		{
			InputEvent inputEvent(InputType::mouse_enter);
			inputEvent.m_event.m_entered = MouseEnterEvent(window, entered);
			static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInputObserver().ReceiveEvent(inputEvent);
		};
		glfwSetCursorEnterCallback(m_window, cursorEnterCallback);

		auto mouseButtonCallback = [](GLFWwindow* window, int button, int action, int mods)
		{
			if(action == GLFW_PRESS)
			{
				InputEvent inputEvent(InputType::mouse_button_pressed);
				inputEvent.m_event.m_mouse = MouseButtonEvent(window, button, mods, true);
				auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInputObserver();
				inputObserver.ReceiveEvent(inputEvent);
				inputObserver.SetLastMouseButtonEvent(inputEvent.m_event.m_mouse);
			}
			else if(action == GLFW_RELEASE)
			{
				InputEvent inputEvent(InputType::mouse_button_released);
				inputEvent.m_event.m_mouse = MouseButtonEvent(window, button, mods, false);
				auto& inputObserver = static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInputObserver();
				inputObserver.ReceiveEvent(inputEvent);
				inputObserver.SetLastMouseButtonEvent(inputEvent.m_event.m_mouse);
			}
		};
		glfwSetMouseButtonCallback(m_window, mouseButtonCallback);

		auto scrollCallback = [](GLFWwindow* window, double xoffset, double yoffset)
		{
			InputEvent inputEvent(InputType::mouse_scroll);
			inputEvent.m_event.m_scroll = MouseScrollEvent(window, xoffset, yoffset);
			static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInputObserver().ReceiveEvent(inputEvent);
		};
		glfwSetScrollCallback(m_window, scrollCallback);

		// Joystick
		// TODO: Set joystick callback

		// Keyboard
		auto keyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if(action == GLFW_PRESS)
			{
				InputEvent inputEvent(InputType::key_pressed);
				inputEvent.m_event.m_key = KeyEvent(window, key, scancode, mods, true);
				static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInputObserver().ReceiveEvent(inputEvent);
			}
			else if(action == GLFW_RELEASE)
			{
				InputEvent inputEvent(InputType::key_released);
				inputEvent.m_event.m_key = KeyEvent(window, key, scancode, mods, false);
				static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInputObserver().ReceiveEvent(inputEvent);
			}
		};
		glfwSetKeyCallback(m_window, keyCallback);

		// Text
		auto charModsCallback = [](GLFWwindow* window, unsigned int codepoint, int mods)
		{
			InputEvent inputEvent(InputType::text);
			inputEvent.m_event.m_text = TextEvent(window, codepoint, mods);
			static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInputObserver().ReceiveEvent(inputEvent);
		};
		glfwSetCharModsCallback(m_window, charModsCallback);

		// Drag & drop
		auto dropCallback = [](GLFWwindow* window, int count, const char** paths)
		{
			InputEvent inputEvent(InputType::drop);
			inputEvent.m_event.m_drop = DropEvent(window, count, paths);
			static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInputObserver().ReceiveEvent(inputEvent);
		};
		glfwSetDropCallback(m_window, dropCallback);
	
		// Window resize
		auto resizeCallback = [](GLFWwindow* window, int width, int height)
		{
			static_cast<Window*>(glfwGetWindowUserPointer(window))->ResizeCallback(window, width, height);

			InputEvent inputEvent(InputType::resize);
			inputEvent.m_event.m_resize = ResizeEvent(window, width, height);
			static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInputObserver().ReceiveEvent(inputEvent);
		};
		glfwSetFramebufferSizeCallback(m_window, resizeCallback);
	
		// Window focused
		auto focusCallback = [](GLFWwindow* window, int focused)
		{
			if(focused == GLFW_TRUE)
			{
				InputEvent inputEvent(InputType::gained_focus);
				inputEvent.m_event.m_focus = FocusEvent(window, true);
				static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInputObserver().ReceiveEvent(inputEvent);
			}
			else if(focused == GLFW_FALSE)
			{
				InputEvent inputEvent(InputType::lost_focus);
				inputEvent.m_event.m_focus = FocusEvent(window, false);
				static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInputObserver().ReceiveEvent(inputEvent);
			}
		};
		glfwSetWindowFocusCallback(m_window, focusCallback);

		// Window closed
		auto closeCallback = [](GLFWwindow* window)
		{
			InputEvent inputEvent(InputType::closed);
			inputEvent.m_event.m_closed = ClosedEvent(window);
			static_cast<Window*>(glfwGetWindowUserPointer(window))->GetInputObserver().ReceiveEvent(inputEvent);
		};
		glfwSetWindowCloseCallback(m_window, closeCallback);
}

void Window::InitOpenGL()
{
	glEnable(GL_CULL_FACE);
	glPolygonMode(GL_FRONT, GL_LINE);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Window::PrintVersions() const
	{
		int major = 0;
		int minor = 0;

		sscanf_s((const char*)glGetString(GL_VERSION), "%d.%d", &major, &minor);
		
		printf("LIBRARY VERSIONS\n\n");
		printf("OpenGL v%d.%d\n", major, minor);
		printf("GLEW v%s\n", glewGetString(GLEW_VERSION));
		printf("GLFW v%d.%d.%d\n", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR, GLFW_VERSION_REVISION);
	}

	glm::ivec2 Window::GetWindowResolution() const
	{
		glm::ivec2 resolution;
		glfwGetFramebufferSize(m_window, &resolution.x, &resolution.y);
		return resolution;
	}

	glm::ivec2 Window::GetWindowPosition() const
	{
		glm::ivec2 position;
		glfwGetWindowPos(m_window, &position.x, &position.y);
		return position;
	}

	void Window::Tick(const float timeDelta)
	{
		m_inputObservable.InformAll();
	}

	void Window::GoFullscreen()
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		if(!monitor)
		{
			return;
		}
		m_windowedResolutionLast = GetWindowResolution();
		m_windowPositionLast = GetWindowPosition();

		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		int width = mode->width;
		int height = mode->height;
		glfwSetWindowMonitor(m_window, monitor, 0, 0, width, height, GLFW_DONT_CARE);
	}

	void Window::CloseWindow()
	{
		glfwSetWindowShouldClose(m_window, GLFW_TRUE);
	}

	void Window::SetClearColor(const glm::vec4& clearColor)
	{
		m_clearColor = clearColor;
	}

	const glm::vec4& Window::GetClearColor() const
	{
		return m_clearColor;
	}

	GLFWwindow* Window::GetWindow() const
	{
		return m_window;
	}

}