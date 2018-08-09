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
		void Tick(const float timeDelta);

		/* Camera access */
		void SetCamera(Camera* camera);
		Camera* GetCamera() const;

	protected:
		virtual void ProcessEvent(const InputEvent& event) override;

		/* Routines for different input types */
		void ProcessMouseMovement(const MouseMoveEvent& event);
		void ProcessMouseButtonDown(const MouseButtonEvent& event);
		void ProcessMouseButtonUp(const MouseButtonEvent& event);

		void ProcessKeyDownInput(const KeyEvent& event);
		void ProcessKeyUpInput(const KeyEvent&  event);
		void ProcessScrollInput(const MouseScrollEvent& event);

	private:
		/* Initializes the camera controller */
		void Init();

		/* Active camera */
		Camera* m_camera;

		/* Maximal and current linear velocity */
		glm::vec3 m_cameraVelocity;
		glm::vec3 m_cameraVelocityCurrent;
		float m_cameraSpeed;

		/* Maximal and current rotational velocity */
		float m_cameraRotationSpeed;
		glm::vec3 m_cameraRotation;
		glm::vec3 m_cameraRotationCurrent;

		/* Mouse controlled camera rotation */
		bool m_mouseChangeCameraDirFirst = true;
		bool m_mouseChangeCameraDir = false;
		glm::vec2 m_mouseCoordsLast;
		glm::vec2 m_mouseMovement;
	};
}