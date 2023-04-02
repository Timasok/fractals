#include <immintrin.h>

int FormMandelbrot(RenderWindow &window)
{
    int point_vector[N_BITES] = {};
                             
    __m256 R2_max =  _mm256_set1_ps (Mandb_Initial.R_max2);                     //float R2_max[N_BITES]     = Mandb_Initial.R_max2;  

    int yi = 0;
    for (; yi < Mandb_Initial.w_height; yi+=N_BITES)
    {
        __m256 Y0 = _mm256_setr_m128 (__m128 lo, __m128 hi);                    // float Y0[N_BITES] = {yi, yi+1, yi+2, yi+3, yi+4, yi+5, yi+6, yi+7};     
        __m256 Y0 =_mm256_mul_ps (__m256 a, __m256 b);                          //       Y0[i] *= Mandb_Initial.dy*scale;                                  
        __m256 Y0 =_mm256_add_ps (__m256 a, __m256 b);                          //       Y0[i]  +=(Mandb_Initial.y_min + Y_shift*Mandb_Initial.dy*scale);  

        int xi = 0;
        for(; xi < Mandb_Initial.w_width; xi += N_BITES)
        {

        float X0[N_BITES] = {xi, xi+1, xi+2, xi+3, xi+4, xi+5, xi+6, xi+7};     // __m256 _mm256_setr_m128 (__m128 lo, __m128 hi)
              X0[i] *= Mandb_Initial.dx*scale;                                  // __m256 _mm256_mul_ps (__m256 a, __m256 b)
              X0[i]  +=(Mandb_Initial.x_min + X_shift*Mandb_Initial.dx*scale);  // __m256 _mm256_add_ps (__m256 a, __m256 b)
                             
                                                                                //__m256 _mm256_set1_ps (float a)                                                                                
            float X[N_BITES]  = X0;                                             //__m256 _mm256_set1_ps (float a)
            float Y[N_BITES]  = Y0; 

            int c[N_BITES] = {};                                                //__m256 _mm256_setzero_ps (void)
            int cmp[N_BITES] = {};                                              // __m256i _mm256_set1_epi32 (int a) - set 1
            
            int N[N_BITES]          = Mandb_Initial.N_max;                      //__m256 _mm256_set1_ps (float a)

            int mask = 1; 
                                                                  //__m256i _mm256_blend_epi32 (__m256i a, __m256i b, const int imm8)
            do {
                float X2[N_BITES]  = X*X;                                           //__m256 _mm256_mul_ps (__m256 a, __m256 b)
                float Y2[N_BITES]  = Y*Y;                                           //__m256 _mm256_mul_ps (__m256 a, __m256 b)
                float R2[N_BITES]  = X2 + Y2;                                       //__m256 _mm256_add_ps (__m256 a, __m256 b)

                set cmp[i]                                                          //__m256 _mm256_cmp_ps (__m256 a, __m256 b, const int imm8)
                mask =                                                              //int _mm256_movemask_ps (__m256 a)                                 
                
                if (!mask)
                    break;

                float XY  = X*Y;                                                    //__m256 _mm256_mul_ps (__m256 a, __m256 b)
                      XY  = XY + X*Y;                                               // __m256 _mm256_add_ps (__m256 a, __m256 b)

                X = X2 - Y2;                                                        //__m256 _mm256_sub_ps (__m256 a, __m256 b)
                X = X + X0;                                                         //__m256 _mm256_add_ps (__m256 a, __m256 b)
                Y = XY + Y0;                                                        //__m256 _mm256_add_ps (__m256 a, __m256 b)

                c = c + cmp;                                                        //__m256i _mm256_add_epi32 (__m256i a, __m256i b)                                                                 //
                N = N - c                                                           //__m256i _mm256_sub_epi32 (__m256i a, __m256i b)
                
                mask<-N                                                             //int _mm256_movemask_ps (__m256 a) 
            } while (!mask );
        }
    }
}