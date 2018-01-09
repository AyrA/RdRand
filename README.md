# RdRand

C# Code that utilizes the RdRand CPU instruction as a random number generator

## Hot to Use

The project is not ready to use yet. It should work though, assuming you have a CPU with RDRAND.
For the C# part, you only need `RdRand_Interop.cs`.
For the unmanaged code, the RdRand.dll file is enough.

## About x64

The C and C# projects both compile to x64 code rather than x86.
The RDRAND instruction is only available on processors that support x64 bits anyways.
If you need to run this on a 32 bit operating system, change the project settings and recompile the DLL.

## C Code

There is code in the `C_Code` directory that serves as the unmanaged part of the project.
The code exports two functions:

### BOOL RdRandSupported()

Returns `1` if the RDRAND instruction is supported on this CPU, `0` otherwise

### void RdRandBytes(char*, int);

Generates `int` random bytes and writes them into the memory, beginning at `char*`

# TODO

- [ ] Provide proper command line interface
- [ ] Convert entire project to DLL to allow easy inclusion in other projects
- [ ] Provide RDRAND as stream
- [ ] Allow mixing with other random number generators to strengthen randomness.
