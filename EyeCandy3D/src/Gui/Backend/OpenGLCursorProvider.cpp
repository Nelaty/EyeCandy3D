#include "ec3/Gui/Backend/OpenGLCursorProvider.h"

#include <stdio.h>

namespace ec
{

	OpenGLCursorProvider::OpenGLCursorProvider()
		: m_standardCursorType{ec::StandardCursorType::arrow}
	{
	}

	OpenGLCursorProvider::~OpenGLCursorProvider()
	= default;

	bool OpenGLCursorProvider::setCursor(const CursorEnum cursor)
	{
		switch(cursor)
		{
			case agui::CursorProvider::DEFAULT_CURSOR:
				return changeCursor(ec::StandardCursorType::arrow);
			case agui::CursorProvider::ARROW_CURSOR:
				return changeCursor(ec::StandardCursorType::arrow);
			case agui::CursorProvider::BUSY_CURSOR:
				return changeCursor(ec::StandardCursorType::arrow);
			case agui::CursorProvider::QUESTION_CURSOR:
				return changeCursor(ec::StandardCursorType::arrow);
			case agui::CursorProvider::EDIT_CURSOR:
				return changeCursor(ec::StandardCursorType::ibeam);
			case agui::CursorProvider::MOVE_CURSOR:
				return changeCursor(ec::StandardCursorType::arrow);
			case agui::CursorProvider::RESIZE_N_CURSOR:
				return changeCursor(ec::StandardCursorType::vertical_resize);
			case agui::CursorProvider::RESIZE_W_CURSOR:
				return changeCursor(ec::StandardCursorType::horizontal_resize);
			case agui::CursorProvider::RESIZE_S_CURSOR:
				return changeCursor(ec::StandardCursorType::vertical_resize);
			case agui::CursorProvider::RESIZE_E_CURSOR:
				return changeCursor(ec::StandardCursorType::horizontal_resize);
			case agui::CursorProvider::RESIZE_NW_CURSOR:
				return changeCursor(ec::StandardCursorType::vertical_resize);
			case agui::CursorProvider::RESIZE_SW_CURSOR:
				return changeCursor(ec::StandardCursorType::vertical_resize);
			case agui::CursorProvider::RESIZE_SE_CURSOR:
				return changeCursor(ec::StandardCursorType::vertical_resize);
			case agui::CursorProvider::RESIZE_NE_CURSOR:
				return changeCursor(ec::StandardCursorType::vertical_resize);
			case agui::CursorProvider::LINK_CURSOR:
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
