#pragma once
#include "EC3D/Core/Scene.h"

#include <string>

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

	void Init();

	virtual void Tick(const float timeDelta) override;

private:
	void ConstructTestSG();
	void SphereTest();

	ec::Window* m_window;

	ec::Node* m_left;
	ec::Node* m_right;
	ec::Node* m_backside;
	ec::Node* m_bottom;
};