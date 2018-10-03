#pragma once
#include "Agui/Widgets/Slider/SliderListener.hpp"

#include <functional>

namespace ec
{
	class GenericSliderListener : public agui::SliderListener
	{
	public:
		using ValueChanged_Callback = std::function<void(agui::Slider* slider, int val)>;
		using MinValueChanged_Callback = std::function<void(agui::Slider* slider, int val)>;
		using MaxValueChanged_Callback = std::function<void(agui::Slider* slider, int val)>;
		using StepLengthChanged_Callback = std::function<void(agui::Slider* slider, int val)>;
		using AlignMarkerChanged_Callback = std::function<void(agui::Slider* slider, bool val)>;
		using OrientationChanged_Callback = std::function<void(agui::Slider* slider, agui::OrientationEnum orientation)>;
		using Death_Callback = std::function<void(agui::Slider* slider)>;

		explicit GenericSliderListener();
		~GenericSliderListener();

		void setValueChangedCallback(const ValueChanged_Callback& callback);
		void setMinValueChangedCallback(const MinValueChanged_Callback& callback);
		void setMaxValueChangedCallback(const MaxValueChanged_Callback& callback);
		void setStepLengthChangedCallback(const StepLengthChanged_Callback& callback);
		void setAlignMarkerChangedCallback(const AlignMarkerChanged_Callback& callback);
		void setOrientationChangedCallback(const OrientationChanged_Callback& callback);
		void setDeathCallback(const Death_Callback& callback);

		void valueChanged(agui::Slider* slider, int val) override;
		void minValueChanged(agui::Slider* slider, int val) override;
		void maxValueChanged(agui::Slider* slider, int val) override;
		void stepLengthChanged(agui::Slider* slider, int val) override;
		void alignMarkerChanged(agui::Slider* slider, bool val) override;
		void orientationChanged(agui::Slider* slider, agui::OrientationEnum orientation) override;
		void death(agui::Slider* slider) override;

	private:
		ValueChanged_Callback m_valueChangedCb;
		MinValueChanged_Callback m_minValueChangedCb;
		MaxValueChanged_Callback m_maxValueChangedCb;
		StepLengthChanged_Callback m_stepLengthChangedCb;
		AlignMarkerChanged_Callback m_alignMarkerChangedCb;
		OrientationChanged_Callback m_orientationChangedCb;
		Death_Callback m_deathCb;
	};
}
