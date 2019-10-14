#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define BigInt int64_t
#define MAX_RESULTS 1000
#define MAX_ROUNDS 100000 // must be bigger than MAX_RESULTS
BigInt cubeNumbers[MAX_ROUNDS]; // pre-calculated
uint32_t numSolutions[MAX_RESULTS];

#define isInSearchRange(n) (n < MAX_RESULTS && n > -MAX_RESULTS)

void printNoSolutions()
{
	for (BigInt n = 0; n < MAX_RESULTS; ++n)
	{
		switch (n % 9)
		{
		case 4: 
		case 5: 
			printf("%ld = no solution\n", n);
			break;
		default:
			break;
		}
	}
}

void printSolution(BigInt n, BigInt x, BigInt y, BigInt z)
{
	if (n < 0)
	{	n = -n;
		x = -x;
		y = -y;
		z = -z;
	}

	if (numSolutions[n]++)
		return; // a solution for <n> already exits

	// print x/y/z sorted by size: (x <= y <= z)
	if (x <= y && y <= z)
		printf("%ld = %ld³ + %ld³ + %ld³\n", n, x, y, z);
	else if (x <= z && z <= y)
		printf("%ld = %ld³ + %ld³ + %ld³\n", n, x, z, y);
	else if (y <= x && x <= z)
		printf("%ld = %ld³ + %ld³ + %ld³\n", n, y, x, z);
	else if (y <= z && z <= x)
		printf("%ld = %ld³ + %ld³ + %ld³\n", n, y, z, x);
	else if (z <= x && x <= y)
		printf("%ld = %ld³ + %ld³ + %ld³\n", n, z, x, y);
	else
		printf("%ld = %ld³ + %ld³ + %ld³\n", n, z, y, x);
}

void printSolutionsByBruteForce() // slow
{
	for (BigInt x = 0; x < MAX_ROUNDS; ++x)
	{
		const BigInt x3 = cubeNumbers[x];

		for (BigInt y = 0; y <= x; ++y)
		{
			const BigInt y3 = cubeNumbers[y];

			for (BigInt z = 0; z <= y; ++z)
			{
				const BigInt z3 = cubeNumbers[z];

			       	register BigInt n = x3 + y3 + z3;
				if (isInSearchRange(n))
					printSolution(n, x, y, z);

				n = -x3 + y3 + z3;
				if (isInSearchRange(n))
					printSolution(n, -x, y, z);

				n = x3 - y3 + z3;
				if (isInSearchRange(n))
					printSolution(n, x, -y, z);

				n = x3 + y3 - z3;
				if (isInSearchRange(n))
					printSolution(n, x, y, -z);

				n = x3 - y3 - z3;
				if (isInSearchRange(n))
					printSolution(n, x, -y, -z);
			}
		}
	}
}

void printSolutionsByBinSearch()
{
	for (BigInt x = 0; x < MAX_ROUNDS; ++x)
	{
		for (BigInt y = 0; y <= x; ++y)
		{
			const BigInt x3_minus_y3 = cubeNumbers[x] - cubeNumbers[y];

			BigInt min = 0, max = y; // binary search
			do
			{
				const BigInt z = (min + max) / 2;
				const BigInt n = x3_minus_y3 - cubeNumbers[z];

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
		}
	}
}

int main()
{
	printf("# List of simple solutions of n = x³ + y³ + z³  (for n < %d and x,y,z < %d, solutions formatted to be: x <= y <= z)\n", MAX_RESULTS, MAX_ROUNDS);

	// pre-calculate cube numbers:
	for (BigInt i = 0; i < MAX_ROUNDS; ++i)
		cubeNumbers[i] = i * i * i;

	printNoSolutions();

	printSolutionsByBruteForce();

	// printSolutionsByBinSearch();

	return 0;
}
