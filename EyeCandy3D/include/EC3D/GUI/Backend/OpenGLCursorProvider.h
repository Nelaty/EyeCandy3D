#pragma once
#include "Agui/CursorProvider.hpp"
#include "EC3D/Common/Common.h"

#include "EC3D/Core/Cursor.h"

#include <map>

namespace agui
{
	class EC3D_DECLSPEC OpenGLCursorProvider : public CursorProvider
	{
	public:
		OpenGLCursorProvider();
		virtual ~OpenGLCursorProvider();
		
		bool setCursor(CursorEnum cursor) override;

	private:
		/** 
		 * Get the cursor with the given key. If it does not exist,
		 * create it.
		 * \return The cursor if it exists/could be created, nullptr otherwise.
		 */
		ec::Cursor* getCursor(ec::StandardCursorType type);

		bool changeCursor(ec::StandardCursorType type);
		ec::Cursor* createCursor(ec::StandardCursorType type);

		ec::StandardCursorType m_standardCursorType;

		std::map<ec::StandardCursorType, ec::Cursor> m_cursors;
	};
}
