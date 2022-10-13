#include "ec3/Gui/Backend/OpenGLGraphics.h"
#include "ec3/Gui/Backend/OpenGLImage.h"
#include "ec3/Gui/GuiShaderInfoObject.h"

#include "ec3/Graphics/Camera.h"
#include "ec3/Window/Viewport.h"
#include "ec3/Graphics/Geometry/LineGeometryFactory.h"

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
			auto viewPos = m_camera->getViewport().getPosition();
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

	void OpenGLGraphics::drawImage(const agui::Image* bmp, 
								   const agui::Point& position,
								   const agui::Point& regionStart,
								   const agui::Dimension& regionSize,
								   const float& opacity)
	{
		const auto* image = static_cast<const OpenGLImage*>(bmp);

	}

	void OpenGLGraphics::drawImage(const agui::Image* bmp, 
								   const agui::Point& position, 
								   const float& opacity)
	{
		const auto* image = static_cast<const OpenGLImage*>(bmp);

		GuiShaderInfoObject obj;
		obj.m_position = glm::vec2(position.getX(), position.getY());
		obj.m_offset = glm::vec2(getOffset().getX(), getOffset().getY());
		obj.m_size = glm::vec2(bmp->getWidth(), bmp->getHeight());
		obj.m_clippingRect = m_clippingRect;
		obj.m_color = glm::vec4(0.0f, 0.0f, 0.0f, opacity * getGlobalOpacity());
		obj.m_usesTexture = true;
		obj.m_texture = image->getTexture();

		m_primitiveRenderer.render(m_context.m_guiShader,
								   obj,
								   m_rectangleGeometry.get());
	}

	void OpenGLGraphics::drawScaledImage(const agui::Image* bmp,
										 const agui::Point& position,
										 const agui::Point& regionStart,
										 const agui::Dimension& regionScale, 
										 const agui::Dimension& scale, 
										 const float& opacity)
	{
		const auto* image = static_cast<const OpenGLImage*>(bmp);

		GuiShaderInfoObject obj;
		obj.m_position = glm::vec2(position.getX(), position.getY());
		obj.m_offset = glm::vec2(getOffset().getX(), getOffset().getY());
		obj.m_size = glm::vec2(scale.getWidth(), scale.getHeight());
		obj.m_clippingRect = m_clippingRect;
		obj.m_color = {0.0f, 0.0f, 0.0f, opacity * getGlobalOpacity()};
		obj.m_usesTexture = true;
		obj.m_texture = image->getTexture();

		m_primitiveRenderer.render(m_context.m_guiShader,
								   obj,
								   m_rectangleGeometry.get());
	}

	void OpenGLGraphics::drawText(const agui::Point& position, 
								  const char* text,
								  const agui::Color& color,
								  const agui::Font* font,
	                              agui::AlignmentEnum align)
	{

	}

	void OpenGLGraphics::drawRectangle(const agui::Rectangle& rect,
									   const agui::Color& color)
	{
		GuiShaderInfoObject obj;
		obj.m_position = glm::vec2(rect.getX(), rect.getY());
		obj.m_offset = glm::vec2(getOffset().getX(), getOffset().getY());
		obj.m_size = glm::vec2(rect.getWidth(), rect.getHeight());
		obj.m_clippingRect = m_clippingRect;
		obj.m_color = glm::vec4(color.getR(), color.getG(), color.getB(), color.getA() * getGlobalOpacity());

		m_primitiveRenderer.render(m_context.m_guiShader,
								   obj,
								   m_rectangleOutlineGeometry.get());
	}

	void OpenGLGraphics::drawFilledRectangle(const agui::Rectangle& rect,
											 const agui::Color& color)
	{
		GuiShaderInfoObject obj;
		obj.m_position = glm::vec2(rect.getX(), rect.getY());
		obj.m_offset = glm::vec2(getOffset().getX(), getOffset().getY());
		obj.m_size = glm::vec2(rect.getWidth(), rect.getHeight());
		obj.m_clippingRect = m_clippingRect;
		obj.m_color = glm::vec4(color.getR(),
								color.getG(),
								color.getB(),
								color.getA() * getGlobalOpacity());

		m_primitiveRenderer.render(m_context.m_guiShader,
								   obj,
								   m_rectangleGeometry.get());
	}

	void OpenGLGraphics::drawPixel(const agui::Point& point,
								   const agui::Color& color)
	{

	}

	void OpenGLGraphics::drawCircle(const agui::Point& center, 
									const float radius, 
									const agui::Color& color)
	{
		GuiShaderInfoObject obj;
		obj.m_position = glm::vec2(center.getX(), center.getY());
		obj.m_offset = glm::vec2(getOffset().getX(), getOffset().getY());
		obj.m_size = glm::vec2(radius, radius);
		obj.m_clippingRect = m_clippingRect;
		obj.m_color = glm::vec4(color.getR(), color.getG(), color.getB(), color.getA() * getGlobalOpacity());

		m_primitiveRenderer.render(m_context.m_guiShader,
								   obj,
								   m_circleOutlineGeometry.get());
	}

	void OpenGLGraphics::drawFilledCircle(const agui::Point& center,
										  const float radius, 
										  const agui::Color& color)
	{
		GuiShaderInfoObject obj;
		obj.m_position = glm::vec2(center.getX(), center.getY());
		obj.m_offset = glm::vec2(getOffset().getX(), getOffset().getY());
		obj.m_size = glm::vec2(radius, radius);
		obj.m_clippingRect = m_clippingRect;
		obj.m_color = glm::vec4(color.getR(), color.getG(), color.getB(), color.getA() * getGlobalOpacity());

		m_primitiveRenderer.render(m_context.m_guiShader,
								   obj,
								   m_circleGeometry.get());
	}

	void OpenGLGraphics::drawLine(const agui::Point& start,
								  const agui::Point& end,
								  const agui::Color& color)
	{
		
	}

	void OpenGLGraphics::setTargetImage(const agui::Image* target)
	{

	}

	void OpenGLGraphics::resetTargetImage()
	{

	}

	void OpenGLGraphics::setClippingRectangle(const agui::Rectangle& rect)
	{
		m_clippingRect = rect;
	}

	void OpenGLGraphics::initGeometries()
	{
		m_rectangleGeometry = std::make_unique<RectangleGeometry>(2.0f);
		m_circleGeometry = std::make_unique<CircleGeometry>(1.0f, 20);
		m_rectangleOutlineGeometry = LineGeometryFactory::createRectangleOutlineGeometry(2.0f, 2.0f);
		m_circleOutlineGeometry = LineGeometryFactory::createCircleOutlineGeometry(1.0f);
		
	}
}
