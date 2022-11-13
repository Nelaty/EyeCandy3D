#include "ec3/Gui/Listener/GenericListBoxListener.h"

namespace ec
{
	GenericListBoxListener::GenericListBoxListener()
		: m_itemAddedCb(nullptr),
		m_itemRemovedCb(nullptr),
		m_sortedChangedCb(nullptr),
		m_rSortedChangedCb(nullptr),
		m_hoverIndexChangedCb(nullptr),
		m_multiselectChangedCb(nullptr),
		m_multiselectExtendedChangedCb(nullptr),
		m_itemHeightChangedCb(nullptr),
		m_mouseWheelSelectChangedCb(nullptr),
		m_deathCb(nullptr)
	{
	}

	GenericListBoxListener::~GenericListBoxListener()
	= default;

	void GenericListBoxListener::setItemAddedCallback(const ItemAdded_Callback& callback)
	{
		m_itemAddedCb = callback;
	}

	void GenericListBoxListener::setItemRemovedCallback(const ItemRemoved_Callback& callback)
	{
		m_itemRemovedCb = callback;
	}

	void GenericListBoxListener::setSortedChangedCallback(const SortedChanged_Callback& callback)
	{
		m_sortedChangedCb = callback;
	}

	void GenericListBoxListener::setRSortedChangedCallback(const RSortedChanged_Callback& callback)
	{
		m_rSortedChangedCb = callback;
	}

	void GenericListBoxListener::setHoverIndexChangedCallback(const HoverIndexChanged_Callback& callback)
	{
		m_hoverIndexChangedCb = callback;
	}

	void GenericListBoxListener::setMultiselectChangedCallback(const MultiselectChanged_Callback& callback)
	{
		m_multiselectChangedCb = callback;
	}

	void GenericListBoxListener::setMultiselectExtendedChangedCallback(const MultiselectExtendedChanged_Callback& callback)
	{
		m_multiselectExtendedChangedCb = callback;
	}

	void GenericListBoxListener::setItemHeightChangedCallback(const ItemHeightChanged_Callback& callback)
	{
		m_itemHeightChangedCb = callback;
	}

	void GenericListBoxListener::setMouseWheelSelectChangedCallback(const MouseWheelSelectChanged_Callback& callback)
	{
		m_mouseWheelSelectChangedCb = callback;
	}

	void GenericListBoxListener::setDeathCallback(const Death_Callback& callback)
	{
		m_deathCb = callback;
	}

	void GenericListBoxListener::itemAdded(agui::ListBox* listBox, 
										   const std::string& item)
	{
		if(m_itemAddedCb)
		{
			m_itemAddedCb(listBox, item);
		}
	}

	void GenericListBoxListener::itemRemoved(agui::ListBox* listBox, 
											 const std::string& item)
	{
		if(m_itemRemovedCb)
		{
			m_itemRemovedCb(listBox, item);
		}
	}

	void GenericListBoxListener::sortedChanged(agui::ListBox* source, 
											   const bool sorted)
	{
		if(m_sortedChangedCb)
		{
			m_sortedChangedCb(source, sorted);
		}
	}

	void GenericListBoxListener::rSortedChanged(agui::ListBox* source, 
												const bool rSorted)
	{
		if(m_rSortedChangedCb)
		{
			m_rSortedChangedCb(source, rSorted);
		}
	}

	void GenericListBoxListener::hoverIndexChanged(agui::ListBox* source,
												   const int index)
	{
		if(m_hoverIndexChangedCb)
		{
			m_hoverIndexChangedCb(source, index);
		}
	}

	void GenericListBoxListener::multiselectChanged(agui::ListBox* source, 
													const bool multiselect)
	{
		if(m_multiselectChangedCb)
		{
			m_multiselectChangedCb(source, multiselect);
		}
	}

	void GenericListBoxListener::multiselectExtendedChanged(agui::ListBox* source, 
															const bool multiselect)
	{
		if(m_multiselectExtendedChangedCb)
		{
			m_multiselectExtendedChangedCb(source, multiselect);
		}
	}	

	void GenericListBoxListener::itemHeightChanged(agui::ListBox* source, 
												   const int height)
	{
		if(m_itemHeightChangedCb)
		{
			m_itemHeightChangedCb(source, height);
		}
	}

	void GenericListBoxListener::mouseWheelSelectionChanged(agui::ListBox* source,
															const bool mWSelection)
	{
		if(m_mouseWheelSelectChangedCb)
		{
			m_mouseWheelSelectChangedCb(source, mWSelection);
		}
	}

	void GenericListBoxListener::death(agui::ListBox* source)
	{
		if(m_deathCb)
		{
			m_deathCb(source);
		}
	}
}
