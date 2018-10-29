#pragma once
#include "Agui/Widgets/Label/LabelListener.hpp"

#include <functional>

namespace ec
{
	/**
	 * \brief Generic gui listener that can handle events by Label
	 * widgets.
	 */
	class GenericLabelListener : public agui::LabelListener
	{
	public:
		using AlignmentChanged_Callback = std::function<void(agui::Label* source, agui::AreaAlignmentEnum alignment)>;
		using IsAutosizingChanged_Callback = std::function<void(agui::Label* source, bool autosizing)>;
		using Death_Callback = std::function<void(agui::Label* label)>;

		explicit GenericLabelListener();
		~GenericLabelListener();

		void setAlignmentChangedCallback(const AlignmentChanged_Callback& callback);
		void setIsAutosizingChangedCallback(const IsAutosizingChanged_Callback& callback);
		void setDeathCallback(const Death_Callback& callback);

		void alignmentChanged(agui::Label* source, agui::AreaAlignmentEnum alignment) override;
		void isAutosizingChanged(agui::Label* source, bool autosizing) override;
		void death(agui::Label* source) override;
	
	private:
		AlignmentChanged_Callback m_alignmentChangedCb;
		IsAutosizingChanged_Callback m_isAutosizingChangedCb;
		Death_Callback m_deathCb;
	};
}
