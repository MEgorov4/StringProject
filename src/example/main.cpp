#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>

#include "nstring.h"

using namespace nstring;

bool revLexSortWithoutCase(const String& lhs, const String& rhs)
{
	for (size_t i = 0; i < std::min(lhs.size(), rhs.size()); ++i)
	{
		char l = static_cast<char>(std::tolower(lhs[i]));
		char r = static_cast<char>(std::tolower(rhs[i]));

		if (l > r)
		{
			return true;
		}

		if (l < r)
		{
			return false;
		}
	}
	return lhs.size() > rhs.size();
}

int main()
{
	std::cout << "Enter the worlds:" << std::endl;

	std::vector<String> lines;
	String buffer;

	while (std::cin >> buffer)
	{
		lines.push_back(buffer);
	}

	std::cout << std::endl;

	std::sort(lines.begin(), lines.end(), &revLexSortWithoutCase);

	std::cout << "Reversed lex-sort result:" << std::endl;

	for (auto& line : lines)
	{
		std::cout << line << std::endl;
	}

	return 0;
}
