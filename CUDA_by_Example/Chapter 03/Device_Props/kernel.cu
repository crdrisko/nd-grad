// Name: Device_Props.cu
// Author: Cody R. Drisko (crdrisko)
// Date: 06/22/2019-15:45:27
// Description: USing device properties


#include <stdio.h>
#include <driver_types.h>
#include "cuda_runtime.h"
#include "../../common/book.h"

int main ( void )
{
	cudaDeviceProp prop;
	int dev;

	HANDLE_ERROR ( cudaGetDevice ( &dev ) );
	printf ( "ID of current CUDA device: %d\n", dev );

	memset ( &prop, 0, sizeof ( cudaDeviceProp ) );
	prop.major = 1;
	prop.minor = 3;
	HANDLE_ERROR ( cudaChooseDevice ( &dev, &prop ) );
	printf ( "ID of CUDA device closest to revision 1.3: %d\n", dev );
	HANDLE_ERROR ( cudaSetDevice ( dev ) );
}