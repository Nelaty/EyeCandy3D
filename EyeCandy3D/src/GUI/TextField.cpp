#include "EC3D/GUI/TextField.h"
#include "EC3D/GUI/Widget.h"

namespace ec_gui
{

	TextField::TextField(Widget* parent)
		: Text(parent)
	{
	}

	TextField::~TextField()
	{

	}

	bool TextField::OnText(unsigned int codepoint, int mods)
	{
		m_text += static_cast<char>(codepoint);
		return __super::OnText(codepoint, mods);
	}

}