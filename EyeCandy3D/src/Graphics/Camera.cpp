#include "EC3D/Graphics/Camera.h"
#include "EC3D/Scene.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/quaternion.hpp>


namespace ec
{
	Camera::Camera(Scene* scene)
		: Node(nullptr),
		m_scene{scene}
	{
		init();
	}	

	Camera::Camera(Scene* scene, const Viewport& viewport)
		: Node(nullptr),
		m_viewport{viewport},
		m_scene{scene}
	{
		init();
	}

	Camera::~Camera()
	= default;

	void Camera::changeAspectRatio(const float aspect)
	{
		m_aspect = aspect;
		if(m_type == CameraType::perspective)
		{
			setProjectionPerspective();
		}
	}

	void Camera::updateLocalMat()
	{
		Node::updateLocalMat();
	}

	void Camera::updateGlobalMatrices(const glm::mat4& parentMat, bool dirty)
	{
		Node::updateGlobalMatrices(parentMat, dirty);

		m_view = glm::lookAt(m_position,
							 m_position + m_forwardVector,
							 m_up);
	}

	const glm::mat4& Camera::getView() const
	{
		return m_view;
	}	

	const glm::mat4& Camera::getProjection() const
	{
		return m_projection;
	}

	void Camera::setProjectionOrtho()
	{
		const auto& pos = m_viewport.getPosition();
		const auto& size = m_viewport.getSize();

		m_projection = glm::ortho(pos.x, pos.x + size.x,
								  pos.y + size.y, pos.y,
								  m_near, m_far);

		m_type = CameraType::orthogonal;
	}

	void Camera::setProjectionPerspective()
	{
		const auto adjustedAspect = m_aspect * (m_viewport.getSizeX() / m_viewport.getSizeY());

		m_projection = glm::perspective(m_fov, adjustedAspect, m_near, m_far);
		m_type = CameraType::perspective;
	}

	void Camera::setFov(const float fov)
	{
		m_fov = fov;
	}

	void Camera::setNear(const float near)
	{
		m_near = near;
	}

	void Camera::setFar(const float far)
	{
		m_far = far;
	}

	float Camera::getFov() const
	{
		return m_fov;
	}

	float Camera::getNear() const
	{
		return m_near;
	}

	float Camera::getFar() const
	{
		return m_far;
	}

	ec::Scene* Camera::getScene() const
	{
		return m_scene;
	}

	Viewport& Camera::getViewport()
	{
		return m_viewport;
	}

	const ec::Viewport& Camera::getViewport() const
	{
		return m_viewport;
	}

	void Camera::setViewport(const Viewport& viewport)
	{
		m_viewport = viewport;
	}

	void Camera::init()
	{
		m_aspect = 1.0f;	
		m_fov = 60.0f;
		m_near = 0.01f;
		m_far = 1000.0f;

		setProjectionPerspective();
	}
}
