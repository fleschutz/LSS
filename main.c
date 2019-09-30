#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define BigInt int64_t
#define MAX_ROUNDS 100000
#define MAX_RESULTS 100000
BigInt cubeNumbers[MAX_ROUNDS];
uint32_t numSolutions[MAX_RESULTS];

#define wanted(n) (-MAX_RESULTS < n && n < MAX_RESULTS && numSolutions[labs(n)]++ == 0)

static void print(const BigInt x, const BigInt y, const BigInt z, const BigInt n)
{
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

	// pre-calculate cube numbers for performance:
	for (BigInt i = 0; i < MAX_ROUNDS; ++i)
		cubeNumbers[i] = i * i * i;

	for (BigInt n = 0; n < MAX_ROUNDS; ++n)
		if (hasNoSolution(n))
			printf("%ld = no solution\n", n);

	// iterate:
	for (BigInt x = 0; x < MAX_ROUNDS; ++x)
	{
		const BigInt x3 = cubeNumbers[x];

		for (BigInt y = 0; y <= x; ++y)
		{
			const BigInt y3 = cubeNumbers[y], x3y3 = x3 + y3;

			for (BigInt z = 0; z <= y; ++z)
			{
				const BigInt z3 = cubeNumbers[z];

			       	register BigInt n = x3y3 + z3;
				if (wanted(n))
					print(x, y, z, n);

				n = -x3 + y3 + z3;
				if (wanted(n))
				{
					if (n >= 0)
						print(-x, y, z, n);
					else
						print(x, -y, -z, -n);
				}

				n = x3 - y3 + z3;
				if (wanted(n))
				{
					if (n >= 0)
						print(x, -y, z, n);
					else
						print(-x, y, -z, -n);
				}

				n = x3y3 - z3;
				if (wanted(n))
				{
					if (n >= 0)
						print(x, y, -z, n);
					else
						print(-x, -y, z, -n);
				}
			}
		}
	}
	return 0;
}
