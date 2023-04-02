#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cassert>
// #include "./AppUtils.h"

#include "fractal.h"

const int EPS        = 0.0001;
static float scale   = 1;                                        //number of pixels in 1 rectangle
static int X_shift   = 0;
static int Y_shift   = 0;
static int shift_val = 10;

int main()
{
    RenderWindow window(VideoMode(Mandb_Initial.w_width, Mandb_Initial.w_height), "Mandelbrot");

    Uint8 pixels[4*Mandb_Initial.w_width*Mandb_Initial.w_height] = {};

    Clock clock;

    Image image;
    image.create(Mandb_Initial.w_width, Mandb_Initial.w_height, pixels);
    Texture texture;
    Sprite sprite(texture);

    float lastTime = 0;

    while(window.isOpen())
    {
        window.clear();
        HandleKey(window);

        FormMandelbrot(window, pixels);
            
        // Draw_Fractal(window, pixels, sprite, texture);
        window.display();

        GetFPS(clock, lastTime);
    }

    return 0;
}

float GetFPS(Clock &clock, float lastTime)
{
    float currentTime = clock.restart().asSeconds();
    float fps = 1.f / (currentTime - lastTime);
    printf("FPS = %g\n", fps);

    lastTime = currentTime;
    
    return fps;
}

Color GetColor(int c)
{
#ifdef GREEN          
            Color col = Color(100, 100, 100, 255);

            if (c != Mandb_Initial.N_max)
            {
                col = Color(144*c, 255 - c, abs(101 - c), c*255);
            }
#elif defined BLUE
            Color col = Color(0, 0, 0, 0);

            if (c != Mandb_Initial.N_max)
            {
                col = Color(5*c, c, 255 - 12*c, 255);
            }
#else
            Color col = Color(255, 255, 255, c);

#endif
    return col;
}

int HandleKey(RenderWindow &window)
{
    Event event;
    while (window.pollEvent(event))
    {
        // "close requested" event: we close the window
        if(event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Escape)
            {
                window.close(); 
            
            } else if(event.key.code == Keyboard::Equal)//+
            {
                scale/=1.25;
                // printf("new scale = %g\n", scale);
            
            } else if(event.key.code == Keyboard::Dash)//-
            {
                scale*=1.25;
                // printf("new scale = %g\n", scale);
            
            } else if(event.key.code == Keyboard::Left)
            {
                X_shift-=(int)(shift_val*scale);

            } else if(event.key.code == Keyboard::Right)
            {
                X_shift+=(int)(shift_val*scale);
            } else if(event.key.code == Keyboard::Up)
            {
                Y_shift-=(int)(shift_val*scale);
            } else if(event.key.code == Keyboard::Down)
            {
                Y_shift+=(int)(shift_val*scale);
            }
        }

        if (event.type == Event::Closed)
            window.close();
    }

    return 0;
}

#ifdef NO_SSE

int FormMandelbrot(RenderWindow &window, Uint8 *pixels)
{
    RectangleShape piece = RectangleShape(Vector2f(1/scale, 1/scale));

    int yi = 0;
    for (; yi < Mandb_Initial.w_height; yi++)
    {
        float Y0 = Mandb_Initial.y_min + (Y_shift+yi)*Mandb_Initial.dy*scale;

        int xi = 0;
        for(; xi < Mandb_Initial.w_width; xi++)
        {
            // pixels[xi*yi] = RectangleShape(Vector2f(1, 1));

            float X0 = Mandb_Initial.x_min + (X_shift + xi)*Mandb_Initial.dx*scale;

            float X  = X0;
            float Y  = Y0; 

            float R2 = X*X + Y*Y;

            int c = 0;
            // while (c < Mandb_Initial.N_max && R2 < Mandb_Initial.R_max2)
            while (c < Mandb_Initial.N_max && R2 - Mandb_Initial.R_max2 < EPS)
            {
                float X2  = X*X;
                float Y2  = Y*Y;
                float XY  = X*Y + X*Y; 

                X = X2 - Y2 + X0;
                Y = XY + Y0;

                R2 = X2 + Y2;

                c++;
            }

            piece.setPosition((float) xi, (float) yi);

            piece.setFillColor(GetColor(c));
            window.draw(piece);

        }
    }   

    return 0;
}

#elif defined INLINE

#include "inline.h"
const int N_BITES = 8;

int FormMandelbrot(RenderWindow &window)
{
    int point_vector[N_BITES] = {};
    float R2_max[N_BITES]     = Mandb_Initial.R_max2;                           //__m256 _mm256_set1_ps (float a)

    int yi = 0;
    for (; yi < Mandb_Initial.w_height; yi+=N_BITES)
    {
        float Y0[N_BITES] = {yi, yi+1, yi+2, yi+3, yi+4, yi+5, yi+6, yi+7};     // __m256 _mm256_setr_m128 (__m128 lo, __m128 hi)
              Y0[i] *= Mandb_Initial.dy*scale;                                  // __m256 _mm256_mul_ps (__m256 a, __m256 b)
              Y0[i]  +=(Mandb_Initial.y_min + Y_shift*Mandb_Initial.dy*scale);  // __m256 _mm256_add_ps (__m256 a, __m256 b)

        int xi = 0;
        for(; xi < Mandb_Initial.w_width; xi+=N_BITES)
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
            do{
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

            // for(int i = 0; i < N_BITES){

            // piece.setPosition((float) xi, (float) yi);

            // piece.setFillColor(GetColor(c));
            // window.draw(piece);
            // }
        }
    }   

}
#elif defined SSE

#include <immintrin.h>
    __m256 quad_vector = _mm256_set_ps(7.f, 6.f, 5.f, 4.f, 3.f, 2.f, 1.f, 0.f);

#endif

int Draw_Fractal(RenderWindow &window, Uint8 *pixels, Sprite &sprite, Texture &texture)
{
    texture.update(pixels, Mandb_Initial.w_width, Mandb_Initial.w_height, 0, 0);
    sprite.setTexture(texture);

    window.draw(sprite);

    return 0;
}

int Test(RenderWindow &window)
{
    RectangleShape piece = RectangleShape(Vector2f(1 , 1));

    for(int counter = 0; counter < 1000; counter++)
    {
        piece.setPosition((float) counter, (float) counter);

        piece.setFillColor(Color(255, 155, 255, 255));

        printf("(%d, %d)\n", counter, counter);

        window.draw(piece);
    }

    return 0;
}