// Provides the BigInt datatype and support functions.
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// Datatype to hold really big integer values.
typedef __int128_t BigInt;

// Returns the given string as BigInt.
static BigInt BigIntFromString(const char *str)
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
static BigInt BigIntFromPowerOf10(int exponent)
{
	BigInt result = 1;
	for (int i = 0; i < exponent; ++i)
		result *= (BigInt)10;
	return result;
}

// Prints the given big number on the console.
static void printBigInt(BigInt n)
{
	char buf[80] = {}, *ptr = buf + sizeof(buf) - 1;  // start at the end
	if (n < 0)
	{
		n = -n;
                fputc('-', stdout);
	}
	do
	{
		*--ptr = "0123456789"[n % 10];    // save last digit
		n /= 10;                // drop it
	} while (n);
	fprintf(stdout, "%s", ptr);
}

// Special printf() to support "%B" for BigInt variables.
static void printLine(const char* formatString, ...)
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
	fprintf(stdout, "\n");
	fflush(stdout); // to disable buffering
	va_end(ptr);
}

static BigInt _cubeNumbers[100000];

static void preCalculateCubeNumbers(void)
{
	for (BigInt i = 0; i < 100000; i++)
		_cubeNumbers[i] = i * i * i;
}

static BigInt cubeNumber(BigInt n)
{
	return n < 100000 ? _cubeNumbers[n] : n*n*n;
}

// Returns the cube root of the given number, e.g. cubicRoot(27) returns 3.
static BigInt cubicRoot(BigInt n)
{
    BigInt start = 0, end = n; // Set start and end for binary search

    for (;;)
    {
        const BigInt mid = (start + end) / (BigInt)2;

        if (start + 1 >= end)
                return mid;

        if ((mid*mid*mid) > n)
            end = mid;
        else
            start = mid;
    }
}
