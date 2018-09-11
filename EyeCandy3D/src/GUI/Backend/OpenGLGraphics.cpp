#include "EC3D/GUI/Backend/OpenGLGraphics.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace agui
{	
	OpenGLGraphics::OpenGLGraphics()
	= default;

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
		int width = 0;
		int height = 0;
		auto* context = glfwGetCurrentContext();
		if(context)
		{
			glfwGetWindowSize(context, &width, &height);
		}
		return {width, height};
	}

	Rectangle OpenGLGraphics::getClippingRectangle()
	{
		auto width = 0;
		auto height = 0;
		auto x = 0;
		auto y = 0;
		auto* context = glfwGetCurrentContext();
		if(context)
		{
			glfwGetWindowSize(context, &width, &height);
			glfwGetWindowPos(context, &x, &y);
		}
		return {x, y, width, height};
	}

	void OpenGLGraphics::drawImage(const Image *bmp, 
								   const Point &position,
								   const Point &regionStart,
								   const Dimension &regionSize,
								   const float &opacity)
	{

	}

	void OpenGLGraphics::drawImage(const Image *bmp, 
								   const Point &position, 
								   const float &opacity)
	{

	}

	void OpenGLGraphics::drawScaledImage(const Image *bmp,
										 const Point &position,
										 const Point &regionStart,
										 const Dimension &regionScale, 
										 const Dimension &scale, 
										 const float &opacity)
	{

	}

	void OpenGLGraphics::drawText(const Point &position, 
								  const char* text,
								  const Color &color,
								  const Font *font, 
								  AlignmentEnum align)
	{

	}

	void OpenGLGraphics::drawRectangle(const Rectangle &rect,
									   const Color &color)
	{
		glBegin(GL_LINE_LOOP);
		glColor4f(color.getR(), color.getG(), color.getB(), color.getA());
		glVertex2i(rect.getLeft(), rect.getBottom());
		glVertex2i(rect.getRight(), rect.getBottom());
		glVertex2i(rect.getRight(), rect.getTop());
		glVertex2i(rect.getLeft(), rect.getTop());
		glEnd();
	}

	void OpenGLGraphics::drawFilledRectangle(const Rectangle &rect,
											 const Color &color)
	{
		glBegin(GL_POLYGON);
		glColor4f(color.getR(), color.getG(), color.getB(), color.getA());	
		glVertex2i(rect.getLeft(), rect.getBottom());
		glVertex2i(rect.getRight(), rect.getBottom());
		glVertex2i(rect.getRight(), rect.getTop());
		glVertex2i(rect.getLeft(), rect.getTop());
		glEnd();
	}

	void OpenGLGraphics::drawPixel(const Point &point,
								   const Color &color)
	{

	}

	void OpenGLGraphics::drawCircle(const Point &center, 
									float radius, 
									const Color &color)
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

	void OpenGLGraphics::drawFilledCircle(const Point &center,
										  float radius, 
										  const Color &color)
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

	void OpenGLGraphics::drawLine(const Point &start, 
								  const Point &end, 
								  const Color &color)
	{
		glBegin(GL_LINE);
		glColor4f(color.getR(), color.getG(), color.getB(), color.getA());
		glVertex2i(start.getX(), start.getY());
		glVertex2i(end.getX(), end.getY());
		glEnd();
	}

	void OpenGLGraphics::setTargetImage(const Image *target)
	{

	}

	void OpenGLGraphics::resetTargetImage()
	{

	}

	void OpenGLGraphics::setClippingRectangle(const Rectangle &rect)
	{

	}

}