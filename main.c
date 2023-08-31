#include <omp.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int64_t        BigInt; // or use __int128_t instead
#define N_MIN               0  // minimum desired value for n
#define N_MAX            1000  // maximum desired value for n
#define XYZ_MIN             0  // minimum value for x,y,z to use
#define XYZ_MAX        100000  // maximum value for x,y,z to use
#define CSV_OUTPUT          0  // CSV output desired, else text output

// Converts the given string into a big number and returns it.
static BigInt string2BigInt(const char *str)
{
	BigInt sign = 1, value = 0;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	size_t len = strlen(str);
	for (size_t i = 0; i < len; i++)
		value = (value * 10) + (str[i] - '0');
	return sign * value;
}

// Provide pre-calculated cube numbers for performance: (afterward, use cubeNumbers[3] instead of: 3*3*3)
static BigInt cubeNumbers[XYZ_MAX + 1];
static void preCalculateCubeNumbers(void) 
{
	for (BigInt x = XYZ_MIN; x <= XYZ_MAX; ++x)
		cubeNumbers[x] = x * x * x;
}

// Print and remember a single solution (formatted to be: x <= y <= z):
static int solutionKnown[N_MAX + 1] = { 0 }; 
static void printNoSolution(BigInt n)
{
#if CSV_OUTPUT
	printf("%5ld, , , ,\n", (int64_t)n);
#else
	printf("%5ld = no solution\n", (int64_t)n);
#endif
	fflush(stdout); // to disable buffering
	solutionKnown[n] = 1;
}
static void printSolution(BigInt n, BigInt x, BigInt y, BigInt z)
{
	if (n < 0)
	{	n = -n;
		x = -x;
		y = -y;
		z = -z;
	}
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
	solutionKnown[n] = 1;
}

static void listNoSolutions(void)
{
	for (BigInt n = N_MIN; n <= N_MAX; ++n)
		if ((n % 9) == 4 || (n % 9) == 5)
			printNoSolution(n);
}

static void listSolutionsForPositiveXYZ(void)
{
	for (BigInt x = XYZ_MIN; x <= XYZ_MAX; ++x)
	{
		BigInt x3 = cubeNumbers[x];
		if (x3 > N_MAX)
			break; // x³ too big already
		for (BigInt y = XYZ_MIN; y <= x; ++y)
		{
			BigInt y3 = cubeNumbers[y], x3_plus_y3 = x3 + y3;
			if (x3_plus_y3 > N_MAX)
				break; // x³ + y³ too big already
			for (BigInt z = XYZ_MIN; z <= y; ++z)
			{
				BigInt z3 = cubeNumbers[z], n = x3_plus_y3 + z3;
				if (n > N_MAX)
				       break; // x³ + y³ + z³ too big already
				if (!solutionKnown[n])
					printSolution(n, x, y, z);
			}
		}
	}
}

static void listSolutionsForNegativeXYZ(void)
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
				if (-N_MAX <= n && n <= N_MAX)
					if (!solutionKnown[abs(n)])
						printSolution(n, x, -y, z);
				n = x3_minus_y3 - cubeNumbers[z];
				if (-N_MAX <= n && n <= N_MAX)
					if (!solutionKnown[abs(n)])
						printSolution(n, x, -y, -z);
			}
		}
	}
}

static void listNontrivialSolutions(BigInt startX)
{
	for (BigInt x = startX; ; ++x)
	{
		BigInt x3 = x * x * x, z = 1, z3 = 1 * 1 * 1;
#pragma omp parallel for
		for (BigInt y = x - 1; y > 0; --y)
		{
			BigInt y3 = y * y * y;

			BigInt n = x3 - y3 - z3;
			while (n > N_MAX)
			{
				++z;
				z3 = z * z * z;
				n = x3 - y3 - z3;
			}
			if (n >= -N_MAX && n != -2)
				printSolution(n, x, -y, -z);
		}
	}
}

int main(int argc, char **argv)
{
	int mode = 2; // print no solutions by default
	if (argc >= 2)
		mode = atoi(argv[1]);
	
	if (mode == 1)
	{
		if (argc == 5)
		{
			BigInt x = string2BigInt(argv[2]);
			BigInt y = string2BigInt(argv[3]);
			BigInt z = string2BigInt(argv[4]);
			BigInt n = (x * x * x) + (y * y * y) + (z * z * z);
			printf("%ld³ + %ld³ + %ld³ = %ld\n", (int64_t)x, (int64_t)y, (int64_t)z, (int64_t)n);
		}
		else
			printf("Sorry, expected syntax is: ./a.out 5 <x> <y> <z>\n");
	}
	else if (mode == 2) 
	{
#if CSV_OUTPUT
		printf("    n, x, y, z,\n");
#else
		printf("# No solutions of n=x³+y³+z³ (for n = [%ld..%ld]\n", (int64_t)N_MIN, (int64_t)N_MAX);
#endif
		listNoSolutions();
	}
	else if (mode == 3)
	{
#if CSV_OUTPUT
		printf("    n, x, y, z,\n");
#else
		printf("# Trivial solutions of n=x³+y³+z³ for positive numbers of x,y,z (for n = [%ld..%ld] and x,y,z = [%ld..%ld], solutions formatted to be: x <= y <= z)\n", (int64_t)N_MIN, (int64_t)N_MAX, (int64_t)XYZ_MIN, (int64_t)XYZ_MAX);
#endif
		preCalculateCubeNumbers();
		listSolutionsForPositiveXYZ();
	}
	else if (mode == 4)
	{
#if CSV_OUTPUT
		printf("    n, x, y, z,\n");
#else
		printf("# Trivial solutions of n=x³+y³+z³ for negative numbers of x,y,z (for n = [%ld..%ld] and x,y,z = [%ld..%ld], solutions formatted to be: x <= y <= z)\n", (int64_t)N_MIN, (int64_t)N_MAX, (int64_t)XYZ_MIN, (int64_t)XYZ_MAX);
#endif
		preCalculateCubeNumbers();
		listSolutionsForNegativeXYZ();
	}
	else if (mode == 5) 
	{
#if CSV_OUTPUT
		printf("    n, x, y, z,\n");
#else
		printf("# Trivial solutions of n=x³+y³+z³  (for n = [%ld..%ld] and x,y,z = [%ld..%ld], solutions formatted to be: x <= y <= z)\n", (int64_t)N_MIN, (int64_t)N_MAX, (int64_t)XYZ_MIN, (int64_t)XYZ_MAX);
#endif
		listNoSolutions();
		preCalculateCubeNumbers();
		listSolutionsForPositiveXYZ();
		listSolutionsForNegativeXYZ();
	}
	else if (mode == 6) 
	{
		BigInt startX = (argc == 3) ? string2BigInt(argv[2]) : 99999999;
#if CSV_OUTPUT
		printf("    n, x, y, z,\n");
#else
		printf("# Nontrivial solutions of n=x³+y³+z³ (x=%ld as starting point, solutions formatted to be: x <= y <= z)\n", (int64_t)startX);
#endif
		listNontrivialSolutions(startX);
	}
	return 0;
}
