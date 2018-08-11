#include "EC3D/Core/Camera.h"
#include "EC3D/Core/Scene.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>


namespace ec
{
	Camera::Camera(Scene* scene)
		: m_scene{scene},
		Node(nullptr)
	{
		Init();
	}	

	Camera::Camera(Scene* scene, const Viewport& viewport)
		: m_scene{scene},
		m_viewport{viewport},
		Node(nullptr)
	{
		Init();
	}

	Camera::~Camera()
	{
	}

	void Camera::ChangeAspectRatio(float aspect)
	{
		m_aspect = aspect;
		if(m_type == CameraType::perspective)
		{
			SetProjectionPerspective();
		}
	}

	void Camera::UpdateLocalMat()
	{
		__super::UpdateLocalMat();
	}

	void Camera::UpdateGlobalMatrices(const glm::mat4& m_parentMat)
	{
		__super::UpdateGlobalMatrices(m_parentMat);

		m_view = glm::lookAt(m_position,
							 m_forwardVector + m_position,
							 m_up);
	}

	const glm::mat4& Camera::GetView() const
	{
		return m_view;
	}	

	const glm::mat4& Camera::GetProjection() const
	{
		return m_projection;
	}

	void Camera::SetProjectionOrtho()
	{
		const auto& pos = m_viewport.GetPosition();
		const auto& size = m_viewport.GetSize();

		m_projection = glm::ortho(pos.x, pos.x + size.x,
								  pos.y + size.y, pos.y,
								  m_near, m_far);

		m_type = CameraType::orthogonal;
	}

	void Camera::SetProjectionPerspective()
	{
		float adjustedAspect = m_aspect * (m_viewport.GetSizeX() / m_viewport.GetSizeY());

		m_projection = glm::perspective(m_fov, adjustedAspect, m_near, m_far);
		m_type = CameraType::perspective;
	}

	void Camera::SetFOV(const float fov)
	{
		m_fov = fov;
	}

	void Camera::SetNear(const float near)
	{
		m_near = near;
	}

	void Camera::SetFar(const float far)
	{
		m_far = far;
	}

	float Camera::GetFOV() const
	{
		return m_fov;
	}

	float Camera::GetNear() const
	{
		return m_near;
	}

	float Camera::GetFar() const
	{
		return m_far;
	}

	ec::Scene* Camera::GetScene() const
	{
		return m_scene;
	}

	const ec::Viewport& Camera::GetViewport() const
	{
		return m_viewport;
	}

	void Camera::SetViewport(const Viewport& viewport)
	{
		m_viewport = viewport;
	}

	void Camera::Init()
	{
		m_aspect = 1.0f;	
		m_fov = 60.0f;
		m_near = 0.01f;
		m_far = 1000.0f;

		SetProjectionPerspective();
	}
}