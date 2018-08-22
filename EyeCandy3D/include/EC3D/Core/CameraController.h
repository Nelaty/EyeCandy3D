#pragma once
#include "InputListener.h"
#include "InputEvent.h"

#include <glm/glm.hpp>

/*
* Control camera movement through user input
*/

namespace ec
{
	class Camera;

	class CameraController : public InputListener
	{
	public:
		explicit CameraController();
		explicit CameraController(Camera* camera);
		~CameraController();

		/* Apply camera movement */
		void tick(float timeDelta);

		/** Reset camera to initial state */
		void reset();

		/* Camera access */
		void setCamera(Camera* camera);
		Camera* getCamera() const;

	protected:
		void processEvent(const InputEvent& event) override;

		/* Routines for different input types */
		void processMouseMovement(const MouseEvent& event);
		void processMouseButtonDown(const MouseEvent& event);
		void processMouseButtonUp(const MouseEvent& event);

		void processKeyDownInput(const KeyboardEvent& event);
		void processKeyUpInput(const KeyboardEvent&  event);
		void processScrollInput(const MouseEvent& event) const;

	private:
		/* Initializes the camera controller */
		void init();

		/* Active camera */
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