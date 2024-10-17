#include <omp.h>              // OpenMP API for multi-threading
#include "BigInt.h"           // BigInt datatype and support functions

#define N_MIN               0 // we are interested in n >= 0
#define N_MAX           10000 //                  and n <= 10,000 

#define TRIVIAL_X_MIN       0 // for trivial searches use x >= 0
#define TRIVIAL_X_MAX  100000 //                      and x <= 100,000 

void calculateSolution(BigInt x, BigInt y, BigInt z) // mode 1
{
	BigInt n = x*x*x + y*y*y + z*z*z;
	printfBigInts("%B³ + %B³ + %B³ = %B", x, y, z, n);
}

// A potential solution has been found, so check + print + remember it.
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
	if (n == 30 || n == 33 || n == 42 || n == 52 || n == 74 || n == 165 || n == 795 || n == 906)
		printf("YES - found a KNOWN nontrivial solution !!!\n");
	else if (n == 114 || n == 390 || n == 627 || n == 633 || n == 732 || n == 921 || n == 975)
		printf("JACKPOT - found an UNKNOWN nontrivial solution !!!\n");
}

void listNoSolutions(void) // mode 2
{
	for (int n = N_MIN; n <= N_MAX; ++n)
		if ((n % 9) == 4 || (n % 9) == 5)
			printf("%d = no solution\n", n);
}

void listSolutionsForPositiveXYZ(void) // mode 3
{
	for (BigInt x = 0; x < N_MAX; ++x)
	{
		const BigInt x3 = x*x*x;
		if (x3 > N_MAX)
			break; // x³ is too big already

		for (BigInt y = 0; y <= x; ++y)
		{
			const BigInt x3_plus_y3 = x3 + y*y*y;
			if (x3_plus_y3 > N_MAX)
				break; // x³ + y³ is too big already

			for (BigInt z = 0; z <= y; ++z)
			{
				const BigInt n = x3_plus_y3 + z*z*z;
				if (n > N_MAX)
				       break; // x³ + y³ + z³ is too big already
				onSolutionFound(n, x, y, z);
			}
		}
	}
}

void listSolutionsForNegativeZ(void) // mode 4
{
	for (BigInt x = TRIVIAL_X_MIN; x <= TRIVIAL_X_MAX; ++x)
	{
		const BigInt x3 = x*x*x;
		BigInt z = x;

#pragma omp parallel for
		for (BigInt y = 1; y < x; ++y)
		{
			const BigInt x3_plus_y3 = x3 + y*y*y;

			while (x3_plus_y3 - z*z*z > N_MAX)
				++z;
		
			if (x3_plus_y3 - z*z*z >= N_MIN)
				onSolutionFound(x3_plus_y3 - z*z*z, x, y, -z);
		}
	}
}

void listSolutionsForNegativeYZ(void) // mode 5
{
	for (BigInt x = TRIVIAL_X_MIN; x <= TRIVIAL_X_MAX; ++x)
	{
		const BigInt x3 = x*x*x;

#pragma omp parallel for
		for (BigInt y = 1; y < x; ++y)
		{
			const BigInt x3_minus_y3 = x3 - y*y*y; // result is never negative

			for (BigInt z = 1; z < y; ++z)
			{
				const BigInt n = x3_minus_y3 - z*z*z;
				if (n < -N_MAX)
					break; // z is too big already
				if (n <= N_MAX)
					onSolutionFound(n, x, -y, -z);
			}
		}
	}
}

void listNontrivialSolutions(const BigInt x_min, const BigInt x_max) // mode 7
{
	for (BigInt x = x_min; x <= x_max; ++x)
	{
		BigInt x3 = x*x*x, z = 1; // z walks up

#pragma omp parallel for
		for (BigInt y = x - 1; y > z; --y) // y walks down
		{
			const BigInt x3_minus_y3 = x3 - y*y*y;
			
			while (x3_minus_y3 - z*z*z > N_MAX)
				++z;

			if (x3_minus_y3 - z*z*z >= -N_MAX)
				onSolutionFound(x3_minus_y3 - z*z*z, x, -y, -z);
		}
	}
}

int main(int argc, char **argv)
{
	int mode = (argc >= 2) ? atoi(argv[1]) : 0/*invalid*/;
	
	if (mode == 1 && argc == 5)
	{
		calculateSolution(stringToBigInt(argv[2]), stringToBigInt(argv[3]), stringToBigInt(argv[4]));
	}
	else if (mode == 2) 
	{
		printf("# List of no solutions for: n = x³ + y³ + z³  with n=[%d..%d]\n", N_MIN, N_MAX);
		listNoSolutions();
	}
	else if (mode == 3)
	{
		printf("# List of solutions for: n = x³ + y³ + z³  with n=[%d..%d] and x,y,z >= 0\n", N_MIN, N_MAX);
		listSolutionsForPositiveXYZ();
	}
	else if (mode == 4)
	{
		printf("# List of solutions for: n = x³ + y³ + z³  with n=[%d..%d] and x=[%d..%d] and z < 0\n",
		    N_MIN, N_MAX, TRIVIAL_X_MIN, TRIVIAL_X_MAX);

		listSolutionsForNegativeZ();
	}
	else if (mode == 5)
	{
		printf("# List of solutions for: n = x³ + y³ + z³  with n=[%d..%d] and x=[%d..%d] and y,z < 0\n",
		    N_MIN, N_MAX, TRIVIAL_X_MIN, TRIVIAL_X_MAX);

		listSolutionsForNegativeYZ();
	}
	else if (mode == 6) 
	{
		printf("# List of trivial solutions for: n = x³ + y³ + z³  with n=[%d..%d] and x=[%d..%d]\n",
		    N_MIN, N_MAX, TRIVIAL_X_MIN, TRIVIAL_X_MAX);

		listNoSolutions();
		listSolutionsForPositiveXYZ();
		listSolutionsForNegativeZ();
		listSolutionsForNegativeYZ();
	}
	else if (mode == 7 && argc == 3) 
	{
		int exponent = atoi(argv[2]);
		printf("# List of solutions for: n = x³ + y³ + z³  with n=[%d..%d] and x=[10^%d..10^%d]\n",
		    N_MIN, N_MAX, exponent, exponent + 1);

		BigInt x_min = baseAndExponentToBigInt(10, exponent);
		BigInt x_max = baseAndExponentToBigInt(10, exponent + 1);
		listNontrivialSolutions(x_min, x_max);
	}
	else
	{
		printf("Syntax: ./mode 1 <x> <y> <z> - Calculates a solution for x, y, z\n");
		printf("        ./mode 2             - Lists no solutions\n");
		printf("        ./mode 3             - Lists all solutions for positive x, y z\n");
		printf("        ./mode 4             - Lists trivial solutions for negative z\n");
		printf("        ./mode 5             - Lists trivial solutions for negative y and z\n");
		printf("        ./mode 6             - Lists all trivial solutions\n");
		printf("        ./mode 7 <exponent>  - Lists nontrivial solutions for value range\n");
	}
	return 0;
}
