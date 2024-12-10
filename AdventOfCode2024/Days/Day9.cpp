#include "Helpers/BaseDay.hpp"

#include <optional>
#include <unordered_map>

namespace AdventOfCode2024 {

	class Day9 : public BaseDayTest
	{
	protected:
		Day9() : BaseDayTest(9) {}

		void FirstStage()
		{
			std::vector<short> memory(input.GetInputStr().size() * 9, -1); // worst case

			auto inserted_end = memory.begin();
			short id = 0;
			bool is_data = true;
			for (auto c : input.GetInputStr())
			{
				if (c == '\n' || c == '\0')
					break;

				auto number_of_el = c - '0';
				if (is_data)
				{
					inserted_end = std::fill_n(inserted_end, number_of_el, id);
					id++;
				}
				else
				{
					inserted_end = std::next(inserted_end, number_of_el);
				}
				is_data = !is_data;
			}

			// rearrange
			auto last = inserted_end;
			auto empty = memory.begin();

			while (last != empty)
			{
				// find empty space
				while (last != empty && (*empty) != -1)
				{
					empty++;
				}
				// no more free space
				if (last == empty)
					break;

				// find value to replace
				while (last != empty && (*last) == -1)
				{
					last--;
				}
				// no more data to copy
				if (last == empty)
					break;

				std::iter_swap(last, empty);
			}

			// calc checksumm
			size_t res = 0;
			size_t index = 0;
			for (auto it = memory.begin(); it != inserted_end; it++)
			{
				res += *it == -1 ? 0 : (*it) * index;
				index++;
			}

			PrintAnswer(res);
		}

		void SecondStage()
		{
			struct Chunk
			{
				std::optional<short> id = {};
				unsigned char size = 0;
			};

			std::list<Chunk> memory;

			short id = 0;
			bool is_data = false;
			for (auto c : input.GetInputStr())
			{
				if (c == '\n' || c == '\0')
					break;

				unsigned char number_of_el = c - '0';

				is_data = !is_data;

				if (number_of_el == 0)
					continue;

				if (is_data)
				{
					memory.push_back({ id, number_of_el });
					id++;
				}
				else
				{
					memory.push_back({ {}, number_of_el });
				}
			}

			// rearrange
			auto current = std::prev(memory.end());
			auto first_empty = memory.begin();
			while (first_empty != current && first_empty->id.has_value())
				first_empty++;

			while (current != std::prev(first_empty))
			{
				// find value to replace
				while (current != std::prev(first_empty) && !current->id.has_value())
				{
					current--;
				}
				// no more data to copy
				if (current == std::prev(first_empty))
					break;

				auto empty = first_empty;
				// find empty space
				while (current != empty
					&& (empty->id.has_value() || empty->size < current->size))
				{
					empty++;
				}

				// no free space for this item
				if (current == empty)
				{
					current--;
					continue;
				}

				if (empty->size == current->size)
				{
					std::iter_swap(empty, current);

					while (first_empty != current
						&& first_empty->id.has_value())
					{
						first_empty++;
					}
					if (first_empty == current)
						break;
				}
				else
				{
					auto inserted_el = memory.insert(std::next(empty), { {}, (unsigned char)(empty->size - current->size) });
					if (first_empty == empty)
						first_empty = inserted_el;
					*empty = *current;
					current->id.reset();
				}
			}

			// calc checksumm
			size_t res = 0;
			size_t index = 0;
			for (const auto& chunk : memory)
			{
				if (chunk.id.has_value())
				{
					for (auto i = 0; i < chunk.size; i++)
					{
						res += index * chunk.id.value();
						index++;
					}
				}
				else
				{
					index += chunk.size;
				}
			}

			PrintAnswer(res);
		}
	};

	TEST_F(Day9, FirstStage_Example)
	{
		ReadInput(true);
		FirstStage();
	}

	TEST_F(Day9, SecondStage_Example)
	{
		ReadInput(true);
		SecondStage();
	}

	TEST_F(Day9, FirstStage)
	{
		ReadInput(false);
		FirstStage();
	}

	TEST_F(Day9, SecondStage)
	{
		ReadInput(false);
		SecondStage();
	}
}
