#include "PuzzleInput.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

using namespace Common;

PuzzleInput::PuzzleInput(std::string folder_name, std::string file_name) {
	ReadInput(folder_name, file_name);
}

bool PuzzleInput::ReadInput(std::string folder_name, std::string file_name)
{
	std::ifstream file(folder_name + "/" + file_name);

	if (!file.is_open())
	{
		return false;
	}
	std::string str;
	while (std::getline(file, str))
	{
		m_input_lines.push_back(str);
		m_input_string += str + "\n";
	}
	return true;
}

void PuzzleInput::Clear()
{
	m_input_lines.clear();
	m_input_string.clear();
}

const std::vector<std::string>& PuzzleInput::GetInputStrByLine() const
{
	return m_input_lines;
}

size_t Common::PuzzleInput::NumberOfLines() const
{
	return m_input_lines.size();
}

const std::string& PuzzleInput::GetInputStr() const
{
	return m_input_string;
}

std::vector<int> Common::GetAllNums(std::string::const_iterator begin, std::string::const_iterator end)
{
	std::regex index_r("\\d+");
	std::smatch m;
	std::vector<int> res;
	while (std::regex_search(begin, end, m, index_r))
	{
		int val = std::stoi(m[0]);
		res.push_back(val);
		begin = m.suffix().first;
	}
	return res;
}

std::vector<std::size_t> Common::GetAllNumsULL(std::string::const_iterator begin, std::string::const_iterator end)
{
	std::regex index_r("\\d+");
	std::smatch m;
	std::vector<std::size_t> res;
	while (std::regex_search(begin, end, m, index_r))
	{
		std::size_t val = std::stoull(m[0]);
		res.push_back(val);
		begin = m.suffix().first;
	}
	return res;
}

std::vector<long long> Common::GetAllNumsLL(std::string::const_iterator begin, std::string::const_iterator end)
{
	std::regex index_r("-?\\d+(\\.\\d+)?");
	std::smatch m;
	std::vector<long long> res;
	while (std::regex_search(begin, end, m, index_r))
	{
		long long val = std::stoll(m[0]);
		res.push_back(val);
		begin = m.suffix().first;
	}
	return res;
}

std::vector<int> Common::GetAllNums(const std::string& s) { return GetAllNums(s.cbegin(), s.cend()); }

std::vector<std::size_t> Common::GetAllNumsULL(const std::string& s) { return GetAllNumsULL(s.cbegin(), s.cend()); }

std::vector<long long> Common::GetAllNumsLL(const std::string& s) { return GetAllNumsLL(s.cbegin(), s.cend()); }

