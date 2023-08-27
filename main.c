#include <omp.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

typedef int64_t        BigInt; // or use __int128_t instead
#define N_MIN               0  // minimum value for n
#define N_MAX            1000  // maximum value for n
#define XYZ_MIN             0  // minimum value for x,y,z
#define XYZ_MAX       1000000  // maximum value for x,y,z
#define CSV_OUTPUT          1  // CSV output, else text output

static void printNoSolutions(void)
{
	for (BigInt n = N_MIN; n <= N_MAX; ++n)
	{
		if ((n % 9) == 4 || (n % 9) == 5)
		{
#if CSV_OUTPUT
			printf("%5ld, , , \n", (int64_t)n);
#else
			printf("%5ld = no solution\n", (int64_t)n);
#endif
		}
	}
}

static BigInt cubeNumbers[XYZ_MAX + 1]; // pre-calculate for performance
static void calculateCubeNumbers(void) 
{
	for (BigInt x = XYZ_MIN; x <= XYZ_MAX; ++x)
		cubeNumbers[x] = x * x * x;
}

static int solutionKnown[N_MAX + 1] = { 0 }; 
static void setNontrivialSolutionsAsUnknown(void)
{
	for (BigInt n = N_MIN; n <= N_MAX; ++n)
		switch (n)
		{
		case  30:
		case  33:
		case  42:
		case  52:
		case  74:
		case 114:
		case 165:
		case 390:
		case 627:
		case 633:
		case 732:
		case 795:
		case 906:
		case 921:
		case 975:
			solutionKnown[n] = 0;
			break;
		default:
			solutionKnown[n] = 1;
			break;
		}
}
// print a solution (formatted to be: x <= y <= z) and remember it:
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
		printf("%5ld, %ld, %ld, %ld\n", (int64_t)n, (int64_t)x, (int64_t)y, (int64_t)z);
	else if (x <= z && z <= y)
		printf("%5ld, %ld, %ld, %ld\n", (int64_t)n, (int64_t)x, (int64_t)z, (int64_t)y);
	else if (y <= x && x <= z)
		printf("%5ld, %ld, %ld, %ld\n", (int64_t)n, (int64_t)y, (int64_t)x, (int64_t)z);
	else if (y <= z && z <= x)
		printf("%5ld, %ld, %ld, %ld\n", (int64_t)n, (int64_t)y, (int64_t)z, (int64_t)x);
	else if (z <= x && x <= y)
		printf("%5ld, %ld, %ld, %ld\n", (int64_t)n, (int64_t)z, (int64_t)x, (int64_t)y);
	else
		printf("%5ld, %ld, %ld, %ld\n", (int64_t)n, (int64_t)z, (int64_t)y, (int64_t)x);
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

static void printSolutionsForPositiveNumbers(void)
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

static void printSolutionsForNegativeNumbersUsingBruteForce(void)
{
	for (BigInt x = XYZ_MIN; x <= XYZ_MAX; ++x)
	{
		BigInt x3 = cubeNumbers[x];
#pragma omp parallel for
		for (BigInt y = XYZ_MIN; y <= x; ++y)
		{
			BigInt y3 = cubeNumbers[y];
			for (BigInt z = XYZ_MIN; z <= y; ++z)
			{
				BigInt z3 = cubeNumbers[z], n = -x3 + y3 + z3;
				if (-N_MAX < n && n < N_MAX && !solutionKnown[abs(n)])
					printSolution(n, -x, y, z);

				n = x3 - y3 + z3;
				if (-N_MAX < n && n < N_MAX && !solutionKnown[abs(n)])
					printSolution(n, x, -y, z);

				n = x3 + y3 - z3;
				if (-N_MAX < n && n < N_MAX && !solutionKnown[abs(n)])
					printSolution(n, x, y, -z);

				n = x3 - y3 - z3;
				if (-N_MAX < n && n < N_MAX && !solutionKnown[abs(n)])
					printSolution(n, x, -y, -z);
			}
		}
	}
}

static void printSolutionsForNegativeNumbersVersion1(void)
{
	for (BigInt x = XYZ_MIN; x <= XYZ_MAX; ++x)
	{
		BigInt x3 = cubeNumbers[x];
#pragma omp parallel for
		for (BigInt y = XYZ_MIN; y <= x; ++y)
		{
			BigInt y3 = cubeNumbers[y];
			BigInt x3_plus_y3 = x3 + y3;
			for (BigInt z = XYZ_MIN; z <= y; ++z)
			{
				BigInt z3 = cubeNumbers[z], n = x3_plus_y3 - z3;
				if (n > N_MAX)
					continue; // still too big
				if (n < -N_MAX)
				       break; // too small already
				if (!solutionKnown[abs(n)])
					printSolution(n, x, y, -z);
			}
			BigInt x3_minus_y3 = x3 - y3;
			for (BigInt z = XYZ_MIN; z <= y; ++z)
			{
				BigInt z3 = cubeNumbers[z], n = x3_minus_y3 + z3;
				if (n < -N_MAX)
				       continue; // still too small 
				if (n > N_MAX)
					break; // already too big
				if (!solutionKnown[abs(n)])
					printSolution(n, x, -y, z);
			}
			for (BigInt z = XYZ_MIN; z <= y; ++z)
			{
				BigInt z3 = cubeNumbers[z], n = x3_minus_y3 - z3;
				if (n > N_MAX)
					continue; // still too big
				if (n < -N_MAX)
				       break; // too small already
				if (!solutionKnown[abs(n)])
					printSolution(n, x, -y, -z);
			}
			BigInt minus_x3_plus_y3 = -x3 + y3;
			for (BigInt z = XYZ_MIN; z <= y; ++z)
			{
				BigInt z3 = cubeNumbers[z], n = minus_x3_plus_y3 + z3;
				if (n < -N_MAX)
					continue; // still too small
				if (n > N_MAX)
				       break; // too big already
				if (!solutionKnown[abs(n)])
					printSolution(n, -x, y, z);
			}
		}
	}
}

static void TrySomething(void)
{
	BigInt x = -284650292555885;
	BigInt y =  283450105697727;
	BigInt z =   66229832190556;
	for(;;)
	{
		BigInt n = (x*x*x) + (y*y*y) + (z*z*z);
		if (n >= N_MIN && n <= N_MAX && !solutionKnown[n])
			printSolution(n, x, y, z);
		x -= 3;
		y += 3;
		z += 3;
	} 
}

static void printSolutionsUsingBinarySearch(BigInt beginOfSearch, BigInt endOfSearch)
{
#pragma omp parallel for
	for (BigInt x = beginOfSearch; x < endOfSearch; ++x)
	{
		BigInt x3 = cubeNumbers[x];
		for (BigInt y = XYZ_MIN; y <= x; ++y)
		{
			BigInt y3 = cubeNumbers[y];

			// Binary search for: x³ - y³ - z³
			BigInt min = 0, max = x; 
			do
			{
				const BigInt z = (min + max) / (BigInt)2;
				const BigInt n = x3 - y3 - cubeNumbers[z];

				if (n >= N_MAX)
					max = z - 1;
				else if (n <= -N_MAX)
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
				const BigInt n = x3 - y3 + cubeNumbers[z];

				if (n >= N_MAX)
					max = z - 1;
				else if (n <= -N_MAX)
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
				const BigInt n = -x3 + y3 + cubeNumbers[z];

				if (n >= N_MAX)
					max = z - 1;
				else if (n <= -N_MAX)
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

int main(int argc, char **argv)
{
	int mode = 0; // print no solutions by default
	if (argc == 2)
		mode = atoi(argv[1]);
	
#if CSV_OUTPUT
	printf("    n, x, y, z\n");
#else
	printf("# Solutions of n = x³ + y³ + z³  (for n < %ld and x,y,z < %ld, solutions formatted to be: x <= y <= z)\n", (int64_t)N_MAX, (int64_t)XYZ_MAX);
#endif
	// setNontrivialSolutionsAsUnknown();

	// 

	if (mode == 0)
	{
		printNoSolutions();
	}
	else if (mode == 1)
	{
		calculateCubeNumbers();
		printSolutionsForPositiveNumbers();
	}

	// printSolutionsForNegativeNumbersUsingBruteForce();
	
	// printSolutionsForNegativeNumbersVersion1();

	// TrySomething();

	// printSolutionsUsingBinarySearch(0/*5000*/, XYZ_MAX);

	return 0;
}
