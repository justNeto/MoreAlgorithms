#ifndef GEN_TXT_FILES
#define GEN_TXT_FILES

#include <iostream>
#include <fstream>
#include <chrono>

void genPattern(int pattern_length, std::string name)
{
	std::ofstream file;
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::srand(seed); // sets seed

	int max_val = 16; // size of the gen_word dictionary
	char gen_word[max_val] = {'A', 'B', 'C', 'D', 'E', 'F', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

	file.open(name);

	for (int i = 0; i < pattern_length; i++)
	{
		int select_char = (std::rand() % max_val);
		file << gen_word[select_char];
	}

	file.close();
}

void genText(int text_length, std::string name)
{
	std::ofstream file;
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::srand(seed); // sets seed

	int max_val = 17; // size of the gen_word dictionary
	char gen_word[max_val] = {'A', 'B', 'C', 'D', 'E', 'F', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '\n'};

	file.open(name);

	for (int i = 0; i < text_length; i++)
	{
		int select_char = (std::rand() % max_val);
		file << gen_word[select_char];
	}

	file.close();
}

#endif
