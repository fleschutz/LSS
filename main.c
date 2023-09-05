#include <omp.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef __int128_t     BigInt;
#define N_MIN               0 // minimum desired value for n
#define N_MAX            1000 // maximum desired value for n
#define XYZ_MIN             0 // minimum value for x,y,z to use
#define XYZ_MAX        100000 // maximum value for x,y,z to use
#define CSV_OUTPUT          0 // CSV output desired, else text output

// Returns the given string as BigInt.
BigInt BigIntFromString(const char *str)
{
	BigInt sign = 1, value = 0;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	for (size_t i = 0; i < strlen(str); ++i)
		value = (value * 10) + (str[i] - '0');
	return sign * value;
}

// Returns the given power of 10 number as BigInt.
BigInt BigIntFromPowerOf10(int exponent)
{
	BigInt result = 1;
	for (int i = 0; i < exponent; ++i)
		result *= (BigInt)10;
	return result;
}

// Prints the given big number on the console.
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
	fprintf(stdout, "%s", s);
}

// Special printf() to support "%B" for BigInt variables.
void printfBig(const char* formatString, ...)
{
	va_list ptr;
	va_start(ptr, formatString);

	for (int i = 0; formatString[i] != '\0'; ++i)
	{
		if (formatString[i] == '%') {
			if (formatString[++i] == 'B')
				printBigInt(va_arg(ptr, BigInt));
		}
		else
                	fputc(formatString[i], stdout);
	}
	fflush(stdout); // to disable buffering
	va_end(ptr);
}

// Provides pre-calculated cube numbers for performance. Afterward, use 'cubeNumbers[x]' instead of 'x*x*x'.
BigInt cubeNumbers[XYZ_MAX + 1];
void preCalculateCubeNumbers(void) 
{
	for (BigInt x = XYZ_MIN; x <= XYZ_MAX; ++x)
		cubeNumbers[x] = x * x * x;
}

// Prints single NO solution.
void printNoSolution(BigInt n)
{
#if CSV_OUTPUT
	printfBig("%B, , , ,\n", n);
#else
	printfBig("%B = no solution\n", n);
#endif
}

// Prints and remembers a single solution (formatted to be: x <= y <= z).
int solutionKnown[N_MAX + 1] = { 0 }; 
void printSolution(BigInt n, BigInt x, BigInt y, BigInt z)
{
	solutionKnown[n] = 1;
#if CSV_OUTPUT	
	if (x <= y && y <= z)
		printfBig("%B, %B, %B, %B,\n", n, x, y, z);
	else if (x <= z && z <= y)
		printfBig("%B, %B, %B, %B,\n", n, x, z, y);
	else if (y <= x && x <= z)
		printfBig("%B, %B, %B, %B,\n", n, y, x, z);
	else if (y <= z && z <= x)
		printfBig("%B, %B, %B, %B,\n", n, y, z, x);
	else if (z <= x && x <= y)
		printfBig("%B, %B, %B, %B,\n", n, z, x, y);
	else
		printfBig("%B, %B, %B, %B,\n", n, z, y, x);
#else
	if (x <= y && y <= z)
		printfBig("%B = %B³ + %B³ + %B³\n", n, x, y, z);
	else if (x <= z && z <= y)
		printfBig("%B = %B³ + %B³ + %B³\n", n, x, z, y);
	else if (y <= x && x <= z)
		printfBig("%B = %B³ + %B³ + %B³\n", n, y, x, z);
	else if (y <= z && z <= x)
		printfBig("%B = %B³ + %B³ + %B³\n", n, y, z, x);
	else if (z <= x && x <= y)
		printfBig("%B = %B³ + %B³ + %B³\n", n, z, x, y);
	else
		printfBig("%B = %B³ + %B³ + %B³\n", n, z, y, x);
#endif
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
				z3 = z * z * z;
				n = x3 - y3 - z3;
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
			printfBig("Sorry, syntax for mode 1 is: ./mode 1 <x> <y> <z>\n");
			return 1; 
		}
		BigInt x = BigIntFromString(argv[2]);
		BigInt y = BigIntFromString(argv[3]);
		BigInt z = BigIntFromString(argv[4]);
		BigInt n = (x * x * x) + (y * y * y) + (z * z * z);
		printfBig("%B³ + %B³ + %B³ = %B\n", x, y, z, n);
	}
	else if (mode == 2) 
	{
#if CSV_OUTPUT
		printfBig("    n, x, y, z,\n");
#else
		printfBig("# No solutions of n=x³+y³+z³ for n=[%B..%B]\n", (BigInt)N_MIN, (BigInt)N_MAX);
#endif
		listNoSolutions();
	}
	else if (mode == 3)
	{
#if CSV_OUTPUT
		printfBig("    n, x, y, z,\n");
#else
		printfBig("# Trivial solutions of n=x³+y³+z³ for n=[%B..%B] and x,y,z=[%B..%B] (formatted to be: x <= y <= z)\n", (BigInt)N_MIN, (BigInt)N_MAX, (BigInt)XYZ_MIN, (BigInt)XYZ_MAX);
#endif
		preCalculateCubeNumbers();
		listTrivialSolutionsForPositiveXYZ();
	}
	else if (mode == 4)
	{
#if CSV_OUTPUT
		printfBig("    n, x, y, z,\n");
#else
		printfBig("# Trivial solutions of n=x³+y³+z³ for negative numbers of x,y,z (for n=[%B..%B] and x,y,z=[%B..%B], solutions formatted to be: x <= y <= z)\n", (BigInt)N_MIN, (BigInt)N_MAX, (BigInt)XYZ_MIN, (BigInt)XYZ_MAX);
#endif
		preCalculateCubeNumbers();
		listTrivialSolutionsForNegativeXYZ();
	}
	else if (mode == 5) 
	{
#if CSV_OUTPUT
		printfBig("    n, x, y, z,\n");
#else
		printfBig("# Trivial solutions of n=x³+y³+z³  for n=[%B..%B] and x,y,z=[%B..%B], solutions formatted to be: x <= y <= z)\n", (BigInt)N_MIN, (BigInt)N_MAX, (BigInt)XYZ_MIN, (BigInt)XYZ_MAX);
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
		printfBig("    n, x, y, z,\n");
#else
		printfBig("# Solutions of n=x³+y³+z³ for n=[%B..%B] and x=[10^%B..10^%B] (formatted to be: x <= y <= z)\n", (BigInt)N_MIN, (BigInt)N_MAX, (BigInt)exponent, (BigInt)(exponent + 1));
#endif
		listSolutionsForNegativeYZ(BigIntFromPowerOf10(exponent), BigIntFromPowerOf10(exponent + 1));
	}
	return 0;
}
