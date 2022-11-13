#include "ec3/window/window.h"

#include "ec3/common/config.h"
#include "ec3/common/logging.h"
#include "ec3/graphics/shader/shader.h"
#include "ec3/input/input-event.h"
#include "ec3/utilities/profiler.h"

#include "stb/stb_image.h"

#include <utility>
#include <stdexcept>
#include <cstring>

using namespace std::string_literals;

namespace ec {
	Window::Window(const unsigned int windowWidth,
				   const unsigned int windowHeight,
				   std::string windowTitle)
		: m_windowWidth{windowWidth}
        , m_windowHeight{windowHeight}
        , m_windowTitle{std::move(windowTitle)}
		, m_sceneSystem{this}
		, m_eventSystem{this}
		, m_clearColor{0.5,0.5,0.5,1.0}
		, m_initSuccessful{false}
	{
		m_renderer = std::make_unique<Renderer>();

		init();

		m_frameInterval = 1.0 / 100.0;

		m_windowedResolutionLast = getResolution();
		m_windowPositionLast = getPosition();
	}

	Window::~Window()
    {
    }

	void Window::init()
	{
        Logger::info("(START) Window Initialization");

		m_initSuccessful = initImpl();
		
		if(m_initSuccessful) 
            Logger::info("(END) Window initialization: Success");
		else 
            Logger::error("(END) Window initialization: Error");

		if(!m_initSuccessful)
		{
			throw std::runtime_error("Error: Couldn't initialize window!");
		}
	}

	void Window::makeContextCurrent() const
	{
		glfwMakeContextCurrent(m_window);
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

		// Update shaders
		const auto timeDelta = static_cast<float>(m_timer.getTimeDelta());
		const auto time = static_cast<float>(m_timer.getTime());
		m_shaderManager.update(time, timeDelta);

		// Render everything in this window
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);

		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_BLEND); // Enable blending for water transparency

		m_renderer->render(this);

		glDisable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);

		// Swap front and back buffers
		glfwSwapBuffers(m_window);
	}

	void Window::setFrameRate(const double fps)
	{
		m_frameRate = fps;
		m_frameInterval = 1.0 / fps;
	}

	void Window::errorCallback(const int error, const char* description)
	{
		Logger::error("Window callback: "s + std::to_string(error) + " " + description);
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
		Logger::info("(...) GLFW initialization");
        glfwSetErrorCallback(Window::errorCallback);
		if(!glfwInit())
		{
            Logger::info("(...) GLFW initialization: Error");
			m_initSuccessful = false;
			return m_initSuccessful;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, conf::g_glMajor);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, conf::g_glMinor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Create a windowed mode window and its OpenGL context */
        Logger::info("(...) Window creation");
		m_window = glfwCreateWindow(m_windowWidth,
									m_windowHeight,
									m_windowTitle.c_str(), nullptr, nullptr);
		if(!m_window)
		{
            Logger::info("(...) Window creation: Error");
			m_initSuccessful = false;
			glfwTerminate();
			return m_initSuccessful;
		}

		/* Make the window's context current */
		makeContextCurrent();

		/* Init GLEW */
		Logger::info("(...) GLEW initialization");
		const GLenum glewError = glewInit();
		if(glewError != GLEW_OK)
		{
		    Logger::info("(...) GLEW initialization: Error "s + std::to_string(static_cast<int>(glewError)) + ": " 
                         + reinterpret_cast<const char*>(glewGetErrorString(glewError)));
			m_initSuccessful = false;
			return m_initSuccessful;
		}

		m_callbacks.init(m_window, this);
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

	glm::ivec2 Window::getResolution() const
	{
		glm::ivec2 resolution;
		glfwGetFramebufferSize(m_window, &resolution.x, &resolution.y);
		return resolution;
	}

	void Window::setAspectRatio(const int numerator, const int denominator) const
	{
		glfwSetWindowAspectRatio(m_window, numerator, denominator);
	}

	void Window::setSizeLimits(int widthMin,
	                           int heightMin,
	                           int widthMax,
	                           int heightMax) const
	{
		widthMin = widthMin < 0 ? GLFW_DONT_CARE : widthMin;
		heightMin = heightMin < 0 ? GLFW_DONT_CARE : heightMin;
		widthMax = widthMax < 0 ? GLFW_DONT_CARE : widthMax;
		heightMax = heightMax < 0 ? GLFW_DONT_CARE : heightMax;
		
		glfwSetWindowSizeLimits(m_window, widthMin, heightMin, widthMax, heightMax);
	}	

	glm::ivec2 Window::getPosition() const
	{
		glm::ivec2 position;
		glfwGetWindowPos(m_window, &position.x, &position.y);
		return position;
	}

	void Window::setPosition(const int x, const int y) const
	{
		glfwSetWindowPos(m_window, x, y);
	}

	glm::ivec2 Window::getSize() const
	{
		glm::ivec2 size;
		glfwGetWindowSize(m_window, &size.x, &size.y);
		return size;
	}

	void Window::setSize(const int width, const int height)
	{
		glfwSetWindowSize(m_window, width, height);
	}

	glm::ivec4 Window::getFrameSize() const
	{
		glm::ivec4 size;
		glfwGetWindowFrameSize(m_window, &size.x, &size.y, &size.z, &size.w);
		return size;
	}

	glm::ivec2 Window::getFrameBufferSize() const
	{
		glm::ivec2 size;
		glfwGetFramebufferSize(m_window, &size.x, &size.y);
		return size;
	}

	void Window::setIcon(const char* iconPath, const char* iconPathSmall) const
	{
		GLFWimage images[2];
		auto count = 0;
		count = strcmp(iconPath, "") == 0 ? count : count + 1;
		count = strcmp(iconPathSmall, "") == 0 ? count : count + 1;

		if(count == 0)
		{
			glfwSetWindowIcon(m_window, 0, nullptr);
			return;
		}

		int nrComponents;
		images[0].pixels = stbi_load(iconPath, &images[0].width, &images[0].height, &nrComponents, 0);
		if(count == 2)
		{
			images[1].pixels = stbi_load(iconPathSmall, &images[1].width, &images[1].height, &nrComponents, 0);
		}

		glfwSetWindowIcon(m_window, count, images);

		stbi_image_free(images[0].pixels);
		if(count == 2)
		{
			stbi_image_free(images[1].pixels);
		}
	}

	void Window::setTitle(const char* title) const
	{
		glfwSetWindowTitle(m_window, title);
	}

	void Window::focus() const
	{
		glfwFocusWindow(m_window);
	}

	bool Window::isFocused() const
	{
		return glfwGetWindowAttrib(m_window, GLFW_FOCUSED);
	}

	bool Window::isMinimized() const
	{
		return glfwGetWindowAttrib(m_window, GLFW_ICONIFIED);
	}

	bool Window::isMaximized() const
	{
		return glfwGetWindowAttrib(m_window, GLFW_MAXIMIZED);
	}

	bool Window::isResizable() const
	{
		return glfwGetWindowAttrib(m_window, GLFW_RESIZABLE);
	}

	bool Window::isDecorated() const
	{
		return glfwGetWindowAttrib(m_window, GLFW_DECORATED);
	}

	bool Window::isFloating() const
	{
		return glfwGetWindowAttrib(m_window, GLFW_FLOATING);
	}

	void Window::restore() const
	{
		glfwRestoreWindow(m_window);
	}

	void Window::minimize() const
	{
		glfwIconifyWindow(m_window);
	}

	void Window::show() const
	{
		glfwShowWindow(m_window);
	}

	void Window::hide() const
	{
		glfwHideWindow(m_window);
	}

	bool Window::isVisible() const
	{
		return glfwGetWindowAttrib(m_window, GLFW_VISIBLE);
	}

	int Window::getContextApi() const
	{
		return glfwGetWindowAttrib(m_window, GLFW_CLIENT_API);
	}

	int Window::getContextCreationApi() const
	{
		return glfwGetWindowAttrib(m_window, GLFW_CONTEXT_CREATION_API);
	}

	std::array<int, 3> Window::getContextVersion() const
	{
		std::array<int, 3> version{};
		version[0] = glfwGetWindowAttrib(m_window, GLFW_VERSION_MAJOR);
		version[1] = glfwGetWindowAttrib(m_window, GLFW_VERSION_MINOR);
		version[2] = glfwGetWindowAttrib(m_window, GLFW_VERSION_REVISION);
		return version;
	}

	bool Window::isOpenGlForwardCompatible() const
	{
		return glfwGetWindowAttrib(m_window, GLFW_OPENGL_FORWARD_COMPAT);
	}

	bool Window::isOpenGlDebugContext() const
	{
		return glfwGetWindowAttrib(m_window, GLFW_OPENGL_DEBUG_CONTEXT);
	}

	int Window::getOpenGlProfile() const
	{
		return glfwGetWindowAttrib(m_window, GLFW_OPENGL_CORE_PROFILE);
	}

	int Window::getContextRobustnessStrategies() const
	{
		return glfwGetWindowAttrib(m_window, GLFW_CONTEXT_ROBUSTNESS);
	}

	int Window::getRedBits()
	{
		int value;
		glGetIntegerv(GL_RED_BITS, &value);
		return value;
	}

	int Window::getGreenBits()
	{
		int value;
		glGetIntegerv(GL_GREEN_BITS, &value);
		return value;
	}

	int Window::getBlueBits()
	{
		int value;
		glGetIntegerv(GL_BLUE_BITS, &value);
		return value;
	}

	int Window::getAlphaBits()
	{
		int value;
		glGetIntegerv(GL_ALPHA_BITS, &value);
		return value;
	}

	int Window::getDepthBits()
	{
		int value;
		glGetIntegerv(GL_DEPTH_BITS, &value);
		return value;
	}

	int Window::getStencilBits()
	{
		int value;
		glGetIntegerv(GL_STENCIL_BITS, &value);
		return value;
	}

	int Window::getMsaaSamples()
	{
		int value;
		glGetIntegerv(GL_SAMPLES, &value);
		return value;
	}

	void Window::swapBuffers() const
	{
		glfwSwapBuffers(m_window);
	}

	void Window::setSwapInterval(const unsigned int interval)
	{
		glfwSwapInterval(interval);
	}

	void Window::setClipboardString(const char* str) const
	{
		glfwSetClipboardString(m_window, str);
	}

	const char* Window::getClipboardString() const
	{
		return glfwGetClipboardString(m_window);
	}

	GLFWmonitor* Window::getPrimaryMonitor()
	{
		return glfwGetPrimaryMonitor();
	}

	GLFWmonitor** Window::getMonitors(int* count)
	{
		return glfwGetMonitors(count);
	}

	const GLFWvidmode* Window::getVideoMode(GLFWmonitor* monitor)
	{
		return glfwGetVideoMode(monitor);
	}

	const GLFWvidmode* Window::getVideoModes(GLFWmonitor* monitor, int* count)
	{
		return glfwGetVideoModes(monitor, count);
	}

	glm::ivec2 Window::getMonitorPhysicalSize(GLFWmonitor* monitor)
	{
		glm::ivec2 result{};
		glfwGetMonitorPhysicalSize(monitor, &result.x, &result.y);
		return result;
	}

	glm::ivec2 Window::getMonitorPosition(GLFWmonitor* monitor)
	{
		glm::ivec2 result{};
		glfwGetMonitorPos(monitor, &result.x, &result.y);
		return result;
	}

	const char* Window::getMonitorName(GLFWmonitor* monitor)
	{
		return glfwGetMonitorName(monitor);
	}

	void Window::printMonitorInformation()
	{
		int count;
		auto monitors = Window::getMonitors(&count);
		for(int i = 0; i < count; ++i)
		{
			auto* m = monitors[i];
			auto name = Window::getMonitorName(m);
			auto size = Window::getMonitorPhysicalSize(m);
			auto pos = Window::getMonitorPosition(m);
			printf("(%d) %s | Position: (%d,%d) | Size: %.2fcm x %.2fcm)\n",
				   i, name, pos.x, pos.y, size.x * 0.1f, size.y * 0.1f);
		}
	}

	void Window::setGammaRamp(GLFWmonitor* monitor, const float exponent)
	{
		glfwSetGamma(monitor, exponent);
	}

	void Window::setGammaRamp(GLFWmonitor* monitor,
	                          const int size,
							  unsigned short* red,
							  unsigned short* green,
							  unsigned short* blue)
	{
		GLFWgammaramp ramp;
		ramp.size = size;
		ramp.red = red;
		ramp.green = green;
		ramp.blue = blue;
		glfwSetGammaRamp(monitor, &ramp);
	}

	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose(m_window);
	}

	void Window::destroy() const
	{
		glfwDestroyWindow(m_window);
	}

	void Window::tick(const float timeDelta)
	{
	}

	void ec::Window::windowTick(const float timeDelta)
	{
		const auto time = static_cast<float>(m_timer.getTime());

		m_eventSystem.informAll();
		m_sceneSystem.tick(timeDelta);
		m_shaderManager.update(time, timeDelta);
		m_renderer->tick();
	}

	void Window::goFullscreen()
	{
		auto* monitor = glfwGetPrimaryMonitor();
		if(!monitor)
		{
			return;
		}
		m_windowedResolutionLast = getResolution();
		m_windowPositionLast = getPosition();

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

	Window* Window::getCurrentWindow()
	{
		auto* window = glfwGetCurrentContext();
		return static_cast<Window*>(glfwGetWindowUserPointer(window));
	}
    bool Window::isInitialized() const
    {
        return m_initSuccessful;
    }
}
