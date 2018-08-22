#pragma once
#include <GL/glew.h>

#include "Agui/Graphics.hpp"

#include <corecrt_math_defines.h>

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
		
		void _beginPaint() override;
		void _endPaint() override;

		Dimension getDisplaySize()  override;
		Rectangle getClippingRectangle()  override;
		void drawImage(const Image *bmp,
					   const Point &position,
					   const Point &regionStart,
					   const Dimension &regionSize,
					   const float &opacity = 1.0f) override;
			
		void drawImage(const Image *bmp,
					   const Point &position,
					   const float &opacity = 1.0f) override;
			
		void drawScaledImage(const Image *bmp,
							 const Point &position,
							 const Point &regionStart,
							 const Dimension &regionScale,
							 const Dimension &scale, 
							 const float &opacity = 1.0f) override;
			
		void drawText(const Point &position,const char* text,
					  const Color &color, 
					  const Font *font,
					  AlignmentEnum align = ALIGN_LEFT) override;
			
		void drawRectangle(const Rectangle &rect, 
						   const Color &color) override;
			
		void drawFilledRectangle(const Rectangle &rect, const Color &color) override;
		void drawPixel(const Point &point, const Color &color) override;
		void drawCircle(const Point &center,float radius, const Color &color) override;
		void drawFilledCircle(const Point &center,float radius,const Color &color) override;
		void drawLine(const Point &start, const Point &end,	const Color &color) override;

		virtual void setTargetImage(const Image *target) override;
		virtual void resetTargetImage() override;

	protected:
		virtual void setClippingRectangle(const Rectangle &rect) override;

		static constexpr int s_circleStepsNum = 20;
		static constexpr float s_circleStep = 2 * M_PI / s_circleStepsNum;
	};
}