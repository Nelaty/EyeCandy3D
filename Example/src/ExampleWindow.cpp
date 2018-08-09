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
#include "EC3D/Core/Scene.h"

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
	__super::Tick(timeDelta);

	if(m_activeScene)
	{
		m_activeScene->Tick(timeDelta);
	}

	m_cameraController.Tick(timeDelta);
	//m_cameraController2.Tick(timeDelta);
}

void ExampleWindow::InitCamera()
{
	m_camera = new ec::Camera(m_exampleScene);
	m_camera->SetNear(0.01f);
	m_camera->SetFar(1000.0f);
	m_camera->SetFOV(glm::radians(60.0f));
	m_camera->SetTranslation(glm::vec3(0.0f, 0.0f, 10.0f));
	//m_camera->RotateY(glm::radians(-90.0f));

	m_cameraController.SetCamera(m_camera);
	m_inputObservable.RegisterInputController(&m_cameraController);

	//////////////////////////////////////////////////////////////////////////
	/// TEST
	m_camera2 = new ec::Camera(m_exampleScene);
	m_camera2->SetNear(0.01f);
	m_camera2->SetFar(1000.0f);
	m_camera2->SetFOV(glm::radians(60.0f));
	m_camera2->SetTranslation(glm::vec3(0.0f, 0.0f, 30.0f));
	//cam->RotateY(glm::radians(-90.0f));
	
	//m_cameraController2.SetCamera(m_camera2);
	//m_inputObservable.RegisterInputController(&m_cameraController2);




	m_camera3 = new ec::Camera(m_exampleScene);
	m_camera3->SetNear(0.01f);
	m_camera3->SetFar(1000.0f);
	m_camera3->SetFOV(glm::radians(60.0f));
	m_camera3->RotateX(glm::radians(-45.0f));
	m_camera3->SetTranslation(glm::vec3(0.0f, 15.0f, 20.0f));
	//////////////////////////////////////////////////////////////////////////
}

void ExampleWindow::InitScenes()
{
	m_exampleScene = new ExampleScene("example");

	m_sceneSystem.RegisterScene(m_exampleScene);
	
	ConstructTestSG();
	SphereTest();

	InitCamera();

	// Init camera viewports
	ec::Viewport view(glm::vec2(0.0, 0.0), glm::vec2(0.75f, 1.0f));
	m_camera->SetViewport(view);
	ec::Viewport view2(glm::vec2(0.75, 0.5), glm::vec2(0.25f, 0.5f));
	m_camera2->SetViewport(view2);
	ec::Viewport view3(glm::vec2(0.75, 0.0), glm::vec2(0.25f, 0.5f));
	m_camera3->SetViewport(view3);


	// Init frame
	Frame exampleFrame;
	exampleFrame.AddCamera(m_camera);
	exampleFrame.AddCamera(m_camera2);
	exampleFrame.AddCamera(m_camera3);

	// Init Renderer
	m_exampleRenderer = new SceneRenderer();
	m_exampleRenderer->SetFrame(exampleFrame);

	m_renderer.RegisterSceneRenderer("example", m_exampleRenderer);
	m_renderer.ChangeRenderer("example");
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

void ExampleWindow::ConstructTestSG()
{
	CubeMesh* cubeMesh = new CubeMesh(1.0f);
	Shader* shader = m_shaderManager.GetShader("basic");
	Material* woodMat = new Material();
	woodMat->AddDiffuseTextureFromPath("Resources/Textures/wood.jpg");
	Material* wallMat00 = new Material();
	wallMat00->AddDiffuseTextureFromPath("Resources/Textures/wall_00.jpg");
	Material* wallMat01 = new Material();
	wallMat01->AddDiffuseTextureFromPath("Resources/Textures/wall_01.jpg");

	Drawable* woodCube = new Drawable(cubeMesh, woodMat, shader);
	Drawable* wall00Cube = new Drawable(cubeMesh, wallMat00, shader);
	Drawable* wall01Cube = new Drawable(cubeMesh, wallMat01, shader);

	Node* left = new Node(nullptr);
	Node* right = new Node(nullptr);
	Node* backside = new Node(nullptr);
	Node* bottom = new Node(nullptr);

	float translation = 5;
	float width = 0.1f;
	float height = 10.0f;
	float length = 10.0f;

	left->AddDrawable(wall01Cube);
	left->TranslateX(-translation);
	left->Scale(glm::vec3(width, height, length));

	right->AddDrawable(wall01Cube);
	right->TranslateX(translation);
	right->Scale(glm::vec3(width, height, length));

	backside->AddDrawable(wall00Cube);
	backside->TranslateZ(-translation);
	backside->Scale(glm::vec3(length, height, width));

	bottom->AddDrawable(woodCube);
	bottom->TranslateY(-translation);
	bottom->Scale(glm::vec3(height, width, length));

	auto* rootNode = m_exampleScene->GetRoot();
	rootNode->AddChild(left);
	rootNode->AddChild(right);
	rootNode->AddChild(bottom);
	rootNode->AddChild(backside);
}

void ExampleWindow::SphereTest()
{
	SphereMesh* sphereMesh = new SphereMesh(1.0f, 20, 20);
	Shader* shader = m_shaderManager.GetShader("basic");
	Material* woodMat = new Material();
	woodMat->AddDiffuseTextureFromPath("Resources/Textures/melon2.jpg");

	Drawable* sphereDrawable = new Drawable(sphereMesh, woodMat, shader);
	Node* sphereNode = new Node(nullptr);

	sphereNode->AddDrawable(sphereDrawable);

	auto* rootNode = m_exampleScene->GetRoot();
	rootNode->AddChild(sphereNode);
}
