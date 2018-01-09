/* DLL Function header */
#include "dll.h"

RANDINT getRand() {
	/*Holds the random value*/
	RANDINT value;
	/*
		This is the magic line that obtains a random number.
		DO NOT REMOVE 'volatile' KEYWORD.
		This took way too fucking long to figure out.
	*/
	__asm__ volatile("rdrand %[value]":[value]"=r"(value)::"cc");
	return value;
}

/*
	Checks if RdRand is supported on this CPU.
	This is done by executing CPUID instruction and checking for a specific bit to be set.
*/
BOOL DLLIMPORT RdRandSupported() {
	/*Bit in ecx that contains the RDRAND Support Flag*/
	const unsigned int flag_RDRAND = (1 << 30);
	unsigned int eax = 0, ebx = 0, ecx = 0, edx = 0;
	/*Get CPU Capabilities*/
	__get_cpuid(1, &eax, &ebx, &ecx, &edx);
	/*Return if RDRAND Flag is Set*/
	return ((ecx & flag_RDRAND) == flag_RDRAND)?TRUE:FALSE;
}

/*Generates random bytes and fills them into the buffer*/
void DLLIMPORT RdRandBytes(char* buffer, int length) {
	/*Holds the random value*/
	RANDINT value;
	/*Number of chars copied*/
	int counter=0;
	if(RdRandSupported() == TRUE) {
		while(counter < length) {
			value = getRand();
			/*Copy the number to the destination, use MIN to not copy too much*/
			memcpy(buffer + counter, &value, MIN((int)sizeof(RANDINT), length-counter));
			/*Increase counter with the size of the number we just copied*/
			counter += sizeof(RANDINT);
		}
	}
}


