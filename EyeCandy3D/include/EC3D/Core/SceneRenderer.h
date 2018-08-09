#pragma once
#include "EC3D/GUI/GUIRenderer.h"
#include "EC3D/Core/Frame.h"

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

	class SceneRenderer
	{
	private:
		struct RenderContext
		{
			Window* m_window;
			std::set<Scene*> m_uniqueScenes;
		};

	public:
		explicit SceneRenderer();
		~SceneRenderer();

		/* Render the currently active scene */
		void Render(Window* window);

		/* Scene access */
		void SetScene(Scene* scene);
		Scene* GetScene();

		/* Frame access */
		Frame& GetFrame();
		const Frame& GetFrame() const;
		void SetFrame(const Frame& frame);

		/*
		* Nodes add themselves as rendering targets, if they should
		* be rendered.
		*/
		void AddRenderingTarget(Node* node);

	protected:
		void OnBeginRender(RenderContext& context);
		void OnRender(RenderContext& context);
		void OnEndRender(RenderContext& context);

	private:
		/** Render all previously collected render targets */
		void RenderTargets();
		/** Update matrices of all shaders */
		void UpdateShaders(ShaderManager& shaderManager, Camera* camera);
		/**  */
		void UpdateViewport(RenderContext& context, Camera* camera);

		/* Clear all rendering targets */
		void Clear();
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