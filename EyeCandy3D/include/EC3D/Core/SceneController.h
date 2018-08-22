#pragma once
#include "InputListener.h"

#include <functional>

/**
* Specialized InputObserver for controlling a scene
*/
namespace ec
{
	class Scene;

	class SceneController : public InputListener
	{
	public:
		explicit SceneController(std::string controllerName);
		virtual ~SceneController();

		/* Controller name access */
		const std::string& getName() const;

	private:

		std::string m_name;
	};
}