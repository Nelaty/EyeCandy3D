#pragma once
#include <memory>
#include <string>
#include <map>

namespace ec
{
	class Window;
	class IRenderer;

	class RenderSystem
	{
	public:
		using Renderer_Ptr = std::shared_ptr<IRenderer>;

		explicit RenderSystem();
		~RenderSystem();

		/** \brief Use the currently active renderer to render
		 * to a given window. */
		void render(Window* window);

		/** \brief Register a renderer with a given id. */
		void addRenderer(const Renderer_Ptr& renderer,
						 const std::string& id);
		/** \brief Try to unregister a renderer with a given id. 
		 * \return True if a renderer was found, false otherwise. */
		bool removeRenderer(const std::string& id);

		/** \brief Set the currently used renderer. 
		 * \param id The id of a registered renderer. 
		 * \return True if a renderer was found, false otherwise. */
		bool setActiveRenderer(const std::string& id);

	private:
		IRenderer* m_activeRenderer{};

		std::map<std::string, Renderer_Ptr> m_rendererRegistry;
	};
}