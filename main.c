#include <inttypes.h>
#include <stdio.h>

#define BigInt int64_t
#define MAX_ROUNDS 1000
#define MAX_RESULTS 100000
BigInt cubeNumbers[MAX_ROUNDS];
unsigned char gotResult[MAX_RESULTS];

#define wanted(k) (k < MAX_RESULTS && !gotResult[k])

static void print(BigInt x, BigInt y, BigInt z, BigInt k)
{
	if (x >= y && y >= z)
		printf("%ld = %ld³ + %ld³ + %ld³\n", k, x, y, z);
	else if (x >= z && z >= y)
		printf("%ld = %ld³ + %ld³ + %ld³\n", k, x, z, y);
	else if (y >= x && x >= z)
		printf("%ld = %ld³ + %ld³ + %ld³\n", k, y, x, z);
	else if (y >= z && z >= x)
		printf("%ld = %ld³ + %ld³ + %ld³\n", k, y, z, x);
	else if (z >= x && x >= y)
		printf("%ld = %ld³ + %ld³ + %ld³\n", k, z, x, y);
	else
		printf("%ld = %ld³ + %ld³ + %ld³\n", k, z, y, x);
	gotResult[k] = 1;
}

int main()
{
	printf("# List of simple solutions of x³ + y³ + z³ = k  (for k < %d, search band < %d)\n", MAX_RESULTS, MAX_ROUNDS);

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

			       	BigInt k = x3 + y3 + z3;
				if (k >= 0)
				{	
					if (wanted(k))
						print(x, y, z, k);
				}
				else if (wanted(-k))
					print(-x, -y, -z, -k);

				k = -x3 + y3 + z3;
				if (k >= 0)
				{
					if (wanted(k))
						print(-x, y, z, k);
				}
				else if (wanted(-k))
					print(x, -y, -z, -k);

				k = x3 - y3 + z3;
				if (k >= 0)
				{
					if (wanted(k))
						print(x, -y, z, k);
				}
				else if (wanted(-k))
					print(-x, y, -z, -k);

				k = x3 + y3 - z3;
				if (k >= 0)
				{
					if (wanted(k))
						print(x, y, -z, k);
				}
				else if (wanted(-k))
					print(-x, -y, z, -k);

			}
		}
	}
	return 0;
}
