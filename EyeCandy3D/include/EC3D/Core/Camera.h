#pragma once
#include "Node.h"
#include "EC3D/Common/Common.h"

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
	class EC3D_DECLSPEC Camera : public Node
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
		void changeAspectRatio(float aspect);

		/** 
		 * DO NOT USE
		 * Update the view matrix 
		 */
		void updateLocalMat() override;

		void updateGlobalMatrices(const glm::mat4& parentMat) override;

		/** Get the current view matrix */
		const glm::mat4& getView() const;
		/** Get the current projection matrix */
		const glm::mat4& getProjection() const;

		/** Change to orthogonal projection */
		void setProjectionOrtho();
		/** Change to perspective projection */
		void setProjectionPerspective();

		/** 
		 * Set the fov
		 * \param fov FOV in radians 
		 */
		void setFov(float fov);
		/** Get the current fov in radians */
		float getFov() const;

		/** Set the near plane */
		void setNear(float near);
		/** Get the current near plane */
		float getNear() const;

		/** Set the far plane */
		void setFar(float far);		
		/** Get the current far plane */
		float getFar() const;

		/** Access to the related scene */
		Scene* getScene() const;

		const Viewport& getViewport() const;
		void setViewport(const Viewport& viewport);

	private:
		void init();

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