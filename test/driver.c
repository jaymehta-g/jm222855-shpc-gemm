#include "assignment3.h"

int main(int argc, char *argv[])
{
	int first, last, inc, nrepeats;
    
    int err = get_args( argc, argv, &nrepeats, &first, &last, &inc );
    if ( err != 0 ) return 1;

    test_gemm(  nrepeats,  first,  last,  inc);

    // double* A = malloc(8*sizeof(double) * 3);
    // double* B = malloc(6*sizeof(double) * 3);
    // double* Cmine = malloc(48*sizeof(double) * 3);
    // double* Ctheirs = malloc(48*sizeof(double) * 3);

	// bli_drandm( 0, BLIS_DENSE, 8, 3, A, 1, 8);
	// bli_drandm( 0, BLIS_DENSE, 3, 6, B, 1, 6);
	// // bli_drandm( 0, BLIS_DENSE, 8, 6, Cmine, 1, 8);
    // memset(Cmine, 0, 48*sizeof(double) * 3);
    // memcpy(Ctheirs, Cmine, 8*6*sizeof(double) * 3);

    // double done = 1.0;
	// bli_dgemm( BLIS_NO_TRANSPOSE, BLIS_NO_TRANSPOSE,  
	// 			8, 6, 3, &done, 
	// 			A, 1, 8, 
	// 			B, 1, 6, 
	// 			&done, Ctheirs, 1, 8 );	
    // mkernel(A, 1, 8, B, 1, 6, Cmine, 1, 8, 3);

    // for (int i = 0; i < 48 * 3; i++)
    // {
    //     // printf("%f vs %f\n", Cmine[i], Ctheirs[i]);
    //     printf("diff %f\n", Cmine[i] - Ctheirs[i]);
    // }

}
