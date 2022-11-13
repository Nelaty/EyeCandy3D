#include "ec3/Gui/Listener/GenericActionListener.h"

namespace ec
{
	GenericActionListener::GenericActionListener()
		: m_actionPerformedCb(nullptr)
	{
	}

	GenericActionListener::~GenericActionListener()
	= default;

	void GenericActionListener::setActionPerformedCallback(const ActionPerformed_Callback& callback)
	{
		m_actionPerformedCb = callback;
	}

	void GenericActionListener::actionPerformed(const agui::ActionEvent& event)
	{
		if(m_actionPerformedCb)
		{
			m_actionPerformedCb(event);
		}
	}
}
