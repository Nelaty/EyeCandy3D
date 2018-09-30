#pragma once
#include "EC3D/Core/Scene.h"

#include <string>
#include <glm/glm.hpp>

namespace ec
{
	class Window;
	class Node;
}

class ExampleScene : public ec::Scene
{
public:
	explicit ExampleScene(const std::string& name, ec::Window* window);
	~ExampleScene();

	void init();

	void tick(float timeDelta) override;

private:
	void constructTestSg();
	void sphereTest();
	void cylinderTest();
	void rectangleTest();
	void circleTest();


	ec::Window* m_window;

	ec::Node* m_left;
	ec::Node* m_right;
	ec::Node* m_backside;
	ec::Node* m_bottom;

	ec::Node* m_origin;
};