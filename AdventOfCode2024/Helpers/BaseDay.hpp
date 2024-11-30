#pragma once
#include "gtest/gtest.h"

#include "../../Common/PuzzleInput.h"

namespace AdventOfCode2024 {
	class BaseDayTest : public testing::Test {
	protected:
		BaseDayTest(int day) {
			// You can do set-up work for each test here.
			current_day = std::to_string(day);
		}

		~BaseDayTest() override {
			// You can do clean-up work that doesn't throw exceptions here.
		}

		// If the constructor and destructor are not enough for setting up
		// and cleaning up each test, you can define the following methods:
		void SetUp() override {
			// Code here will be called immediately after the constructor (right
			// before each test).
		}

		void TearDown() override {
			// Code here will be called immediately after each test (right
			// before the destructor).
			input.Clear();
		}

		void ReadInput(bool example)
		{
			const auto filename = std::string(example ? "example" : "input") + ".txt";
			ASSERT_TRUE(input.ReadInput("../../AdventOfCode2024/Inputs/" + current_day, filename));
		}

		std::string current_day;
		Common::PuzzleInput input;
	};
}