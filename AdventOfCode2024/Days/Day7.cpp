#include "Helpers/BaseDay.hpp"

namespace AdventOfCode2024 {

	class Day7 : public BaseDayTest
	{
	protected:
		Day7() : BaseDayTest(7) {}

		enum class Op
		{
			add,
			mul,
			concat
		};

		void progress(std::vector<Op>& operations)
		{
			int i = 0;
			while (i < operations.size())
			{
				switch (operations[i])
				{
				case Op::add:
					operations[i] = Op::mul;
					return;
				case Op::mul:
					operations[i] = Op::add;
					i++;
					break;
				}
			}
		}

		void progress2(std::vector<Op>& operations)
		{
			int i = 0;
			while (i < operations.size())
			{
				switch (operations[i])
				{
				case Op::add:
					operations[i] = Op::mul;
					return;
				case Op::mul:
					operations[i] = Op::concat;
					return;
				case Op::concat:
					operations[i] = Op::add;
					i++;
					break;
				}
			}
		}

		int GetNumberOfDigits(long long i)
		{
			return i > 0 ? std::log10(i) + 1 : 1;
		}

		template <typename iterator>
		bool check(long long result, iterator begin, iterator end, int number_of_operations)
		{
			const auto num_of_operands = std::distance(begin, end);
			// start with all add
			std::vector<Op> operations(num_of_operands - 1, Op::add);
			size_t variant = 0;
			size_t last_variant = std::pow(number_of_operations, num_of_operands - 1) - 1;

			while (variant <= last_variant)
			{
				long long potential = *begin;
				int operation_ind = num_of_operands - 1 - 1;
				for (auto it = begin + 1; it != end; it++, operation_ind--)
				{

					switch (operations[operation_ind])
					{
					case Op::add:
						potential += (*it);
						break;
					case Op::mul:
						potential *= (*it);
						break;
					case Op::concat:

						potential = potential * (GetNumberOfDigits(*it) * 10) + (*it);
						break;
					}

					if (potential > result)
					{
						break;
					}
				}

				if (potential == result)
				{
					return true;
				}
				variant++;
				number_of_operations == 2
					? progress(operations)
					: progress2(operations);
			}
			return false;
		}

		void FirstStage()
		{
			size_t res = 0;
			for (const auto& line : input.GetInputStrByLine())
			{
				auto values = Common::GetAllNumsLL(line);
				{
					auto result_str = line.substr(0, line.find(":"));
					ASSERT_EQ(result_str, std::to_string(values[0]));
				}
				if (check(values[0], values.begin() + 1, values.end(), 2)) {
					res += values[0];
				}
			}

			PrintAnswer(res);
		}

		void SecondStage()
		{
			size_t res = 0;
			for (const auto& line : input.GetInputStrByLine())
			{
				auto values = Common::GetAllNumsLL(line);
				{
					auto result_str = line.substr(0, line.find(":"));
					ASSERT_EQ(result_str, std::to_string(values[0]));
				}
				if (check(values[0], values.begin() + 1, values.end(), 3)) {
					res += values[0];
				}
			}

			PrintAnswer(res);
		}
	};

	TEST_F(Day7, FirstStage_Example)
	{
		ReadInput(true);
		FirstStage();
	}

	TEST_F(Day7, SecondStage_Example)
	{
		ReadInput(true);
		SecondStage();
	}

	TEST_F(Day7, FirstStage)
	{
		ReadInput(false);
		FirstStage();
	}

	TEST_F(Day7, SecondStage)
	{
		ReadInput(false);
		SecondStage();
	}
}
