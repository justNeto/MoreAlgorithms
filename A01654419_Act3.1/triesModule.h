#ifndef TRS_MODULE
#define TRS_MODULE

#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Node
{
	char value; // value of the node
	std::vector<struct Node*> connected_nodes;
	Node() : connected_nodes(0) {}

	void printLevels (std::string prefix, int currLevel)
	{
		if (currLevel == 0)
			std::cout << " R <-- Level " << currLevel << "\n\n";
		else
			std::cout << " " << prefix << value << " <-- Level " << currLevel << "\n\n";

		currLevel++;

		for (struct Node * node : connected_nodes) // iterates for current node in all the structure
		{
			node->printLevels(prefix + "|   ", currLevel);
		}
	}
};

void search_in_trie(std::vector<std::string> words, std::vector<std::string> find, bool verbose)
{
	struct Node *root = new Node(); // ptr to root struct in memory
	root->value = ' '; // value set

	for (auto word : words)
	{
		// Each time a word is passed then the curr_node pointer that points to the root struct in memory is updated
		struct Node *curr_node = new Node(); // ptr to root struct in memory
		curr_node =	root;

		word.erase(remove_if(word.begin(), word.end(), isspace), word.end());
		if (verbose) std::cout << "| --- Current word: " << word << "--- |\n";

		for (auto letter : word)
		{
			if (verbose)
			{
				std::cout << "\n[ LETTER SECTION]\n";
				std::cout << "Current letter: [" << letter << "]\n";
				std::cout << "Current node value: [" << curr_node->value << "].\n\n";
			}

			if (letter == curr_node->value) // if the current letter is the same as the current node then
			{
				if (verbose) std::cout << "::- Letter value is the same as current node value\n";
				continue; // goes to the next leter
			}
			else if (letter != curr_node->value) // if the current letter is not the same as the value in the current node
			{
				if (verbose)
				{
					std::cout << "[ CREATING/UPDATING NODE SECTION]\n";
					std::cout << "::-Letter is not the same as curr_node value: " << letter << "\n";
				}

				int size = curr_node->connected_nodes.size();

				if (verbose)
				{
					std::cout << "::///Current node array size is " << size << "\n";
					std::cout << "::/--Current node ptr value: " << curr_node << "\n\n";
				}

				// Check the curr_ptrs vector and see if you can find the value of the current letter inside
				bool value_found = false; // bool var to register when a value was found inside the vector of current node

				// Search for the value in the lists of node
				if (curr_node->connected_nodes.size() == 0)
				{
					value_found = false;
				}
				else  // search for it
				{
					for (int i = 0; i < size; i++)
					{
						struct Node *search_ptr; // ptr to root struct in memory

						search_ptr = curr_node->connected_nodes[i];
						if (verbose) std::cout << "--------- search_ptr set with value of: [" << search_ptr << "]\n";

						if (search_ptr->value == letter) // if a value of a node in the current node vector of pointers is found
						{
							// Do not create a new ptr an add it to the curr_node, only set the curr_node to the ptr found
							if (verbose) std::cout << "The letter [" << letter << "] and the search_ptr->value [" << search_ptr->value << "] do coincide\n";
							curr_node = curr_node->connected_nodes[i];
							value_found = true;
							break;
						}
					}
				}

				if (!value_found)
				{
					if (verbose) std::cout << "	No letter value was found. Creating a new node\n";

					// Create new node and add it to curr_node vect
					struct Node *new_ptr = new Node(); // ptr to root struct in memory

					new_ptr->value = letter; // new value of the new node is the word

					if (verbose)
					{
						std::cout << "	[[Updating current row vector array]]\n";
						std::cout << "		--Size of the current node before " << curr_node->connected_nodes.size() << "\n";
					}
					curr_node->connected_nodes.push_back(new_ptr); // pushes the pointer of the new node to the curr_node vector of pointers
					if (verbose) std::cout << "		--Size of the current node after " << curr_node->connected_nodes.size() << "\n";

					if (verbose)
					{
						int size = new_ptr->connected_nodes.size();
						std::cout << " 	::/--New node array size is " << size << "\n";
						std::cout << "	------: New ptr value: " << new_ptr << "\n";
						std::cout << "	------: New node value: " << new_ptr->value << "\n";
						std::cout << "	Current node will now be new node.\n";
					}
					// Updates current node
					curr_node = new_ptr;
				}
			}

		}
	} // trie structure created

	for (auto word : find)
	{
		// Each time a word is passed then the curr_node pointer that points to the root struct in memory is updated
		struct Node *curr_node = new Node(); // curr_node is used to find the word
		curr_node =	root;

		bool in_tree = true;

		word.erase(remove_if(word.begin(), word.end(), isspace), word.end()); // parses in case of spaces or empty or whatever
		if (verbose) std::cout << "| --- Current word: " << word << "--- |\n";

		for (auto letter : word)
		{

			bool value_found = false; // bool var to register when a value was found inside the vector of current node

			if (verbose)
			{
				std::cout << "\n[ LETTER SECTION]\n";
				std::cout << "Current letter: [" << letter << "]\n";
				std::cout << "Current node value: [" << curr_node->value << "].\n\n";
			}

			if (letter == curr_node->value) // if the current letter is the same as the current node
			{
				if (verbose) std::cout << "::- Letter value is the same as current node value\n"; // we know a letter has been found
				continue; // checking for next letter
			}
			else if (letter != curr_node->value) // if the current letter is not the same as the value in the current node, look for it inside the ptrs vect
			{
				if (verbose)
				{
					std::cout << "[ CREATING/UPDATING NODE SECTION]\n";
					std::cout << "::-Letter is not the same as curr_node value: " << letter << "\n";
				}

				int size = curr_node->connected_nodes.size();

				if (verbose)
				{
					std::cout << "::///Current node array size is " << size << "\n";
					std::cout << "::/--Current node ptr value: " << curr_node << "\n\n";
				}

				// Check the curr_ptrs vector and see if you can find the value of the current letter inside

				// Search for the value in the lists of node
				if (curr_node->connected_nodes.size() == 0)
				{
					value_found = false; // does not exist the current word in the tree
				}
				else  // search for it
				{
					for (int i = 0; i < size; i++)
					{
						struct Node *search_ptr; // ptr to root struct in memory

						search_ptr = curr_node->connected_nodes[i];
						if (verbose) std::cout << "--------- search_ptr set with value of: [" << search_ptr << "]\n";

						if (search_ptr->value == letter) // if a value of a node in the current node vector of pointers is found it might still be in the tree
						{
							// Do not create a new ptr an add it to the curr_node, only set the curr_node to the ptr found
							if (verbose) std::cout << "The letter [" << letter << "] and the search_ptr->value [" << search_ptr->value << "] do coincide\n";
							curr_node = curr_node->connected_nodes[i];
							value_found = true;
							break;
						}
					}
				}

			}

			if (!value_found) // if the value was not found, print so
			{
				std::cout << "||-- [ Current word " << word << " is NOT in the tree! ] --||\n";
				in_tree = false;
				break;
			}
		}

		if (in_tree)
		{
			std::cout << "||-- [ Current word " << word << " is in the tree! ] --||\n";
		}
	}

	std::cout << "\nLevels <n> | value :\n";
	root->printLevels("", 0);
}

std::string parse_files(std::string line)
{
	line.erase(remove_if(line.begin(), line.end(), isspace), line.end()); // removes empty spaces
	return line;
}

void findInFile(std::string file_name, std::string pattern_name, bool verbose)
{
	std::ifstream infile(file_name); // read each line of file
	std::ifstream inpattern(pattern_name); // read each line of pattern

	std::string searching = "\n[ Creating TRIE structure using " + pattern_name + " and searching words in " + file_name + " ]\n";
	std::cout << searching;

	std::string pattern;
	std::string line;

	std::vector<std::string> words;
	std::vector<std::string> find_words;

	while (std::getline(infile, line)) // gets a line
	{
		if (line.empty()) // ignore that line
		{
			std::cout << "empty line found. ignoring...\n";
		}
		else
		{
			words.push_back(parse_files(line));
		}
	}

	while (std::getline(inpattern, pattern)) // gets a line
	{
		if (pattern.empty()) // ignore that line
		{
			std::cout << "empty line found. ignoring...\n";
		}
		else
		{
			find_words.push_back(parse_files(pattern));
		}
	}

	// After parsing input files and vectors are created, pass them to the solution function
	search_in_trie(words, find_words, verbose);
}

// First problem consist in each transmission file
void tries_words_solutions(std::vector<std::string> files, std::vector<std::string> patterns, bool verbose)
{
	std::string greetings = "| --- Start searching for patterns --- | \n";
	std::cout << greetings;

	for (auto &file_name : files) // selects the current file name in vector
	{
		for (auto &pattern_name : patterns) // selects the current pattern in vector
		{
			findInFile(file_name, pattern_name, verbose); // passes the file and the patterns files
		}
	}
}

#endif
