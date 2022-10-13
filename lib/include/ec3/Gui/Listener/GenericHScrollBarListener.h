#pragma once
#include "Agui/Widgets/ScrollBar/HScrollBarListener.hpp"

#include <functional>

namespace ec
{
	/**
	 * \brief Generic gui listener that can handle events by
	 * HScrollbar widgets.
	 */
	class GenericHScrollBarListener : public agui::HScrollBarListener
	{
	public:
		using ValueChanged_Callback = std::function<void(agui::HScrollBar* source, int val)>;
		using MinValueChanged_Callback = std::function<void(agui::HScrollBar* source, int val)>;
		using MaxValueChanged_Callback = std::function<void(agui::HScrollBar* source, int val)>;
		using ArrowWidthChanged_Callback = std::function<void(agui::HScrollBar* source, int val)>;
		using LargeAmountChanged_Callback = std::function<void(agui::HScrollBar* source, int val)>;
		using LeftAmountChanged_Callback = std::function<void(agui::HScrollBar* source, int val)>;
		using RightAmountChanged_Callback = std::function<void(agui::HScrollBar* source, int val)>;
		using MinThumbWidthChanged_Callback = std::function<void(agui::HScrollBar* source, int val)>;
		using Death_Callback = std::function<void(agui::HScrollBar* source)>;

		explicit GenericHScrollBarListener();
		~GenericHScrollBarListener();

		void setValueChangedCallback(const ValueChanged_Callback& callback);
		void setMinValueChangedCallback(const MinValueChanged_Callback& callback);
		void setMaxValueChangedCallback(const MaxValueChanged_Callback& callback);
		void setArrowWidthChangedCallback(const ArrowWidthChanged_Callback& callback);
		void setLargeAmountChangedCallback(const LargeAmountChanged_Callback& callback);
		void setLeftAmountChangedCallback(const LeftAmountChanged_Callback& callback);
		void setRightAmountChangedCallback(const RightAmountChanged_Callback& callback);
		void setMinThumbWidthChangedCallback(const MinThumbWidthChanged_Callback& callback);
		void setDeathCallback(const Death_Callback& callback);

		void valueChanged(agui::HScrollBar* source, int val) override;
		void minValueChanged(agui::HScrollBar* source, int val) override;
		void maxValueChanged(agui::HScrollBar* source, int val) override;
		void arrowWidthChanged(agui::HScrollBar* source, int val) override;
		void largeAmountChanged(agui::HScrollBar* source, int val) override;
		void leftAmountChanged(agui::HScrollBar* source, int val) override;
		void rightAmountChanged(agui::HScrollBar* source, int val) override;
		void minThumbWidthChanged(agui::HScrollBar* source, int val) override;
		void death(agui::HScrollBar* source) override;

	private:
		ValueChanged_Callback m_valueChangedCb;
		MinValueChanged_Callback m_minValueChangedCb;
		MaxValueChanged_Callback m_maxValueChangedCb;
		ArrowWidthChanged_Callback m_arrowWidthChangedCb;
		LargeAmountChanged_Callback m_largeAmountChangedCb;
		LeftAmountChanged_Callback m_leftAmountChangedCb;
		RightAmountChanged_Callback m_rightAmountChangedCb;
		MinThumbWidthChanged_Callback m_minThumbWidthChangedCb;
		Death_Callback m_deathCallback;
	};
}