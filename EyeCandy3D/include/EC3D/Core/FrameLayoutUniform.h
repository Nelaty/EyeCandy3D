#pragma once
#include "IFrameLayout.h"

namespace ec
{
	class FrameLayoutUniform : public IFrameLayout
	{
	public:
		explicit FrameLayoutUniform(bool preferHorizontal = true,
									bool stretchUneven = true);
		~FrameLayoutUniform();

		void setSplitPreference(bool preferHorizontal);
		void setStretchUneven(bool stretchUneven);

		void applyLayout(std::vector<FrameSlot>& frames);

	private:
		void applyLayoutHorizontal(std::vector<FrameSlot>& frames);
		void applyLayoutVertical(std::vector<FrameSlot>& frames);

		bool m_stretchUneven{true};
		bool m_preferHorizontal{true};
	};
}