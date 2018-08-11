#include "ExampleWindow.h"
#include "ExampleScene.h"

#include "EC3D/Core/Scene.h"
#include "EC3D/Core/Node.h"
#include "EC3D/Core/Drawable.h"
#include "EC3D/Core/CubeMesh.h"
#include "EC3D/Core/SphereMesh.h"
#include "EC3D/Core/Material.h"
#include "EC3D/Core/Camera.h"
#include "EC3D/Core/Frame.h"
#include "EC3D/Core/SceneRenderer.h"
#include "EC3D/Core/Shader/Shader.h"

using namespace ec;

ExampleWindow::ExampleWindow(int width, int height, const char* windowTitle)
	: Window(width, height, windowTitle)
{
	InitShaders();
	InitScenes();

	// SwitchToWireframeMode();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::Tick(const float timeDelta)
{
	m_cameraController.Tick(timeDelta);
	//m_cameraController2.Tick(timeDelta);
}

void ExampleWindow::InitCameras()
{
	// Create first camera
	m_camera = new ec::Camera(m_exampleScene);
	m_camera->SetFOV(glm::radians(60.0f));
	m_camera->SetTranslation(glm::vec3(0.0f, 0.0f, 10.0f));

	m_cameraController.SetCamera(m_camera);
	m_inputObservable.RegisterInputListener(&m_cameraController);

	// Create a second camera
	m_camera2 = new ec::Camera(m_exampleScene);
	m_camera2->SetFOV(glm::radians(60.0f));
	m_camera2->SetTranslation(glm::vec3(0.0f, 0.0f, 30.0f));
	
	// Create a third camera
	m_camera3 = new ec::Camera(m_exampleScene);
	m_camera3->SetFOV(glm::radians(60.0f));
	m_camera3->RotateY(glm::radians(-180.0f));
	m_camera3->SetTranslation(glm::vec3(0.0f, 0.0f, -30.0f));

	// Init camera viewports
	ec::Viewport view(glm::vec2(0.0, 0.0), glm::vec2(0.75f, 1.0f));
	m_camera->SetViewport(view);
	ec::Viewport view2(glm::vec2(0.75, 0.5), glm::vec2(0.25f, 0.5f));
	m_camera2->SetViewport(view2);
	ec::Viewport view3(glm::vec2(0.75, 0.0), glm::vec2(0.25f, 0.5f));
	m_camera3->SetViewport(view3);

	// Init frame, which is a collection of the previously created cameras
	Frame exampleFrame;
	exampleFrame.AddCamera(m_camera);
	exampleFrame.AddCamera(m_camera2);
	exampleFrame.AddCamera(m_camera3);

	// Create a renderer, which uses the frame from the last step
	m_exampleRenderer = new SceneRenderer();
	m_exampleRenderer->SetFrame(exampleFrame);

	// Register the scene renderer with the main renderer
	m_renderer.RegisterSceneRenderer("example", m_exampleRenderer);
	// Tell the main renderer to use the example scene renderer, 
	// which was registered in the last step.
	m_renderer.ChangeRenderer("example");
}

void ExampleWindow::InitScenes()
{
	m_exampleScene = new ExampleScene("example", this);
	m_sceneSystem.RegisterScene(m_exampleScene);

	InitCameras();

	// Add drawable to camera
	Shader* shader = m_shaderManager.GetShader("basic");
	CubeMesh* cubeMesh = new CubeMesh(1.0f);
	Material* woodMat = new Material();
	woodMat->AddDiffuseTextureFromPath("Resources/Textures/wall_02.jpg");

	Drawable* cameraDrawable = new Drawable(cubeMesh, woodMat, shader);
	//m_camera->AddDrawable(cameraDrawable);

	auto* root = m_exampleScene->GetRoot();
	root->AddChild(m_camera);

	Node* blockNode = new Node(nullptr);
	blockNode->AddDrawable(cameraDrawable);
	blockNode->TranslateZ(-6);
	m_camera->AddChild(blockNode);
}

void ExampleWindow::InitShaders()
{
	std::string path = "Resources/Shaders/";

	m_shaderManager.AddShader("basic",
							  path + "basic.vert",
							  path + "basic.frag");

	m_shaderManager.AddShader("gui",
							  path + "gui.vert",
							  path + "gui.frag");

	m_shaderManager.AddShader("text",
							  path + "text.vert",
							  path + "text.frag");
}