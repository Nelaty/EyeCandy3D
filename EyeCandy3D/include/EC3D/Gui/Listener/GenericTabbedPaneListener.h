#pragma once
#include "Agui/Widgets/Tab/TabbedPaneListener.hpp"

#include <functional>

namespace ec
{
	class GenericTabbedPaneListener : public agui::TabbedPaneListener
	{
	public:
		using SelectedTabChanged_Callback = std::function<void(agui::TabbedPane* source, agui::Tab* tab)>;
		using ResizingTabContentChanged_Callback = std::function<void(agui::TabbedPane* source, bool resizing)>;
		using TabAdded_Callback = std::function<void(agui::TabbedPane* source, agui::Tab* tab, agui::Widget* tabContent)>;
		using TabRemoved_Callback = std::function<void(agui::TabbedPane* source, agui::Tab* tab)>;
		using Death_Callback = std::function<void(agui::TabbedPane* source)>;

		explicit GenericTabbedPaneListener();
		~GenericTabbedPaneListener();

		void setSelectedTabChangedCallback(const SelectedTabChanged_Callback& callback);
		void setResizingTabContentChangedCallback(const ResizingTabContentChanged_Callback& callback);
		void setTabAddedCallback(const TabAdded_Callback& callback);
		void setTabRemovedCallback(const TabRemoved_Callback& callback);
		void setDeathCallback(const Death_Callback& callback);

		void selectedTabChanged(agui::TabbedPane* source, agui::Tab* tab) override;
		void resizingTabContentChanged(agui::TabbedPane* source, bool resizing) override;
		void tabAdded(agui::TabbedPane* source, agui::Tab* tab, agui::Widget* tabContent) override;
		void tabRemoved(agui::TabbedPane* source, agui::Tab* tab) override;
		void death(agui::TabbedPane* source) override;

	private:
		SelectedTabChanged_Callback m_selectedTabChangedCb;
		ResizingTabContentChanged_Callback m_resizingTabContentChangedCb;
		TabAdded_Callback m_tabAddedCb;
		TabRemoved_Callback m_tabRemovedCb;
		Death_Callback m_deathCb;
	};
}
