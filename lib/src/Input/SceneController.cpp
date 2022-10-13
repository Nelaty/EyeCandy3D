#include <utility>
#include "ec3/Input/SceneController.h"

namespace ec
{
	SceneController::SceneController(std::string controllerName)
		: m_name{std::move(controllerName)}
	{
	}

	SceneController::~SceneController()
	= default;

	const std::string& SceneController::getName() const
	{
		return m_name;
	}
}