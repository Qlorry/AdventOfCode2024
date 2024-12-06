#pragma once
#include "Coordinate.h"

namespace Common {

	template <typename T>
	struct CoordinateHasher
	{
		inline std::size_t operator()(const Coordinate<T>& el) const
		{
			auto first = static_cast<std::size_t>(el.row);
			auto second = static_cast<std::size_t>(el.col);
			return (first << 32) + second;
		}
	};

	template <typename T>
	bool IsInside(Coordinate<T> pos, Coordinate<T> max, Coordinate<T> min = { static_cast<T>(0),static_cast<T>(0) })
	{
		if (min.row > pos.row)
			return false;
		if (min.col > pos.col)
			return false;
		if (max.row < pos.row)
			return false;
		if (max.col < pos.col)
			return false;
		return true;
	}
}