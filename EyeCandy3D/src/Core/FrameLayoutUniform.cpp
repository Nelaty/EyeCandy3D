#include "EC3D/Core/FrameLayoutUniform.h"

#include <cmath>

namespace ec
{

	FrameLayoutUniform::FrameLayoutUniform(bool preferHorizontal,
										   bool stretchUneven)
		: m_preferHorizontal(preferHorizontal),
		m_stretchUneven(stretchUneven)
	{
	}

	FrameLayoutUniform::~FrameLayoutUniform()
	{
	}

	void FrameLayoutUniform::setSplitPreference(bool preferHorizontal)
	{
		m_preferHorizontal = preferHorizontal;
	}

	void FrameLayoutUniform::setStretchUneven(bool stretch)
	{
		m_stretchUneven = stretch;
	}

	void FrameLayoutUniform::applyLayout(std::vector<FrameSlot>& frames)
	{
		if(frames.empty()) return;

		if(m_preferHorizontal)
		{
			applyLayoutHorizontal(frames);
		}
		else
		{
			applyLayoutVertical(frames);
		}
	}

	void FrameLayoutUniform::applyLayoutHorizontal(std::vector<FrameSlot>& frames)
	{
		auto count = frames.size();

		// Calculate row and column counts
		int rows = ceil(sqrt(count));
		int cols = ceil(float(count) / float(rows));

		// Set position and size of frame slots
		glm::vec2 size(1.0f / cols, 1.0f / rows);

		int index = 0;
		int stretchSizeInElements = 0;
		for(int y = 0; y < rows; ++y)
		{
			for(int x = 0; x < cols; ++x)
			{
				glm::vec2 pos = size * glm::vec2(x, y);

				if(index < count)
				{
					auto& slot = frames[index];
					slot.setPosition(pos);
					slot.setSizeRelative(size);
					++index;
				}
				else
				{
					++stretchSizeInElements;
				}
			}
		}

		// Check if the last frame slot should be stretched
		if(m_stretchUneven && rows * cols != count)
		{
			auto& lastSlot = frames.back();

			glm::vec2 stretchSize = size;
			stretchSize.x = 1.0f - size.x * stretchSizeInElements;
			lastSlot.setSizeRelative(size);
		}
	}

	void FrameLayoutUniform::applyLayoutVertical(std::vector<FrameSlot>& frames)
	{
		auto count = frames.size();

		// Calculate row and column counts
		int cols = ceil(sqrt(count));
		int rows = ceil(float(count) / float(cols));

		// Set position and size of frame slots
		glm::vec2 size(1.0f / cols, 1.0f / rows);


		int index = 0;
		int stretchSizeInElements = 0;
		for(int x = 0; x < cols; ++x)
		{
			for(int y = 0; y < rows; ++y)
			{
				glm::vec2 pos = size * glm::vec2(x, y);

				if(index < count)
				{
					auto& slot = frames[index];
					slot.setPosition(pos);
					slot.setSizeRelative(size);
					++index;
				}
				else
				{
					++stretchSizeInElements;
				}
			}
		}

		// Check if the last frame slot should be stretched
		if(m_stretchUneven && rows * cols != count)
		{
			auto& lastSlot = frames.back();

			glm::vec2 stretchSize = size;
			stretchSize.y = 1.0f - size.y * stretchSizeInElements;
			lastSlot.setSizeRelative(size);
		}
	}
}