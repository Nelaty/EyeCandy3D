#pragma once

#include "Agui/ImageLoader.hpp"

namespace agui 
{
	class OpenGLImageLoader : public ImageLoader
	{
	public:
		explicit OpenGLImageLoader();
		virtual ~OpenGLImageLoader();
		
		Image* loadImage(const std::string &fileName, 
						 bool convertMask = false,
						 bool convertToDisplayFormat = false) override;
	};
}