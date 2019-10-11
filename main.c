#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define BigInt int64_t
#define MAX_RESULTS 1000
#define MAX_ROUNDS 100000 // must be bigger than MAX_RESULTS
BigInt cubeNumbers[MAX_ROUNDS]; // pre-calculated
uint32_t numSolutions[MAX_RESULTS];

#define isInSearchRange(n) (n < MAX_RESULTS && n > -MAX_RESULTS)

static void printSolution(BigInt n, BigInt x, BigInt y, BigInt z)
{
	if (n < 0)
	{	n = -n;
		x = -x;
		y = -y;
		z = -z;
	}

	// check if solution is unknown yet
	if (numSolutions[n]++)
		return;

	// print sorted by size: (from low to high)
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

static int hasNoSolution(const BigInt n)
{
	switch (n % 9)
	{
	case 4: 
	case 5: 
		return 1;
	default:
		return 0;
	}
}

int main()
{
	printf("# List of simple solutions of x³ + y³ + z³ = n  (for n < %d and x,y,z < %d)\n", MAX_RESULTS, MAX_ROUNDS);

	// pre-calculate cube numbers:
	for (BigInt i = 0; i < MAX_ROUNDS; ++i)
		cubeNumbers[i] = i * i * i;

	// print the no solutions:
	for (BigInt n = 0; n < MAX_RESULTS; ++n)
		if (hasNoSolution(n))
			printf("%ld = no solution\n", n);

	// iterate slow:
	for (BigInt x = 0; x < MAX_RESULTS; ++x)
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

	// iterate fast:
	for (BigInt x = MAX_RESULTS; x < MAX_ROUNDS; ++x)
	{
		const BigInt x3 = cubeNumbers[x];

		for (BigInt y = 0; y <= x; ++y)
		{
			const BigInt y3 = cubeNumbers[y], x3_minus_y3 = x3 - y3;

			for (BigInt z = 0; z <= y; ++z)
			{
				const BigInt z3 = cubeNumbers[z];

			       	const BigInt n = x3_minus_y3 - z3;
				if (n >= MAX_RESULTS)
					continue; // z is still too small
				if (n <= -MAX_RESULTS)
					break; // z is already too big
				printSolution(n, x, -y, -z);
			}
		}
	}
	return 0;
}
