#include <omp.h>              // OpenMP API for multi-threading
#include "BigInt.h"           // BigInt datatype and support functions

#define N_MIN               0 // we are interested in n >= 0
#define N_MAX           10000 //        and n <= 10,000 only
#define XYZ_MIN             0 // minimum x,y,z value for trivial search
#define XYZ_MAX        100000 // maximum x,y,z value for trivial search

// A solution has been found - remember and print it.
void onSolutionFound(BigInt n, BigInt x, BigInt y, BigInt z)
{
	static int knownSolutions[N_MAX + 1] = { 0 }; 

	if (n < 0)
		onSolutionFound(-n, -x, -y, -z); // negate everything
	else if (knownSolutions[n]++ > 0)
		; // already found a solution for <n> 
	else if (x > 0 && y < 0 && z < 0)
		printLine("%B = %B³ - %B³ - %B³", n, x, -y, -z);
	else if (x > 0 && y > 0 && z < 0)
		printLine("%B = %B³ + %B³ - %B³", n, x, y, -z);
	else if (x < 0 && y > 0 && z > 0)
		printLine("%B = %B³ + %B³ - %B³", n, y, z, -x);
	else
		printLine("%B = %B³ + %B³ + %B³", n, x, y, z);
}

void listNoSolutions(void)
{
	for (BigInt n = N_MIN; n <= N_MAX; ++n)
		if ((n % 9) == 4 || (n % 9) == 5)
			printLine("%B = no solution", n);
}

void listTrivialSolutionsForPositiveXYZ(void)
{
	for (BigInt x = XYZ_MIN; x <= XYZ_MAX; ++x)
	{
		BigInt x3 = x*x*x;
		if (x3 > N_MAX)
			break; // x³ is too big already
		for (BigInt y = XYZ_MIN; y <= x; ++y)
		{
			BigInt y3 = y*y*y, x3_plus_y3 = x3 + y3;
			if (x3_plus_y3 > N_MAX)
				break; // x³ + y³ is too big already
			for (BigInt z = XYZ_MIN; z <= y; ++z)
			{
				BigInt z3 = z*z*z, n = x3_plus_y3 + z3;
				if (n > N_MAX)
				       break; // x³ + y³ + z³ is too big already
				onSolutionFound(n, x, y, z);
			}
		}
	}
}

void listTrivialSolutionsForNegativeYZ(void)
{
	for (BigInt x = XYZ_MIN; x <= XYZ_MAX; ++x)
	{
		BigInt x3 = x*x*x;
		for (BigInt y = XYZ_MIN; y <= x; ++y)
		{
			BigInt x3_minus_y3 = x3 - y*y*y;
#pragma omp parallel for
			for (BigInt z = XYZ_MIN; z <= y; ++z)
			{
				BigInt n = x3_minus_y3 + z*z*z;
				if (N_MIN <= n && n <= N_MAX)
					onSolutionFound(n, x, -y, z);

				n = x3_minus_y3 - z*z*z;
				if (N_MIN <= n && n <= N_MAX)
					onSolutionFound(n, x, -y, -z);
			}
		}
	}
}

void listSolutionsForNegativeYZ(BigInt x_min, BigInt x_max)
{
#pragma omp parallel for
	for (BigInt x = x_min; x <= x_max; ++x)
	{
		const BigInt x3 = x*x*x;

		for (BigInt y = x, z = 1, z3 = 1*1*1; --y >= z; )
		{
			const BigInt y3 = y*y*y;
			
			BigInt n = x3 - y3 - z3;
			while (n > N_MAX)
			{
				++z;
				z3 = z * z * z;
				n = x3 - y3 - z3;
			}
			if (n >= -N_MAX)
				onSolutionFound(n, x, -y, -z);
		}
	}
}

int main(int argc, char **argv)
{
	int mode = (argc >= 2) ? atoi(argv[1]) : 2; // mode 2 when no arguments given
	
	if (mode == 1)
	{
		if (argc != 5)
		{
			printLine("Sorry, syntax for mode 1 is: ./mode 1 <x> <y> <z>");
			return 1; 
		}
		BigInt x = BigIntFromString(argv[2]);
		BigInt y = BigIntFromString(argv[3]);
		BigInt z = BigIntFromString(argv[4]);
		BigInt n = (x * x * x) + (y * y * y) + (z * z * z);
		printLine("%B³ + %B³ + %B³ = %B", x, y, z, n);
	}
	else if (mode == 2) 
	{
		printLine("# List of no solutions for n=x³+y³+z³ with n=[%B..%B]", (BigInt)N_MIN, (BigInt)N_MAX);
		listNoSolutions();
	}
	else if (mode == 3)
	{
		printLine("# List of trivial solutions for n=x³+y³+z³ with n=[%B..%B] and x,y,z=[%B..%B]",
		    (BigInt)N_MIN, (BigInt)N_MAX, (BigInt)XYZ_MIN, (BigInt)XYZ_MAX);
		listTrivialSolutionsForPositiveXYZ();
	}
	else if (mode == 4)
	{
		printLine("# List of trivial solutions for n=x³+y³+z³ with negative numbers of y and z (for n=[%B..%B] and x,y,z=[%B..%B]",
		    (BigInt)N_MIN, (BigInt)N_MAX, (BigInt)XYZ_MIN, (BigInt)XYZ_MAX);
		listTrivialSolutionsForNegativeYZ();
	}
	else if (mode == 5) 
	{
		printLine("# List of trivial solutions for n=x³+y³+z³ with n=[%B..%B] and x,y,z=[%B..%B]",
		    (BigInt)N_MIN, (BigInt)N_MAX, (BigInt)XYZ_MIN, (BigInt)XYZ_MAX);
		listNoSolutions();
		listTrivialSolutionsForPositiveXYZ();
		listTrivialSolutionsForNegativeXYZ();
	}
	else if (mode == 6) 
	{
		int exponent = (argc == 3 ? atoi(argv[2]) : 6);
		printLine("# List of solutions for n=x³+y³+z³ with n=[%B..%B] and x=[10^%B..10^%B]",
		    (BigInt)N_MIN, (BigInt)N_MAX, (BigInt)exponent, (BigInt)(exponent + 1));

		listSolutionsForNegativeYZ(BigIntFromPowerOf10(exponent), BigIntFromPowerOf10(exponent + 1));
	}
	return 0;
}
