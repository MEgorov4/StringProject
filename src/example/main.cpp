#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>

#include "nstring.h"

using namespace nstring;

bool sortInsens(const String& lhs, const String& rhs)
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
	std::cout << "Enter the words:" << std::endl;

	std::vector<String> lines;
	String buffer;

	while (std::cin >> buffer)
	{
		lines.push_back(buffer);
	}

	std::cout << std::endl;

	std::sort(lines.begin(), lines.end(), sortInsens);

	std::cout << "Reversed ilex-sort result:" << std::endl;

	for (size_t i = 0; i < lines.size(); i++)
	{
		std::cout << lines[i] << std::endl;
	}

	return 0;
}
