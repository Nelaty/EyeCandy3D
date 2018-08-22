#include "EC3D/GUI/Backend/OpenGLImageLoader.h"
#include "EC3D/GUI/Backend/OpenGLImage.h"

namespace agui
{
	
	OpenGLImageLoader::OpenGLImageLoader()
	= default;

	OpenGLImageLoader::~OpenGLImageLoader()
	= default;

	agui::Image* OpenGLImageLoader::loadImage(const std::string &fileName,
											  bool convertMask, 
											  bool converToDisplayFormat)
	{
		return new OpenGLImage(fileName, convertMask);
	}

}