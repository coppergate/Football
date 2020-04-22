#pragma once

#include <array>
#include <math.h>
#include <assert.h>
#include <numeric>

#include "Types.h"

namespace FootballSimulation
{
	template <typename enumType, size_t resolution>
	class ProbabilityDistribution
	{		
		array<enumType, resolution> _Distribution;

	public: 
		void BuildDistribution(const EnumArray& probabilities)
		{
			double_t sum = std::accumulate(probabilities.begin(), probabilities.end(), (double_t) 0);

			size_t curIndex = 0;
			for (auto val : probabilities)
			{
				size_t valIntRange = static_cast<size_t>((val / sum) * resolution);
				_Distribution.
			}

		}

		enumType GetValue(double_t probValue)
		{
			std::assert(0.0 <= probValue <= 1.0);
			size_t index = static_cast<size_t>(resolution * probValue);
			return _Distribution[index];
		}


	};

}