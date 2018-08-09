#pragma once
#include "Widget.h"

#include <type_traits>

namespace ec_gui
{
	/*
	* Encapsulates two widgets.
	* Template arguments need to be derived from widget.
	*/
	template<class FirstWidget, class SecondWidget>
	class SlotPair : public Widget
	{
	public:
		explicit SlotPair(Widget* parent);
		~SlotPair();

		/* Slot data access */
		const FirstWidget* GetFirstSlotData() const;
		FirstWidget* GetFirstSlotData();
		void SetFirstSlotData(FirstWidget* slotData);

		const FirstWidget* GetSecondSlotData() const;
		FirstWidget* GetSecondSlotData();
		void SetSecondSlotData(FirstWidget* slotData);

	private:
		FirstWidget* m_firstWidget;
		SecondWidget* m_secondWidget;
	};
}

namespace ec_gui
{
	template<class FirstWidget, class SecondWidget>
	void ec_gui::SlotPair<FirstWidget, SecondWidget>::SetSecondSlotData(FirstWidget* slotData)
	{
		if(m_secondWidget)
		{
			RemoveChild(m_secondWidget);
		}
		AddChild(slotData);
		if(m_firstWidget)
		{
			m_secondWidget->SetPositionX(m_firstWidget->GetSize().x)
		}
		m_secondWidget = slotData;
	}

	template<class FirstWidget, class SecondWidget>
	FirstWidget* ec_gui::SlotPair<FirstWidget, SecondWidget>::GetSecondSlotData()
	{
		return m_secondWidget;
	}

	template<class FirstWidget, class SecondWidget>
	const FirstWidget* ec_gui::SlotPair<FirstWidget, SecondWidget>::GetSecondSlotData() const
	{
		return m_secondWidget;
	}

	template<class FirstWidget, class SecondWidget>
	void ec_gui::SlotPair<FirstWidget, SecondWidget>::SetFirstSlotData(FirstWidget* slotData)
	{
		if(m_firstWidget)
		{
			RemoveChild(m_firstWidget);
		}
		AddChild(slotData);
		if(m_secondWidget)
		{
			m_secondWidget->SetPositionX(m_firstWidget->GetSize().x)
		}
		m_firstWidget = slotData;
	}

	template<class FirstWidget, class SecondWidget>
	FirstWidget* ec_gui::SlotPair<FirstWidget, SecondWidget>::GetFirstSlotData()
	{
		return m_firstWidget;
	}

	template<class FirstWidget, class SecondWidget>
	const FirstWidget* ec_gui::SlotPair<FirstWidget, SecondWidget>::GetFirstSlotData() const
	{
		return m_firstWidget;
	}

	template<class FirstWidget, class SecondWidget>
	ec_gui::SlotPair<FirstWidget, SecondWidget>::~SlotPair()
	{
	}

	template<class FirstWidget, class SecondWidget>
	ec_gui::SlotPair<FirstWidget, SecondWidget>::SlotPair(Widget* parent)
		: Widget(parent)
	{
		static_assert(std::is_base_of<Widget, FirstWidget>, "FirstWidget is not derived from Widget!");
		static_assert(std::is_base_of<Widget, SecondWidget>, "SecondWidget is not derived from Widget!");
	}
}