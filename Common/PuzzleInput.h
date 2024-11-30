#pragma once
#include <iostream>
#include <string>
#include <vector>

namespace Common
{
	class PuzzleInput {
	public:
		PuzzleInput() = default;
		PuzzleInput(std::string folder_name, std::string file_name = "/input.txt");

		bool ReadInput(std::string folder_name, std::string file_name);
		void Clear();

		const std::string& GetInputStr() const;
		const std::vector<std::string>& GetInputStrByLine() const;

	private:
		std::string m_input_string;
		std::vector<std::string> m_input_lines;
	};

	std::vector<int> GetAllNums(std::string::const_iterator begin, std::string::const_iterator end);
	std::vector<std::size_t> GetAllNumsULL(std::string::const_iterator begin, std::string::const_iterator end);
	std::vector<long long> GetAllNumsLL(std::string::const_iterator begin, std::string::const_iterator end);

	std::vector<int> GetAllNums(const std::string& s);
	std::vector<std::size_t> GetAllNumsULL(const std::string& s);
	std::vector<long long> GetAllNumsLL(const std::string& s);
}