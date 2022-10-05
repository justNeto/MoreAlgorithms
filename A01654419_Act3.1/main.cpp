#ifndef MAIN
#define MAIN

#include "genTxtFiles.h"
#include "triesModule.h"
#include <vector>

bool verbose = false;

// Prints the current development version
void prtVersion()
{
	std::cout << "3.2.0\n";
}

// Prints the help usage of the program
void prtHelp(std::string name)
{
	std::cout << "Usage: " << name << " [OPTIONS] ... [FILE] ... \n\n";

	std::cout << "Use the following options for generating test random files and patterns.\n\n";
	std::cout << "  -gf, --generate-files <N> <M>\n";
	std::cout << "       Generate a number of <N> random files with a length of <M>. They will be named automatically as create_nodes<0..N>.\n";
	std::cout << "       If no <M> value selected, default file size of length 10000 will be used.\n\n";
	std::cout << "  -gp, --generate-patterns <N> <M>\n";
	std::cout << "       Generate a number of <N> random patterns with a length of <M>. They will be automatically as words<0...N>.\n";
	std::cout << "       If no <M> value selected, default file size of length 10 will be used.\n\n";

	std::cout << ":: < Create TRIE and find them in a file  > :: \n";
	std::cout << "Use the following options for searching patterns in files.\n";
	std::cout << "  -cnff, --create-nodes-from-file FILE1, FILE2 ...\n";
	std::cout << "       Specify the files that will be used to create nodes. -sfw or --search-for-words option must be used along this one.\n\n";

	std::cout << "  -sfw, --search-for-words	FILE1, FILE2 ...\n";
	std::cout << "       Specify the words that will be searched. -sfw or --search-for-words option must be used along this one.\n\n";

	std::cout << ":: < Simulation mode > :: \n";
	std::cout << "  -s, --simulate					Creates three random files in current directory and solves the problems using them.\n\n";

	std::cout << ":: < Other opts > :: \n";

	std::cout << "  -v, --verbose						prints the program specifics in runtime.\n";
	std::cout << "  -h, --help						shows this help menu and exit.\n";
	std::cout << "  --version						displays current version of script.\n";
}

// Argc: number of arguments including the program name
// Argv: the vector in char ** format
int main(int argc, char ** argv)
{
	std::string binary_name = argv[0];

	// Vectors to save the names of the files and patterns the program will later use
	std::vector<std::string> files; // existing files for first problem
	std::vector<std::string> patterns; // existing patterns for first problem
	std::vector<std::string> gen_files; // create files
	std::vector<std::string> gen_patterns; // create patterns

	// Boolean opts
	bool file_opt = false;
	bool pattern_opt = false;
	bool gen_file_opt = false;
	bool gen_pattern_opt = false;

	// Boolean control variables
	bool patterns_inputed = false;
	bool patterns_generated = false;
	bool files_inputed = false;
	bool files_generated = false;

	// Boolean extras
	bool simulation = false; // inputting patterns

	// Some defaults
	int default_text_size = 10000;
	int default_pattern_size = 5;

	if (argc == 1) // no opts passed, program was just executed
	{
		prtHelp(binary_name);
		exit(1);
	}

	int aux = 1;

	// Loop to get the correct opts for the program
	while (aux != argc)
	{
		if ((file_opt == true) && (files_inputed == false))  // if file_opt active and files_inputed still false
		{
			// New opt in argv[aux] detected
			if (argv[aux][0] == '-')
			{
				files_inputed = true; // can no longer add into this opt
				continue;
			}

			files.push_back(argv[aux]);
			aux++;

			continue;
		}

		if ((pattern_opt == true) && (patterns_inputed == false))  // if file_opt active and files_inputed still false
		{
			if (argv[aux][0] == '-')
			{
				patterns_inputed = true; // can no longer add into this opt
				continue;
			}

			patterns.push_back(argv[aux]);
			aux++;

			continue;
		}

		if ((gen_file_opt == true) && (files_generated == false))  // if file_opt active and files_inputed still false
		{
			if (argv[aux][0] == '-')
			{
				files_generated = true;
				continue;
			}

			gen_files.push_back(argv[aux]);
			aux++;

			continue;
		}

		if ((gen_pattern_opt == true) && (patterns_generated == false))  // if file_opt active and files_inputed still false
		{
			if (argv[aux][0] == '-')
			{
				patterns_generated = true;
				continue;
			}

			gen_patterns.push_back(argv[aux]);
			aux++;

			continue;
		}

		// Generate new files of random characters
		if ((argv[aux] == std::string("-gf")) || (argv[aux] == std::string("--generate-files")))
	      {
			gen_file_opt = true; // selects the option to work with
			aux++;
			continue;
	      }

		// Generate new files of random patterns
		if ((argv[aux] == std::string("-gp")) || (argv[aux] == std::string("--generate-patterns")))
	      {
			gen_pattern_opt = true; // selects the option to work with
			aux++;
			continue;
	      }

		// Use files to solve first problem
		if ((argv[aux] == std::string("-cnff")) || (argv[aux] == std::string("--create-nodes-from-file")))
	      {
	            file_opt = true;
			aux++;
		      continue;
	      }

		// Use patterns to solve first problem
	      if ((argv[aux] == std::string("-sfw")) || (argv[aux] == std::string("--search-for-words")))
	      {
		      pattern_opt = true; // selects the option to work with
			aux++;
		      continue;
	      }

		// Start simulation mode
		if ((argv[aux] == std::string("-s")) || (argv[aux] == std::string("--simulate")))
	      {
			simulation = true; //automatically ignore any other commands and go straight to simulation
			files.clear();
			patterns.clear();
			break;
	      }

		// Activate verbose mode
	      if ((argv[aux] == std::string("-v")) || (argv[aux] == std::string("--verbose"))) // if file options selected
	      {
			verbose = true;
			aux++;
			continue;
	      }

		// Show current version of proyect
	      if (argv[aux] == std::string ("--version")) // if file options selected
	      {
			prtVersion();
		      exit(0);
	      }

	      if ((argv[aux] == std::string ("-h")) || (argv[aux] == std::string("--help"))) // if file options selected
	      {
			prtHelp(binary_name);
			exit(0);
	      }

	      // If not entering a file then some erros has been made
	      std::cout << "Invalid option. Please try " << binary_name << " -h or " << binary_name << " --help for more information.\n";
		exit(1);
	}

	// Checking all the opts
	if (simulation == true)
	{
		if (verbose) std::cout << "| --- [Simulation mode activated] --- | \n";
		if (verbose) std::cout << "In simulation mode, default values will be used for file and words to find.\n";
		if (verbose) std::cout << "::- Creating files\n";

		// Creating vectors to find solution
		std::vector<std::string> files_vector;
		std::vector<std::string> patterns_vector;

		// Creating default files
		genText(default_text_size, "create_nodes1.txt");
		genText(default_text_size, "create_nodes2.txt");
		genPattern(default_pattern_size, "words1.txt");
		genPattern(default_pattern_size, "words2.txt");
		genPattern(default_pattern_size, "words3.txt");

		// Pushing transmission vectors
		files.push_back("create_nodes1.txt");
		files.push_back("create_nodes2.txt");

		// Pushing mcode patterns
		patterns.push_back("words1.txt");
		patterns.push_back("words2.txt");
		patterns.push_back("words3.txt");

		if (verbose) std::cout << "::- Vectors & files created\n";

		// Once the files are created, the solutions for the three problems will run

		if (verbose) std::cout << "::- Solution for the first problem:\n";
		// Solution one
		tries_words_solutions(files, patterns, verbose); // passes files and patterns

		if (verbose) std::cout << "::- Simulation mode terminated.\n";
		exit(0);
	}

	// Code to generate random files
	if (gen_file_opt)
	{
		if (verbose) std::cout << "Generating files.\n";

		if (gen_files.empty())
		{
			std::cout << "\n::- Missing arguments. Try " << binary_name << " -h or " << binary_name << " --help for more information.\n";
			exit(1);
		}

		// If default is only one, then only number of files selected. Thus, using default size.
		if (gen_files.size() == 1)
		{
			// Generate all the files with default value
			if (verbose) std::cout << "Generating " << gen_files[0] << " files.\n";

			for (int i = 1; i < std::stoi(gen_files[0]) + 1; i++)
			{
				std::string aux = std::to_string(i);
				std::string result = "create_nodes" + aux + ".txt";

				genText(default_text_size, result);
			}
		}

		// If default is two, using <N> and <M> options
		if (gen_files.size() == 2)
		{
			// Generate all the files with default value
			if (verbose) std::cout << "Generating " << gen_files[0] << " files of length " << gen_files[1] << ".\n"; // number of files

			for (int i = 1; i < std::stoi(gen_files[0]) + 1; i++)
			{
				std::string aux = std::to_string(i);
				std::string result = "create_nodes" + aux + ".txt";

				int aux2 = std::stoi(gen_files[1]);

				genText(aux2, result);
			}
		}
		// After inputing opts process them
		if (gen_files.size() > 2)
		{
			std::cout << "\n::- Invalid arguments. Try " << binary_name << " -h or " << binary_name << " --help for more information.\n";
			exit(1);
		}

	}

	// Code to validate if files exist
	if (file_opt)
	{
		if (files.empty())
		{
			std::cout << "\n::- Missing arguments. Try " << binary_name << " -h or " << binary_name << " --help for more information.\n";
			exit(1);
		}

		// Else use the files
		for (auto &file_name : files)
		{
			if (verbose) std::cout << "Searching for file : " << file_name << "\n";

			std::ifstream infile(file_name); // create ifstream var to read from

			if(infile.fail())
			{
				if (verbose) std::cout << "File does not exist\n";
				std::cout << "\n::-Inputted '" << file_name << "' file does not exist. Ignoring it and going to the next file.\n\n";

				continue;
			}

			if (verbose) std::cout << "File does exist\n";
		}
	}

	// Code to generate random patterns
	if (gen_pattern_opt)
	{
		if (verbose) std::cout << "Generating patterns.\n";

		// If empty then delete the pattern.
		if (gen_patterns.empty())
		{
			std::cout << "\n::- Missing arguments. Try " << binary_name << " -h or " << binary_name << " --help for more information.\n";
			exit(1);
		}

		// If default is only one, then only number of files selected. Use default size
		if (gen_patterns.size() == 1)
		{
			// Generate all the files with default value
			if (verbose) std::cout << "Generating " << gen_patterns[0] << " files.\n";

			for (int i = 1; i < std::stoi(gen_patterns[0]) + 1; i++)
			{
				std::string aux = std::to_string(i);
				std::string result = "words" + aux + ".txt";

				genPattern(default_pattern_size, result);
			}
		}

		// If default is two, using <N> and <M> options
		if (gen_patterns.size() == 2)
		{
			// Generate all the files with default value
			if (verbose) std::cout << "Generating " << gen_patterns[0] << " files of length " << gen_patterns[1] << ".\n"; // number of files

			for (int i = 1; i < std::stoi(gen_patterns[0]) + 1; i++)
			{
				std::string aux = std::to_string(i);
				std::string result = "words" + aux + ".txt";

				int aux2 = std::stoi(gen_patterns[1]);

				genPattern(aux2, result);
			}
		}

		// After inputing opts process them
		if (gen_patterns.size() > 2)
		{
			std::cout << "\n::- Invalid syntax. Try " << binary_name << " -h or " << binary_name << " --help for more information.\n";
			exit(1);
		}

	}

	// Code to validate if patterns exist
	if (pattern_opt)
	{
		if (patterns.empty())
		{
			std::cout << "\n::- Missing arguments. Try " << binary_name << " -h or " << binary_name << " --help for more information.\n";
			exit(1);
		}

		// Else use the patterns
		for (auto &file_name : patterns)
		{
			if (verbose) std::cout << "Searching for pattern : " << file_name << "\n";
			std::ifstream infile(file_name); // create ifstream var to read from

			if(infile.fail())
			{
				std::cout << "\n::-Error. Inputted '" << file_name << "' file does not exist.";
				exit(1);
			}

			if (verbose) std::cout << "Pattern file does exist\n\n";
		}
	}

	// If both patterns and files exist, pass those vectors to function 1.
	if ((files.size() != 0) && (patterns.size() != 0) && (file_opt) && (pattern_opt)) // if file_opt and pattern_opt selected
	{
		// Solve first problem function
		tries_words_solutions(files, patterns, verbose);
	}
	else if ((files.size() != 0) && patterns.empty()) // if files exist but patterns does not
	{
			std::cout << "::-Missing arguments. -sfw or --search-for-words files should also be specified.\n";
			exit(1);
	}
	else if (files.empty() && (patterns.size() != 0)) // if patterns exist but files does not
	{
			std::cout << "::-Missing arguments. -cnff or --create-nodes-from-file files should also be specified.\n";
			exit(1);
	}
}

#endif
