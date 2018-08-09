#pragma once
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
	class Camera
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
		void UpdateView();

		/** Get the current view matrix */
		const glm::mat4& GetView() const;
		/** Get the current projection matrix */
		const glm::mat4& GetProjection() const;
		/** Get the current up vector */
		const glm::vec3& GetUpVector() const;
		/** Get the current orientation */
		const glm::vec3& GetDirection() const;

		/** Rotate with a quaternion */
		void Rotate(const glm::quat& rot);
		/** Rotate around an axis by a given angle */
		void Rotate(float angle, const glm::vec3& axis);
		/** Rotate around the x axis by a given angle */
		void RotateX(const float angle);
		/** Rotate around the y axis by a given angle */
		void RotateY(const float angle);
		/** Rotate around the z axis by a given angle */
		void RotateZ(const float angle);
		void SetOrientation(const glm::vec3& orientation);

		/* Translation */
		const glm::vec3& GetTranslation() const;
		void Translate(const float x, const float y, const float z);
		void Translate(const glm::vec3& v);
		void TranslateX(const float x);
		void TranslateY(const float y);
		void TranslateZ(const float z);
		void SetTranslation(const glm::vec3& translation);

		void TranslateLocal(const float x, const float y, const float z);
		void TranslateLocal(const glm::vec3& v);

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

		glm::vec3 m_up;
		glm::vec3 m_position;
		glm::vec3 m_orientation;

		glm::mat4 m_view;
		glm::mat4 m_projection;
	
		Viewport m_viewport;
		Scene* m_scene;
	};
}