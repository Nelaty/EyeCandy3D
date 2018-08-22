#include "EC3D/GUI/Backend/OpenGLImageLoader.h"
#include "EC3D/GUI/Backend/OpenGLImage.h"

namespace agui
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