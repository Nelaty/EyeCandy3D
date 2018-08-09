#include "EC3D/Core/Scene.h"
#include "EC3D/Core/Node.h"
#include "EC3D/Core/SceneSystem.h"
#include "EC3D/Core/Window.h"

namespace ec
{
	Scene::Scene(const std::string& name)
		: m_root(nullptr),
		m_sceneController{nullptr},
		m_name{name},
		m_sceneSystem{nullptr}
	{
		InitSceneRenderer();
		m_root = std::make_unique<Node>(nullptr);
	}

	Scene::~Scene()
	{
	}

	void Scene::Tick(const float timeDelta)
	{
	}

	const std::string& Scene::GetName() const
	{
		return m_name;
	}
	
	ec::Node* Scene::GetRoot()
	{
		return m_root.get();
	}

	void Scene::SetSceneController(SceneController* sceneController)
	{
		m_sceneController = sceneController;
	}

	ec::SceneController* Scene::GetSceneController()
	{
		return m_sceneController;
	}

	void Scene::SetSceneRenderer(const SceneRenderer& sceneRenderer)
	{
		m_sceneRenderer = sceneRenderer;
		InitSceneRenderer();
	}

	ec::SceneRenderer& Scene::GetSceneRenderer()
	{
		return m_sceneRenderer;
	}

	void Scene::SetSceneSystem(SceneSystem* sceneSystem)
	{
		m_sceneSystem = sceneSystem;
	}

	ec::SceneSystem* Scene::GetSceneSystem()
	{
		return m_sceneSystem;
	}

	void Scene::InitSceneRenderer()
	{
		m_sceneRenderer.SetScene(this);
	}
}