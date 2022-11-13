#include "ec3/cursor.h"

#include "ec3/window/window.h"

namespace ec
{
	Cursor::Cursor(const StandardCursorType type)
	{
		initType(type);
	}

	Cursor::Cursor(const int width,
	               const int height, 
				   unsigned char* pixels, 
				   int hotSpotX, 
				   int hotSpotY)
	{
		initType(width, height, pixels);
	}

	Cursor::~Cursor() = default;

	void Cursor::initType(StandardCursorType type)
	{
		destroyCursor();

		m_cursor = glfwCreateStandardCursor(static_cast<int>(type));
	}

	void Cursor::initType(const int width,
	                      const int height,
						  unsigned char* pixels,
	                      const int hotSpotX,
	                      const int hotSpotY)
	{
		destroyCursor();

		GLFWimage image;
		image.width = width;
		image.height = height;
		image.pixels = pixels;

		m_cursor = glfwCreateCursor(&image, hotSpotX, hotSpotY);
	}

	void Cursor::useCursor(GLFWwindow* window) const
	{
		glfwSetCursor(window, m_cursor);
	}

	void Cursor::destroyCursor() const
	{
		glfwDestroyCursor(m_cursor);
	}

}