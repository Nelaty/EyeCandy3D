#include "EC3D/Gui/Listener/GenericLabelListener.h"

namespace ec
{
	GenericLabelListener::GenericLabelListener()
		: m_alignmentChangedCb(nullptr),
		m_isAutosizingChangedCb(nullptr),
		m_deathCb(nullptr)
	{
	}

	GenericLabelListener::~GenericLabelListener()
	= default;

	void GenericLabelListener::setAlignmentChangedCallback(const AlignmentChanged_Callback& callback)
	{
		m_alignmentChangedCb = callback;
	}

	void GenericLabelListener::setIsAutosizingChangedCallback(const IsAutosizingChanged_Callback& callback)
	{
		m_isAutosizingChangedCb = callback;
	}

	void GenericLabelListener::setDeathCallback(const Death_Callback& callback)
	{
		m_deathCb = callback;
	}

	void GenericLabelListener::alignmentChanged(agui::Label* source,
												const agui::AreaAlignmentEnum alignment)
	{
		if(m_alignmentChangedCb)
		{
			m_alignmentChangedCb(source, alignment);
		}
	}

	void GenericLabelListener::isAutosizingChanged(agui::Label* source,
												   const bool autosizing)
	{
		if(m_isAutosizingChangedCb)
		{
			m_isAutosizingChangedCb(source, autosizing);
		}
	}

	void GenericLabelListener::death(agui::Label* source)
	{
		if(m_deathCb)
		{
			m_deathCb(source);
		}
	}
}
