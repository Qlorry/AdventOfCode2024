#include "Helpers/BaseDay.hpp"

#include <string>

namespace AdventOfCode2024 {

	class Day1 : public BaseDayTest
	{
	protected:
		Day1() : BaseDayTest(1) {
			std::cout << "Running Day #1!" << std::endl;
		}

		void FirstStage()
		{
			std::vector<int> first, second;
			first.reserve(input.NumberOfLines());
			second.reserve(input.NumberOfLines());
			for (const auto& line : input.GetInputStrByLine())
			{
				auto first_num_end = line.find(" ");
				std::string first_val(line.begin(), line.begin() + first_num_end);
				std::string second_val(line.begin() + first_num_end, line.end());
				first.push_back(std::stoi(first_val));
				second.push_back(std::stoi(second_val));
			}

			std::sort(first.begin(), first.end());
			std::sort(second.begin(), second.end());

			size_t res = 0;

			auto first_it = first.begin();
			auto second_it = second.begin();
			for (; first_it != first.end() && second_it != second.end(); first_it++, second_it++)
			{
				res += static_cast<size_t>(std::abs((*first_it) - (*second_it)));
			}

			PrintAnswer(res);
		}

		void SecondStage()
		{
			std::vector<size_t> first;
			std::map<size_t, size_t> second;
			first.reserve(input.NumberOfLines());
			for (const auto& line : input.GetInputStrByLine())
			{
				auto first_num_end = line.find(" ");
				std::string first_val(line.begin(), line.begin() + first_num_end);
				std::string second_val(line.begin() + first_num_end, line.end());
				first.push_back(std::stoull(first_val));
				second[std::stoull(second_val)] += 1;
			}

			size_t res = 0;

			auto first_it = first.begin();
			for (; first_it != first.end(); first_it++)
			{
				res += *first_it * second[*first_it];
			}

			PrintAnswer(res);
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