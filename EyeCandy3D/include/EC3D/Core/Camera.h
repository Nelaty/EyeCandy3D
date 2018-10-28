#pragma once
#include "Node.h"
#include "EC3D/Common/Common.h"

#include "Viewport.h"
#include "CameraType.h"
#include "EC3D/Gui/GuiSystem.h"

#include <glm/glm.hpp>

namespace ec
{
	class Scene;

	/**
	* \brief A camera encapsulates a view and a projection matrix. It is used
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

		/** 
		 * \brief Recursively update global matrices.
		 */
		void updateGlobalMatrices(const glm::mat4& parentMat) override;

		/** 
		 * \brief Get the current view matrix.
		 */
		const glm::mat4& getView() const;
		/** 
		 * \brief Get the current projection matrix.
		 */
		const glm::mat4& getProjection() const;

		/** 
		 *\brief Change to orthogonal projection.
		 */
		void setProjectionOrtho();
		/** 
		 * \brief Change to perspective projection.
		 */
		void setProjectionPerspective();

		/** 
		 * \brief Set the field of view.
		 * \param fov FOV in radians 
		 */
		void setFov(float fov);
		/** 
		 * \brief Get the current fov in radians.
		 */
		float getFov() const;

		/** 
		 * \brief Set the near plane.
		 */
		void setNear(float near);
		/** 
		 * \brief Get the current near plane. 
		 */
		float getNear() const;

		/**
		 * \brief Set the far plane.
		 */
		void setFar(float far);		
		/** 
		 * \brief Get the current far plane.
		 */
		float getFar() const;

		/**
		 * \brief Access to the related scene.
		 */
		Scene* getScene() const;

		/** 
		 * \brief Get the current viewport. 
		 */
		Viewport& getViewport();
		/**
		 * \brief Get the current viewport. 
		 */
		const Viewport& getViewport() const;
		/** 
		 * \brief Change the current viewport. 
		 */
		void setViewport(const Viewport& viewport);

		/** 
		 * \brief Get this camera's gui system.
		 */
		const GuiSystem& getGuiSystem() const;
		/**
		 * \brief Get this camera's gui system. 
		 */
		GuiSystem& getGuiSystem();

	private:
		/**
		 * \brief Initialize the camera with default values.
		 */
		void init();

		CameraType m_type;
		
		Viewport m_viewport;
		Scene* m_scene;

		GuiSystem m_guiSystem;

		//@{
		/** Projection matrix attribute */
		float m_aspect;
		float m_fov;

		float m_near;
		float m_far;
		//@}

		glm::mat4 m_view;
		glm::mat4 m_projection;
	};
}