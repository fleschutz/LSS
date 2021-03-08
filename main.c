#include <omp.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define BigInt int64_t // or __int128_t 
#define MAX_RESULTS 1000 // print only results between 0...1000
#define MAX_ROUNDS 1000000 
static uint32_t numSolutions[MAX_RESULTS];

static void printNoSolutions()
{
#pragma omp parallel for
	for (BigInt n = 0; n < MAX_RESULTS; ++n)
		switch (n % 9)
		{
		case 4: 
		case 5: 
			printf("%ld = no solution exist\n", (int64_t)n);
			break;
		default:
			break;
		}
}

static BigInt cubeNumbers[MAX_ROUNDS]; 
static void preCalculateCubeNumbers() // for performance
{
#pragma omp parallel for
	for (BigInt i = 0; i < MAX_ROUNDS; ++i)
		cubeNumbers[i] = i * i * i;
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
		return; // a solution for <n> already exits

	// print formatted to be: x <= y <= z
	if (x <= y && y <= z)
		printf("%ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)x, (int64_t)y, (int64_t)z);
	else if (x <= z && z <= y)
		printf("%ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)x, (int64_t)z, (int64_t)y);
	else if (y <= x && x <= z)
		printf("%ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)y, (int64_t)x, (int64_t)z);
	else if (y <= z && z <= x)
		printf("%ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)y, (int64_t)z, (int64_t)x);
	else if (z <= x && x <= y)
		printf("%ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)z, (int64_t)x, (int64_t)y);
	else
		printf("%ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)z, (int64_t)y, (int64_t)x);

	fflush(stdout); // to disable buffering
}

static void printSolutionsByBruteForce(BigInt beginOfSearch, BigInt endOfSearch)
{
#pragma omp parallel for
	for (BigInt x = beginOfSearch; x < endOfSearch; ++x)
	{
		BigInt *x3Ptr = &cubeNumbers[x];
		for (BigInt y = 0, *y3Ptr = &cubeNumbers[0]; y <= x; ++y, ++y3Ptr)
		{
			for (BigInt z = 0, *z3Ptr = &cubeNumbers[0]; z <= y; ++z, ++z3Ptr)
			{
			       	register BigInt n = *x3Ptr + *y3Ptr + *z3Ptr;
				if (n < MAX_RESULTS)
					printSolution(n, x, y, z);

				n = -*x3Ptr + *y3Ptr + *z3Ptr;
				if (-MAX_RESULTS < n && n < MAX_RESULTS)
					printSolution(n, -x, y, z);

				n = *x3Ptr - *y3Ptr + *z3Ptr;
				if (-MAX_RESULTS < n && n < MAX_RESULTS)
					printSolution(n, x, -y, z);

				n = *x3Ptr + *y3Ptr - *z3Ptr;
				if (-MAX_RESULTS < n && n < MAX_RESULTS)
					printSolution(n, x, y, -z);

				n = *x3Ptr - *y3Ptr - *z3Ptr;
				if (-MAX_RESULTS < n && n < MAX_RESULTS)
					printSolution(n, x, -y, -z);
			}
		}
	}
}

static void printSolutionsByBinarySearch(BigInt beginOfSearch, BigInt endOfSearch)
{
#pragma omp parallel for
	for (BigInt x = beginOfSearch; x < endOfSearch; ++x)
	{
		BigInt *x3Ptr = &cubeNumbers[x];
		for (BigInt y = 0, *y3Ptr = &cubeNumbers[0]; y <= x; ++y, ++y3Ptr)
		{
			// Binary search for: x³ - y³ - z³
			BigInt min = 0, max = x; 
			do
			{
				const BigInt z = (min + max) / (BigInt)2;
				const BigInt n = *x3Ptr - *y3Ptr - cubeNumbers[z];

				if (n >= MAX_RESULTS)
					max = z - 1;
				else if (n <= -MAX_RESULTS)
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
				const BigInt n = *x3Ptr - *y3Ptr + cubeNumbers[z];

				if (n >= MAX_RESULTS)
					max = z - 1;
				else if (n <= -MAX_RESULTS)
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
				const BigInt n = -*x3Ptr + *y3Ptr + cubeNumbers[z];

				if (n >= MAX_RESULTS)
					max = z - 1;
				else if (n <= -MAX_RESULTS)
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
	printf("# List of simple solutions of n = x³ + y³ + z³  (for n < %d and x,y,z < %d, solutions formatted to be: x <= y <= z)\n", MAX_RESULTS, MAX_ROUNDS);

	printNoSolutions();

	preCalculateCubeNumbers();

	// printSolutionsByBruteForce(0, 5000);

	printSolutionsByBinarySearch(0/*5000*/, MAX_ROUNDS);

	return 0;
}
