#include "ec3/Gui/Backend/OpenGLImageLoader.h"
#include "ec3/Gui/Backend/OpenGLImage.h"

namespace ec
{
	
	OpenGLImageLoader::OpenGLImageLoader()
	= default;

	OpenGLImageLoader::~OpenGLImageLoader()
	= default;

	agui::Image* OpenGLImageLoader::loadImage(const std::string &fileName,
	                                          const bool convertMask, 
											  bool convertToDisplayFormat)
	{
		return new OpenGLImage(fileName, convertMask);
	}

}
