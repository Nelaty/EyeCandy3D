#pragma once
#include "Widget.h"

#include <type_traits>

namespace ec_gui
{
	/*
	* A slot encapsulates a widget.
	* Template arguments need to be derived from widget.
	*/
	template<class WidgetType>
	class Slot : public Widget
	{
	public:
		explicit Slot(Widget* parent);
		~Slot();

		/* Slot data access */
		const WidgetType* GetSlotData() const;
		WidgetType* GetSlotData();
		void SetSlotData(WidgetType* slotData);

	private:
		WidgetType* m_slotData;
	};
}

namespace ec_gui
{
	template<class WidgetType>
	void ec_gui::Slot<WidgetType>::SetSlotData(WidgetType* slotData)
	{
		if(m_slotData)
		{
			removeChild(slotData);
		}
		addChild(slotData);
		m_slotData = slotData;
	}

	template<class WidgetType>
	WidgetType* ec_gui::Slot<WidgetType>::GetSlotData()
	{
		return m_slotData;
	}

	template<class WidgetType>
	const WidgetType* ec_gui::Slot<WidgetType>::GetSlotData() const
	{
		return m_slotData;
	}

	template<class WidgetType>
	ec_gui::Slot<WidgetType>::~Slot()
	{
	}

	template<class WidgetType>
	ec_gui::Slot<WidgetType>::Slot(Widget* parent)
		: Widget(parent)
	{
		static_assert(std::is_base_of<Widget, WidgetType>::value, "WidgetType is not a subclass of Widget!");
	}
}