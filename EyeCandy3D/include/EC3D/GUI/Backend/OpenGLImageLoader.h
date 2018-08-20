#pragma once

#include "Agui/ImageLoader.hpp"

namespace agui 
{
	class OpenGLImageLoader : public ImageLoader
	{
	public:
		explicit OpenGLImageLoader();
		virtual ~OpenGLImageLoader();
		
		virtual Image* loadImage(const std::string &fileName, 
			bool convertMask = false,
			bool converToDisplayFormat = false);
	};
}