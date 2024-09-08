#include <omp.h>              // OpenMP API for multi-threading
#include "BigInt.h"           // BigInt datatype and support functions

#define N_MIN               0 // we are interested in n >= 0
#define N_MAX           10000 //                  and n <= 10,000 
			      //
#define TRIVIAL_X_MIN       0 // use x >= 0
#define TRIVIAL_X_MAX  100000 // and x <= 100,000 for trivial searches

// Loops through every x from <min> to <max> and calculates x^3. 
#define foreach_x_and_x3(_min, _max) \
	for (BigInt x = (_min), x3 = x*x*x; x <= (_max); ++x, x3 = x*x*x)

// Loops through every y from <min> to <max> and calculates y^3. 
#define foreach_y_and_y3(_min, _max) \
	for (BigInt y = (_min), y3 = y*y*y; y <= (_max); ++y, y3 = y*y*y)

// Loops through every z from <min> to <max> and calculates z^3. 
#define foreach_z_and_z3(_min, _max) \
	for (BigInt z = (_min), z3 = z*z*z; z <= (_max); ++z, z3 = z*z*z)

void calculateSolution(BigInt x, BigInt y, BigInt z) // mode 1
{
	BigInt n = x*x*x + y*y*y + z*z*z;
	printfBigInts("%B³ + %B³ + %B³ = %B", x, y, z, n);
}

// A potential solution has been found, so check/print/remember it.
void onSolutionFound(BigInt n, BigInt x, BigInt y, BigInt z)
{
	static int knownSolutions[N_MAX + 1] = { 0 }; 

	if (n < 0)
		onSolutionFound(-n, -x, -y, -z); // negate everything
	else if (n < N_MIN || n > N_MAX)
		return; // out of range (should not happen)
	else if (knownSolutions[n]++ > 0)
		return; // already found a solution for <n> 
	else if (x > 0 && y < 0 && z < 0)
		printfBigInts("%B = %B³ - %B³ - %B³", n, x, -y, -z);
	else if (x > 0 && y > 0 && z < 0)
		printfBigInts("%B = %B³ + %B³ - %B³", n, x, y, -z);
	else if (x < 0 && y > 0 && z > 0)
		printfBigInts("%B = %B³ + %B³ - %B³", n, z, y, -x);
	else
		printfBigInts("%B = %B³ + %B³ + %B³", n, x, y, z);
	if (n == 30 || n == 33 || n == 42 || n == 52 || n == 74 || n == 165 || n == 795 || n == 906 // known nontrivial solutions
	    || n == 114 || n == 390 || n == 627 || n == 633 || n == 732 || n == 921 || n == 975) // unknown nontrivial solutions
		printf("JACKPOT - found a nontrivial solution !!!\n");
}

void listNoSolutions(void) // mode 2
{
	for (int n = N_MIN; n <= N_MAX; ++n)
		if ((n % 9) == 4 || (n % 9) == 5)
			printf("%d = no solution\n", n);
}

void listSolutionsForPositiveXYZ(void) // mode 3
{
	foreach_x_and_x3(0, N_MAX)
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
	foreach_x_and_x3(TRIVIAL_X_MIN, TRIVIAL_X_MAX)
	{
		foreach_y_and_y3(0, x)
		{
			const BigInt x3_minus_y3 = x3 - y3; // result is never negative
			foreach_z_and_z3(0, y)
			{
				if (x3_minus_y3 + z3 <= N_MAX)
					onSolutionFound(x3_minus_y3 + z3, x, -y, z);

				const BigInt n = x3_minus_y3 - z3;
				if (-N_MAX <= n && n <= N_MAX)
					onSolutionFound(n, x, -y, -z);
			}
		}
	}
}

void listNontrivialSolutions(int exponent) // mode 6
{
	const BigInt x_min = baseAndExponentToBigInt(10, exponent);
	const BigInt x_max = baseAndExponentToBigInt(10, exponent + 1);

	printf("# List of solutions for: n = x³ + y³ + z³  with n=[%d..%d] and x=[10^%d..10^%d]\n",
	    N_MIN, N_MAX, exponent, exponent + 1);

	foreach_x_and_x3(x_min, x_max)
	{
		BigInt z = 1, z3 = z*z*z;

#pragma omp parallel for
		for (BigInt y = x - 1; y >= z; --y)
		{
			const BigInt x3_minus_y3 = x3 - y*y*y;
			
			while (x3_minus_y3 - z3 > N_MAX)
			{
				++z;
				z3 = z*z*z;
			}
			if (x3_minus_y3 - z3 >= -N_MAX)
				onSolutionFound(x3_minus_y3 - z3, x, -y, -z);
		}
	}
}

int main(int argc, char **argv)
{
	int mode = (argc >= 2) ? atoi(argv[1]) : 0/*invalid*/;
	
	if (mode == 1)
	{
		if (argc == 5)
			calculateSolution(stringToBigInt(argv[2]), stringToBigInt(argv[3]), stringToBigInt(argv[4]));
		else
			printf("Syntax for mode 1 is: ./mode 1 <x> <y> <z>\n");
	}
	else if (mode == 2) 
	{
		printf("# List of no solutions for: n = x³ + y³ + z³  with n=[%d..%d]\n", N_MIN, N_MAX);
		listNoSolutions();
	}
	else if (mode == 3)
	{
		printf("# List of solutions for: n = x³ + y³ + z³  with n=[%d..%d] and x,y,z > 0 (positive numbers only)\n", N_MIN, N_MAX);

		listSolutionsForPositiveXYZ();
	}
	else if (mode == 4)
	{
		printf("# List of trivial solutions for: n = x³ + y³ + z³  with n=[%d..%d] and x=[%d..%d]\n",
		    N_MIN, N_MAX, TRIVIAL_X_MIN, TRIVIAL_X_MAX);

		listTrivialSolutionsForNegativeNumbers();
	}
	else if (mode == 5) 
	{
		printf("# List of trivial solutions for: n = x³ + y³ + z³  with n=[%d..%d] and x=[%d..%d]\n",
		    N_MIN, N_MAX, TRIVIAL_X_MIN, TRIVIAL_X_MAX);

		listNoSolutions();
		listSolutionsForPositiveXYZ();
		listTrivialSolutionsForNegativeNumbers();
	}
	else if (mode == 6) 
	{
		if (argc == 3)
			listNontrivialSolutions(atoi(argv[2]));
		else
			printf("Syntax for mode 6 is: ./mode 6 <exponent>\n");

	}
	else
		printf("Syntax is: ./mode <NUMBER> (with value range 1...6)\n");
	return 0;
}
