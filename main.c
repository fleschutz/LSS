#include <omp.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef __int128_t     BigInt;
#define N_MIN               0  // minimum desired value for n
#define N_MAX            1000  // maximum desired value for n
#define XYZ_MIN             0  // minimum value for x,y,z to use
#define XYZ_MAX        100000  // maximum value for x,y,z to use
#define CSV_OUTPUT          0  // CSV output desired, else text output

// Returns the given string as BigInt.
BigInt getBigIntFromString(const char *str)
{
	BigInt sign = 1, value = 0;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
	{
		sign = 1;
		str++;
	}
	for (size_t i = 0; i < strlen(str); ++i)
		value = (value * 10) + (str[i] - '0');
	return sign * value;
}

// Returns the given 10^exponent number as BigInt.
BigInt getBigIntFromPowerOf10(int exponent)
{
	BigInt result = 1;
	for (int i = 0; i < exponent; ++i)
		result *= (BigInt)10;
	return result;
}

// Prints the given number on the console.
void printBigInt(BigInt n)
{
	char buf[80] = {};
	char *s = buf + sizeof(buf) - 1;  // start at the end
	int neg = (n < 0);
	if (neg)
		n = -n;
	do
	{
		*--s = "0123456789"[n % 10];    // save last digit
		n /= 10;                // drop it
	} while (n);
 	if (neg)
 		*--s = '-';
	printf("%s", s);
}

// Provide pre-calculated cube numbers for performance: (afterward, use cubeNumbers[3] instead of: 3*3*3)
BigInt cubeNumbers[XYZ_MAX + 1];
void preCalculateCubeNumbers(void) 
{
	for (BigInt x = XYZ_MIN; x <= XYZ_MAX; ++x)
		cubeNumbers[x] = x * x * x;
}

// Print and remember a single solution (formatted to be: x <= y <= z):
int solutionKnown[N_MAX + 1] = { 0 }; 
void printNoSolution(BigInt n)
{
#if CSV_OUTPUT
	printf("%5ld, , , ,\n", (int64_t)n);
#else
	printf("%5ld = no solution\n", (int64_t)n);
#endif
}
void printSolution(BigInt n, BigInt x, BigInt y, BigInt z)
{
	solutionKnown[n] = 1;
#if CSV_OUTPUT	
	if (x <= y && y <= z)
		printf("%5ld, %ld, %ld, %ld,\n", (int64_t)n, (int64_t)x, (int64_t)y, (int64_t)z);
	else if (x <= z && z <= y)
		printf("%5ld, %ld, %ld, %ld,\n", (int64_t)n, (int64_t)x, (int64_t)z, (int64_t)y);
	else if (y <= x && x <= z)
		printf("%5ld, %ld, %ld, %ld,\n", (int64_t)n, (int64_t)y, (int64_t)x, (int64_t)z);
	else if (y <= z && z <= x)
		printf("%5ld, %ld, %ld, %ld,\n", (int64_t)n, (int64_t)y, (int64_t)z, (int64_t)x);
	else if (z <= x && x <= y)
		printf("%5ld, %ld, %ld, %ld,\n", (int64_t)n, (int64_t)z, (int64_t)x, (int64_t)y);
	else
		printf("%5ld, %ld, %ld, %ld,\n", (int64_t)n, (int64_t)z, (int64_t)y, (int64_t)x);
#else
	if (x <= y && y <= z)
		printf("%5ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)x, (int64_t)y, (int64_t)z);
	else if (x <= z && z <= y)
		printf("%5ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)x, (int64_t)z, (int64_t)y);
	else if (y <= x && x <= z)
		printf("%5ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)y, (int64_t)x, (int64_t)z);
	else if (y <= z && z <= x)
		printf("%5ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)y, (int64_t)z, (int64_t)x);
	else if (z <= x && x <= y)
		printf("%5ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)z, (int64_t)x, (int64_t)y);
	else
		printf("%5ld = %ld³ + %ld³ + %ld³\n", (int64_t)n, (int64_t)z, (int64_t)y, (int64_t)x);
#endif
	fflush(stdout); // to disable buffering
}

void listNoSolutions(void)
{
	for (BigInt n = N_MIN; n <= N_MAX; ++n)
		if ((n % 9) == 4 || (n % 9) == 5)
			printNoSolution(n);
}

void listTrivialSolutionsForPositiveXYZ(void)
{
	for (BigInt x = XYZ_MIN; x <= XYZ_MAX; ++x)
	{
		BigInt x3 = cubeNumbers[x];
		if (x3 > N_MAX)
			break; // x³ is too big already
		for (BigInt y = XYZ_MIN; y <= x; ++y)
		{
			BigInt y3 = cubeNumbers[y], x3_plus_y3 = x3 + y3;
			if (x3_plus_y3 > N_MAX)
				break; // x³ + y³ is too big already
			for (BigInt z = XYZ_MIN; z <= y; ++z)
			{
				BigInt z3 = cubeNumbers[z], n = x3_plus_y3 + z3;
				if (n > N_MAX)
				       break; // x³ + y³ + z³ is too big already
				if (!solutionKnown[n])
					printSolution(n, x, y, z);
			}
		}
	}
}

void listTrivialSolutionsForNegativeXYZ(void)
{
	for (BigInt x = XYZ_MIN; x <= XYZ_MAX; ++x)
	{
		BigInt x3 = cubeNumbers[x];
		for (BigInt y = XYZ_MIN; y <= x; ++y)
		{
			BigInt x3_minus_y3 = x3 - cubeNumbers[y];
#pragma omp parallel for
			for (BigInt z = XYZ_MIN; z <= y; ++z)
			{
				BigInt n = x3_minus_y3 + cubeNumbers[z];
				if (N_MIN <= n && n <= N_MAX && !solutionKnown[n])
					printSolution(n, x, -y, z);

				n = x3_minus_y3 - cubeNumbers[z];
				if (N_MIN <= n && n <= N_MAX && !solutionKnown[n])
					printSolution(n, x, -y, -z);
			}
		}
	}
}

void listSolutionsForNegativeYZ(BigInt x_min, BigInt x_max)
{
#pragma omp parallel for
	for (BigInt x = x_min; x <= x_max; ++x)
	{
		BigInt x3 = x*x*x, z = 1, z3 = 1*1*1;

		for (BigInt y = x - 1; y >= z; --y)
		{
			BigInt y3 = y*y*y, n = x3 - y3 - z3;

			while (n > N_MAX)
			{
				++z;
				n += z3; // to remove previous z³
				z3 = z * z * z;
				n -= z3; // to add new z³
			}
			if (n >= N_MIN)
				printSolution(n, x, -y, -z);
		}
	}
}

int main(int argc, char **argv)
{
	int mode = (argc >= 2) ? atoi(argv[1]) : 2; // list no solutions when no arguments given
	
	if (mode == 1)
	{
		if (argc != 5)
		{
			printf("Sorry, expected syntax is: ./mode 1 <x> <y> <z>\n");
			return 1; 
		}
		BigInt x = getBigIntFromString(argv[2]);
		BigInt y = getBigIntFromString(argv[3]);
		BigInt z = getBigIntFromString(argv[4]);
		BigInt n = (x * x * x) + (y * y * y) + (z * z * z);
		printBigInt(x);
		printf("³ + ");
		printBigInt(y);
		printf("³ + ");
		printBigInt(z);
		printf("³ = ");
		printBigInt(n);
		printf("\n");
	}
	else if (mode == 2) 
	{
#if CSV_OUTPUT
		printf("    n, x, y, z,\n");
#else
		printf("# No solutions of n=x³+y³+z³ for n=[%ld..%ld]\n", (int64_t)N_MIN, (int64_t)N_MAX);
#endif
		listNoSolutions();
	}
	else if (mode == 3)
	{
#if CSV_OUTPUT
		printf("    n, x, y, z,\n");
#else
		printf("# Trivial solutions of n=x³+y³+z³ for n=[%ld..%ld] and x,y,z=[%ld..%ld] (formatted to be: x <= y <= z)\n", (int64_t)N_MIN, (int64_t)N_MAX, (int64_t)XYZ_MIN, (int64_t)XYZ_MAX);
#endif
		preCalculateCubeNumbers();
		listTrivialSolutionsForPositiveXYZ();
	}
	else if (mode == 4)
	{
#if CSV_OUTPUT
		printf("    n, x, y, z,\n");
#else
		printf("# Trivial solutions of n=x³+y³+z³ for negative numbers of x,y,z (for n=[%ld..%ld] and x,y,z=[%ld..%ld], solutions formatted to be: x <= y <= z)\n", (int64_t)N_MIN, (int64_t)N_MAX, (int64_t)XYZ_MIN, (int64_t)XYZ_MAX);
#endif
		preCalculateCubeNumbers();
		listTrivialSolutionsForNegativeXYZ();
	}
	else if (mode == 5) 
	{
#if CSV_OUTPUT
		printf("    n, x, y, z,\n");
#else
		printf("# Trivial solutions of n=x³+y³+z³  for n=[%ld..%ld] and x,y,z=[%ld..%ld], solutions formatted to be: x <= y <= z)\n", (int64_t)N_MIN, (int64_t)N_MAX, (int64_t)XYZ_MIN, (int64_t)XYZ_MAX);
#endif
		listNoSolutions();
		preCalculateCubeNumbers();
		listTrivialSolutionsForPositiveXYZ();
		listTrivialSolutionsForNegativeXYZ();
	}
	else if (mode == 6) 
	{
		int exponent = (argc == 3 ? atoi(argv[2]) : 6);
#if CSV_OUTPUT
		printf("    n, x, y, z,\n");
#else
		printf("# Solutions of n=x³+y³+z³ for n=[%ld..%ld] and x=[10^%d..10^%d] (formatted to be: x <= y <= z)\n", (int64_t)N_MIN, (int64_t)N_MAX, exponent, exponent + 1);
#endif
		listSolutionsForNegativeYZ(getBigIntFromPowerOf10(exponent), getBigIntFromPowerOf10(exponent + 1));
	}
	return 0;
}
