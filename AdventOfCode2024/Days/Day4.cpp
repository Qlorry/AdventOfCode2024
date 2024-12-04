#include "Helpers/BaseDay.hpp"

namespace AdventOfCode2024 {

	class Day4 : public BaseDayTest
	{
	protected:
		Day4() : BaseDayTest(4) {}

		size_t GetNumberOfOccurences(const std::string& line)
		{
			const std::string word_to_find = "XMAS";
			size_t res = 0;
			size_t start = 0;
			size_t end = 0;

			while ((end = line.find(word_to_find, start)) != std::string::npos) {
				start = end + word_to_find.length();
				res++;
			}

			auto reversed_word = word_to_find;
			std::reverse(reversed_word.begin(), reversed_word.end());

			start = 0;
			end = 0;

			while ((end = line.find(reversed_word, start)) != std::string::npos) {
				start = end + word_to_find.length();
				res++;
			}
			return res;
		}

		void FirstStage()
		{
			size_t res = 0;

			for (const auto& line : input.GetInputStrByLine())
			{
				res += GetNumberOfOccurences(line);
			}

			std::vector<std::string> vertical;
			auto size_for_flipped = input.GetInputStrByLine().front().size();
			vertical.resize(size_for_flipped);
			for (const auto& line : input.GetInputStrByLine())
			{
				ASSERT_EQ(size_for_flipped, line.size());
				auto row_it = vertical.begin();
				for (auto c : line)
				{
					*row_it += c;
					row_it++;
				}
			}

			for (const auto& line : vertical)
			{
				res += GetNumberOfOccurences(line);
			}

			std::vector<std::string> horizontal;

			//  .
			//  | 0000
			//  | 0000
			//  | 0000
			// \ /0000
			const auto& lines = input.GetInputStrByLine();
			for (auto start = 0; start < lines.size(); start++)
			{
				auto& current = horizontal.emplace_back("");
				auto col = 0;
				auto row = start;
				while (row < lines.size() && col < lines[row].size())
				{
					current += lines[row][col];
					row++;
					col++;
				}
			}

			// --> 
			//0000
			//0000
			//0000
			//0000
			for (auto start = 1; start < lines[0].size(); start++)
			{
				auto& current = horizontal.emplace_back("");
				auto col = start;
				auto row = 0;
				while (row < lines.size() && col < lines[row].size())
				{
					current += lines[row][col];
					row++;
					col++;
				}
			}

			for (const auto& line : horizontal)
			{
				res += GetNumberOfOccurences(line);
			}

			horizontal.clear();

			//	   .
			//0000 |
			//0000 |
			//0000 |
			//0000\ /
			for (auto start = 0; start < lines.size(); start++)
			{
				auto& current = horizontal.emplace_back("");
				auto row = start;
				int col = lines[start].size() - 1;
				while (row < lines.size() && col >= 0)
				{
					current += lines[row][col];
					row++;
					col--;
				}
			}

			//<--  
			//0000
			//0000
			//0000
			//0000
			for (int start = lines[0].size() - 2; start >= 0; start--)
			{
				auto& current = horizontal.emplace_back("");
				int row = 0;
				int col = start;
				while (row < lines.size() && col >= 0)
				{
					current += lines[row][col];
					row++;
					col--;
				}
			}

			for (const auto& line : horizontal)
			{
				res += GetNumberOfOccurences(line);
			}

			PrintAnswer(res);
		}

		void SecondStage()
		{
			std::vector<std::pair<int, int>> all_a_letters;
			const auto& lines = input.GetInputStrByLine();
			for (auto row = 1; row < lines.size() - 1; row++)
			{
				for (auto col = 1; col < lines[row].size() - 1; col++)
				{
					if (lines[row][col] == 'A')
						all_a_letters.push_back({ row, col });
				}
			}

			size_t res = 0;
			const auto is_valid = [](char symbol)
				{
					if (symbol != 'M' && symbol != 'S')
					{
						return false;
					}
					return true;
				};
			for (const auto [row, col] : all_a_letters)
			{
				const auto top_left = lines[row - 1][col - 1];
				if (!is_valid(top_left))
				{
					continue;
				}
				const auto bot_right = lines[row + 1][col + 1];
				if (!is_valid(bot_right))
				{
					continue;
				}

				if (top_left == bot_right)
				{
					continue;
				}

				const auto top_right = lines[row - 1][col + 1];
				if (!is_valid(top_left))
				{
					continue;
				}
				const auto bot_left = lines[row + 1][col - 1];
				if (!is_valid(bot_right))
				{
					continue;
				}

				if (top_left == top_right && bot_left == bot_right)
				{
					res++;
				}
				else if (bot_right == top_right && bot_left == top_left)
				{
					res++;
				}
			}


			PrintAnswer(res);
		}
	};

	TEST_F(Day4, FirstStage_Example)
	{
		ReadInput(true);
		FirstStage();
	}

	TEST_F(Day4, SecondStage_Example)
	{
		ReadInput(true);
		SecondStage();
	}

	TEST_F(Day4, FirstStage)
	{
		ReadInput(false);
		FirstStage();
	}

	TEST_F(Day4, SecondStage)
	{
		ReadInput(false);
		SecondStage();
	}
}
