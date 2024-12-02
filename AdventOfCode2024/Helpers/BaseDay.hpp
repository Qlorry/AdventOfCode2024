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

		template <typename ...T>
		void PrintAnswer(T... answer)
		{
			const std::string left = "------>  Answer is: ";
			const std::string right = "  <------";

			std::ostringstream oss;
			oss << left;
			((oss << answer << " "), ...);
			oss << right;
			std::string content = oss.str();

			const int min_width = 40;
			int width = min_width;
			{
				int left_padding = 0;
				int right_padding = 0;
				auto content_size = content.size();
				const auto minimal_padding = 3;
				if (content_size < (width - minimal_padding))
				{
					const auto leftover = width - content_size;

					left_padding = leftover / 2;
					right_padding = (leftover % 2) == 0 ? leftover / 2 : leftover + 1;
				}
				else
				{
					auto required = content_size - width;
					required = required % 2 == 0 ? required : required + 1;

					right_padding = left_padding = required + 5;
				}
				content = std::string(left_padding, ' ') + content + std::string(right_padding, ' ');
			}


			const std::string pattern = "_.:*~*:.";
			int content_final_size = content.size() + (18 + 16) - ((pattern.size() - 1)); // with snowflakes on sides and without starting .:*~*:.
			{
				if (auto chars_not_aliged_with_pattern = content_final_size % pattern.size();
					chars_not_aliged_with_pattern != 0)
				{
					auto chars_to_align_with_pattern = pattern.size() - chars_not_aliged_with_pattern;
					content_final_size += chars_to_align_with_pattern;
					if (chars_to_align_with_pattern % 2 == 0)
					{
						content = std::string(chars_to_align_with_pattern / 2, ' ')
							+ content
							+ std::string(chars_to_align_with_pattern / 2, ' ');
					}
					else
					{
						content = std::string(chars_to_align_with_pattern / 2, ' ')
							+ content
							+ std::string((chars_to_align_with_pattern / 2) + 1, ' ');
					}
				}
			}


			const auto pattern_repeats = (content_final_size) / pattern.size();
			{
				std::cout << ".:*~*:.";
				for (auto i = 0; i < pattern_repeats; i++)
				{
					std::cout << pattern;
				}
				std::cout << std::endl;
			}
			std::cout << R"(.                 )" << std::string(content.size(), ' ') << R"(               .)" << "\n";
			std::cout << R"(.      .      .   )" << std::string(content.size(), ' ') << R"( .        .    .)" << "\n";
			std::cout << R"(.      _\/  \/_   )" << std::string(content.size(), ' ') << R"(  '.|  |.'     .)" << "\n";
			std::cout << R"(.       _\/\/_    )" << std::string(content.size(), ' ') << R"(. ~~\  /~~ .   .)" << "\n";
			std::cout << R"(.   _\_\_\/\/_/_/_)" << std::string(content.size(), ' ') << R"(_\_._\/_._/_   .)" << "\n";
			std::cout << R"(.    / /_/\/\_\ \ )" << content/*                     */ << R"( / ' /\ ' \    .)" << "\n";
			std::cout << R"(.       _/\/\_    )" << std::string(content.size(), ' ') << R"(' __/  \__ '   .)" << "\n";
			std::cout << R"(.       /\  /\    )" << std::string(content.size(), ' ') << R"(' .'|  |'.     .)" << "\n";
			std::cout << R"(.      '      '   )" << std::string(content.size(), ' ') << R"( .        .    .)" << "\n";
			std::cout << R"(.                 )" << std::string(content.size(), ' ') << R"(               .)" << "\n";

			{
				std::cout << ".:*~*:.";
				for (auto i = 0; i < pattern_repeats; i++)
				{
					std::cout << pattern;
				}
			}
			std::cout << std::endl;
		}

		std::string current_day;
		Common::PuzzleInput input;
	};
}

namespace
{
	//compiled by Ron <eli97@geocities.com>

	//-=[ snowflakes ]=-  1/97
	//                     *  .  *
	//                   . _\/ \/_ .
	//                    \  \ /  /             .      .   
	//      ..    ..    -==>: X :<==-           _\/  \/_
	//      '\    /'      / _/ \_ \              _\/\/_
	//        \\//       '  /\ /\  '         _\_\_\/\/_/_/_
	//   _.__\\\///__._    *  '  *            / /_/\/\_\ \
	//    '  ///\\\  '                           _/\/\_
	//        //\\                               /\  /\ 
	//      ./    \.             ._    _.       '      '
	//      ''    ''             (_)  (_)                  <> \  / <>
	//                            .\::/.                   \_\/  \/_/ 
	//           .:.          _.=._\\//_.=._                  \\//
	//      ..   \o/   ..      '=' //\\ '='             _<>_\_\<>/_/_<>_
	//      :o|   |   |o:         '/::\'                 <> / /<>\ \ <>
	//       ~ '. ' .' ~         (_)  (_)      _    _       _ //\\ _
	//           >O<             '      '     /_/  \_\     / /\  /\ \
	//       _ .' . '. _                        \\//       <> /  \ <>
	//      :o|   |   |o:                   /\_\\><//_/\
	//      ''   /o\   ''     '.|  |.'      \/ //><\\ \/
	//           ':'        . ~~\  /~~ .       _//\\_
	//jgs                   _\_._\/_._/_      \_\  /_/ 
	//                       / ' /\ ' \                   \o/
	//       o              ' __/  \__ '              _o/.:|:.\o_
	//  o    :    o         ' .'|  |'.                  .\:|:/.
	//    '.\'/.'                 .                 -=>>::>o<::<<=-
	//    :->@<-:                 :                   _ '/:|:\' _
	//    .'/.\'.           '.___/*\___.'              o\':|:'/o 
	//  o    :    o           \* \ / */                   /o\
	//       o                 >--X--<
	//                        /*_/ \_*\
	//                      .'   \*/   '.
	//                            :
	//                            '


	//.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:.
	//.     *                                       .
	//.    /.\                                      .
	//.   /..'\                                     .
	//.   /'.'\                                     .
	//.  /.''.'\                                    .
	//.  /.'.'.\                                    .
	//. /'.''.'.\                                   .
	//. ^^^[_]^^^                                   .
	//.                                             .
	//.                                             .
	//.jgs                                          .
	//.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:.
	//
	//
	//.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:.
	//.                                             .
	//.                                 .      .    .
	//.                                 _\/  \/_    .
	//.                                  _\/\/_     .
	//.                              _\_\_\/\/_/_/_ .
	//.                               / /_/\/\_\ \  .
	//.                                  _/\/\_     .
	//.                                  /\  /\     .
	//.                                 '      '    .
	//.                                             .
	//.                                             .
	//.                                          jgs.
	//.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:._.:*~*:.
}