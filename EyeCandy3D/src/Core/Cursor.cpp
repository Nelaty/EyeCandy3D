#include "EC3D/Core/Cursor.h"
#include "EC3D/Core/Window.h"

namespace ec
{
	Cursor::Cursor(StandardCursorType type)
	{
		InitType(type);
	}

	Cursor::Cursor(int width, int height, unsigned char* pixels, int hotSpotX, int hotSpotY)
	{
		InitType(width, height, pixels);
	}

	Cursor::~Cursor()
	{
	}

	void Cursor::InitType(StandardCursorType type)
	{
		DestroyCursor();

		m_cursor = glfwCreateStandardCursor((int)type);
	}

	void Cursor::InitType(int width, int height, unsigned char* pixels, int hotSpotX, int hotSpotY)
	{
		DestroyCursor();

		GLFWimage image;
		image.width = width;
		image.height = height;
		image.pixels = pixels;

		m_cursor = glfwCreateCursor(&image, hotSpotX, hotSpotY);
	}

	void Cursor::UseCursor(GLFWwindow* window)
	{
		glfwSetCursor(window, m_cursor);
	}

	void Cursor::DestroyCursor()
	{
		glfwDestroyCursor(m_cursor);
	}

}