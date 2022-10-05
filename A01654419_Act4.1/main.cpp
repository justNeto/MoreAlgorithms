#ifndef MAIN
#define MAIN

#include "genMatFiles.h"
#include "dijstrakModule.h"
#include "floydModule.h"
#include <string>
#include <vector>

bool verbose = false;

// Prints the current development version
void prtVersion()
{
	std::cout << "1.2.0\n";
}

// Prints the help usage of the program
void prtHelp(std::string name)
{
	std::cout << "Usage: " << name << " [OPTIONS] ... [FILE] ... \n\n";

	std::cout << "Use the following options for generating test random matrix first_matrix.\n\n";
	std::cout << "  -gmf, --generate-matrix-files <F> <N>\n";
	std::cout << "       Generate a number of <F>, <N> x <N> random matrix files. They will be named automatically as matrix<0..N>.\n";
	std::cout << "       If no <N> x <M> value selected, default matrix of size 10x10 will be used.\n\n";

	std::cout << ":: < Find shortest path using dijstrak starting from all the nodes to all the nodes > :: \n";
	std::cout << "Use the following options for using dijstrak using matrix files.\n";
	std::cout << "  -ds, --dijstrak-solution FILE1, FILE2 ...\n";
	std::cout << "       Specify the files that will be used to find the shortest path for all nodes with dijstrak.\n\n";

	std::cout << "  -fs, --floyd-solution FILE1, FILE2 ...\n";
	std::cout << "       Specify the files that will be used to find the shortest path for all the nodes with floyd.\n\n";

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

	// Vectors to save the names of the first_matrix and second_matrix the program will later use
	std::vector<std::string> first_matrix; // existing first_matrix for first problem
	std::vector<std::string> second_matrix; // existing second_matrix for first problem
	std::vector<std::string> gen_files; // create matrix files

	// Boolean opts
	bool first_problem_opt = false;
	bool second_problem_opt = false;
	bool gen_file_opt = false;

	// Boolean control variables
	bool second_problem_inputed = false;
	bool first_problem_inputed = false;
	bool files_generated = false;

	// Boolean extras
	bool simulation = false; // inputting second_matrix

	// Some defaults
	int default_mat_size = 10;

	if (argc == 1) // no opts passed, program was just executed
	{
		prtHelp(binary_name);
		exit(1);
	}

	int aux = 1;

	// Loop to get the correct opts for the program
	while (aux != argc)
	{
		if ((first_problem_opt == true) && (first_problem_inputed == false))  // if first_problem_opt active and first_problem_inputed still false
		{
			// New opt in argv[aux] detected
			if (argv[aux][0] == '-')
			{
				first_problem_inputed = true; // can no longer add into this opt
				continue;
			}

			first_matrix.push_back(argv[aux]);
			aux++;

			continue;
		}

		if ((second_problem_opt == true) && (second_problem_inputed == false))  // if first_problem_opt active and first_problem_inputed still false
		{
			if (argv[aux][0] == '-')
			{
				second_problem_inputed = true; // can no longer add into this opt
				continue;
			}

			second_matrix.push_back(argv[aux]);
			aux++;

			continue;
		}

		if ((gen_file_opt == true) && (files_generated == false))  // if first_problem_opt active and first_problem_inputed still false
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

		// Generate new first_matrix of random characters
		if ((argv[aux] == std::string("-gmf")) || (argv[aux] == std::string("--generate-matrix-files")))
	      {
			gen_file_opt = true; // selects the option to work with
			aux++;
			continue;
	      }

		// Use first_matrix to solve first problem
		if ((argv[aux] == std::string("-ds")) || (argv[aux] == std::string("--dijstrak-solution")))
	      {
	            first_problem_opt = true;
			aux++;
		      continue;
	      }

		// Use second_matrix to solve first problem
	      if ((argv[aux] == std::string("-fs")) || (argv[aux] == std::string("--floyd-solution")))
	      {
		      second_problem_opt = true; // selects the option to work with
			aux++;
		      continue;
	      }

		// Start simulation mode
		if ((argv[aux] == std::string("-s")) || (argv[aux] == std::string("--simulate")))
	      {
			simulation = true; //automatically ignore any other commands and go straight to simulation
			first_matrix.clear();
			second_matrix.clear();
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
		if (verbose) std::cout << "::- Creating matrixes\n";

		// Creating vectors to find solution
		std::vector<std::string> first_matrix;
		std::vector<std::string> second_matrix;

		// Creating default first_matrix
		genMat(default_mat_size, default_mat_size, "matrix1.txt");
		genMat(default_mat_size, default_mat_size, "matrix2.txt");
		genMat(default_mat_size, default_mat_size, "matrix3.txt");

		// Pushing transmission vectors
		first_matrix.push_back("matrix1.txt");
		first_matrix.push_back("matrix1.txt");
		first_matrix.push_back("matrix3.txt");

		// Pushing mcode second_matrix
		second_matrix.push_back("matrix1.txt");
		second_matrix.push_back("matrix1.txt");
		second_matrix.push_back("matrix3.txt");

		if (verbose) std::cout << "::- Vectors & first_matrix created\n";

		// Once the first_matrix are created, the solutions for the three problems will run

		if (verbose) std::cout << "::- Solution for the first problem:\n";

		// Solution one
		solve_dijstrak(first_matrix, verbose); // passes first_matrix and second_matrix

		// Solution two
		if (verbose) std::cout << "::- Solution for the second problem:\n";
		solve_floyd(second_matrix, verbose); // passes first_matrix and second_matrix

		if (verbose) std::cout << "::- Simulation mode terminated.\n";
		exit(0);
	}

	// Code to generate random first_matrix
	if (gen_file_opt)
	{
		if (verbose) std::cout << "Generating matrix files.\n";
		std::cout << "GEN_FILES SIZE: " << gen_files.size() << "\n";

		if (gen_files.empty())
		{
			std::cout << "\n::- Missing arguments. Try " << binary_name << " -h or " << binary_name << " --help for more information.\n";
			exit(1);
		}

		// If default is only one, then only number of files to generated selected. Thus, using default sizes for matrix files.
		if (gen_files.size() == 1)
		{
			// Generate all the first_matrix with default value
			if (verbose) std::cout << "Generating " << gen_files[0] << " files.\n";

			for (int i = 1; i < std::stoi(gen_files[0]) + 1; i++)
			{
				std::string aux = std::to_string(i);
				std::string result = "matrix" + aux + ".txt";

				genMat(default_mat_size, default_mat_size, result); // generates a mat file of default size
			}
		}

		// If default is two then error, using <N> and <M> options
		if (gen_files.size() == 2)
		{
			// Generate all the first_matrix with default value
			if (verbose) std::cout << "Generating " << gen_files[0] << " files.\n";

			for (int i = 1; i < std::stoi(gen_files[0]) + 1; i++)
			{
				std::string aux = std::to_string(i);
				std::string result = "matrix" + aux + ".txt";

				genMat(std::stoi(gen_files[1]), std::stoi(gen_files[1]), result); // gens a mat file of size gen_file[1] x gen_file[1]
			}
		}

		if (gen_files.size() > 2) // using <F> : number of files, <N> rows and  <M> cols
		{
			std::cout << "\n::- Invalid arguments. Try " << binary_name << " -h or " << binary_name << " --help for more information.\n";
			exit(1);
		}
	}

	// Code to validate if first_matrix exist
	if (first_problem_opt)
	{
		if (first_matrix.empty())
		{
			std::cout << "\n::- Missing arguments. Try " << binary_name << " -h or " << binary_name << " --help for more information UWU.\n";
			exit(1);
		}

		// Else use the first_matrix
		for (auto &file_name : first_matrix)
		{
			if (verbose) std::cout << "Searching for file : " << file_name << "\n";

			std::ifstream infile(file_name); // create ifstream var to read from

			if (infile.fail())
			{
				if (verbose) std::cout << "File does not exist\n";
				std::cout << "\n::-Inputted '" << file_name << "' file does not exist. Ignoring it and going to the next file.\n\n";

				continue;
			}

			if (verbose) std::cout << "File does exist\n";
		}
	}

	// Code to validate if second_matrix exist
	if (second_problem_opt)
	{
		if (second_matrix.empty())
		{
			std::cout << "\n::- Missing arguments. Try " << binary_name << " -h or " << binary_name << " --help for more information OWO.\n";
			exit(1);
		}

		// Else use the second_matrix
		for (auto &file_name : second_matrix)
		{
			if (verbose) std::cout << "Searching for file : " << file_name << "\n";
			std::ifstream infile(file_name); // create ifstream var to read from

			if(infile.fail())
			{
				std::cout << "\n::-Error. Inputted '" << file_name << "' file does not exist.";
				exit(1);
			}

			if (verbose) std::cout << "File does exist\n\n";
		}
	}

	// Call solve problems
	if ((first_matrix.size() != 0) && (first_problem_opt)) // if first_problem_opt and file is not empty
	{
		// Solve first problem function
		solve_dijstrak(first_matrix, verbose);
	}
	else if ((first_problem_opt) && (first_matrix.size() == 0)) // if first_problem_opt and file is empty
	{
		std::cout << "\n::- Missing arguments. Try " << binary_name << " -h or " << binary_name << " --help for more information.\n";
		exit(1);
	}

	if ((second_matrix.size() != 0) && (second_problem_opt)) // if first_problem_opt and second_problem_opt selected
	{
		// Solve first problem function
		solve_floyd(second_matrix, verbose);
	}
	else if ((second_problem_opt) && (second_matrix.size() == 0)) // if second_problem_opt and file is empty
	{
		std::cout << "\n::- Missing arguments. Try " << binary_name << " -h or " << binary_name << " --help for more information.\n";
		exit(1);
	}
}

#endif
