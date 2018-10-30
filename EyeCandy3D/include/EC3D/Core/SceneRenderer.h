#pragma once
#include "EC3D/Common/Common.h"
#include "EC3D/Core/Frame.h"

#include <glm/glm.hpp>

#include <set>

/**
* \brief A SceneRenderer is able to render a scene with its 
* underlying scene graph. 
*/
namespace ec
{
	class Node;
	class Scene;
	class Camera;
	class Shader;
	class ShaderManager;
	class Window;

	class EC3D_DECLSPEC SceneRenderer
	{
	private:
		struct RenderContext
		{
			explicit RenderContext();
		
			Window* m_window;
			std::set<Scene*> m_uniqueScenes;
		};

	public:
		explicit SceneRenderer();
		~SceneRenderer();

		/** 
		 * \brief Update guis.
		 */
		void tick();

		/**
		 * \brief Render the currently active scene.
		 */
		void render(Window* window);

		/**
		 * \brief Get the frame holding all registered cameras.
		 */
		Frame& getFrame();
		/**
		 * \brief Get the frame holding all registered cameras.
		 */
		const Frame& getFrame() const;
		/**
		 * \brief Set the frame holding all registered cameras.
		 */
		void setFrame(const Frame& frame);

		/*
		* \brief Nodes add themselves as rendering targets, if they
		* should be rendered.
		*/
		void addRenderingTarget(Node* node);

	protected:
		void onBeginRender(RenderContext& context);
		void onRender(RenderContext& context);
		void onEndRender(RenderContext& context);

	private:
		/** 
		 * \brief Render all previously collected render targets.
		 */
		void renderTargets();
		/** 
		 * \brief Update matrices of all shaders.
		 * \param shaderManager Holds shader, which should be updated.
		 * \param camera Holds the current view matrix.
		 */
		void updateShaders(ShaderManager& shaderManager, Camera* camera);
		/** 
		 * \brief Update the OpenGL viewport.
		 * \param context Window information.
		 * \param camera New viewport size and position.
		 */
		void updateViewport(RenderContext& context, Camera* camera) const;

		/**
		 * \brief Clear all rendering targets.
		 */
		void clear();
		std::vector<Node*> m_renderingTargets;

		Frame m_frame;		

		/**
		* \brief The global transformation is used to transform the 
		* whole scene without changing the root node.
		*/
		glm::mat4 m_globalTransformation;

	};
}