#pragma once
#include "EC3D/Common/Common.h"
#include "EC3D/Core/Frame.h"

#include <glm/glm.hpp>

#include <set>

/**
* A SceneRenderer is able to render a scene with its underlying
* scene graph. 
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

		/* Render the currently active scene */
		void render(Window* window);

		/* Scene access */
		void setScene(Scene* scene);
		Scene* getScene();

		/* Frame access */
		Frame& getFrame();
		const Frame& getFrame() const;
		void setFrame(const Frame& frame);

		/*
		* Nodes add themselves as rendering targets, if they should
		* be rendered.
		*/
		void addRenderingTarget(Node* node);

	protected:
		void onBeginRender(RenderContext& context);
		void onRender(RenderContext& context);
		void onEndRender(RenderContext& context);

	private:
		/** Render all previously collected render targets */
		void renderTargets();
		/** Update matrices of all shaders */
		void updateShaders(ShaderManager& shaderManager, Camera* camera);
		/**  */
		void updateViewport(RenderContext& context, Camera* camera) const;

		/* Clear all rendering targets */
		void clear();
		std::vector<Node*> m_renderingTargets;

		Frame m_frame;
		Scene* m_scene;
		

		/**
		* The global transformation is used to transform the whole
		* scene without changing the root node
		*/
		glm::mat4 m_globalTransformation;

	};
}