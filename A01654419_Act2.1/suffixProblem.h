#include <iostream>
#include <vector>
#include <algorithm>

bool compareTwoStrings (std::string a, std::string b)
{
	return a < b;
}

void creating_and_sorting_suffixes(std::string str, int str_length)
{
	std::vector<std::string> order;

	for (int i = 0; i < str_length; i++)
	{
		order.push_back(str.substr(i, str_length));
	}

	std::sort(order.begin(), order.end(), compareTwoStrings);

	for (int i = 0; i < str.length(); i++)
	{
		std::cout << order[i] << "\n";
	}
}

void creating_suffixes(std::string file_name)
{
	std::ifstream infile(file_name); // read current file with file_name name
	std::string searching = "\n[ Creating suffixes in " + file_name + " ]\n";
	std::cout << searching;

	std::string line;

	while (std::getline(infile, line)) // gets a line in line variable
	{
		line.erase(remove_if(line.begin(), line.end(), isspace), line.end());
		std::transform(line.begin(), line.end(), line.begin(), ::tolower);
		creating_and_sorting_suffixes(line, line.length());
	}
}

void solutionSuffixArray(std::vector<std::string> suffix_files)
{

	std::string greetings = "\n| --- Starting suffix finding --- | \n";
	std::cout << greetings;

	for (auto &file_name : suffix_files) // for file_name in files
	{
		std::cout << "files to process: " << file_name << "\n";
		creating_suffixes(file_name);
	}
}
