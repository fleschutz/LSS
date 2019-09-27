#include <inttypes.h>
#include <stdio.h>

#define BigInt int64_t
#define MAX_ROUNDS 100000
#define MAX_RESULTS 100000
BigInt cubeNumbers[MAX_ROUNDS];
unsigned char gotResult[MAX_RESULTS];

#define wanted(n) (n < MAX_RESULTS && !gotResult[n])

static void printAndRemember(BigInt x, BigInt y, BigInt z, BigInt n)
{
	// print sorted by size: (low to high)
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

	// remember this:
	gotResult[n] = 1;
}

int main()
{
	printf("# List of simple solutions of x³ + y³ + z³ = n  (for n < %d and x,y,z < %d)\n", MAX_RESULTS, MAX_ROUNDS);

	// pre-calculate cube numbers for performance:
	for (BigInt i = 0; i < MAX_ROUNDS; ++i)
		cubeNumbers[i] = i * i * i;

	// iterate:
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
				if (wanted(n))
					printAndRemember(x, y, z, n);

				n = -x3 + y3 + z3;
				if (n >= 0)
				{
					if (wanted(n))
						printAndRemember(-x, y, z, n);
				}
				else if (wanted(-n))
					printAndRemember(x, -y, -z, -n);

				n = x3 - y3 + z3;
				if (n >= 0)
				{
					if (wanted(n))
						printAndRemember(x, -y, z, n);
				}
				else if (wanted(-n))
					printAndRemember(-x, y, -z, -n);

				n = x3 + y3 - z3;
				if (n >= 0)
				{
					if (wanted(n))
						printAndRemember(x, y, -z, n);
				}
				else if (wanted(-n))
					printAndRemember(-x, -y, z, -n);
			}
		}
	}
	return 0;
}
