#include "Helpers/BaseDay.hpp"

namespace AdventOfCode2024 {

	class Day1 : public BaseDayTest
	{
	protected:
		Day1() : BaseDayTest(1) {
			std::cout << "Running Day #1!" << std::endl;
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


	TEST_F(Day1, FirstStage_Example)
	{
		ReadInput(true);
		FirstStage();
	}

	TEST_F(Day1, SecondStage_Example)
	{
		ReadInput(true);
		SecondStage();
	}

	TEST_F(Day1, FirstStage)
	{
		ReadInput(false);
		FirstStage();
	}

	TEST_F(Day1, SecondStage)
	{
		ReadInput(false);
		SecondStage();
	}
}