#include "EC3D/Gui/Listener/GenericTabbedPaneListener.h"

namespace ec
{
	GenericTabbedPaneListener::GenericTabbedPaneListener()
		: m_selectedTabChangedCb(nullptr),
		m_resizingTabContentChangedCb(nullptr),
		m_tabAddedCb(nullptr),
		m_tabRemovedCb(nullptr),
		m_deathCb(nullptr)
	{
	}

	GenericTabbedPaneListener::~GenericTabbedPaneListener()
	= default;

	void GenericTabbedPaneListener::setSelectedTabChangedCallback(const SelectedTabChanged_Callback& callback)
	{
		m_selectedTabChangedCb = callback;
	}

	void GenericTabbedPaneListener::setResizingTabContentChangedCallback(const ResizingTabContentChanged_Callback& callback)
	{
		m_resizingTabContentChangedCb = callback;
	}

	void GenericTabbedPaneListener::setTabAddedCallback(const TabAdded_Callback& callback)
	{
		m_tabAddedCb = callback;
	}

	void GenericTabbedPaneListener::setTabRemovedCallback(const TabRemoved_Callback& callback)
	{
		m_tabRemovedCb = callback;
	}

	void GenericTabbedPaneListener::setDeathCallback(const Death_Callback& callback)
	{
		m_deathCb = callback;
	}

	void GenericTabbedPaneListener::selectedTabChanged(agui::TabbedPane* source, 
													   agui::Tab* tab)
	{
		if(m_selectedTabChangedCb)
		{
			m_selectedTabChangedCb(source, tab);
		}
	}

	void GenericTabbedPaneListener::resizingTabContentChanged(agui::TabbedPane* source, 
															  const bool resizing)
	{
		if(m_resizingTabContentChangedCb)
		{
			m_resizingTabContentChangedCb(source, resizing);
		}
	}

	void GenericTabbedPaneListener::tabAdded(agui::TabbedPane* source, 
											 agui::Tab* tab,
											 agui::Widget* tabContent)
	{
		if(m_tabAddedCb)
		{
			m_tabAddedCb(source, tab, tabContent);
		}
	}

	void GenericTabbedPaneListener::tabRemoved(agui::TabbedPane* source, 
											   agui::Tab* tab)
	{
		if(m_tabRemovedCb)
		{
			m_tabRemovedCb(source, tab);
		}
	}

	void GenericTabbedPaneListener::death(agui::TabbedPane* source)
	{
		if(m_deathCb)
		{
			m_deathCb(source);
		}
	}
}
