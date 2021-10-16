#include <iostream>
#include <climits>
#include <iomanip>
using namespace std;

// Total number of vertices in the `adjMatrix`
#define N 4

// Define infinity
#define I INT_MAX

// Recursive function to print path of given
// vertex `u` from source vertex `v`
void printPath(int path[][N], int v, int u)
{
	if (path[v][u] == v) {
		return;
	}

	printPath(path, v, path[v][u]);
	cout << path[v][u] << " ";
}

// Function to print the shortest cost with path
// information between all pairs of vertices
void printSolution(int cost[N][N], int path[N][N])
{
	for (int v = 0; v < N; v++)
	{
		for (int u = 0; u < N; u++)
		{
			if (u != v && path[v][u] != -1)
			{
				cout << "The shortest path from " << v << " —> " << u << " is ("
					<< v << " ";
				printPath(path, v, u);
				cout << u << ")" << endl;
			}
		}
	}
}

// Function to run the Floyd–Warshall algorithm
void floydWarshall(int adjMatrix[][N])
{
	// `cost[]` and `parent[]` stores shortest path
	// (shortest-cost/shortest route) information
	int cost[N][N], path[N][N];

	// initialize `cost[]` and `parent[]`
	for (int v = 0; v < N; v++)
	{
		for (int u = 0; u < N; u++)
		{
			// initially, cost would be the same as the weight of the edge
			cost[v][u] = adjMatrix[v][u];

			if (v == u) {
				path[v][u] = 0;
			}
			else if (cost[v][u] != INT_MAX) {
				path[v][u] = v;
			}
			else {
				path[v][u] = -1;
			}
		}
	}

	// run Floyd–Warshall
	for (int k = 0; k < N; k++)
	{
		for (int v = 0; v < N; v++)
		{
			for (int u = 0; u < N; u++)
			{
				// If vertex `k` is on the shortest path from `v` to `u`,
				// then update the value of `cost[v][u]` and `path[v][u]`

				if (cost[v][k] != INT_MAX && cost[k][u] != INT_MAX
					&& cost[v][k] + cost[k][u] < cost[v][u])
				{
					cost[v][u] = cost[v][k] + cost[k][u];
					path[v][u] = path[k][u];
				}
			}

			// if diagonal elements become negative, the
			// graph contains a negative-weight cycle
			if (cost[v][v] < 0)
			{
				cout << "Negative-weight cycle found!!";
				return;
			}
		}
	}

	// Print the shortest path between all pairs of vertices
	printSolution(cost, path);
}

int main()
{
	// given adjacency representation of the matrix
	int adjMatrix[N][N] =
	{
		{ 0, I, -2, I },
		{ 4, 0, 3, I },
		{ I, I, 0, 2 },
		{ I, -1, I, 0 }
	};

	// Run Floyd–Warshall algorithm
	floydWarshall(adjMatrix);

	return 0;
}