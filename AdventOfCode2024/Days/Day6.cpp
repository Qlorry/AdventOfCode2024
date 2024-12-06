#include "Helpers/BaseDay.hpp"
#include <Coordinate.h>

#include <PositionHelper.h>
#include <unordered_set>

namespace AdventOfCode2024 {
	using Map = std::vector<std::vector<bool>>;

	class Day6 : public BaseDayTest
	{
	protected:
		Day6() : BaseDayTest(6) {}

		std::pair<Common::Coordinate<int>, Map> ParseMap()
		{
			std::vector<std::vector<bool>> res;
			Common::Coordinate<int> start, current;
			for (const auto& line : input.GetInputStrByLine())
			{
				auto& row = res.emplace_back();
				for (auto c : line)
				{
					if (c == '^')
					{
						start = current;
					}
					row.push_back(c == '#');
					current.col++;
				}
				current.row++;
				current.col = 0;
			}

			return { start, res };
		}

		std::vector<Common::Coordinate<int>> GetPathToNextPoint(
			const Map& map, Common::Coordinate<int> start,
			Common::Direction direction)
		{
			std::vector<Common::Coordinate<int>> steps;
			auto current = start;
			Common::Coordinate<int> max_pos{ static_cast<int>(map.size()) - 1,  static_cast<int>(map[0].size()) - 1 };
			while (Common::IsInside(current, max_pos)
				&& !map[current.row][current.col])
			{
				steps.push_back(current);
				current = current.move_to_by(direction, 1);
			}
			return steps;
		}

		Common::Direction GetNextDirection(Common::Direction current)
		{
			switch (current)
			{
			case Common::Direction::up:
				return Common::Direction::right;
			case Common::Direction::down:
				return Common::Direction::left;
			case Common::Direction::left:
				return Common::Direction::up;
			case Common::Direction::right:
				return Common::Direction::down;
			default:
				return Common::Direction::up;
			}
		}

		void FirstStage()
		{
			const auto [start, map] = ParseMap();

			std::unordered_set<Common::Coordinate<int>, Common::CoordinateHasher<int>> positions;
			auto current = start;
			Common::Direction direction = Common::Direction::up;

			Common::Coordinate<int> max_pos{ static_cast<int>(map.size()) - 2,  static_cast<int>(map[0].size()) - 2 };
			while (Common::IsInside(current, max_pos, { 1, 1 }))
			{
				auto steps = GetPathToNextPoint(map, current, direction);
				positions.insert(steps.begin(), steps.end());

				direction = GetNextDirection(direction);
				current = steps.back();
			}

			PrintAnswer(positions.size());
		}

		struct PositionHasher {
			inline size_t operator()(const std::pair<Common::Direction, Common::Coordinate<int>>& position) const {
				return (static_cast<size_t> (position.first) << 63)
					+ Common::CoordinateHasher<int> {}(position.second);
			}
		};

		void SecondStage()
		{
			const auto [start, map] = ParseMap();

			std::unordered_set<Common::Coordinate<int>, Common::CoordinateHasher<int>> positions;
			auto current = start;
			Common::Direction direction = Common::Direction::up;

			Common::Coordinate<int> max_pos{ static_cast<int>(map.size()) - 2,  static_cast<int>(map[0].size()) - 2 };
			while (Common::IsInside(current, max_pos, { 1, 1 }))
			{
				auto steps = GetPathToNextPoint(map, current, direction);
				positions.insert(steps.begin(), steps.end());

				direction = GetNextDirection(direction);
				current = steps.back();
			}

			positions.erase(start);

			size_t res = 0;
			for (const auto& position : positions)
			{
				std::unordered_set<std::pair<Common::Direction, Common::Coordinate<int>>, PositionHasher> pivotal_points;

				current = start;
				direction = Common::Direction::up;
				auto modified_map = map;

				modified_map[position.row][position.col] = true;

				while (Common::IsInside(current, max_pos, { 1, 1 }))
				{
					auto steps = GetPathToNextPoint(modified_map, current, direction);
					current = steps.back();
					auto [_, inserted] = pivotal_points.insert({ direction, current });
					if (!inserted)
					{
						res++;
						break;
					}

					direction = GetNextDirection(direction);
				}
			}

			PrintAnswer(res);
		}
	};

	TEST_F(Day6, FirstStage_Example)
	{
		ReadInput(true);
		FirstStage();
	}

	TEST_F(Day6, SecondStage_Example)
	{
		ReadInput(true);
		SecondStage();
	}

	TEST_F(Day6, FirstStage)
	{
		ReadInput(false);
		FirstStage();
	}

	TEST_F(Day6, SecondStage)
	{
		ReadInput(false);
		SecondStage();
	}
}
