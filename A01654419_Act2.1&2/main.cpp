#ifndef MAIN
#define MAIN

#include "genTxtFiles.h"
#include "hashProblem.h"
#include "suffixProblem.h"
#include <ctime>
#include <vector>

bool verbose;

// Prints the current development version
void prtVersion()
{
	std::cout << "1.0.0\n";
}

// Prints the help usage of the program
void prtHelp(std::string name)
{
	/* std::cout << "Usage: runProject [OPTIONS] ... [FILE] ... \n\n"; */
	std::cout << "Usage: " << name << " [OPTIONS] ... [FILE] ... \n\n";

	std::cout << "Use the following options for generating test random files and patterns.\n\n";
	std::cout << "  -gf, --generate-files <N> <M>\n";
	std::cout << "       Generate a number of <N> random files with a length of <M>. They will be named automatically as hash_file_<0..N>.\n";
	std::cout << "       If no <M> value selected, default file size of length 10000 will be used.\n\n";
	std::cout << "  -gs, --generate-string <N> <M>\n";
	std::cout << "       Generate a number of <N> random patterns with a length of <M>. They will be automatically as suffix_file_<0...N>.\n";
	std::cout << "       If no <M> value selected, default file size of length 10 will be used.\n\n";

	std::cout << "Use the following options for converting a file to a single string file.\n\n";

	std::cout << ":: < Hash string problem > :: \n";
	std::cout << "Passes a text file and solves it.\n";
	std::cout << "  -hs, --hash-string FILE1, <N_COL> ...\n";
	std::cout << "		Solves hash string problem by passing a file from standard input and generating <N_COL> columns. <N_COL> value should be between 16 and 64.\n\n";

	std::cout << ":: < Sufix array problem > :: \n";
	std::cout << "Passes a text file and solves it.\n";
	std::cout << "  -sa --sufix-array FILE1\n";
	std::cout << "       Specify the file that will be used to create the suffix array and order them alphabetically. \n\n";

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
	std::vector<std::string> files_hash_array; // existing files
	std::vector<std::string> files_suffix_array; // existing files
	std::vector<std::string> gen_files; // existing files
	std::vector<std::string> gen_patterns; // create patterns

	// Boolean opts
	bool files_hash_opt = false;
	bool files_suffix_opt = false;
	bool gen_file_opt = false;
	bool gen_pattern_opt = false;

	// Boolean control variables
	bool files_hash_inputted = false;
	bool files_suffix_inputted = false;
	bool files_generated = false;
	bool patterns_generated = false;

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
		if ((files_hash_opt == true) && (files_hash_inputted == false))  // if file_opt active and files_inputed still false
		{
			// New opt in argv[aux] detected
			if (argv[aux][0] == '-')
			{
				files_hash_inputted = true; // can no longer add into this opt
				continue;
			}

			files_hash_array.push_back(argv[aux]);
			aux++;

			continue;
		}

		if ((files_suffix_opt == true) && (files_suffix_inputted == false))  // if file_opt active and files_inputed still false
		{
			// New opt in argv[aux] detected
			if (argv[aux][0] == '-')
			{
				files_suffix_inputted = true; // can no longer add into this opt
				continue;
			}

			files_suffix_array.push_back(argv[aux]);
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

		/*
		Detecting the opts and starting file inputting
		*/

		// Generate files
		if ((argv[aux] == std::string("-gf")) || (argv[aux] == std::string("--generate-files")))
	      {
			gen_file_opt = true; // selects the option to work with
			aux++;
			continue;
	      }

		if ((argv[aux] == std::string("-gs")) || (argv[aux] == std::string("--generate-string")))
	      {
			gen_pattern_opt = true; // selects the option to work with
			aux++;
			continue;
	      }

		// Files for first problem
		if ((argv[aux] == std::string("-hs")) || (argv[aux] == std::string("--hash-string")))
	      {
	            files_hash_opt = true;
			aux++;
		      continue;
	      }

		// Files for second problem
	      if ((argv[aux] == std::string("-sa")) || (argv[aux] == std::string("--suffix-array")))
	      {
		      files_suffix_opt = true; // selects the option to work with
			aux++;
		      continue;
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
	      std::cout << "Invalid option. Try " << binary_name << " -h or " << binary_name << " --help for more information.\n";
		exit(1);
	}

	/*
	   | --- After parsing options then validate the files that will be used. If there are errors then return status 1 --- |
	*/

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
				std::string result = "suffix_file_" + aux + ".txt";

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
				std::string result = "suffix_file_" + aux + ".txt";

				int aux2 = std::stoi(gen_patterns[1]);

				genPattern(aux2, result);
			}
		}

		// After inputing opts process them
		if (gen_patterns.size() > 2)
		{
			std::cout << "\n::- Invalid syntax. Try findPattern -h or findPattern --help for more information. \n";
			exit(1);
		}

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
				std::string result = "hash_file_" + aux + ".txt";

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
				std::string result = "hash_file_" + aux + ".txt";

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

	// Code to validate if files for hash opt exist
	if (files_hash_opt)
	{
		if (files_hash_array.empty())
		{
			std::cout << "\n::- Missing arguments. Try " << binary_name << " -h or " << binary_name << " --help for more information.\n";
			exit(1);
		}

		if (files_hash_array.size() == 1)
		{
			std::cout << "\n::- Missing arguments. Try " << binary_name << " -h or " << binary_name << " --help for more information.\n";
			exit(1);
		}

		if (files_hash_array.size() >= 2) // if is bigger or equal than 2
		{
			int n;

			try
			{
				n = std::stoi(files_hash_array[files_hash_array.size()-1]);

				if ((n >= 16) && (n <= 64))
				{
					if (verbose) std::cout << "<N_COL> value is correct.\n";
				}
				else
				{
					std::cout << "\n::- <N_COL> value is not between 16 and 64. Try " << binary_name << " -h or " << binary_name << " --help for more information.\n";
					exit(1);
				}

				if (n % 4 != 0) // not a multiple of 4
				{
					std::cout << "\n::- <N_COL> value is not a multiple of 4. Try " << binary_name << " -h or " << binary_name << " --help for more information.\n";
					exit(1);
				}
			}
			catch (...)
			{
				std::cout << "\n::- Error. Try " << binary_name << " -h or " << binary_name << " --help for more information.\n";
				exit(1);
			}

			std::cout << "n value " << n << "\n";

			for (int i = 0; i < files_hash_array.size()-2; i++)
			{
				if (verbose) std::cout << "Searching for file : " << files_hash_array[i] << "\n";

				std::ifstream infile(files_hash_array[i]); // create ifstream var to read from

				if(infile.fail())
				{
					std::cout << "\n::-Error. Inputted '" << files_hash_array[i] << "' file does not exist.";
					exit(0);
				}

				if (verbose) std::cout << "File does exist\n";
			}

		}
		else
		{
			std::cout << "\n::- Missing arguments. Try " << binary_name << " -h or " << binary_name << " --help for more information.\n";
			exit(1);
		}
	}

	// Code to validate if files for suffix opt exist
	if (files_suffix_opt)
	{
		if (files_suffix_array.empty())
		{
			std::cout << "\n::-Missing arguments. Try findPattern -h or findPattern --help for more information. \n";
			exit(1);
		}

		// Else use the files
		for (auto &file_name : files_suffix_array)
		{
			if (verbose) std::cout << "Searching for file : " << file_name << "\n";

			std::ifstream infile(file_name); // create ifstream var to read from

			if(infile.fail())
			{
				std::cout << "\n::-Error. Inputted '" << file_name << "' file does not exist.";
				exit(0);
			}

			if (verbose) std::cout << "File does exist\n";
		}
	}

	/*
	   | --- Invoke the code to solve the problems --- |
	*/

	if ((files_hash_array.size() != 0) && (files_hash_opt)) // if file_opt and pattern_opt selected
	{
		// Solve hash string problem and pass the string vectors with the files to be used
		solutionHashString(files_hash_array);
	}

	if ((files_suffix_array.size() != 0) && (files_suffix_opt))
	{
		// Solve hash string problem and pass the string vectors with the files to be used
		solutionSuffixArray(files_suffix_array);
	}
}

#endif
