// Name: Kernel_Call.cu
// Author: Cody R. Drisko (crdrisko)
// Date: 06/22/2019-15:30:42
// Description: A complete "Hello, World!" script run on the device

#include <stdio.h>
#include "cuda_runtime.h"

__global__ void kernel ( void ) {}

int main ( void )
{
	kernel <<< 1, 1 >>> ( );
	printf ( "Hello, World!\n" );
	return 0;
}
