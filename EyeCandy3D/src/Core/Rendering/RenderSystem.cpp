#include "EC3D/Core/Rendering/RenderSystem.h"
#include "EC3D/Core/Rendering/RenderingContext.h"
#include "EC3D/Core/Rendering/IRenderer.h"
#include "EC3D/Core/Window.h"

namespace ec
{
	RenderSystem::RenderSystem()
	{
	}

	RenderSystem::~RenderSystem()
	{
	}

	void RenderSystem::render(Window* window)
	{
		if(window && m_activeRenderer)
		{
			RenderingContext context;
			context.m_window = window;
			m_activeRenderer->render(context);
		}
	}

	void RenderSystem::addRenderer(const Renderer_Ptr& renderer, 
								   const std::string& id)
	{
		m_rendererRegistry.insert({id, renderer});
	}

	bool RenderSystem::removeRenderer(const std::string& id)
	{
		auto foundItem = m_rendererRegistry.find(id);
		if(foundItem != m_rendererRegistry.end())
		{
			if(foundItem->second.get() == m_activeRenderer)
			{
				m_activeRenderer = nullptr;
			}
			m_rendererRegistry.erase(foundItem);
			return true;
		}
		return false;
	}

	bool RenderSystem::setActiveRenderer(const std::string& id)
	{
		auto foundItem = m_rendererRegistry.find(id);
		if(foundItem != m_rendererRegistry.end())
		{
			m_activeRenderer = foundItem->second.get();
			return true;
		}
		return false;
	}

}