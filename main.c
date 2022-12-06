#include <omp.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define BigInt    int64_t  // or __int128_t 
#define N_MIN           0  // minimum value for n
#define N_MAX        1000  // maximum value for n
#define XYZ_MIN         0  // minimum value for x,y,z
#define XYZ_MAX   1000000  // maximum value for x,y,z
			   //
static uint32_t numSolutions[N_MAX];
static BigInt cubeNumbers[XYZ_MAX + 1]; 

static void preCalculateCubeNumbers(void) // for performance
{
#pragma omp parallel for
	for (BigInt x = XYZ_MIN; x <= XYZ_MAX; ++x)
		cubeNumbers[x] = x * x * x;
}

static void printNoSolutions(void)
{
#pragma omp parallel for
	for (BigInt n = N_MIN; n <= N_MAX; ++n)
	{	switch (n % 9)
		{
		case 4: 
		case 5: 
			printf("%3ld = no solution\n", (int64_t)n);
			break;
		default:
			break;
		}
	}
}

static void printSolution(BigInt n, BigInt x, BigInt y, BigInt z)
{
	if (n < 0)
	{	n = -n;
		x = -x;
		y = -y;
		z = -z;
	}

	if (numSolutions[n]++)
		return; // a solution for <n> exists already

	// print solution: (formatted to be: x <= y <= z)
	if (x <= y && y <= z)
		printf("%3ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)x, (int64_t)y, (int64_t)z);
	else if (x <= z && z <= y)
		printf("%3ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)x, (int64_t)z, (int64_t)y);
	else if (y <= x && x <= z)
		printf("%3ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)y, (int64_t)x, (int64_t)z);
	else if (y <= z && z <= x)
		printf("%3ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)y, (int64_t)z, (int64_t)x);
	else if (z <= x && x <= y)
		printf("%3ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)z, (int64_t)x, (int64_t)y);
	else
		printf("%3ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)z, (int64_t)y, (int64_t)x);

	fflush(stdout); // to disable buffering
}

static void printSolutionsUsingBruteForce(void)
{
	for (BigInt x = XYZ_MIN; x <= XYZ_MAX; ++x)
	{
		const BigInt x3 = cubeNumbers[x];
#pragma omp parallel for
		for (BigInt y = XYZ_MIN; y <= x; ++y)
		{
			const BigInt y3 = cubeNumbers[y];
			for (BigInt z = XYZ_MIN; z <= y; ++z)
			{
				const BigInt z3 = cubeNumbers[z];
				BigInt n = x3 + y3 + z3;
				if (n < N_MAX)
					printSolution(n, x, y, z);

				n = -x3 + y3 + z3;
				if (-N_MAX < n && n < N_MAX)
					printSolution(n, -x, y, z);

				n = x3 - y3 + z3;
				if (-N_MAX < n && n < N_MAX)
					printSolution(n, x, -y, z);

				n = x3 + y3 - z3;
				if (-N_MAX < n && n < N_MAX)
					printSolution(n, x, y, -z);

				n = x3 - y3 - z3;
				if (-N_MAX < n && n < N_MAX)
					printSolution(n, x, -y, -z);
			}
		}
	}
}

static void printSolutionsUsingBinarySearch(BigInt beginOfSearch, BigInt endOfSearch)
{
#pragma omp parallel for
	for (BigInt x = beginOfSearch; x < endOfSearch; ++x)
	{
		BigInt x3 = cubeNumbers[x];
		for (BigInt y = XYZ_MIN; y <= x; ++y)
		{
			BigInt y3 = cubeNumbers[y];

			// Binary search for: x³ - y³ - z³
			BigInt min = 0, max = x; 
			do
			{
				const BigInt z = (min + max) / (BigInt)2;
				const BigInt n = x3 - y3 - cubeNumbers[z];

				if (n >= N_MAX)
					max = z - 1;
				else if (n <= -N_MAX)
					min = z + 1;
				else
				{
					printSolution(n, x, -y, -z);
					break;
				}
			} while (min <= max);
			
			// Binary search for: x³ - y³ + z³
			min = 0;
		       	max = x;
			do
			{
				const BigInt z = (min + max) / (BigInt)2;
				const BigInt n = x3 - y3 + cubeNumbers[z];

				if (n >= N_MAX)
					max = z - 1;
				else if (n <= -N_MAX)
					min = z + 1;
				else
				{
					printSolution(n, x, -y, z);
					break;
				}
			} while (min <= max);
			
			// Binary search for: -x³ + y³ + z³
			min = 0;
		       	max = x;
			do
			{
				const BigInt z = (min + max) / (BigInt)2;
				const BigInt n = -x3 + y3 + cubeNumbers[z];

				if (n >= N_MAX)
					max = z - 1;
				else if (n <= -N_MAX)
					min = z + 1;
				else
				{
					printSolution(n, -x, y, z);
					break;
				}
			} while (min <= max);
		}
	}
}

int main()
{
	printf("# List of simple solutions of n = x³ + y³ + z³  (for n < %d and x,y,z < %d, solutions formatted to be: x <= y <= z)\n", N_MAX, XYZ_MAX);

	printNoSolutions();

	preCalculateCubeNumbers();

	printSolutionsUsingBruteForce();

	//printSolutionsUsingBinarySearch(0/*5000*/, XYZ_MAX);

	return 0;
}
