#pragma once
#include "Agui/Widgets/ScrollBar/VScrollBarListener.hpp"

#include <functional>

namespace ec
{
	class GenericVScrollBarListener : public agui::VScrollBarListener
	{
	public:
		using ValueChanged_Callback = std::function<void(agui::VScrollBar* source, int val)>;
		using MinValueChanged_Callback = std::function<void(agui::VScrollBar* source, int val)>;
		using MaxValueChanged_Callback = std::function<void(agui::VScrollBar* source, int val)>;
		using ArrowHeightChanged_Callback = std::function<void(agui::VScrollBar* source, int val)>;
		using LargeAmountChanged_Callback = std::function<void(agui::VScrollBar* source, int val)>;
		using TopAmountChanged_Callback = std::function<void(agui::VScrollBar* source, int val)>;
		using BottomAmountChanged_Callback = std::function<void(agui::VScrollBar* source, int val)>;
		using MinThumbHeightChanged_Callback = std::function<void(agui::VScrollBar* source, int val)>;
		using Death_Callback = std::function<void(agui::VScrollBar* source)>;

		explicit GenericVScrollBarListener();
		~GenericVScrollBarListener();

		void setValueChangedCallback(const ValueChanged_Callback& callback);
		void setMinValueChangedCallback(const MinValueChanged_Callback& callback);
		void setMaxValueChangedCallback(const MaxValueChanged_Callback& callback);
		void setArrowHeightChangedCallback(const ArrowHeightChanged_Callback& callback);
		void setLargeAmountChangedCallback(const LargeAmountChanged_Callback& callback);
		void setTopAmountChangedCallback(const TopAmountChanged_Callback& callback);
		void setBottomAmountChangedCallback(const BottomAmountChanged_Callback& callback);
		void setMinThumbHeightChangedCallback(const MinThumbHeightChanged_Callback& callback);
		void setDeathCallback(const Death_Callback& callback);

		void valueChanged(agui::VScrollBar* source, int val) override;
		void minValueChanged(agui::VScrollBar* source, int val) override;
		void maxValueChanged(agui::VScrollBar* source, int val) override;
		void arrowHeightChanged(agui::VScrollBar* source, int val) override;
		void largeAmountChanged(agui::VScrollBar* source, int val) override;
		void topAmountChanged(agui::VScrollBar* source, int val) override;
		void bottomAmountChanged(agui::VScrollBar* source, int val) override;
		void minThumbHeightChanged(agui::VScrollBar* source, int val) override;
		void death(agui::VScrollBar* source) override;

	private:
		ValueChanged_Callback m_valueChangedCb;
		MinValueChanged_Callback m_minValueChangedCb;
		MaxValueChanged_Callback m_maxValueChangedCb;
		ArrowHeightChanged_Callback m_arrowHeightChangedCb;
		LargeAmountChanged_Callback m_largeAmountChangedCb;
		TopAmountChanged_Callback m_topAmountChangedCb;
		BottomAmountChanged_Callback m_bottomAmountChangedCb;
		MinThumbHeightChanged_Callback m_minThumbHeightChangedCb;
		Death_Callback m_deathCallback;
	};
}