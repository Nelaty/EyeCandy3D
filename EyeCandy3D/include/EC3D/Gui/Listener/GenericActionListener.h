#pragma once
#include "Agui/ActionListener.hpp"

#include <functional>

namespace ec
{
	/**
	 * \brief Generic gui listener that can handle ActionEvents.
	 */
	class GenericActionListener : public agui::ActionListener
	{
	public:
		using ActionPerformed_Callback = std::function<void(const agui::ActionEvent& event)>;

		explicit GenericActionListener();
		~GenericActionListener();

		void setActionPerformedCallback(const ActionPerformed_Callback& callback);

		void actionPerformed(const agui::ActionEvent& event) override;

	private:
		ActionPerformed_Callback m_actionPerformedCb;
	};
}