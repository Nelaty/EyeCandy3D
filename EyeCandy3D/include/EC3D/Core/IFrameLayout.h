#pragma once
#include "FrameSlot.h"

#include <vector>

namespace ec
{
	class IFrameLayout
	{
	public:
		virtual ~IFrameLayout() = 0;

		virtual void applyLayout(std::vector<FrameSlot>& frames) = 0;

	protected:
		explicit IFrameLayout();
	};
}