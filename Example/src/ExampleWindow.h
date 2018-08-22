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

	void tick(float timeDelta) override;

	void initCameras();
	void initScenes();
	void initShaders();

private:

	ExampleScene* m_exampleScene;
	
	ec::SceneRenderer* m_exampleRenderer;

	ec::Camera* m_camera;
	ec::Camera* m_camera2;
	ec::Camera* m_camera3;

	ec::CameraController m_cameraController;
	ec::CameraController m_cameraController2;	
};
