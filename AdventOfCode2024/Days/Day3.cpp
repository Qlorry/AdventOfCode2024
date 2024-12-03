#include "Helpers/BaseDay.hpp"
#include <regex>

namespace AdventOfCode2024 {

	class Day3 : public BaseDayTest
	{
	protected:
		Day3() : BaseDayTest(3) {}

		size_t CalculateMulSums(const std::string& data)
		{
			size_t res = 0;

			std::regex pattern(R"(mul\(([0-9]{1,3}),([0-9]{1,3})\))");
			std::smatch match;
			std::vector<std::pair<int, int>> extractedPairs;

			auto begin = data.cbegin();
			auto end = data.cend();

			while (std::regex_search(begin, end, match, pattern)) {
				// match[1] contains the first number, match[2] contains the second number
				int first = std::stoi(match[1]);
				int second = std::stoi(match[2]);

				extractedPairs.emplace_back(first, second);

				// Move to the next part of the string
				begin = match.suffix().first;
			}

			for (const auto [first, second] : extractedPairs)
			{
				res += static_cast<size_t>(first) * static_cast<size_t>(second);
			}
			return res;
		}

		void FirstStage()
		{

			PrintAnswer(CalculateMulSums(input.GetInputStr()));
		}

		std::vector<size_t> GetAllPositions(const std::string& item)
		{
			std::vector<size_t> res;
			auto offset = 0;
			auto pos = std::string::npos;
			while (true)
			{
				pos = input.GetInputStr().find(item, offset);
				if (pos == std::string::npos)
					break;

				res.push_back(pos);
				offset = pos + item.size();
			}
			return res;
		}

		std::vector<std::string> SplitStringWithDelim(const std::string& str, const std::string& delimiter) {
			std::vector<std::string> result;
			size_t start = 0;
			size_t end = 0;

			while ((end = str.find(delimiter, start)) != std::string::npos) {
				if (start == 0)
				{
					result.push_back(str.substr(start, end - start));
				}
				else
				{
					result.push_back(delimiter + str.substr(start, end - start));
				}
				start = end + delimiter.length();
			}
			// Add the last part of the string
			if (start == 0)
			{
				result.push_back(str.substr(start, end - start));
			}
			else
			{
				result.push_back(delimiter + str.substr(start, end - start));
			}
			return result;
		}

		void SecondStage()
		{
			std::string only_do_input;
			auto dont_splited_strs = SplitStringWithDelim(input.GetInputStr(), "don't()");
			dont_splited_strs[0] = "do()" + dont_splited_strs[0];
			for (const auto& dont_str : dont_splited_strs)
			{
				auto do_and_dont_splited_strs = SplitStringWithDelim(dont_str, "do()");
				for (const auto one_action_str : do_and_dont_splited_strs)
				{
					if (one_action_str.starts_with("do()"))
					{
						only_do_input += one_action_str;
					}
				}
			}

			PrintAnswer(CalculateMulSums(only_do_input));
		}
	};

	TEST_F(Day3, FirstStage_Example)
	{
		ReadInput(true);
		FirstStage();
	}

	TEST_F(Day3, SecondStage_Example)
	{
		ReadInput(true);
		SecondStage();
	}

	TEST_F(Day3, FirstStage)
	{
		ReadInput(false);
		FirstStage();
	}

	TEST_F(Day3, SecondStage)
	{
		ReadInput(false);
		SecondStage();
	}
}
