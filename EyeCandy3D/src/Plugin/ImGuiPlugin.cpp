#include "EC3D/Plugin/ImGuiPlugin.h"

#include <gl/glew.h>
#include <GLFW/glfw3.h>

#include "EC3D/Core/Window.h"
#include "EC3D/Common/Config.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"



namespace ec
{
	ImGuiPlugin::ImGuiPlugin()
	{
	}

	ImGuiPlugin::~ImGuiPlugin()
	{
	}

	void ImGuiPlugin::init(Window* window)
	{
		m_window = window;

		// Init imgui
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(m_window->getWindow(), true);
		ImGui_ImplOpenGL3_Init(conf::g_glslVersion);
	}

	void ImGuiPlugin::onBegin()
	{
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiPlugin::onTick(float timeDelta)
	{
	}

	void ImGuiPlugin::onRender(float timeDelta)
	{
		auto glfwWindow = m_window->getWindow();

		ImGui::Render();
		int display_w, display_h;
		glfwGetFramebufferSize(glfwWindow, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiPlugin::onEnd()
	{
	}

	void ImGuiPlugin::cleanup()
	{
	}
}