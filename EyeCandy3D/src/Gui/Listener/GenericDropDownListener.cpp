#include "EC3D/Gui/Listener/GenericDropDownListener.h"

namespace ec
{
	GenericDropDownListener::GenericDropDownListener()
		: m_deathCb(nullptr),
		m_dropDownShownCb(nullptr),
		m_dropDownHiddenCb(nullptr),
		m_resizeToWidestItemChangedCb(nullptr),
		m_maxDropDownHeightChangedCb(nullptr),
		m_itemAddedCb(nullptr),
		m_itemRemovedCb(nullptr)
	{
	}

	GenericDropDownListener::~GenericDropDownListener()
	= default;

	void GenericDropDownListener::setDeathCallback(const DeathCallback_Callback& callback)
	{
		m_deathCb = callback;
	}

	void GenericDropDownListener::setDropDownShownCallback(const DropDownShown_Callback& callback)
	{
		m_dropDownShownCb = callback;
	}

	void GenericDropDownListener::setDropDownHiddenCallback(const DropDownHidden_Callback& callback)
	{
		m_dropDownHiddenCb = callback;
	}

	void GenericDropDownListener::setResizeToWidestItemChanged(const ResizeToWidestItemChanged_Callback& callback)
	{
		m_resizeToWidestItemChangedCb = callback;
	}

	void GenericDropDownListener::setMaxDropDownHeightChanged(const MaxDropDownHeightChanged_Callback& callback)
	{
		m_maxDropDownHeightChangedCb = callback;
	}

	void GenericDropDownListener::setItemAddedCallback(const ItemAdded_Callback& callback)
	{
		m_itemAddedCb = callback;
	}

	void GenericDropDownListener::setItemRemovedCallback(const ItemRemoved_Callback& callback)
	{
		m_itemRemovedCb = callback;
	}

	void GenericDropDownListener::death(agui::DropDown* source)
	{
		if(m_deathCb)
		{
			m_deathCb(source);
		}
	}

	void GenericDropDownListener::dropDownShown(agui::DropDown* source)
	{
		if(m_dropDownShownCb)
		{
			m_dropDownShownCb(source);
		}
	}

	void GenericDropDownListener::dropDownHidden(agui::DropDown* source)
	{
		if(m_dropDownHiddenCb)
		{
			m_dropDownHiddenCb(source);
		}
	}

	void GenericDropDownListener::resizeToWidestItemChanged(agui::DropDown* source,
															const bool resize)
	{
		if(m_resizeToWidestItemChangedCb)
		{
			m_resizeToWidestItemChangedCb(source, resize);
		}
	}

	void GenericDropDownListener::maxDropDownHeightChanged(agui::DropDown* source,
														   const int height)
	{
		if(m_maxDropDownHeightChangedCb)
		{
			m_maxDropDownHeightChangedCb(source, height);
		}
	}

	void GenericDropDownListener::itemAdded(agui::DropDown* source, 
											const std::string& item)
	{
		if(m_itemAddedCb)
		{
			m_itemAddedCb(source, item);
		}
	}

	void GenericDropDownListener::itemRemoved(agui::DropDown* source,
											  const std::string& item)
	{
		if(m_itemRemovedCb)
		{
			m_itemRemovedCb(source, item);
		}
	}
}
