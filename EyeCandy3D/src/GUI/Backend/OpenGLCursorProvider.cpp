#include "EC3D/GUI/Backend/OpenGLCursorProvider.h"

namespace agui
{

	OpenGLCursorProvider::OpenGLCursorProvider()
		: m_standardCursorType{ec::StandardCursorType::arrow}
	{
	}

	OpenGLCursorProvider::~OpenGLCursorProvider()
	{
	}

	bool OpenGLCursorProvider::setCursor(CursorEnum cursor)
	{
		switch(cursor)
		{
			case CursorProvider::DEFAULT_CURSOR:
				return changeCursor(ec::StandardCursorType::arrow);
				break;
			case CursorProvider::ARROW_CURSOR:
				return changeCursor(ec::StandardCursorType::arrow);
				break;
			case CursorProvider::BUSY_CURSOR:
				return changeCursor(ec::StandardCursorType::arrow);
				break;
			case CursorProvider::QUESTION_CURSOR:
				return changeCursor(ec::StandardCursorType::arrow);
				break;
			case CursorProvider::EDIT_CURSOR:
				return changeCursor(ec::StandardCursorType::ibeam);
				break;
			case CursorProvider::MOVE_CURSOR:
				return changeCursor(ec::StandardCursorType::arrow);
				break;
			case CursorProvider::RESIZE_N_CURSOR:
				return changeCursor(ec::StandardCursorType::vertical_resize);
				break;
			case CursorProvider::RESIZE_W_CURSOR:
				return changeCursor(ec::StandardCursorType::horizontal_resize);
				break;
			case CursorProvider::RESIZE_S_CURSOR:
				return changeCursor(ec::StandardCursorType::vertical_resize);
				break;
			case CursorProvider::RESIZE_E_CURSOR:
				return changeCursor(ec::StandardCursorType::horizontal_resize);
				break;
			case CursorProvider::RESIZE_NW_CURSOR:
				return changeCursor(ec::StandardCursorType::vertical_resize);
				break;
			case CursorProvider::RESIZE_SW_CURSOR:
				return changeCursor(ec::StandardCursorType::vertical_resize);
				break;
			case CursorProvider::RESIZE_SE_CURSOR:
				return changeCursor(ec::StandardCursorType::vertical_resize);
				break;
			case CursorProvider::RESIZE_NE_CURSOR:
				return changeCursor(ec::StandardCursorType::vertical_resize);
				break;
			case CursorProvider::LINK_CURSOR:
				return changeCursor(ec::StandardCursorType::hand);
				break;
			default:
				break;
		}

		return false;
	}

	ec::Cursor* OpenGLCursorProvider::getCursor(ec::StandardCursorType type)
	{
		auto foundCursor = m_cursors.find(type);
		if(foundCursor != m_cursors.end())
		{
			return &foundCursor->second;
		}

		return createCursor(type);
	}

	bool OpenGLCursorProvider::changeCursor(ec::StandardCursorType type)
	{
		ec::Cursor* cursor = getCursor(type);
		if(cursor)
		{
			GLFWwindow* window = glfwGetCurrentContext();
			cursor->UseCursor(window);
			return true;
		}
		else
		{
			printf("Couldn't set cursor!\n");
			return false;
		}
	}

	ec::Cursor* OpenGLCursorProvider::createCursor(ec::StandardCursorType type)
	{
		ec::Cursor cursor(type);
		m_cursors.insert(std::make_pair(type, cursor));
		return getCursor(type);
	}
}
