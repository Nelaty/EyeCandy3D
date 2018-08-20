#pragma once

#include "Agui/Graphics.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

/**
 * OpenGL GUI back end class for graphics and drawing.
 */
namespace agui
{
	class OpenGLGraphics : public Graphics
	{
	public:
		explicit OpenGLGraphics();
		virtual ~OpenGLGraphics();
		
		virtual void _beginPaint() override;
		virtual void _endPaint() override;

		virtual Dimension getDisplaySize()  override;
		virtual Rectangle getClippingRectangle()  override;
		virtual void drawImage(const Image *bmp,
							   const Point &position,
							   const Point &regionStart,
							   const Dimension &regionSize,
							   const float &opacity = 1.0f) override;
			
		virtual void drawImage(const Image *bmp,
							   const Point &position,
							   const float &opacity = 1.0f) override;
			
		virtual void drawScaledImage(const Image *bmp,
									 const Point &position,
									 const Point &regionStart,
									 const Dimension &regionScale,
									 const Dimension &scale, 
									 const float &opacity = 1.0f) override;
			
		virtual void drawText(const Point &position,const char* text,
							  const Color &color, 
							  const Font *font,
							  AlignmentEnum align = ALIGN_LEFT) override;
			
		virtual void drawRectangle(const Rectangle &rect, 
								   const Color &color) override;
			
		virtual void drawFilledRectangle(const Rectangle &rect, const Color &color) override;
		virtual void drawPixel(const Point &point, const Color &color) override;
		virtual void drawCircle(const Point &center,float radius, const Color &color) override;
		virtual void drawFilledCircle(const Point &center,float radius,const Color &color) override;
		virtual void drawLine(const Point &start, const Point &end,	const Color &color) override;

		virtual void setTargetImage(const Image *target) override;
		virtual void resetTargetImage() override;

	protected:
		virtual void setClippingRectangle(const Rectangle &rect) override;

		static constexpr int s_circleStepsNum = 20;
		static constexpr float s_circleStep = 2 * M_PI / s_circleStepsNum;
	};
}

#undef _USE_MATH_DEFINES