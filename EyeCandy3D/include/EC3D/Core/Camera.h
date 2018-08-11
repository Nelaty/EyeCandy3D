#pragma once
#include "Node.h"

#include "Viewport.h"
#include "CameraType.h"

#include <glm/glm.hpp>

namespace ec
{
	class Scene;

	/**
	* A camera encapsulates a view and a projection matrix. It is used
	* to render the related scene. It contains a viewport, which defines
	* the area of the render target the scene should be rendered into.
	*/
	class Camera : public Node
	{
	public:
		explicit Camera(Scene* scene);
		explicit Camera(Scene* scene, const Viewport& viewport);
		~Camera();

		/**  
		 * DO NOT USE
		 * Update the viewport, so the aspect ratio of it equals the
		 * aspect ratio of the window.
		 */
		void ChangeAspectRatio(float aspect);

		/** 
		 * DO NOT USE
		 * Update the view matrix 
		 */
		virtual void UpdateLocalMat() override;

		virtual void UpdateGlobalMatrices(const glm::mat4& m_parentMat) override;

		/** Get the current view matrix */
		const glm::mat4& GetView() const;
		/** Get the current projection matrix */
		const glm::mat4& GetProjection() const;

		/** Change to orthogonal projection */
		void SetProjectionOrtho();
		/** Change to perspective projection */
		void SetProjectionPerspective();

		/** 
		 * Set the fov
		 * \param fov FOV in radians 
		 */
		void SetFOV(const float fov);
		/** Get the current fov in radians */
		float GetFOV() const;

		/** Set the near plane */
		void SetNear(const float near);
		/** Get the current near plane */
		float GetNear() const;

		/** Set the far plane */
		void SetFar(const float far);		
		/** Get the current far plane */
		float GetFar() const;

		/** Access to the related scene */
		Scene* GetScene() const;

		const Viewport& GetViewport() const;
		void SetViewport(const Viewport& viewport);

	private:
		void Init();

		CameraType m_type;

		float m_aspect;

		float m_fov;
		float m_near;
		float m_far;

		glm::mat4 m_view;
		glm::mat4 m_projection;
	
		Viewport m_viewport;
		Scene* m_scene;
	};
}