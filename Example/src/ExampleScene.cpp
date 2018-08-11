#include "ExampleScene.h"

#include "EC3D/Core/Window.h"
#include "EC3D/Core/Scene.h"
#include "EC3D/Core/Node.h"
#include "EC3D/Core/Drawable.h"
#include "EC3D/Core/CubeMesh.h"
#include "EC3D/Core/SphereMesh.h"
#include "EC3D/Core/Material.h"
#include "EC3D/Core/Camera.h"
#include "EC3D/Core/Frame.h"
#include "EC3D/Core/Shader/Shader.h"
#include "EC3D/Core/Shader/ShaderManager.h"

using namespace ec;

ExampleScene::ExampleScene(const std::string& name, ec::Window* window)
	: Scene(name),
	m_window{window}
{
	Init();
}

ExampleScene::~ExampleScene()
{
}

void ExampleScene::Init()
{
	ConstructTestSG();
	SphereTest();
}

void ExampleScene::Tick(const float timeDelta)
{
	m_right->RotateX(timeDelta * 0.1f);
}

void ExampleScene::ConstructTestSG()
{
	auto& shaderManager = m_window->GetShaderManager();	
	Shader* shader = shaderManager.GetShader("basic");

	// Create meshes
	CubeMesh* cubeMesh = new CubeMesh(1.0f);

	// Create new materials and load textures
	Material* woodMat = new Material();
	woodMat->AddDiffuseTextureFromPath("Resources/Textures/wood.jpg");
	Material* wallMat00 = new Material();
	wallMat00->AddDiffuseTextureFromPath("Resources/Textures/wall_00.jpg");
	Material* wallMat01 = new Material();
	wallMat01->AddDiffuseTextureFromPath("Resources/Textures/wall_01.jpg");

	// Link mesh, material and shader in drawables
	Drawable* woodCube = new Drawable(cubeMesh, woodMat, shader);
	Drawable* wall00Cube = new Drawable(cubeMesh, wallMat00, shader);
	Drawable* wall01Cube = new Drawable(cubeMesh, wallMat01, shader);

	// Create new scene graph nodes
	m_left = new Node(nullptr);
	m_right = new Node(nullptr);
	m_backside = new Node(nullptr);
	m_bottom = new Node(nullptr);

	float translation = 5;
	float width = 0.1f;
	float height = 10.0f;
	float length = 10.0f;

	// Add drawables to nodes and transform the nodes
	m_left->AddDrawable(wall01Cube);
	m_left->TranslateX(-translation);
	m_left->Scale(glm::vec3(width, height, length));

	m_right->AddDrawable(wall01Cube);
	m_right->TranslateX(translation);
	m_right->Scale(glm::vec3(width, height, length));

	m_backside->AddDrawable(wall00Cube);
	m_backside->TranslateZ(translation);
	m_backside->Scale(glm::vec3(length, height, width));

	m_bottom->AddDrawable(woodCube);
	m_bottom->TranslateY(-translation);
	m_bottom->Scale(glm::vec3(height, width, length));

	// Build the scene graph with the previously created nodes
	auto* rootNode = this->GetRoot();
	rootNode->AddChild(m_left);
	rootNode->AddChild(m_right);
	rootNode->AddChild(m_bottom);
	rootNode->AddChild(m_backside);

	Node* testNode = new Node(nullptr);
	testNode->AddDrawable(woodCube);
	testNode->SetTranslationX(2);
	m_right->AddChild(testNode);
}

void ExampleScene::SphereTest()
{
	auto& shaderManager = m_window->GetShaderManager();

	SphereMesh* sphereMesh = new SphereMesh(1.0f, 20, 20);
	Shader* shader = shaderManager.GetShader("basic");
	Material* woodMat = new Material();
	woodMat->AddDiffuseTextureFromPath("Resources/Textures/sand_00.jpg");

	Drawable* sphereDrawable = new Drawable(sphereMesh, woodMat, shader);
	Node* sphereNode = new Node(nullptr);

	sphereNode->AddDrawable(sphereDrawable);

	auto* rootNode = this->GetRoot();
	rootNode->AddChild(sphereNode);
}
