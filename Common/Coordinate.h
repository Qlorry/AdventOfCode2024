#pragma once
#include "Direction.h"

namespace Common
{
	template <typename T>
	struct Coordinate
	{
		T row = {};
		T col = {};

		Coordinate operator+(const Coordinate other) const
		{
			return { this->row + other.row, this->col + other.col };
		}

		Coordinate operator-(const Coordinate other) const
		{
			return { this->row - other.row, this->col - other.col };
		}

		Coordinate& operator+=(const Coordinate other)
		{
			this->row += other.row;
			this->col += other.col;
			return *this;
		}

		Coordinate& operator-=(const Coordinate other)
		{
			this->row -= other.row;
			this->col -= other.col;
			return *this;
		}

		//bool operator==(const Coordinate& other) const
		//{
		//	return this.row == other.row &&
		//		this.col == other.col;
		//}

		friend bool operator==(const Coordinate& lhs, const Coordinate& rhs)
		{
			return lhs.row == rhs.row &&
				lhs.col == rhs.col;
		}

		Coordinate& move_to_by(Direction direction, T amount = 1)
		{
			switch (direction)
			{
			case Common::Direction::up:
				row -= amount;
				break;
			case Common::Direction::down:
				row += amount;
				break;
			case Common::Direction::left:
				col -= amount;
				break;
			case Common::Direction::right:
				col += amount;
				break;
			default:
				break;
			}
			return *this;
		}
	};

}

