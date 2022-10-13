#include "ExampleWindow.h"
#include "ExampleScene.h"

#include "ec3/Scene.h"
#include "ec3/Node.h"
#include "ec3/Graphics/Drawable.h"
#include "ec3/Graphics/Geometry/CubeGeometry.h"
#include "ec3/Graphics/Material/Material.h"
#include "ec3/Graphics/Camera.h"
#include "ec3/Frame.h"
#include "ec3/Graphics/Geometry/DynamicLineGeometry.h"

#include "ec3/SceneRenderer.h"
#include "ec3/Graphics/Shader/Shader.h"

#include <memory>

using namespace ec;

ExampleWindow::ExampleWindow(const unsigned width, 
							 const unsigned height,
							 const std::string& windowTitle)
	: Window(width, height, windowTitle)
{
	initShaders();
	initScenes();

	initGeometries();

	//dynamicGeoTest();
	// Render everything as a wire frame
	// SwitchToWireframeMode();
	
	//->setIcon("icon.png");// , "icon_small.png");
}

ExampleWindow::~ExampleWindow() = default;

void ExampleWindow::tick(float timeDelta)
{
	m_cameraController.tick(timeDelta);
	//m_cameraController2.Tick(timeDelta);
}

void ExampleWindow::initCameras()
{
	// Create first camera
	m_camera = new ec::Camera(m_exampleScene);
	m_camera->setFov(glm::radians(60.0f));
	m_camera->setTranslation(glm::vec3(0.0f, 0.0f, 10.0f));

	m_cameraController.setCamera(m_camera);
	m_eventSystem.registerInputListener(&m_cameraController);

	// Create a second camera
	m_camera2 = new ec::Camera(m_exampleScene);
	m_camera2->setFov(glm::radians(60.0f));
	m_camera2->setTranslation(glm::vec3(0.0f, 0.0f, 30.0f));
	
	//m_cameraController2.SetCamera(m_camera2);
	//m_inputObservable.RegisterInputListener(&m_cameraController2);

	// Create a third camera
	m_camera3 = new ec::Camera(m_exampleScene);
	m_camera3->setFov(glm::radians(60.0f));
	m_camera3->rotateY(glm::radians(-180.0f));
	m_camera3->setTranslation(glm::vec3(0.0f, 0.0f, -30.0f));

	// Init camera viewports
	//m_camera->setViewport(Viewport(glm::vec2(0.0, 0.0), glm::vec2(1.0f, 1.0f)));
	m_camera->setViewport(Viewport(glm::vec2(0.0, 0.0), glm::vec2(0.75f, 1.0f)));
	m_camera2->setViewport(Viewport(glm::vec2(0.75, 0.5), glm::vec2(0.25f, 0.5f)));
	m_camera3->setViewport(Viewport(glm::vec2(0.75, 0.0), glm::vec2(0.25f, 0.5f)));


	// Init gui
    /*
    	const auto& guiSystem = m_camera->getGuiSystem();

	auto gui = std::make_unique<ExampleGui>();
	gui->setGraphics(guiSystem.getGraphicsHandler());
	gui->setInput(guiSystem.getInputHandler());
	gui->init();
	m_camera->getGuiSystem().setModel(std::move(gui));
	*/

	// Init frame, which is a collection of the previously created cameras
	Frame exampleFrame;
	exampleFrame.addCameraBack(m_camera);
	exampleFrame.addCameraBack(m_camera2);
	exampleFrame.addCameraBack(m_camera3);

	// Create a renderer, which uses the frame from the last step
	m_exampleRenderer = new SceneRenderer();
	m_exampleRenderer->setFrame(exampleFrame);

	// Register the scene renderer with the main renderer
	m_renderer->registerSceneRenderer("example", m_exampleRenderer);
	// Tell the main renderer to use the example scene renderer, 
	// which was registered in the last step.
	m_renderer->changeRenderer("example");
}

void ExampleWindow::initScenes()
{
	m_exampleScene = new ExampleScene("example", this);
	m_sceneSystem.registerScene(m_exampleScene);

	initCameras();

	// Add drawable to camera
	auto* shader = m_shaderManager.getShader("basic");
	auto* cubeMesh = new CubeGeometry(1.0f);
	m_woodMat = new Material();
	m_woodMat->addDiffuseTextureFromPath("./Resources/Textures/wall_02.jpg");

	auto* cameraDrawable = new Drawable(cubeMesh, m_woodMat, shader);
	//m_camera->AddDrawable(cameraDrawable);

	auto* root = m_exampleScene->getRoot();
	root->addChild(m_camera);

	auto* blockNode = new Node();
	blockNode->addDrawable(cameraDrawable);
	blockNode->translateZ(-6);
	m_camera->addChild(blockNode);
}

void ExampleWindow::initShaders()
{
	const std::string path = "./Resources/Shaders/";

	m_shaderManager.addShader("basic",
							  path + "basic.vert",
							  path + "basic.frag");

	m_shaderManager.addShader("gui",
							  path + "gui.vert",
							  path + "gui.frag");

	m_shaderManager.addShader("text",
							  path + "text.vert",
							  path + "text.frag");

	m_renderer->init(m_shaderManager.getShader("gui"),
					 m_shaderManager.getShader("text"));
}

void ExampleWindow::dynamicGeoTest()
{
	auto origin = new Node();
	auto endNode = new Node();
	endNode->translateZ(-10);

	auto lineGeo = new DynamicLineGeometry(origin, endNode, 10.0f);
	auto drawable = new Drawable(lineGeo, m_woodMat, m_shaderManager.getShader("basic"));
	origin->addDrawable(drawable);

	auto* root = m_exampleScene->getRoot();
	root->addChild(origin);
	root->addChild(endNode);
}

void ExampleWindow::initGeometries()
{
	
}

void ExampleWindow::initMaterials()
{
	
}

void ExampleWindow::initTextures()
{
}

void ExampleWindow::initDrawables()
{
}
