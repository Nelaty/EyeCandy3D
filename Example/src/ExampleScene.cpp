#include "ExampleScene.h"

#include "EC3D/Core/Window.h"
#include "EC3D/Core/Scene.h"
#include "EC3D/Core/Node.h"
#include "EC3D/Core/Drawable.h"
#include "EC3D/Core/CubeGeometry.h"
#include "EC3D/Core/SphereGeometry.h"
#include "EC3D/Core/CylinderGeometry.h"
#include "EC3D/Core/RectangleGeometry.h"

#include "EC3D/Core/Material.h"
#include "EC3D/Core/Shader/Shader.h"
#include "EC3D/Core/Shader/ShaderManager.h"
#include "EC3D/Utilities/Random.h"
#include "EC3D/Core/CircleGeometry.h"

using namespace ec;

ExampleScene::ExampleScene(const std::string& name, ec::Window* window)
	: Scene(name),
	m_window{window}
{
	init();
}

ExampleScene::~ExampleScene() = default;

void ExampleScene::init()
{
	constructTestSg();
	//sphereTest();
	//cylinderTest();
	rectangleTest();
	//circleTest();
}

void ExampleScene::tick(const float timeDelta)
{
	/*
	float min = 0.0f;
	float max = 0.1f;

	m_right->rotate(ec::Random::randomFloat(min, max),
					ec::Random::randomVec3(0.0f, 1.0f));
	*/
}

void ExampleScene::constructTestSg()
{
	auto& shaderManager = m_window->getShaderManager();	
	Shader* shader = shaderManager.getShader("basic");

	// Create meshes
	auto* cubeMesh = new CubeGeometry(1.0f);

	// Create new materials and load textures
	auto* woodMat = new Material();
	woodMat->addDiffuseTextureFromPath("../Resources/Textures/wood_00.jpg");
	auto* wallMat00 = new Material();
	wallMat00->addDiffuseTextureFromPath("../Resources/Textures/wall_00.jpg");
	auto* wallMat01 = new Material();
	wallMat01->addDiffuseTextureFromPath("../Resources/Textures/wall_01.jpg");

	// Link mesh, material and shader in drawables
	auto* woodCube = new Drawable(cubeMesh, woodMat, shader);
	auto* wall00Cube = new Drawable(cubeMesh, wallMat00, shader);
	auto* wall01Cube = new Drawable(cubeMesh, wallMat01, shader);

	// Create new scene graph nodes
	m_left = new Node();
	m_right = new Node();
	m_backside = new Node();
	m_bottom = new Node();

	const auto translation = 5.0f;
	const auto width = 0.1f;
	const auto height = 10.0f;
	const auto length = 10.0f;

	// Add drawables to nodes and transform the nodes
	m_left->addDrawable(wall01Cube);
	m_left->translateX(-translation);
	m_left->scale(glm::vec3(width, height, length));

	m_right->addDrawable(wall01Cube);
	m_right->translateX(translation);
	m_right->scale(glm::vec3(width, height, length));

	m_backside->addDrawable(wall00Cube);
	m_backside->translateZ(-translation);
	m_backside->scale(glm::vec3(length, height, width));

	m_bottom->addDrawable(woodCube);
	m_bottom->translateY(-translation);
	m_bottom->scale(glm::vec3(height, width, length));

	// Build the scene graph with the previously created nodes
	auto* rootNode = this->getRoot();
	rootNode->addChild(m_left);
	rootNode->addChild(m_right);
	rootNode->addChild(m_bottom);
	rootNode->addChild(m_backside);

	/*Node* testNode = new Node(nullptr);
	testNode->AddDrawable(woodCube);
	testNode->SetTranslationX(2);
	m_right->AddChild(testNode);*/
}

void ExampleScene::sphereTest()
{
	auto& shaderManager = m_window->getShaderManager();

	auto* sphereMesh = new SphereGeometry(1.0f, 20, 20);
	auto* shader = shaderManager.getShader("basic");
	auto* woodMat = new Material();
	woodMat->addDiffuseTextureFromPath("../Resources/Textures/sand_00.jpg");

	auto* sphereDrawable = new Drawable(sphereMesh, woodMat, shader);
	auto* sphereNode = new Node(nullptr);

	sphereNode->addDrawable(sphereDrawable);

	auto* rootNode = this->getRoot();
	rootNode->addChild(sphereNode);
}

void ExampleScene::cylinderTest()
{
	auto& shaderManager = m_window->getShaderManager();

	auto* cylinderMesh = new CylinderGeometry();
	auto* shader = shaderManager.getShader("basic");
	auto* woodMat = new Material();
	woodMat->addDiffuseTextureFromPath("../Resources/Textures/sand_00.jpg");

	auto* drawable = new Drawable(cylinderMesh, woodMat, shader);
	auto* node = new Node(nullptr);

	node->addDrawable(drawable);

	auto* rootNode = this->getRoot();
	rootNode->addChild(node);
}

void ExampleScene::rectangleTest()
{
	auto& shaderManager = m_window->getShaderManager();

	auto* rectangleMesh = new RectangleGeometry(1.0f);
	auto* shader = shaderManager.getShader("basic");
	auto* woodMat = new Material();
	woodMat->addDiffuseTextureFromPath("../Resources/Textures/sand_00.jpg");
	
	auto* drawable = new Drawable(rectangleMesh, woodMat, shader);
	auto* node = new Node(nullptr);

	node->addDrawable(drawable);
	node->rotateZ(-glm::radians(45.0f));

	auto* rootNode = this->getRoot();
	rootNode->addChild(node);
}

void ExampleScene::circleTest()
{
	auto& shaderManager = m_window->getShaderManager();

	auto* circleMesh = new CircleGeometry(1.0f);
	auto* shader = shaderManager.getShader("basic");
	auto* woodMat = new Material();
	woodMat->addDiffuseTextureFromPath("../Resources/Textures/sand_00.jpg");

	auto* drawable = new Drawable(circleMesh, woodMat, shader);
	auto* node = new Node(nullptr);

	node->addDrawable(drawable);
	node->rotateZ(-glm::radians(45.0f));

	auto* rootNode = this->getRoot();
	rootNode->addChild(node);
}
