#include "ec3/graphics/camera-controller.h"

#include "ec3/graphics/camera.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ec
{
	CameraController::CameraController()
		: m_camera{nullptr}
	{
		init();
	}

	CameraController::CameraController(Camera* camera)
		: m_camera{camera}
	{
		init();
	}

	CameraController::~CameraController()
	= default;

	void CameraController::tick(const float timeDelta)
	{
		if(!m_camera) return;

		m_camera->translateLocal(m_cameraVelocityCurrent * timeDelta * m_cameraSpeed);
		if(m_mouseChangeCameraDir && m_mouseMovement != glm::vec2(0.0f))
		{
			m_camera->rotateY(-m_mouseMovement.x * m_mouseSensitivity);
			m_camera->rotateXLocal(-m_mouseMovement.y * m_mouseSensitivity);

			m_mouseMovement = glm::vec2(0.0f);
		}
	}

	void CameraController::reset()
	{
		init();
	}

	void CameraController::setCamera(Camera* camera)
	{
		m_camera = camera;
	}

	ec::Camera* CameraController::getCamera() const
	{
		return m_camera;
	}

	void CameraController::processEvent(const InputEvent& event)
	{		
		switch(event.m_type)
		{
			case InputType::mouse_move:
				processMouseMovement(event.m_event.m_mouse);
				break;
			case InputType::key_pressed:
				processKeyDownInput(event.m_event.m_keyboard);
				break;
			case InputType::key_released:
				processKeyUpInput(event.m_event.m_keyboard);
				break;
			case InputType::mouse_scroll:
				processScrollInput(event.m_event.m_mouse);
				break;
			case InputType::mouse_button_pressed:
				processMouseButtonDown(event.m_event.m_mouse);
				break;
			case InputType::mouse_button_released:
				processMouseButtonUp(event.m_event.m_mouse);
				break;
			default:
				break;
		}
	}

	void CameraController::processMouseMovement(const MouseEvent& event)
	{
		if(!m_mouseChangeCameraDir)
		{
			return;
		}
		if(m_mouseChangeCameraDirFirst)
		{
			m_mouseCoordsLast = glm::vec2(event.m_x, event.m_y);
			m_mouseChangeCameraDirFirst = false;
		}

		m_mouseMovement = glm::vec2(event.m_x, event.m_y) - m_mouseCoordsLast;
		m_mouseCoordsLast = glm::vec2(event.m_x, event.m_y);
	}

	void CameraController::processMouseButtonDown(const MouseEvent& event)
	{
		if(event.m_button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			m_mouseChangeCameraDir = true;
			glfwSetInputMode(event.m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}

	void CameraController::processMouseButtonUp(const MouseEvent& event)
	{
		if(event.m_button == GLFW_MOUSE_BUTTON_RIGHT)
		{
			m_mouseChangeCameraDirFirst = true;
			m_mouseChangeCameraDir = false;
			glfwSetInputMode(event.m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}	

	void CameraController::processKeyDownInput(const KeyboardEvent& event)
	{
		if(event.m_key == GLFW_KEY_LEFT_SHIFT)
		{
			m_cameraSpeed = 5.0f;
		}

		// Handle linear movement
		if(event.m_key == GLFW_KEY_D)
		{
			m_cameraVelocityCurrent.x += 1.0f;
		}
		if(event.m_key == GLFW_KEY_A)
		{
			m_cameraVelocityCurrent.x -= 1.0f;
		}

		if(event.m_key == GLFW_KEY_R)
		{			
			m_cameraVelocityCurrent.y += 1.0f;
		}
		if(event.m_key == GLFW_KEY_F)
		{
			m_cameraVelocityCurrent.y -= 1.0f;
		}

		if(event.m_key == GLFW_KEY_W)
		{
			m_cameraVelocityCurrent.z += 1.0f;
		}
		if(event.m_key == GLFW_KEY_S)
		{
			m_cameraVelocityCurrent.z -= 1.0f;
		}

		// Handle rotations
		if(event.m_key == GLFW_KEY_LEFT)
		{			
			m_cameraRotationCurrent.y += m_cameraRotation.y;			
		}
		if(event.m_key == GLFW_KEY_RIGHT)
		{
			m_cameraRotationCurrent.y -= m_cameraRotation.y;
		}
	}

	void CameraController::processKeyUpInput(const KeyboardEvent& event)
	{
		if(event.m_key == GLFW_KEY_LEFT_SHIFT)
		{
			m_cameraSpeed = 1.0f;
		}

		// Handle linear movement
		if(event.m_key == GLFW_KEY_D)
		{
			m_cameraVelocityCurrent.x -= 1.0f;
		}
		if(event.m_key == GLFW_KEY_A)
		{
			m_cameraVelocityCurrent.x += 1.0f;
		}

		if(event.m_key == GLFW_KEY_R)
		{
			m_cameraVelocityCurrent.y -= 1.0f;
		}
		if(event.m_key == GLFW_KEY_F)
		{
			m_cameraVelocityCurrent.y += 1.0f;
		}

		if(event.m_key == GLFW_KEY_W)
		{
			m_cameraVelocityCurrent.z -= 1.0f;
		}
		if(event.m_key == GLFW_KEY_S)
		{
			m_cameraVelocityCurrent.z += 1.0f;
		}

		// Handle rotations
		if(event.m_key == GLFW_KEY_LEFT)
		{
			m_cameraRotationCurrent.y -= m_cameraRotation.y;
		}
		if(event.m_key == GLFW_KEY_RIGHT)
		{
			m_cameraRotationCurrent.y += m_cameraRotation.y;
		}
	}

	void CameraController::processScrollInput(const MouseEvent& event) const
	{
		if(!m_camera) return;

		float FOV = m_camera->getFov();
		FOV -= event.m_scrollY * m_fovStep;
		if(FOV < m_fovMin)
		{
			FOV = m_fovMin;
		}
		else if(FOV > m_fovMax)
		{
			FOV = m_fovMax;
		}

		m_camera->setFov(FOV);
	}

	void CameraController::init()
	{
		m_cameraSpeed = 1.0f;

		m_cameraRotationCurrent = glm::vec3(0.0f);
		m_cameraVelocityCurrent = glm::vec3(0.0f);

		m_mouseSensitivity = 0.001f;
		m_mouseChangeCameraDirFirst = true;
		m_mouseChangeCameraDir = false;

		m_cameraRotationSpeed = 0.003f;
		m_cameraRotation = glm::vec3(1.0f, 1.0f, 1.0f);
		
		m_fovMin = glm::radians(0.1f);
		m_fovMax = glm::radians(179.9f);
		m_fovStep = glm::radians(3.0f);
	}
}
