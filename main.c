#include <omp.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef int64_t  BigInt; // or use __int128_t instead
#define N_MIN          0 // minimum value for n
#define N_MAX     100000 // maximum value for n
#define XYZ_MIN        0 // minimum value for x,y,z
#define XYZ_MAX   100000 // maximum value for x,y,z

// pre-calculate the cube numbers for performance
static BigInt cubeNumbers[XYZ_MAX + 2]; 
static void calculateCubeNumbers(void) 
{
	for (BigInt x = XYZ_MIN; x <= XYZ_MAX; ++x)
		cubeNumbers[x] = x * x * x;
}

// print and remember the given solution (formatted to be: x <= y <= z)
static int solutionKnown[N_MAX + 1] = { 0 };
static void printSolution(BigInt n, BigInt x, BigInt y, BigInt z)
{
	if (n < 0)
	{	n = -n;
		x = -x;
		y = -y;
		z = -z;
	}
	
	if (x <= y && y <= z)
		printf("%4ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)x, (int64_t)y, (int64_t)z);
	else if (x <= z && z <= y)
		printf("%4ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)x, (int64_t)z, (int64_t)y);
	else if (y <= x && x <= z)
		printf("%4ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)y, (int64_t)x, (int64_t)z);
	else if (y <= z && z <= x)
		printf("%4ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)y, (int64_t)z, (int64_t)x);
	else if (z <= x && x <= y)
		printf("%4ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)z, (int64_t)x, (int64_t)y);
	else
		printf("%4ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)z, (int64_t)y, (int64_t)x);
	fflush(stdout); // to disable buffering

	solutionKnown[n] = 1;
}

static void printNoSolutions(void)
{
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

static void printAdditionSolutionsUsingBruteForce(void)
{
	for (BigInt x = XYZ_MIN, x3 = cubeNumbers[XYZ_MIN]; x <= XYZ_MAX; x3 = cubeNumbers[++x])
	{
		if (x3 > N_MAX)
			break; // outside range of interest 
		for (BigInt y = XYZ_MIN, y3 = cubeNumbers[XYZ_MIN]; y <= XYZ_MAX; y3 = cubeNumbers[++y])
		{
			BigInt x3y3 = x3 + y3;
			if (x3y3 > N_MAX)
				break; // outside range of interest 
			for (BigInt z = XYZ_MIN, z3 = cubeNumbers[XYZ_MIN]; z <= XYZ_MAX; z3 = cubeNumbers[++z])
			{
				BigInt n = x3y3 + z3;
				if (n > N_MAX)
				       break; // outside range of interest 
				if (!solutionKnown[n])
					printSolution(n, x, y, z);
			}
		}
	}
}

static void printRestSolutionsUsingBruteForce(void)
{
	for (BigInt x = XYZ_MIN, x3 = cubeNumbers[XYZ_MIN]; x <= XYZ_MAX; x3 = cubeNumbers[++x])
	{
#pragma omp parallel for
		for (BigInt y = XYZ_MIN; y <= XYZ_MAX; ++y)
		{
			BigInt y3 = cubeNumbers[y];
			for (BigInt z = XYZ_MIN, z3 = cubeNumbers[XYZ_MIN]; z <= XYZ_MAX; z3 = cubeNumbers[++z])
			{
				BigInt n = -x3 + y3 + z3;
				if (-N_MAX < n && n < N_MAX && !solutionKnown[abs(n)])
					printSolution(n, -x, y, z);

				n = x3 - y3 + z3;
				if (-N_MAX < n && n < N_MAX && !solutionKnown[abs(n)])
					printSolution(n, x, -y, z);

				n = x3 + y3 - z3;
				if (-N_MAX < n && n < N_MAX && !solutionKnown[abs(n)])
					printSolution(n, x, y, -z);

				n = x3 - y3 - z3;
				if (-N_MAX < n && n < N_MAX && !solutionKnown[abs(n)])
					printSolution(n, x, y, -z);
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
	printf("# List of simple solutions of n = x³ + y³ + z³  (for n < %ld and x,y,z < %ld, solutions formatted to be: x <= y <= z)\n", (int64_t)N_MAX, (int64_t)XYZ_MAX);

	printNoSolutions();

	calculateCubeNumbers();

	printAdditionSolutionsUsingBruteForce();

	printRestSolutionsUsingBruteForce();

	//printSolutionsUsingBinarySearch(0/*5000*/, XYZ_MAX);

	return 0;
}
