target_sources(Agui
PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/Clipboard.cpp
)

if(WIN32)
	target_sources(Agui
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/WinClipboard.cpp
	)
elseif(APPLE)
	target_sources(Agui
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}/OSXClipboard.mm
	)
endif()

