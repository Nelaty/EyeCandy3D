#pragma once
#include "InputListener.h"
#include "InputEvent.h"

#include <functional>
#include <vector>
#include <unordered_map>
#include <utility>

/*
* Specialized InputObserver for controlling a scene
*/
namespace ec
{
	class Scene;

	class SceneController : public InputListener
	{
	public:
		explicit SceneController(const std::string& controllerName);
		virtual ~SceneController();

		/* Controller name access */
		const std::string& GetName() const;

	private:

		std::string m_name;
	};
}