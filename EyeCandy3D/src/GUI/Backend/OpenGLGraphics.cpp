#include "EC3D/GUI/Backend/OpenGLGraphics.h"

#include "EC3D/Core/Camera.h"
#include "EC3D/Core/Viewport.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ec
{	
	OpenGLGraphics::OpenGLGraphics(Camera* camera)
		: m_camera{camera}
	{
	}

	OpenGLGraphics::~OpenGLGraphics()
	= default;

	void OpenGLGraphics::_beginPaint()
	{
		/// \todo enable transparency, enable shader, set current context
	}

	void OpenGLGraphics::_endPaint()
	{
		/// \todo disable transparency, disable shader
	}

	agui::Dimension OpenGLGraphics::getDisplaySize()
	{
		auto width = 0;
		auto height = 0;
		auto* context = glfwGetCurrentContext();
		if(context)
		{
			glfwGetFramebufferSize(context, &width, &height);
		}
		return {width, height};
	}

	agui::Rectangle OpenGLGraphics::getClippingRectangle()
	{
		const auto& view = m_camera->getViewport();
		const auto& pos = view.getPosition();
		const auto& size = view.getSize();

		auto width = 0;
		auto height = 0;
		auto* context = glfwGetCurrentContext();
		if(context)
		{
			glfwGetFramebufferSize(context, &width, &height);
		}

		return agui::Rectangle(pos.x * width, pos.y * height,
							   size.x * width, size.y * height);
	}

	void OpenGLGraphics::drawImage(const agui::Image *bmp, 
								   const agui::Point &position,
								   const agui::Point &regionStart,
								   const agui::Dimension &regionSize,
								   const float &opacity)
	{

	}

	void OpenGLGraphics::drawImage(const agui::Image *bmp, 
								   const agui::Point &position, 
								   const float &opacity)
	{

	}

	void OpenGLGraphics::drawScaledImage(const agui::Image *bmp,
										 const agui::Point &position,
										 const agui::Point &regionStart,
										 const agui::Dimension &regionScale, 
										 const agui::Dimension &scale, 
										 const float &opacity)
	{

	}

	void OpenGLGraphics::drawText(const agui::Point &position, 
								  const char* text,
								  const agui::Color &color,
								  const agui::Font *font,
	                              agui::AlignmentEnum align)
	{

	}

	void OpenGLGraphics::drawRectangle(const agui::Rectangle &rect,
									   const agui::Color &color)
	{
		glBegin(GL_LINE_LOOP);
		glColor4f(color.getR(), color.getG(), color.getB(), color.getA());
		glVertex2i(rect.getLeft(), rect.getBottom());
		glVertex2i(rect.getRight(), rect.getBottom());
		glVertex2i(rect.getRight(), rect.getTop());
		glVertex2i(rect.getLeft(), rect.getTop());
		glEnd();
	}

	void OpenGLGraphics::drawFilledRectangle(const agui::Rectangle &rect,
											 const agui::Color &color)
	{
		glBegin(GL_POLYGON);
		glColor4f(color.getR(), color.getG(), color.getB(), color.getA());	
		glVertex2i(rect.getLeft(), rect.getBottom());
		glVertex2i(rect.getRight(), rect.getBottom());
		glVertex2i(rect.getRight(), rect.getTop());
		glVertex2i(rect.getLeft(), rect.getTop());
		glEnd();
	}

	void OpenGLGraphics::drawPixel(const agui::Point &point,
								   const agui::Color &color)
	{

	}

	void OpenGLGraphics::drawCircle(const agui::Point &center, 
									float radius, 
									const agui::Color &color)
	{
		const float x = center.getX();
		const float y = center.getY();

		auto xPrev = x;
		auto yPrev = y;

		glBegin(GL_LINE_LOOP);
		glColor4f(color.getR(), color.getG(), color.getB(), color.getA());
		glVertex2f(x, y);

		for(auto i = 0; i < s_circleStepsNum; ++i)
		{
			const auto angle = i * s_circleStep;

			const auto xCurrent = x + cos(angle) * radius;
			const auto yCurrent = y + sin(angle) * radius;

			glVertex2f(xPrev, yPrev);
			glVertex2f(xCurrent, yCurrent);

			xPrev = xCurrent;
			yPrev = yCurrent;
		}
		glEnd();
	}

	void OpenGLGraphics::drawFilledCircle(const agui::Point &center,
										  float radius, 
										  const agui::Color &color)
	{
		const float x = center.getX();
		const float y = center.getY();

		glBegin(GL_TRIANGLE_FAN);
		glColor4f(color.getR(), color.getG(), color.getB(), color.getA());
		glVertex2f(x, y);

		for(auto i = 0; i < s_circleStepsNum; ++i)
		{
			const auto angle = i * s_circleStep;
			glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
		}
		glEnd();
	}

	void OpenGLGraphics::drawLine(const agui::Point &start,
								  const agui::Point &end,
								  const agui::Color &color)
	{
		glBegin(GL_LINE);
		glColor4f(color.getR(), color.getG(), color.getB(), color.getA());
		glVertex2i(start.getX(), start.getY());
		glVertex2i(end.getX(), end.getY());
		glEnd();
	}

	void OpenGLGraphics::setTargetImage(const agui::Image *target)
	{

	}

	void OpenGLGraphics::resetTargetImage()
	{

	}

	void OpenGLGraphics::setClippingRectangle(const agui::Rectangle &rect)
	{

	}

}