#pragma once
#include "EC3D/Core/InputListener.h"
#include "EC3D/Common/Common.h"

#include <functional>

/**
* Specialized InputObserver for controlling a scene
*/
namespace ec
{
	class Scene;

	class EC3D_DECLSPEC SceneController : public InputListener
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