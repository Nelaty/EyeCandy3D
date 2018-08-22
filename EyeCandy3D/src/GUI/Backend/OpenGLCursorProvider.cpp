#include "EC3D/GUI/Backend/OpenGLCursorProvider.h"

namespace agui
{

	OpenGLCursorProvider::OpenGLCursorProvider()
		: m_standardCursorType{ec::StandardCursorType::arrow}
	{
	}

	OpenGLCursorProvider::~OpenGLCursorProvider()
	= default;

	bool OpenGLCursorProvider::setCursor(CursorEnum cursor)
	{
		switch(cursor)
		{
			case CursorProvider::DEFAULT_CURSOR:
				return changeCursor(ec::StandardCursorType::arrow);
			case CursorProvider::ARROW_CURSOR:
				return changeCursor(ec::StandardCursorType::arrow);
			case CursorProvider::BUSY_CURSOR:
				return changeCursor(ec::StandardCursorType::arrow);
			case CursorProvider::QUESTION_CURSOR:
				return changeCursor(ec::StandardCursorType::arrow);
			case CursorProvider::EDIT_CURSOR:
				return changeCursor(ec::StandardCursorType::ibeam);
			case CursorProvider::MOVE_CURSOR:
				return changeCursor(ec::StandardCursorType::arrow);
			case CursorProvider::RESIZE_N_CURSOR:
				return changeCursor(ec::StandardCursorType::vertical_resize);
			case CursorProvider::RESIZE_W_CURSOR:
				return changeCursor(ec::StandardCursorType::horizontal_resize);
			case CursorProvider::RESIZE_S_CURSOR:
				return changeCursor(ec::StandardCursorType::vertical_resize);
			case CursorProvider::RESIZE_E_CURSOR:
				return changeCursor(ec::StandardCursorType::horizontal_resize);
			case CursorProvider::RESIZE_NW_CURSOR:
				return changeCursor(ec::StandardCursorType::vertical_resize);
			case CursorProvider::RESIZE_SW_CURSOR:
				return changeCursor(ec::StandardCursorType::vertical_resize);
			case CursorProvider::RESIZE_SE_CURSOR:
				return changeCursor(ec::StandardCursorType::vertical_resize);
			case CursorProvider::RESIZE_NE_CURSOR:
				return changeCursor(ec::StandardCursorType::vertical_resize);
			case CursorProvider::LINK_CURSOR:
				return changeCursor(ec::StandardCursorType::hand);
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
		auto* cursor = getCursor(type);
		if(cursor)
		{
			auto* window = glfwGetCurrentContext();
			cursor->useCursor(window);
			return true;
		}
		
		printf("Couldn't set cursor!\n");
		return false;
	}

	ec::Cursor* OpenGLCursorProvider::createCursor(ec::StandardCursorType type)
	{
		ec::Cursor cursor(type);
		m_cursors.insert(std::make_pair(type, cursor));
		return getCursor(type);
	}
}
