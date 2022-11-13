#include "ec3/graphics/shader/shader-timed.h"

namespace ec
{
	ShaderTimed::ShaderTimed(const std::string& vertPath,
							 const std::string& fragPath,
							 const std::string& geomPath,
							 const std::string& tessCtrlPath,
							 const std::string& tessEvalPath)
	: Shader(vertPath,
			 fragPath,
			 geomPath,
			 tessCtrlPath,
			 tessEvalPath)
	{
	}

	ShaderTimed::~ShaderTimed()
	= default;

	void ShaderTimed::update(float time, float timeDelta)
	{
	}
}
