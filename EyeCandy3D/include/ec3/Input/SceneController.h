#pragma once
#include "ec3/Input/InputListener.h"
#include "ec3/Common/Common.h"

#include <functional>
#include <string>

namespace ec
{
	class Scene;

	/**
	 * \brief Specialized InputListener for controlling a scene.
	 */
	class EC3D_DECLSPEC SceneController : public InputListener
	{
	public:
		/**
		 * \brief SceneController constructor.
		 * \param controllerName The name of the scene controller.
		 */
		explicit SceneController(std::string controllerName);
		virtual ~SceneController();

		/**
		 * \brief Get the name of the scene controller. 
		 */
		const std::string& getName() const;

	private:
		std::string m_name;
	};
}