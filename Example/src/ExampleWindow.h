#pragma once
#include "EC3D/Core/Window.h"
#include "EC3D/Core/CameraController.h"

namespace ec
{
	class SceneRenderer;
	class Camera;
	class Scene;
}

class ExampleScene;

class ExampleWindow : public ec::Window
{
public:
	explicit ExampleWindow(int width, int height, const char* windowTitle);
	~ExampleWindow();

	virtual void Tick(const float timeDelta) override;

	void InitCamera();
	void InitScenes();
	void InitShaders();

	void ConstructTestSG();
	void SphereTest();

private:

	ec::Scene * m_activeScene;

	ExampleScene* m_exampleScene;
	
	ec::Camera* m_camera;
	ec::SceneRenderer* m_exampleRenderer;

	ec::CameraController m_cameraController;

	ec::Camera* m_camera2;
	ec::CameraController m_cameraController2;

	ec::Camera* m_camera3;
};
