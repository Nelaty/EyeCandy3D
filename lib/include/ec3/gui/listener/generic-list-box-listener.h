#pragma once
#include "Agui/Widgets/ListBox/ListBoxListener.hpp"

#include <functional>

namespace ec
{
	/**
	 * \brief Generic gui listener that can handle events by
	 * ListBox widgets.
	 */
	class GenericListBoxListener : public agui::ListBoxListener
	{
	public:
		using ItemAdded_Callback = std::function<void(agui::ListBox* listBox, const std::string& item)>;
		using ItemRemoved_Callback = std::function<void(agui::ListBox* listBox, const std::string& item)>;
		using SortedChanged_Callback = std::function<void(agui::ListBox* source, bool sorted)>;
		using RSortedChanged_Callback = std::function<void(agui::ListBox* source, bool rSorted)>;
		using HoverIndexChanged_Callback = std::function<void(agui::ListBox* source, int index)>;
		using MultiselectChanged_Callback = std::function<void(agui::ListBox* source, bool multiselect)>;
		using MultiselectExtendedChanged_Callback = std::function<void(agui::ListBox* source, bool multiselect)>;
		using ItemHeightChanged_Callback = std::function<void(agui::ListBox* source, int height)>;
		using MouseWheelSelectChanged_Callback = std::function<void(agui::ListBox* source, bool mWSelection)>;
		using Death_Callback = std::function<void(agui::ListBox* source)>;

		explicit GenericListBoxListener();
		~GenericListBoxListener();

		void setItemAddedCallback(const ItemAdded_Callback& callback);
		void setItemRemovedCallback(const ItemRemoved_Callback& callback);
		void setSortedChangedCallback(const SortedChanged_Callback& callback);
		void setRSortedChangedCallback(const RSortedChanged_Callback& callback);
		void setHoverIndexChangedCallback(const HoverIndexChanged_Callback& callback);
		void setMultiselectChangedCallback(const MultiselectChanged_Callback& callback);
		void setMultiselectExtendedChangedCallback(const MultiselectExtendedChanged_Callback& callback);
		void setItemHeightChangedCallback(const ItemHeightChanged_Callback& callback);
		void setMouseWheelSelectChangedCallback(const MouseWheelSelectChanged_Callback& callback);
		void setDeathCallback(const Death_Callback& callback);

		void itemAdded(agui::ListBox* listBox, const std::string& item) override;
		void itemRemoved(agui::ListBox* listBox, const std::string& item) override;
		void sortedChanged(agui::ListBox* source, bool sorted) override;
		void rSortedChanged(agui::ListBox* source, bool rSorted) override;
		void hoverIndexChanged(agui::ListBox* source, int index) override;
		void multiselectChanged(agui::ListBox* source, bool multiselect) override;
		void multiselectExtendedChanged(agui::ListBox* source, bool multiselect) override;
		void itemHeightChanged(agui::ListBox* source, int height) override;
		void mouseWheelSelectionChanged(agui::ListBox* source, bool mWSelection) override;
		void death(agui::ListBox* source) override;

	private:
		ItemAdded_Callback m_itemAddedCb;
		ItemRemoved_Callback m_itemRemovedCb;
		SortedChanged_Callback m_sortedChangedCb;
		RSortedChanged_Callback m_rSortedChangedCb;
		HoverIndexChanged_Callback m_hoverIndexChangedCb;
		MultiselectChanged_Callback m_multiselectChangedCb;
		MultiselectExtendedChanged_Callback m_multiselectExtendedChangedCb;
		ItemHeightChanged_Callback m_itemHeightChangedCb;
		MouseWheelSelectChanged_Callback m_mouseWheelSelectChangedCb;		
		Death_Callback m_deathCb;
	};
}
