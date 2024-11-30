#include "Helpers/BaseDay.hpp"

namespace AdventOfCode2024 {

	class Day$<day_number> : public BaseDayTest
	{
	protected:
		Day$<day_number>() : BaseDayTest($<day_number>) {
			std::cout << "Running Day #$<day_number>!" << std::endl;
		}

		void FirstStage()
		{
			for (const auto& line : input.GetInputStrByLine())
			{
			}
		}

		void SecondStage()
		{
			for (const auto& line : input.GetInputStrByLine())
			{
			}
		}
	};

	TEST_F(Day$<day_number>, FirstStage_Example)
	{
		ReadInput(true);
		FirstStage();
	}

	TEST_F(Day$<day_number>, SecondStage_Example)
	{
		ReadInput(true);
		SecondStage();
	}

	TEST_F(Day$<day_number>, FirstStage)
	{
		ReadInput(false);
		FirstStage();
	}

	TEST_F(Day$<day_number>, SecondStage)
	{
		ReadInput(false);
		SecondStage();
	}
}