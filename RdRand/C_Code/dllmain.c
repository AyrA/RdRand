/*DLL Stuff*/
#include <windows.h>
/*CPU Capabilities*/
#include <cpuid.h>
/* DLL Function header */
#include "dll.h"

/*Checks if RdRand is supported on this CPU*/
BOOL DLLIMPORT RdRandSupported()
{
	/*Bit in ecx that contains the RDRAND Support Flag*/
    const uint flag_RDRAND = (1 << 30);
    uint eax = 0, ebx = 0, ecx = 0, edx = 0;
    /*Get CPU Capabilities*/
    __get_cpuid(1, &eax, &ebx, &ecx, &edx);
	/*Return if RDRAND Flag is Set*/
    return ((ecx & flag_RDRAND) == flag_RDRAND)?TRUE:FALSE;
}

/*Generates random bytes and fills them in*/
void DLLIMPORT RdRandBytes(char* buffer,int length){
	/*Holds the random value*/
	uint value;
	/*Number of chars copied*/
	int counter=0;
	//uint subcounter=0;
	if(RdRandSupported()==TRUE){
		while(counter<length){
			/*This is the magic line that obtains a random number*/
		    __asm__("rdrand  %[value]":[value]"=r"(value)::"cc");
		    /*Copy the number to the destination, use MIN to not copy too much*/
			memcpy(buffer+counter,&value,MIN((int)sizeof(uint),length-counter));
			/*Increase counter with the size of the number we just copied*/
			counter+=sizeof(uint);
	    }
    }
}

