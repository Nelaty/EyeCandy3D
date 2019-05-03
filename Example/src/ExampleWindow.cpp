#include "ExampleWindow.h"
#include "ExampleScene.h"
#include "ExampleGui.h"

#include "EC3D/Core/Scene.h"
#include "EC3D/Core/Node.h"
#include "EC3D/Core/Drawable.h"
#include "EC3D/Core/Geometry/CubeGeometry.h"
#include "EC3D/Core/Material.h"
#include "EC3D/Core/Camera.h"
#include "EC3D/Core/Geometry/DynamicLineGeometry.h"

#include "EC3D/Core/FrameLayoutUniform.h"
#include "EC3D/Core/Shader/Shader.h"

#include "EC3D/Gui/Backend/OpenGLGraphics.h"
#include "EC3D/Gui/Backend/OpenGLInput.h"

#include <memory>
#include <array>

using namespace ec;

ExampleWindow::ExampleWindow(const unsigned width, 
							 const unsigned height,
							 const std::string& windowTitle)
	: Window(width, height, windowTitle)
{
	initShaders();
	initScenes();

	initGeometries();

	dynamicGeoTest();
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
	m_camera = std::make_shared<ec::Camera>(m_exampleScene);
	m_camera->setFov(glm::radians(60.0f));
	m_camera->setTranslation(glm::vec3(0.0f, 0.0f, 10.0f));

	m_cameraController.setCamera(m_camera.get());
	m_eventSystem.registerInputListener(&m_cameraController);

	
	auto frameLayout = std::make_shared<FrameLayoutUniform>();
	m_frame.setFrameLayout(frameLayout);

	FrameSlot slotMain;
	slotMain.setCamera(m_camera);
	m_frame.addFrameSlot(slotMain);

	// Init gui
	const auto& guiSystem = m_camera->getGuiSystem();

	auto gui = std::make_unique<ExampleGui>();
	gui->setGraphics(guiSystem.getGraphicsHandler());
	gui->setInput(guiSystem.getInputHandler());
	gui->init();
	m_camera->getGuiSystem().setModel(std::move(gui));
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
	m_woodMat->addDiffuseTextureFromPath("../Resources/Textures/wall_02.jpg");

	auto* cameraDrawable = new Drawable(cubeMesh, m_woodMat, shader);
	//m_camera->AddDrawable(cameraDrawable);
}

void ExampleWindow::initShaders()
{
	const std::string path = "../Resources/Shaders/";

	m_shaderManager.addShader("basic",
							  path + "basic.vert",
							  path + "basic.frag");

	m_shaderManager.addShader("gui",
							  path + "gui.vert",
							  path + "gui.frag");

	m_shaderManager.addShader("text",
							  path + "text.vert",
							  path + "text.frag");

	/*m_rendererOld->init(m_shaderManager.getShader("gui"),
					 m_shaderManager.getShader("text"));*/
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
