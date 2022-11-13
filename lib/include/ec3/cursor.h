#pragma once
#include "ec3/common/common.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace ec
{
	/// Describes all standard cursor types provided by GLFW.
	enum class EC3D_DECLSPEC StandardCursorType : int
	{
		arrow = GLFW_ARROW_CURSOR,
		ibeam = GLFW_IBEAM_CURSOR,
		crosshair = GLFW_CROSSHAIR_CURSOR,
		hand = GLFW_HAND_CURSOR,
		horizontal_resize = GLFW_HRESIZE_CURSOR,
		vertical_resize = GLFW_VRESIZE_CURSOR
	};

	class Window;

	/// A cursor describes the bitmap used for a cursor.
	class EC3D_DECLSPEC Cursor
	{
	public:
		explicit Cursor(StandardCursorType type);
		explicit Cursor(int width, 
						int height,
						unsigned char* pixels,
						int hotSpotX = 0, 
						int hotSpotY = 0);
		~Cursor();

		void useCursor(GLFWwindow* window) const;

	private:
		void initType(StandardCursorType type);
		void initType(int width,
					  int height,
					  unsigned char* pixels, 
					  int hotSpotX = 0, 
					  int hotSpotY = 0);

		void destroyCursor() const;

		GLFWcursor* m_cursor;

		// Custom cursor data
		GLFWimage m_image{};
		int m_width{};
		int m_height{};

		//Standard  cursor data
		bool m_useStandardCursor{};
		StandardCursorType m_type;
	};
}