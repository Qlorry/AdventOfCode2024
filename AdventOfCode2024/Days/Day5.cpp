#include "Helpers/BaseDay.hpp"

namespace AdventOfCode2024 {

	class Day5 : public BaseDayTest
	{
	protected:
		Day5() : BaseDayTest(5) {}

		bool FitsRules(
			const std::map<int, std::vector<int>>& can_not_be_before,
			const std::map<int, std::vector<int>>& can_not_be_after,
			const std::vector<int>& row)
		{
			for (auto it = row.begin(); it != row.end(); it++)
			{
				std::vector<int> intersection;
				if (can_not_be_before.contains(*it))
				{
					std::vector<int> before(row.begin(), it);
					std::sort(before.begin(), before.end());

					const auto& can_not_be_before_current = can_not_be_before.at(*it);
					std::set_intersection(before.begin(), before.end(),
						can_not_be_before_current.begin(), can_not_be_before_current.end(),
						std::back_inserter(intersection));

					if (!intersection.empty())
						return false;
				}

				if (can_not_be_after.contains(*it))
				{
					std::vector<int> after(std::next(it), row.end());
					std::sort(after.begin(), after.end());

					const auto& can_not_be_after_current = can_not_be_after.at(*it);
					std::set_intersection(after.begin(), after.end(),
						can_not_be_after_current.begin(), can_not_be_after_current.end(),
						std::back_inserter(intersection));

					if (!intersection.empty())
						return false;
				}
			}
			return true;
		}

		void AddRule(const std::string& line,
			std::map<int, std::vector<int>>& can_not_be_before,
			std::map<int, std::vector<int>>& can_not_be_after)
		{
			auto current_rule = Common::GetAllNums(line);
			ASSERT_EQ(current_rule.size(), 2);

			can_not_be_before[current_rule[0]].push_back(current_rule[1]);
			can_not_be_after[current_rule[1]].push_back(current_rule[0]);

		}

		void FirstStage()
		{
			std::map<int, std::vector<int>> can_not_be_before;
			std::map<int, std::vector<int>> can_not_be_after;

			bool rules = true;

			size_t res = 0;
			for (const auto& line : input.GetInputStrByLine())
			{
				if (line.empty())
				{
					rules = false;
					for (auto& [_, elements] : can_not_be_before)
					{
						std::sort(elements.begin(), elements.end());
					}
					for (auto& [_, elements] : can_not_be_after)
					{
						std::sort(elements.begin(), elements.end());
					}
					continue;
				}

				if (rules)
				{
					AddRule(line, can_not_be_before, can_not_be_after);
				}
				else
				{
					if (auto pages = Common::GetAllNums(line);
						FitsRules(can_not_be_before, can_not_be_after, pages))
					{
						ASSERT_EQ(pages.size() % 2, 1);
						int middle_index = static_cast<int>(pages.size() / 2);
						res += pages[middle_index];
					}
				}
			}

			PrintAnswer(res);
		}

		class RuleBasedSorter {
		private:
			std::map<int, std::vector<int>> m_can_not_be_before;
			std::map<int, std::vector<int>> m_can_not_be_after;
		public:
			// Constructor to initialize the state
			RuleBasedSorter(std::map<int, std::vector<int>> can_not_be_before,
				std::map<int, std::vector<int>> can_not_be_after)
				: m_can_not_be_before(std::move(can_not_be_before)), m_can_not_be_after(std::move(can_not_be_after)) {}

			// Callable operator
			bool operator()(const int& a, const int& b) {
				if (auto illegal = m_can_not_be_before.find(a);
					illegal != m_can_not_be_before.end())
				{
					if (auto it = std::find(illegal->second.begin(), illegal->second.end(), b);
						it != illegal->second.end())
					{
						// a ... b
						return true;
					}
				}

				if (auto illegal = m_can_not_be_before.find(b);
					illegal != m_can_not_be_before.end())
				{
					if (auto it = std::find(illegal->second.begin(), illegal->second.end(), a);
						it != illegal->second.end())
					{
						// b ... a
						return false;
					}
				}

				if (auto illegal = m_can_not_be_after.find(a);
					illegal != m_can_not_be_after.end())
				{
					if (auto it = std::find(illegal->second.begin(), illegal->second.end(), b);
						it != illegal->second.end())
					{
						// b ... a
						return false;
					}
				}

				if (auto illegal = m_can_not_be_after.find(b);
					illegal != m_can_not_be_after.end())
				{
					if (auto it = std::find(illegal->second.begin(), illegal->second.end(), a);
						it != illegal->second.end())
					{
						// a ... b
						return true;
					}
				}

				return true;
				return a < b;
			}
		};

		void SecondStage()
		{
			std::map<int, std::vector<int>> can_not_be_before;
			std::map<int, std::vector<int>> can_not_be_after;

			bool rules = true;

			std::vector<std::vector<int>> incorrect;
			for (const auto& line : input.GetInputStrByLine())
			{
				if (line.empty())
				{
					rules = false;
					for (auto& [_, elements] : can_not_be_before)
					{
						std::sort(elements.begin(), elements.end());
					}
					for (auto& [_, elements] : can_not_be_after)
					{
						std::sort(elements.begin(), elements.end());
					}
					continue;
				}

				if (rules)
				{
					AddRule(line, can_not_be_before, can_not_be_after);
				}
				else
				{
					if (auto pages = Common::GetAllNums(line);
						!FitsRules(can_not_be_before, can_not_be_after, pages))
					{
						incorrect.push_back(std::move(pages));
					}
				}
			}

			RuleBasedSorter sorter(can_not_be_before, can_not_be_after);
			size_t res = 0;
			for (auto& pages : incorrect)
			{
				std::sort(pages.begin(), pages.end(), sorter);
				int middle_index = static_cast<int>(pages.size() / 2);
				res += pages[middle_index];
			}
			PrintAnswer(res);
		}
	};

	TEST_F(Day5, FirstStage_Example)
	{
		ReadInput(true);
		FirstStage();
	}

	TEST_F(Day5, SecondStage_Example)
	{
		ReadInput(true);
		SecondStage();
	}

	TEST_F(Day5, FirstStage)
	{
		ReadInput(false);
		FirstStage();
	}

	TEST_F(Day5, SecondStage)
	{
		ReadInput(false);
		SecondStage();
	}
}
