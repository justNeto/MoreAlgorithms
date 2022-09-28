#ifndef TRS_MODULE
#define TRS_MODULE

#include <iostream>
#include <fstream>
#include <vector>

struct // struct to solve the problem with
{
	char value; // value of the node
	std::vector<struct Node*> connected_nodes;
} Node;


void findInFile(std::string file_name, std::string pattern_name)
{
	std::ifstream infile(file_name); // create ifstream var to read from
	std::ifstream inpattern(pattern_name); // create ifstream var to read from

	std::string searching = "\n[ Searching pattern from " + pattern_name + " in file " + file_name + " ]\n";

	std::cout << searching;

	std::string pattern;
	std::getline(inpattern, pattern);

	std::string line;

	// Create the root node

	while (std::getline(infile, line)) // gets a line
	{
		// This function creates the nodes using infile var
		// Create
		parse_line();
	}

	while (std::getline(infile, line)) // gets a line
	{
		// this function uses the 'dict' to find the inputted pattern
	}

}

// First problem consist in each transmission file
void tries_words_solutions(std::vector<std::string> files, std::vector<std::string> patterns)
{
	std::string greetings = "| --- Start searching for patterns --- | \n";
	std::cout << greetings;

	for (auto &file_name : files) // selects the current file name in vector
	{
		for (auto &pattern_name : patterns) // selects the current pattern in vector
		{
			findInFile(file_name, pattern_name);
		}
	}
}

#endif
