#include <inttypes.h>
#include <stdio.h>

#define BigInt int64_t

#define MAX_ROUNDS 1500
const BigInt MAX_RESULTS = 100000;
BigInt cubeNumbers[MAX_ROUNDS];


void solve(BigInt k)
{
	if ((k % 9) == 4)
	{
		printf("%ld = no solution\n", k);
		return;
	}
	for (BigInt x = 0; x < MAX_ROUNDS; ++x)
	{
		BigInt x3 = cubeNumbers[x];

		for (BigInt y = 0; y <= x; ++y)
		{
			BigInt y3 = cubeNumbers[y];

			for (BigInt z = 0; z <= y; ++z)
			{
				BigInt z3 = cubeNumbers[z];

				if (x3 + y3 + z3 == k) 
					printf("%ld = %ld³ + %ld³ + %ld³\n", k, x, y, z);
				else if (-x3 + y3 + z3 == k)
					printf("%ld = %ld³ + %ld³ + %ld³\n", k, -x, y, z);
				else if (x3 + -y3 + z3 == k)
					printf("%ld = %ld³ + %ld³ + %ld³\n", k, x, -y, z);
				else if (x3 + y3 + -z3 == k)
					printf("%ld = %ld³ + %ld³ + %ld³\n", k, x, y, -z);
				else if (-x3 + -y3 + z3 == k)
					printf("%ld = %ld³ + %ld³ + %ld³\n", k, -x, -y, z);
				else if (-x3 + y3 + -z3 == k)
					printf("%ld = %ld³ + %ld³ + %ld³\n", k, -x, y, -z);
				else if (x3 + -y3 + -z3 == k)
					printf("%ld = %ld³ + %ld³ + %ld³\n", k, x, -y, -z);
				// else if (-x3 + -y3 + -z3 == k)  (negative numbers will never produce positive nums)
				//	printf("%ld = %ld³ + %ld³ + %ld³\n", k, -x, -y, -z);
				else
					continue;
				return;
			}
		}
	}
	printf("%ld = no simple solution\n", k);
}

int main()
{
	printf("List of simple solutions of x³ + y³ + z³ = k    for k < %ld\n", MAX_RESULTS);

	// pre-calculate cube numbers for performance:
	for (BigInt i = 0; i < MAX_ROUNDS; ++i)
		cubeNumbers[i] = i * i * i;

	for (BigInt k = 0; k <= MAX_RESULTS; ++k) 
		solve(k);
	return 0;
}
