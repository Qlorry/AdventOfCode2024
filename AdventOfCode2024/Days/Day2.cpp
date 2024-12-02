#include "Helpers/BaseDay.hpp"
#include "PuzzleInput.h"

#include <optional>

namespace AdventOfCode2024 {

	class Day2 : public BaseDayTest
	{
	protected:
		Day2() : BaseDayTest(2) {
			std::cout << "Running Day #2!" << std::endl;
		}

		bool IsSafe(const std::vector<int> report)
		{
			return std::all_of(report.begin(), report.end(),
				[prev = std::optional<int>(), increasing = std::optional<bool>()]
				(int item) mutable
				{
					if (!prev.has_value())
					{
						prev = item;
						return true;
					}
					if (!increasing.has_value())
					{
						increasing = (item - prev.value()) > 0;
					}

					auto diff = item - prev.value();
					auto current_increasing = diff > 0;
					if (current_increasing != increasing.value())
					{
						return false;
					}
					auto absolute_diff = std::abs(diff);
					if (absolute_diff < 1 || absolute_diff > 3)
					{
						return false;
					}

					prev = item;
					return true;
				});
		}

		void FirstStage()
		{
			size_t safe_reports = 0;
			for (const auto& line : input.GetInputStrByLine())
			{
				if (IsSafe(Common::GetAllNums(line)))
					safe_reports++;
			}
			PrintAnswer(safe_reports, "safe reports");
		}

		void SecondStage()
		{
			size_t safe_reports = 0;
			std::vector<std::vector<int>> unsafe_reports;
			for (const auto& line : input.GetInputStrByLine())
			{
				const auto report = Common::GetAllNums(line);
				if (IsSafe(report))
				{
					safe_reports++;
					continue;
				}
				unsafe_reports.push_back(report);
			}

			for (const auto& report : unsafe_reports)
			{
				for (auto i = 0; i < report.size(); i++)
				{
					auto stripped_report = report;
					stripped_report.erase(stripped_report.begin() + i);
					if (IsSafe(stripped_report))
					{
						safe_reports++;
						break;
					}
				}
			}

			PrintAnswer(safe_reports, "safe reports");
		}
	};

	TEST_F(Day2, FirstStage_Example)
	{
		ReadInput(true);
		FirstStage();
	}

	TEST_F(Day2, SecondStage_Example)
	{
		ReadInput(true);
		SecondStage();
	}

	TEST_F(Day2, FirstStage)
	{
		ReadInput(false);
		FirstStage();
	}

	TEST_F(Day2, SecondStage)
	{
		ReadInput(false);
		SecondStage();
	}
}
