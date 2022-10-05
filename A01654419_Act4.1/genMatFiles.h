#ifndef GEN_MAT_FILES
#define GEN_MAT_FILES

#include <iostream>
#include <fstream>
#include <chrono>

void genMat(int rows_num, int cols_num, std::string name)
{
	std::ofstream file;
	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::srand(seed); // sets seed

	int max_val = 100;

	file.open(name);

	std::cout << "ROWS NUM: " << rows_num << std::endl;
	std::cout << "COLS NUM: " << rows_num << std::endl;

	for (int i = 0; i < rows_num; i++) // while i is less than lenght of rows
	{
		for (int j = 0; j < cols_num; j++)
		{
			if (i == j)
			{
				file << 0 << " ";
			}
			else
			{
				int val = (std::rand() % max_val);
				file << val;
				file << " ";
			}

		}
		file << std::endl;
	}

	file.close();
}

#endif
