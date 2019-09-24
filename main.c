#include <inttypes.h>
#include <stdio.h>

#define BigInt int64_t

#define MAXROUNDS 2000

static void solve(BigInt k)
{
	if ((k % 9) == 4)
	{
		printf("%ld = no solution\n", k);
		return;
	}
	for (BigInt x = 0; x < MAXROUNDS; ++x) {
		BigInt x3 = x * x * x;

		for (BigInt y = 0; y <= x; ++y) {
			BigInt y3 = y * y * y;

			for (BigInt z = 0; z <= y; ++z) {
				BigInt z3 = z * z * z;

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
	printf("List of simple solutions of x³ + y³ + z³ = k    for k < 1000\n");
	for (BigInt k = 0; k <= 1000; ++k) 
		solve(k);
	return 0;
}
