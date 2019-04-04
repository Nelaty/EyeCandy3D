#pragma once
#include <GL/glew.h>
#include "Agui/Graphics.hpp"

#include "EC3D/Common/Common.h"
#include "EC3D/Gui/GuiRenderContext.h"
#include "EC3D/Gui/GuiPrimitiveRenderer.h"

#include "EC3D/Core/RectangleGeometry.h"
#include "EC3D/Core/CircleGeometry.h"
#include "EC3D/Core/LineStripGeometry.h"
#include "EC3D/Core/LineGeometry.h"

#include <corecrt_math_defines.h>

#include   <memory>


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

		void setRenderContext(const GuiRenderContext& context);

		agui::Dimension getDisplaySize()  override;
		agui::Rectangle getClippingRectangle()  override;
		void drawImage(const agui::Image* bmp,
					   const agui::Point& position,
					   const agui::Point& regionStart,
					   const agui::Dimension& regionSize,
					   const float& opacity = 1.0f) override;
			
		/** \brief Draw an image at a given position. */
		void drawImage(const agui::Image* bmp,
					   const agui::Point& position,
					   const float& opacity = 1.0f) override;
			
		/** \brief Draw a scaled image at a given position. */
		void drawScaledImage(const agui::Image* bmp,
							 const agui::Point& position,
							 const agui::Point& regionStart,
							 const agui::Dimension& regionScale,
							 const agui::Dimension& scale, 
							 const float& opacity = 1.0f) override;
			
		/** \brief Draw a given text at a given position. */
		void drawText(const agui::Point& position,const char* text,
					  const agui::Color& color, 
					  const agui::Font* font,
		              agui::AlignmentEnum align = agui::ALIGN_LEFT) override;
			
		/** \brief Draw the outline of a rectangle. */
		void drawRectangle(const agui::Rectangle& rect, 
						   const agui::Color& color) override;
			
		/** \brief Draw a filled rectangle. */
		void drawFilledRectangle(const agui::Rectangle& rect, const agui::Color& color) override;
		
		/** \brief Draw a single pixel at a given position. */
		void drawPixel(const agui::Point& point, const agui::Color& color) override;
		
		/** \brief Draw the outline of a circle. */
		void drawCircle(const agui::Point& center,float radius, const agui::Color& color) override;
		
		/** \brief Draw a filled circle. */
		void drawFilledCircle(const agui::Point& center,float radius,const agui::Color& color) override;
		
		/** \brief Draw a line. */
		void drawLine(const agui::Point& start, const agui::Point& end,	const agui::Color& color) override;

		/** \brief Set the render target. */
		void setTargetImage(const agui::Image* target) override;
		/** \brief Clear the render target buffer. */
		void resetTargetImage() override;

	protected:
		void setClippingRectangle(const agui::Rectangle& rect) override;

		/** Initialize 2D geometries for rendering gui elements. */
		void initGeometries();

		Camera* m_camera;

		GuiRenderContext m_context;
		agui::Rectangle m_clippingRect;
	
		GuiPrimitiveRenderer m_primitiveRenderer;
		std::unique_ptr<RectangleGeometry> m_rectangleGeometry;
		std::unique_ptr<CircleGeometry> m_circleGeometry;
		std::unique_ptr<LineStripGeometry> m_rectangleOutlineGeometry;
		std::unique_ptr<LineStripGeometry> m_circleOutlineGeometry;
		std::unique_ptr<LineGeometry> m_lineGeometry;

		static constexpr int s_circleStepsNum = 20;
		static constexpr float s_circleStep = 2 * M_PI / s_circleStepsNum;
	};
}