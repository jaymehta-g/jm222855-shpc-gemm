#include "assignment3.h"

int main(int argc, char *argv[])
{
	int first, last, inc, nrepeats;
    
    int err = get_args( argc, argv, &nrepeats, &first, &last, &inc );
    if ( err != 0 ) return 1;


    double* A = malloc(8*sizeof(double));
    double* B = malloc(6*sizeof(double));
    double* Cmine = malloc(48*sizeof(double));
    double* Ctheirs = malloc(48*sizeof(double));

	bli_drandm( 0, BLIS_DENSE, 8, 1, A, 1, 8);
	bli_drandm( 0, BLIS_DENSE, 1, 6, B, 6, 1);
	// bli_drandm( 0, BLIS_DENSE, 8, 6, Cmine, 1, 8);
    memset(Cmine, 0, 48*sizeof(double));
    memcpy(Ctheirs, Cmine, 8*6*sizeof(double));

    double done = 1.0;
	bli_dgemm( BLIS_NO_TRANSPOSE, BLIS_NO_TRANSPOSE,  
				8, 6, 1, &done, 
				A, 1, 8, 
				B, 6, 1, 
				&done, Ctheirs, 1, 8 );	
    mkernel(A, B, Cmine, 1, 8, 1);

    for (int i = 0; i < 48; i++)
    {
        // printf("%f vs %f\n", Cmine[i], Ctheirs[i]);
        printf("diff %f\n", Cmine[i] - Ctheirs[i]);
    }

}
