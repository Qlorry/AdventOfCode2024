#include "Helpers/BaseDay.hpp"

namespace AdventOfCode2024 {

	class Day$<day_number> : public BaseDayTest
	{
	protected:
		Day$<day_number>() : BaseDayTest($<day_number>) {}

		void FirstStage()
		{
			size_t res = 0;
			for (const auto& line : input.GetInputStrByLine())
			{
			}

			PrintAnswer(res);
		}

		void SecondStage()
		{
			size_t res = 0;
			for (const auto& line : input.GetInputStrByLine())
			{
			}

			PrintAnswer(res);
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