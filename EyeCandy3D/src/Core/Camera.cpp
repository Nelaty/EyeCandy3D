#include "EC3D/Core/Camera.h"
#include "EC3D/Core/Scene.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>


namespace ec
{
	Camera::Camera(Scene* scene)
		: m_scene{scene}
	{
		Init();
	}	

	Camera::Camera(Scene* scene, const Viewport& viewport)
		: m_scene{scene},
		m_viewport{viewport}
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

	void Camera::UpdateView()
	{
		m_view = glm::lookAt(m_position,
							 m_orientation + m_position,
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

	const glm::vec3& Camera::GetUpVector() const
	{
		return m_up;
	}

	void Camera::Rotate(const glm::quat& rot)
	{
		m_orientation = glm::normalize(rot * m_orientation);
		m_up = glm::normalize(rot * m_up);
	}

	void Camera::Rotate(float angle, const glm::vec3& axis)
	{
		m_orientation = glm::normalize(glm::rotate(m_orientation, angle, axis));
		m_up = glm::rotate(m_up, angle, axis);
	}

	void Camera::RotateX(const float angle)
	{
		glm::vec3 up(0.0f, 1.0f, 0.0f);
		glm::vec3 axis = glm::cross(m_orientation, up);

		m_orientation = glm::normalize(glm::rotate(m_orientation, angle, axis));
		m_up = glm::normalize(glm::rotate(m_up, angle, axis));
	}

	void Camera::RotateY(const float angle)
	{
		glm::vec3 axis = glm::vec3(0.0f, 1.0f, 0.0f);
		m_orientation = glm::normalize(glm::rotate(m_orientation, angle, axis));
		m_up = glm::normalize(glm::rotate(m_up, angle, axis));
	}

	void Camera::RotateZ(const float angle)
	{
		glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f);
		m_orientation = glm::normalize(glm::rotate(m_orientation, angle, axis));
		m_up = glm::normalize(glm::rotate(m_up, angle, axis));
	}

	void Camera::SetOrientation(const glm::vec3& orientation)
	{
		m_orientation = orientation;
	}

	void Camera::Translate(const float x, const float y, const float z)
	{
		m_position.x += x;
		m_position.y += y;
		m_position.z += z;
	}

	void Camera::Translate(const glm::vec3& v)
	{
		m_position += v;
	}

	void Camera::TranslateX(const float x)
	{
		m_position.x += x;
	}

	void Camera::TranslateY(const float y)
	{
		m_position.y += y;
	}

	void Camera::TranslateZ(const float z)
	{
		m_position.z += z;
	}

	void Camera::SetTranslation(const glm::vec3& translation)
	{
		m_position = translation;
	}

	void Camera::TranslateLocal(const float x, const float y, const float z)
	{
		m_position += x * glm::cross(m_orientation, m_up);
		m_position += y * m_up;
		m_position += z * m_orientation;
	}

	void Camera::TranslateLocal(const glm::vec3& v)
	{
		m_position += v.x * glm::cross(m_orientation, m_up);
		m_position += v.y * m_up;
		m_position += v.z * m_orientation;
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
		m_position = glm::vec3(0.0f, 0.0f, 0.0f);
		m_orientation = glm::vec3(0.0f, 0.0f, -1.0f);
		m_up = glm::vec3(0.0f, 1.0f, 0.0f);
		m_view = glm::mat4(1.0f);
		m_fov = 45.0f;
		m_near = 1.0f;
		m_far = 100.0f;

		SetProjectionPerspective();
	}

	const glm::vec3& Camera::GetTranslation() const
	{
		return m_position;
	}

	const glm::vec3& Camera::GetDirection() const
	{
		return m_orientation;
	}
}