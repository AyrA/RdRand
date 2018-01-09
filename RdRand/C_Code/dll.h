#ifndef _DLL_H_
#define _DLL_H_

/*DLL Stuff*/
#include <windows.h>
/*CPU Capabilities*/
#include <cpuid.h>
/*Standard integer types*/
#include <stdint.h>

/*return smaller of two numbers*/
#define MIN(X,Y) (X<Y?X:Y)

/*
	Set the integer to use.
	16, 32 and 64 bit integers are supported.
	It doesn't matters if signed or unsigned.
*/
#define RANDINT int64_t

/*Handle DllImport and DllExport*/
#if BUILDING_DLL
#define DLLIMPORT __declspec(dllexport)
#else
#define DLLIMPORT __declspec(dllimport)
#endif

/*Checks if RDRAND is supported*/
BOOL DLLIMPORT RdRandSupported();
/*Fills the given buffer with random bytes*/
void DLLIMPORT RdRandBytes(char*, int);
/*Get a random integer*/
RANDINT getRand();

#endif

