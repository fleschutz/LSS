#include <omp.h>              // OpenMP API for multi-threading
#include "BigInt.h"           // BigInt datatype and support functions

#define N_MIN               0 // we are interested in n >= 0
#define N_MAX           10000 //        and n <= 10,000 only
#define XYZ_MAX        100000 // maximum x,y,z value for trivial search

// A solution has been found - remember and print it.
void onSolutionFound(BigInt n, BigInt x, BigInt y, BigInt z)
{
	static int knownSolutions[N_MAX + 1] = { 0 }; 

	if (n < 0)
		onSolutionFound(-n, -x, -y, -z); // negate everything
	else if (n < N_MIN || n > N_MAX)
		return; // out of range (should not happen)
	else if (knownSolutions[n]++ > 0)
		; // already found a solution for <n> 
	else if (x > 0 && y < 0 && z < 0)
		printfBigInts("%B = %B³ - %B³ - %B³", n, x, -y, -z);
	else if (x > 0 && y > 0 && z < 0)
		printfBigInts("%B = %B³ + %B³ - %B³", n, x, y, -z);
	else if (x < 0 && y > 0 && z > 0)
		printfBigInts("%B = %B³ + %B³ - %B³", n, y, z, -x);
	else
		printfBigInts("%B = %B³ + %B³ + %B³", n, x, y, z);
}

void listNoSolutions(void) // mode 2
{
	for (BigInt n = N_MIN; n <= N_MAX; ++n)
		if ((n % 9) == 4 || (n % 9) == 5)
			printfBigInts("%B = no solution", n);
}

// Loops through every x and x^3 from <min> to <max> (upwards).
#define foreach_x_and_x3(_min, _max) \
	for (BigInt x = (_min), x3 = x*x*x; x <= (_max); ++x, x3 = x*x*x)

#define foreach_y_and_y3(_min, _max) \
	for (BigInt y = (_min), y3 = y*y*y; y <= (_max); ++y, y3 = y*y*y)

#define foreach_z_and_z3(_min, _max) \
	for (BigInt z = (_min), z3 = z*z*z; z <= (_max); ++z, z3 = z*z*z)

void listTrivialSolutionsForPositiveNumbers(void) // mode 3
{
	foreach_x_and_x3(0, XYZ_MAX)
	{
		if (x3 > N_MAX)
			break; // x³ is too big already
		foreach_y_and_y3(0, x)
		{
			BigInt x3_plus_y3 = x3 + y3;
			if (x3_plus_y3 > N_MAX)
				break; // x³ + y³ is too big already
			foreach_z_and_z3(0, y)
			{
				BigInt n = x3_plus_y3 + z3;
				if (n > N_MAX)
				       break; // x³ + y³ + z³ is too big already
				onSolutionFound(n, x, y, z);
			}
		}
	}
}

void listTrivialSolutionsForNegativeNumbers(void) // mode 4
{
	foreach_x_and_x3(0, XYZ_MAX)
	{
#pragma omp parallel for
		for (BigInt y = 0; y <= x; ++y)
		{
			const BigInt x3_minus_y3 = x3 - y*y*y;
			for (BigInt z = 0; z <= y; ++z)
			{
				const BigInt z3 = z*z*z;
				BigInt n = x3_minus_y3 + z3;
				if (-N_MAX <= n && n <= N_MAX)
					onSolutionFound(n, x, -y, z);

				n = x3_minus_y3 - z3;
				if (-N_MAX <= n && n <= N_MAX)
					onSolutionFound(n, x, -y, -z);
			}
		}
	}
}

void listNontrivialSolutions(BigInt x_min, BigInt x_max) // mode 6
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
				z3 = z*z*z;
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
			printfBigInts("Sorry, syntax for mode 1 is: ./mode 1 <x> <y> <z>");
			return 1; 
		}
		BigInt x = StringToBigInt(argv[2]);
		BigInt y = StringToBigInt(argv[3]);
		BigInt z = StringToBigInt(argv[4]);
		BigInt n = x*x*x + y*y*y + z*z*z;
		printfBigInts("%B³ + %B³ + %B³ = %B", x, y, z, n);
	}
	else if (mode == 2) 
	{
		printfBigInts("# List of no solutions for: n=x³+y³+z³ with n=[%B..%B]",
		    (BigInt)N_MIN, (BigInt)N_MAX);

		listNoSolutions();
	}
	else if (mode == 3)
	{
		printfBigInts("# List of trivial solutions for: n=x³+y³+z³ with n=[%B..%B] and x,y,z=[%B..%B] (positive numbers only)",
		    (BigInt)N_MIN, (BigInt)N_MAX, (BigInt)0, (BigInt)XYZ_MAX);

		listTrivialSolutionsForPositiveNumbers();
	}
	else if (mode == 4)
	{
		printfBigInts("# List of trivial solutions for: n=x³+y³+z³ with n=[%B..%B] and x,y,z=[%B..%B]",
		    (BigInt)N_MIN, (BigInt)N_MAX, (BigInt)-XYZ_MAX, (BigInt)XYZ_MAX);

		listTrivialSolutionsForNegativeNumbers();
	}
	else if (mode == 5) 
	{
		printfBigInts("# List of trivial solutions for: n=x³+y³+z³ with n=[%B..%B] and x,y,z=[%B..%B]",
		    (BigInt)N_MIN, (BigInt)N_MAX, (BigInt)-XYZ_MAX, (BigInt)XYZ_MAX);

		listNoSolutions();
		listTrivialSolutionsForPositiveNumbers();
		listTrivialSolutionsForNegativeNumbers();
	}
	else if (mode == 6) 
	{
		int exponent = (argc == 3 ? atoi(argv[2]) : 6);

		printfBigInts("# List of solutions for: n=x³+y³+z³ with n=[%B..%B] and x=[10^%B..10^%B]",
		    (BigInt)N_MIN, (BigInt)N_MAX, (BigInt)exponent, (BigInt)(exponent + 1));

		listNontrivialSolutions(BaseAndExponentToBigInt(10, exponent),
		    BaseAndExponentToBigInt(10, exponent + 1));
	}
	return 0; // success
}
