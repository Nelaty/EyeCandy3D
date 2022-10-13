#pragma once
#include "ec3/Window/Window.h"
#include "ec3/Graphics/CameraController.h"

#include <string>

namespace ec
{
	class SceneRenderer;
	class Camera;
	class Scene;
	class Material;
}

class ExampleScene;

class ExampleWindow : public ec::Window
{
public:
	explicit ExampleWindow(unsigned int width, 
						   unsigned int height,
						   const std::string& windowTitle);
	~ExampleWindow();

	void tick(float timeDelta) override;

	void initCameras();
	void initScenes();
	void initShaders();

	void dynamicGeoTest();

private:
	void initGeometries();
	void initMaterials();
	void initTextures();
	void initDrawables();

	ExampleScene* m_exampleScene;
	
	ec::SceneRenderer* m_exampleRenderer;

	ec::Camera* m_camera;
	ec::Camera* m_camera2;
	ec::Camera* m_camera3;

	ec::Material* m_woodMat;

	ec::CameraController m_cameraController;
	ec::CameraController m_cameraController2;	
};
