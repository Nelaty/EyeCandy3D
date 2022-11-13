#include "ec3/Gui/Listener/GenericSliderListener.h"

namespace ec
{
	GenericSliderListener::GenericSliderListener()
		: m_valueChangedCb(nullptr),
		m_minValueChangedCb(nullptr),
		m_maxValueChangedCb(nullptr),
		m_stepLengthChangedCb(nullptr),
		m_alignMarkerChangedCb(nullptr),
		m_orientationChangedCb(nullptr),
		m_deathCb(nullptr)
	{
	}

	GenericSliderListener::~GenericSliderListener()
	= default;

	void GenericSliderListener::setValueChangedCallback(const ValueChanged_Callback& callback)
	{
		m_valueChangedCb = callback;
	}

	void GenericSliderListener::setMinValueChangedCallback(const MinValueChanged_Callback& callback)
	{
		m_minValueChangedCb = callback;
	}

	void GenericSliderListener::setMaxValueChangedCallback(const MaxValueChanged_Callback& callback)
	{
		m_maxValueChangedCb = callback;
	}

	void GenericSliderListener::setStepLengthChangedCallback(const StepLengthChanged_Callback& callback)
	{
		m_stepLengthChangedCb = callback;
	}

	void GenericSliderListener::setAlignMarkerChangedCallback(const AlignMarkerChanged_Callback& callback)
	{
		m_alignMarkerChangedCb = callback;
	}

	void GenericSliderListener::setOrientationChangedCallback(const OrientationChanged_Callback& callback)
	{
		m_orientationChangedCb = callback;
	}

	void GenericSliderListener::setDeathCallback(const Death_Callback& callback)
	{
		m_deathCb = callback;
	}

	void GenericSliderListener::valueChanged(agui::Slider* slider,
											 const int val)
	{
		if(m_valueChangedCb)
		{
			m_valueChangedCb(slider, val);
		}
	}

	void GenericSliderListener::minValueChanged(agui::Slider* slider,
												const int val)
	{
		if(m_minValueChangedCb)
		{
			m_minValueChangedCb(slider, val);
		}
	}

	void GenericSliderListener::maxValueChanged(agui::Slider* slider,
												const int val)
	{
		if(m_maxValueChangedCb)
		{
			m_maxValueChangedCb(slider, val);
		}
	}

	void GenericSliderListener::stepLengthChanged(agui::Slider* slider, 
												  const int val)
	{
		if(m_stepLengthChangedCb)
		{
			m_stepLengthChangedCb(slider, val);
		}
	}

	void GenericSliderListener::alignMarkerChanged(agui::Slider* slider,
												   const bool val)
	{
		if(m_alignMarkerChangedCb)
		{
			m_alignMarkerChangedCb(slider, val);
		}
	}

	void GenericSliderListener::orientationChanged(agui::Slider* slider, 
												   const agui::OrientationEnum orientation)
	{
		if(m_orientationChangedCb)
		{
			m_orientationChangedCb(slider, orientation);
		}
	}

	void GenericSliderListener::death(agui::Slider* slider)
	{
		if(m_deathCb)
		{
			m_deathCb(slider);
		}
	}
}