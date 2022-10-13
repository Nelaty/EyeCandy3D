#pragma once
#include "ec3/Input/InputListener.h"
#include "ec3/Common/Common.h"
#include "ec3/Input/InputEvent.h"

#include <glm/glm.hpp>

/*
* Control camera movement through user input
*/

namespace ec
{
	class Camera;

	class EC3D_DECLSPEC CameraController : public InputListener
	{
	public:
		explicit CameraController();
		explicit CameraController(Camera* camera);
		~CameraController();

		/**
		 * \brief Apply camera movement.
		 */
		void tick(float timeDelta);

		/** 
		 * \brief Reset camera to initial state.
		 */
		void reset();

		/**
		 * \brief Set the currently controlled camera.
		 */
		void setCamera(Camera* camera);
		/**
		 * \return The currently controlled camera.
		 */
		Camera* getCamera() const;

	protected:
		/**
		 * \brief Process event to update camera movement.
		 * \param event An input event.
		 */
		void processEvent(const InputEvent& event) override;

		/**
		 * \brief Used to rotate the camera with a mouse.
		 */
		void processMouseMovement(const MouseEvent& event);
		/**
		 * \brief Enables camera rotation by mouse.
		 */
		void processMouseButtonDown(const MouseEvent& event);
		/**
		 * \brief Disables camera rotation by mouse.
		 */
		void processMouseButtonUp(const MouseEvent& event);

		/**
		 * \brief Enable linear movement.
		 */
		void processKeyDownInput(const KeyboardEvent& event);
		/**
		 * \brief Disable linear movement.
		 */
		void processKeyUpInput(const KeyboardEvent&  event);
		/**
		 * \brief Change fov.
		 */
		void processScrollInput(const MouseEvent& event) const;

	private:
		/**
		 * \brief Initializes the camera controller.
		 */
		void init();

		Camera* m_camera;

		/* Maximal and current linear velocity */
		glm::vec3 m_cameraVelocityCurrent;
		float m_cameraSpeed;

		/* Maximal and current rotational velocity */
		float m_cameraRotationSpeed;
		glm::vec3 m_cameraRotation;
		glm::vec3 m_cameraRotationCurrent;

		/* FOV limits */
		float m_fovMin;
		float m_fovMax;
		float m_fovStep;

		/* Mouse controlled camera rotation */
		float m_mouseSensitivity;
		bool m_mouseChangeCameraDirFirst;
		bool m_mouseChangeCameraDir;
		glm::vec2 m_mouseCoordsLast;
		glm::vec2 m_mouseMovement;
	};
}