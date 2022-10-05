#ifndef DIJS_MODULE
#define DIJS_MODULE

#include <iostream>
#include "validationModule.h"
#include <queue>
#include <set>
#include <limits.h>
#include <vector>

void dijstrak_algorithm(std::vector <std::vector<int> > mat, int start, int end)
{
	std::queue<int> path; // queue to store path
	int *distance = new int[mat[0].size()]; // ptr to distance array
	bool *visited = new bool[mat[0].size()]; // ptr to visited array
	int min, next; // min and next node

	for (int i = 0; i < mat[0].size(); i++)
	{
		distance[i] = mat[start][i]; // fill the distance array for the starting node with the weight of the edges
		visited[i] = false; // visited array for the current node start is false as none of the nodes are visited yet
		path.push(start); // first value of the path is the starting node
	}

	distance[start] = 0; // first distance is always 0 for the first node=
	visited[start] = true; // first node has been visited

	for (int i = 0; i < mat[0].size(); i++)  // do that for all the nodes in the mat until the path of the min value has been reached
	{
		min = INT_MAX;
		next = 0;

		for (int j = 0; j < mat[0].size(); j++)
		{
			if (distance[j] < min && !visited[j])  // if any of the distances is less than current min value then the current distance for j is that distance
			{
			min = distance[j];
			next = j; // the next node to be visited according to the min distance found for the current node
			}
		}

		visited[next] = true; // the next node will be visited

		for (int j = 0; j < mat[0].size(); j++)
		{
			if (!visited[j])  // if not visited
			{
				if (min + mat[next][j] < distance[j])  // check if the value of min + [next][j] is less than the distance in that j in distance vector
				{
				distance[j] = min + mat[next][j]; // fi it is then update distance in distance vector
				path.push(next); // push the next node to the path
				}
			}
		}
	}

	std::cout << "--: Shortest distance possible from node " << start << " to node " << end << ": " << distance[end] << std::endl;

	path.push(end);

	bool path_found = false;

	for (int i = 0; i < mat[0].size(); i++)
	{
		if (mat[start][i] == distance[end]) // if the value of end is found in connections then path will be only current node and end node
		{

			std::cout << " Path: " << start << ", " << end << std::endl;
			path_found = true;
			break;
		}
	}

	if (path_found == false) // if the path is not found then print the path
	{
		std::cout << " Path: " << start;
		int last_path = start;

		while (!path.empty())
		{
			if (path.front() == last_path) // if there is not a var "edge"
                  {
                        path.pop();
			}
			else
			{
				std::cout << ", " << path.front() << "";
				last_path = path.front();
				path.pop();
			}
		}

		std::cout << "\n";
	}
}

// First problem consist in each transmission file
void solve_dijstrak(std::vector<std::string> files, bool verbose)
{
	std::string greetings = "| --- Start finding shortest paths for files --- | \n";
	std::cout << greetings;

	std::vector<std::vector<int>> matrix;
	std::string algorithm = "Dijstrak's";

	for (auto &file_name : files) // selects the current file name in vector
	{
		matrix = validate_matrix_input(file_name, algorithm); // passes the file and the patterns files

		// Apply dijstrak after validation using adjacency matrix
		for (int i = 0; i < matrix[0].size(); i++)
		{
			for (int j = 0; j < matrix[0].size(); j++)
			{
				if (i != j)
				{
					dijstrak_algorithm(matrix, i, j);
				}
			}
		}
	}
}

#endif
