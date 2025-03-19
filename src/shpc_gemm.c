#include "assignment3.h"
#include <immintrin.h>

#define min(a,b) ((a) < (b) ? (a) : (b))

// Computed based on number of vector registers available
#define MR 8
#define NR 6

// Computed based on L1 and L2 cache sizes
#define MC 608
#define NC 1296
#define KC 402

// rsMAT and csMAT must be in scope
#define RC(MAT, ROW, COL) MAT[ROW * rs##MAT + COL * cs##MAT]

#define UKERN_LOOP(COL) \
        a_top = _mm256_loadu_pd(&RC(A, 0, p)); \
        a_bot = _mm256_loadu_pd(&RC(A, 4, p)); \
        b_broadcast = _mm256_broadcast_sd(&RC(B, p, COL)); \
        c_0_ ## COL = _mm256_fmadd_pd(a_top, b_broadcast, c_0_ ## COL); \
        c_1_ ## COL = _mm256_fmadd_pd(a_bot, b_broadcast, c_1_ ## COL);

// multiply k by MR on NR by k
// expects column-major A and row-major B
// excepts column major C
// A is MR x k, B is k x NR
void mkernel(double *A, int rsA, int csA, double* B, int rsB, int csB, double* C, int rsC, int csC, int k) {
    __m256d c_0_0 = _mm256_loadu_pd(&RC(C, 0, 0));
    __m256d c_0_1 = _mm256_loadu_pd(&RC(C, 0, 1));
    __m256d c_0_2 = _mm256_loadu_pd(&RC(C, 0, 2));
    __m256d c_0_3 = _mm256_loadu_pd(&RC(C, 0, 3));
    __m256d c_0_4 = _mm256_loadu_pd(&RC(C, 0, 4));
    __m256d c_0_5 = _mm256_loadu_pd(&RC(C, 0, 5));
    __m256d c_1_0 = _mm256_loadu_pd(&RC(C, 4, 0));
    __m256d c_1_1 = _mm256_loadu_pd(&RC(C, 4, 1));
    __m256d c_1_2 = _mm256_loadu_pd(&RC(C, 4, 2));
    __m256d c_1_3 = _mm256_loadu_pd(&RC(C, 4, 3));
    __m256d c_1_4 = _mm256_loadu_pd(&RC(C, 4, 4));
    __m256d c_1_5 = _mm256_loadu_pd(&RC(C, 4, 5));

    for (int p = 0; p < k; p++)
    {
        __m256d b_broadcast;
        __m256d a_top;
        __m256d a_bot;

        UKERN_LOOP(0);
        UKERN_LOOP(1);
        UKERN_LOOP(2);
        UKERN_LOOP(3);
        UKERN_LOOP(4);
        UKERN_LOOP(5);
    }

    _mm256_storeu_pd(&RC(C,0,0), c_0_0);
    _mm256_storeu_pd(&RC(C,0,1), c_0_1);
    _mm256_storeu_pd(&RC(C,0,2), c_0_2);
    _mm256_storeu_pd(&RC(C,0,3), c_0_3);
    _mm256_storeu_pd(&RC(C,0,4), c_0_4);
    _mm256_storeu_pd(&RC(C,0,5), c_0_5);
    _mm256_storeu_pd(&RC(C,4,0), c_1_0);
    _mm256_storeu_pd(&RC(C,4,1), c_1_1);
    _mm256_storeu_pd(&RC(C,4,2), c_1_2);
    _mm256_storeu_pd(&RC(C,4,3), c_1_3);
    _mm256_storeu_pd(&RC(C,4,4), c_1_4);
    _mm256_storeu_pd(&RC(C,4,5), c_1_5);
}

void shpc_dgemm( int m, int n, int k,                                            
                    double *A, int rsA, int csA,                                
                    double *B, int rsB, int csB,                                
                    double *C, int rsC, int csC )
{
    if (m % MR != 0 || n % NR != 0)
    {
        printf("gemm not implemented for arbitrary size yet\n");
        exit(1);
    }
    double* Apack = malloc(MC * KC * sizeof(double));
    double* Bpack = malloc(KC * NC * sizeof(double));
    for (int i_nc = 0; i_nc < n; i_nc += NC)
    {
        int amnt_nc = min(NC, n - i_nc);
        for (int i_kc = 0; i_kc < k; i_kc += KC)
        {
            int amnt_kc = min(KC, k - i_kc);
            int rsBpack = amnt_nc;
            int csBpack = 1;
            double* Bslice = &RC(B, i_kc, i_nc);
            for (int i = 0; i < amnt_kc; i++)
            {
                for (int j = 0; j < amnt_nc; j++)
                {
                    RC(Bpack, i, j) = Bslice[i * rsB + j * csB];
                }
                
            }
            for (int i_mc = 0; i_mc < m; i_mc += MC)
            {
                int amnt_mc = min(MC, m - i_mc);
                int rsApack = 1;
                int csApack = amnt_mc;
                double* Aslice = &RC(A, i_mc, i_kc);
                for (int i = 0; i < amnt_mc; i++)
                {
                    for (int j = 0; j < amnt_kc; j++)
                    {
                        RC(Apack, i, j) = Aslice[i * rsA + j * csA];
                    }
                    
                }
                for (int i_nr = 0; i_nr < amnt_nc; i_nr += NR)
                {
                    for (int i_mr = 0; i_mr < amnt_mc; i_mr += MR)
                    {
                        double* Cblock = &RC(C, i_mc + i_mr, i_nc + i_nr);
                        double* Ablock = &RC(Apack, i_mr, 0);
                        double* Bblock = &RC(Bpack, 0, i_nr);
                        mkernel(Ablock, rsApack, csApack, Bblock, rsBpack, csBpack, Cblock, rsC, csC, amnt_kc);
                    }
                    
                }
            }
        }
        
    }
    
}   
