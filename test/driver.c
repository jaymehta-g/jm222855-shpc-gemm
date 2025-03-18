#include "assignment3.h"

int main(int argc, char *argv[])
{
	int first, last, inc, nrepeats;
    
    int err = get_args( argc, argv, &nrepeats, &first, &last, &inc );
    if ( err != 0 ) return 1;
    	
	// test_gemm(nrepeats, first, last, inc);
    double A[] = {1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3};
    int k = 3;
    double B[] = {1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6};
    double C[8*6];

    memset(C, 0, 8*6*sizeof(double));

    mkernel(A, B, C, k);

    for (int i = 0; i < 8*6; i++)
    {
        printf("%lf, \n", C[i]);
    }
}
