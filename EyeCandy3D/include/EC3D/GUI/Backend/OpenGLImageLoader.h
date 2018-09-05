#pragma once
#include "Agui/ImageLoader.hpp"
#include "EC3D/Common/Common.h"

namespace agui 
{
	class EC3D_DECLSPEC OpenGLImageLoader : public ImageLoader
	{
	public:
		explicit OpenGLImageLoader();
		virtual ~OpenGLImageLoader();
		
		Image* loadImage(const std::string &fileName, 
						 bool convertMask = false,
						 bool convertToDisplayFormat = false) override;
	};
}