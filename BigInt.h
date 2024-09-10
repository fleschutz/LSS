// BigInt.h - Header file to provide the BigInt datatype and support functions.
#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef __int128_t BigInt; // datatype to hold really big integer values

// Returns the given string as BigInt, e.g. stringToBigInt("123") returns 123.
static BigInt stringToBigInt(const char *str)
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

// Returns base and exponent as BigInt, e.g. baseAndExponentToBigInt(10,3) returns 1000.
static BigInt baseAndExponentToBigInt(BigInt base, BigInt exponent)
{
	BigInt result = 1;
	for (BigInt i = 0; i < exponent; ++i)
		result *= base;
	return result;
}

// Converts the given BigInt to a string.
static void BigIntToString(BigInt n, char *str)
{
	char buf[41] = {}, *bufPtr = buf + sizeof(buf) - 1;  // start at the end
	if (n < 0)
	{
		n = -n;
                *str++ = '-';
	}
	do
	{
		*--bufPtr = "0123456789"[n % 10];    // save last digit
		n /= 10;                // drop it
	} while (n);
	strcpy(str, bufPtr);
}

// Special printf() to support "%B" for BigInt variables.
static void printfBigInts(const char* formatString, ...)
{
	char buf[1024], *bufPtr = buf;
	va_list ptr;
	va_start(ptr, formatString);

	for (int i = 0; formatString[i] != '\0'; ++i)
	{
		if (formatString[i] == '%')
		{
			if (formatString[++i] == 'B')
			{
				BigIntToString(va_arg(ptr, BigInt), bufPtr);
				bufPtr += strlen(bufPtr);
			}
		}
		else
                	*bufPtr++ = formatString[i];
	}
	*bufPtr = '\0';
	fprintf(stdout, "%s\n", buf);
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
    BigInt start = 0, end = n; // set start and end for binary search

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
