#include "EC3D/Gui/Backend/OpenGLGraphics.h"
#include "EC3D/Gui/Backend/OpenGLImage.h"
#include "EC3D/Gui/GuiShaderInfoObject.h"

#include "EC3D/Core/Camera.h"
#include "EC3D/Core/Viewport.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ec
{	
	OpenGLGraphics::OpenGLGraphics(Camera* camera)
		: m_camera{camera}
	{
		initGeometries();
	}

	OpenGLGraphics::~OpenGLGraphics()
	= default;

	void OpenGLGraphics::_beginPaint()
	{
		auto* shader = m_context.m_guiShader;
		if(shader)
		{
			shader->bind();

			auto dimensions = getDisplaySize();
			auto viewSize = m_camera->getViewport().getSize();
			/*const auto mat = glm::ortho(0,
										dimensions.getWidth(),
										dimensions.getHeight(),
										0);

			shader->setMat4("projection", mat);
			*/
			shader->setInt("uWindowWidth", dimensions.getWidth());
			shader->setInt("uWindowHeight", dimensions.getHeight());

			glViewport(0, 0,
					   dimensions.getWidth(),
					   dimensions.getHeight());
		}
	}

	void OpenGLGraphics::_endPaint()
	{
		if(m_context.m_guiShader)
		{
			m_context.m_guiShader->unbind();
		}
	}

	void OpenGLGraphics::setRenderContext(const GuiRenderContext& context)
	{
		m_context = context;
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
		const auto* image = static_cast<const OpenGLImage*>(bmp);

	}

	void OpenGLGraphics::drawImage(const agui::Image *bmp, 
								   const agui::Point &position, 
								   const float &opacity)
	{
		const auto* image = static_cast<const OpenGLImage*>(bmp);

	}

	void OpenGLGraphics::drawScaledImage(const agui::Image *bmp,
										 const agui::Point &position,
										 const agui::Point &regionStart,
										 const agui::Dimension &regionScale, 
										 const agui::Dimension &scale, 
										 const float &opacity)
	{
		const auto* image = static_cast<const OpenGLImage*>(bmp);


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
		GuiShaderInfoObject obj;
		obj.m_position = {rect.getX(), rect.getY()};
		obj.m_size = {rect.getWidth(), rect.getHeight()};
		obj.m_clippingRect = m_clippingRect;
		obj.m_color = {color.getR(), color.getG(), color.getB(), color.getA()};

		m_primitiveRenderer.render(m_context.m_guiShader,
								   obj,
								   m_rectangleGeometry.get());
	}

	void OpenGLGraphics::drawPixel(const agui::Point &point,
								   const agui::Color &color)
	{

	}

	void OpenGLGraphics::drawCircle(const agui::Point &center, 
									const float radius, 
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
										  const float radius, 
										  const agui::Color &color)
	{
		GuiShaderInfoObject obj;
		obj.m_position = {center.getX(), center.getY()};
		obj.m_size = {radius, radius};
		obj.m_clippingRect = m_clippingRect;
		obj.m_color = {color.getR(), color.getG(), color.getB(), color.getA()};

		m_primitiveRenderer.render(m_context.m_guiShader,
								   obj,
								   m_circleGeometry.get());
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
		m_clippingRect = rect;
	}

	void OpenGLGraphics::initGeometries()
	{
		m_rectangleGeometry = std::make_unique<RectangleGeometry>(2.0f);
		m_circleGeometry = std::make_unique<CircleGeometry>(1.0f, 20);
	}
}
