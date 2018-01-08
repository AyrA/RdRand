#ifndef _DLL_H_
#define _DLL_H_

/*rdrand can work with 32 bit and 64 bit integers*/
#define uint    unsigned int
#define ulong   unsigned long

/*being extra cheap*/
#define MIN(X,Y) (X<Y?X:Y)

#if BUILDING_DLL
#define DLLIMPORT __declspec(dllexport)
#else
#define DLLIMPORT __declspec(dllimport)
#endif

BOOL DLLIMPORT RdRandSupported();
void DLLIMPORT RdRandBytes(char*,int);

#endif
