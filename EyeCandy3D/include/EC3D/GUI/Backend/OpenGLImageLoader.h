#pragma once
#include "Agui/ImageLoader.hpp"
#include "EC3D/Common/Common.h"

namespace ec
{
	class EC3D_DECLSPEC OpenGLImageLoader : public agui::ImageLoader
	{
	public:
		explicit OpenGLImageLoader();
		virtual ~OpenGLImageLoader();

		agui::Image* loadImage(const std::string &fileName, 
							   bool convertMask = false,
							   bool convertToDisplayFormat = false) override;
	};
}