#pragma once
#include "EC3D/Core/Window.h"
#include "EC3D/Core/CameraController.h"

#include <string>
#include <memory>

namespace ec
{
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

	std::shared_ptr<ec::Camera> m_camera;

	ec::Material* m_woodMat;

	ec::CameraController m_cameraController;
	ec::CameraController m_cameraController2;	
};
