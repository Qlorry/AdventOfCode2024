#include "Coordinate.h"
#include "Helpers/BaseDay.hpp"
#include "PositionHelper.h"
#include <unordered_set>

namespace AdventOfCode2024 {

	class Day8 : public BaseDayTest
	{
	protected:
		Day8() : BaseDayTest(8) {}

		std::map<char, std::vector<Common::Coordinate<int>>> GetAntenas()
		{
			std::map<char, std::vector<Common::Coordinate<int>>> antenas;

			auto map = input.GetInputStrByLine();
			Common::Coordinate<int> current{ 0, 0 };
			for (const auto& line : map)
			{
				for (const auto p : line)
				{
					if (p == '.')
					{
						current.col++;
						continue;
					}
					antenas[p].push_back(current);
					current.col++;
				}
				current.col = 0;
				current.row++;
			}
			return antenas;
		}

		void FirstStage()
		{
			const auto antenas = GetAntenas();
			const auto& map = input.GetInputStrByLine();

			const auto max_pos = Common::Coordinate<int>(map.size() - 1, map[0].size() - 1);
			std::unordered_set<Common::Coordinate<int>, Common::CoordinateHasher<int>> unique_antinodes;;
			for (const auto& [antena_type, positions] : antenas)
			{
				for (auto i = 0; i < positions.size(); i++)
				{
					const auto first_point = positions[i];
					for (auto j = i + 1; j < positions.size(); j++)
					{
						const auto second_point = positions[j];
						auto diff = first_point - second_point;

						auto first_antinode = first_point + diff;
						if (Common::IsInside(first_antinode, max_pos))
						{
							unique_antinodes.insert(first_antinode);
						}

						auto second_antinode = second_point - diff;
						if (Common::IsInside(second_antinode, max_pos))
						{
							unique_antinodes.insert(second_antinode);
						}
					}
				}
			}


			PrintAnswer(unique_antinodes.size());
		}

		void SecondStage()
		{
			const auto antenas = GetAntenas();
			const auto& map = input.GetInputStrByLine();

			const auto max_pos = Common::Coordinate<int>(map.size() - 1, map[0].size() - 1);
			std::unordered_set<Common::Coordinate<int>, Common::CoordinateHasher<int>> unique_antinodes;;
			for (const auto& [antena_type, positions] : antenas)
			{
				for (auto i = 0; i < positions.size(); i++)
				{
					const auto first_point = positions[i];
					for (auto j = i + 1; j < positions.size(); j++)
					{
						const auto second_point = positions[j];
						auto diff = first_point - second_point;

						auto first_antinode = first_point;
						while (Common::IsInside(first_antinode, max_pos))
						{
							unique_antinodes.insert(first_antinode);
							first_antinode += diff;
						}

						auto second_antinode = second_point;
						while (Common::IsInside(second_antinode, max_pos))
						{
							unique_antinodes.insert(second_antinode);
							second_antinode -= diff;
						}
					}
				}
			}


			PrintAnswer(unique_antinodes.size());
		}
	};

	TEST_F(Day8, FirstStage_Example)
	{
		ReadInput(true);
		FirstStage();
	}

	TEST_F(Day8, SecondStage_Example)
	{
		ReadInput(true);
		SecondStage();
	}

	TEST_F(Day8, FirstStage)
	{
		ReadInput(false);
		FirstStage();
	}

	TEST_F(Day8, SecondStage)
	{
		ReadInput(false);
		SecondStage();
	}
}
