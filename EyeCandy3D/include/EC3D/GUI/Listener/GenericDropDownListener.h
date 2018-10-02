#pragma once
#include "Agui/Widgets/DropDown/DropDownListener.hpp"

#include <functional>

namespace ec
{
	class GenericDropDownListener : agui::DropDownListener
	{
	public:
		using DeathCallback_Callback = std::function<void(agui::DropDown*)>;
		using DropDownShown_Callback = std::function<void(agui::DropDown*)>;
		using DropDownHidden_Callback = std::function<void(agui::DropDown*)>;
		using ResizeToWidestItemChanged_Callback = std::function<void(agui::DropDown*, bool)>;
		using MaxDropDownHeightChanged_Callback = std::function<void(agui::DropDown, int)>;
		using ItemAdded_Callback = std::function<void(agui::DropDown*, const std::string&)>;
		using ItemRemoved_Callback = std::function<void(agui::DropDown*, const std::string&)>;

		explicit GenericDropDownListener();
		~GenericDropDownListener();

		void setDeathCallback(const DeathCallback_Callback& callback);
		void setDropDownShownCallback(const DropDownShown_Callback& callback);
		void setDropDownHiddenCallback(const DropDownHidden_Callback& callback);
		void setResizeToWidestItemChanged(const ResizeToWidestItemChanged_Callback& callback);
		void setMaxDrioDownHeightChanged(const MaxDropDownHeightChanged_Callback& callback);
		void setItemAddedCallback(const ItemAdded_Callback& callback);
		void setItemRemovedCallback(const ItemRemoved_Callback& callback);

		void death(agui::DropDown* source) override;
		void dropDownShown(agui::DropDown* source) override;
		void dropDownHidden(agui::DropDown* source) override;
		void resizeToWidestItemChanged(agui::DropDown* source, bool resize) override;
		void maxDropDownHeightChanged(agui::DropDown* source, int height) override;
		void itemAdded(agui::DropDown* source, const std::string& item) override;
		void itemRemoved(agui::DropDown* source, const std::string& item) override;

	private:
		DeathCallback_Callback m_deathCb;
		DropDownShown_Callback m_dropDownShownCb;
		DropDownHidden_Callback m_dropDownHidden;
		ResizeToWidestItemChanged_Callback m_resizeToWidestItemChangedCb;
		MaxDropDownHeightChanged_Callback m_maxDropDownHeightChangedCb;
		ItemAdded_Callback m_itemAddedCb;
		ItemRemoved_Callback m_itemRemovedCb;
	};
}