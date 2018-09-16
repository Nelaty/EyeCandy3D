#pragma once
#include <GL/glew.h>
#include "Agui/Graphics.hpp"
#include "EC3D/Common/Common.h"

#include <corecrt_math_defines.h>

/**
 * OpenGL GUI back end class for graphics and drawing.
 */
namespace ec
{
	class Camera;

	class EC3D_DECLSPEC OpenGLGraphics : public agui::Graphics
	{
	public:
		explicit OpenGLGraphics(Camera* camera);
		virtual ~OpenGLGraphics();
		
		void _beginPaint() override;
		void _endPaint() override;

		agui::Dimension getDisplaySize()  override;
		agui::Rectangle getClippingRectangle()  override;
		void drawImage(const agui::Image *bmp,
					   const agui::Point &position,
					   const agui::Point &regionStart,
					   const agui::Dimension &regionSize,
					   const float &opacity = 1.0f) override;
			
		void drawImage(const agui::Image *bmp,
					   const agui::Point &position,
					   const float &opacity = 1.0f) override;
			
		void drawScaledImage(const agui::Image *bmp,
							 const agui::Point &position,
							 const agui::Point &regionStart,
							 const agui::Dimension &regionScale,
							 const agui::Dimension &scale, 
							 const float &opacity = 1.0f) override;
			
		void drawText(const agui::Point &position,const char* text,
					  const agui::Color &color, 
					  const agui::Font *font,
		              agui::AlignmentEnum align = agui::ALIGN_LEFT) override;
			
		void drawRectangle(const agui::Rectangle &rect, 
						   const agui::Color &color) override;
			
		void drawFilledRectangle(const agui::Rectangle &rect, const agui::Color &color) override;
		void drawPixel(const agui::Point &point, const agui::Color &color) override;
		void drawCircle(const agui::Point &center,float radius, const agui::Color &color) override;
		void drawFilledCircle(const agui::Point &center,float radius,const agui::Color &color) override;
		void drawLine(const agui::Point &start, const agui::Point &end,	const agui::Color &color) override;

		void setTargetImage(const agui::Image *target) override;
		void resetTargetImage() override;

	protected:
		void setClippingRectangle(const agui::Rectangle &rect) override;

		Camera* m_camera;

		static constexpr int s_circleStepsNum = 20;
		static constexpr float s_circleStep = 2 * M_PI / s_circleStepsNum;
	};
}