#include "EC3D/Graphics/Render/Renderer.h"
#include "EC3D/Window/Window.h"
#include "EC3D/Graphics/Shader/ShaderManager.h"

#include "EC3D/Frame.h"
#include "EC3D/Graphics/Camera.h"

namespace ec {
	Renderer::Renderer()
        : m_activeRenderer{nullptr},
        m_lastRenderer{nullptr}
	{
	}

	Renderer::~Renderer()
	= default;

	void Renderer::init(Shader* guiShader, Shader* textShader) const
	{
	}

	void Renderer::tick()
	{
		if(m_activeRenderer)
		{
			m_activeRenderer->tick();
		}
	}

	void Renderer::render(Window* window) const
	{
		if(m_activeRenderer)
		{
			m_activeRenderer->render(window);
			renderGui();
		}		
	}

	void Renderer::changeRenderer(const std::string& name)
	{
		auto* renderer = getSceneRenderer(name);
		if(!renderer) return;

		m_lastRenderer = m_activeRenderer;
		m_activeRenderer = renderer;
	}

	void Renderer::changeRenderer(SceneRenderer* renderer)
	{
		m_lastRenderer = m_activeRenderer;
		m_activeRenderer = renderer;
	}

	void Renderer::registerSceneRenderer(const std::string& name, SceneRenderer* renderer)
	{
		if(getSceneRenderer(name)) return;

		m_renderer.insert(std::make_pair(name, renderer));
	}

	ec::SceneRenderer* Renderer::unregisterSceneRenderer(const std::string& name)
	{
		const auto foundRenderer = m_renderer.find(name);
		if(foundRenderer == m_renderer.end())
		{
			return nullptr;
		}
		m_renderer.erase(foundRenderer);
		return foundRenderer->second;
	}

	ec::SceneRenderer* Renderer::getSceneRenderer(const std::string& name)
	{
		const auto foundRenderer = m_renderer.find(name);

		if(foundRenderer == m_renderer.end())
		{
			return nullptr;
		}
		return foundRenderer->second;
	}

	void Renderer::renderGui() const
	{

	}
}
