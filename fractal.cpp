#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cassert>
#include <unistd.h>
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
                X_shift+=(int)(shift_val*scale);

            } else if(event.key.code == Keyboard::Right)
            {
                X_shift-=(int)(shift_val*scale);
            } else if(event.key.code == Keyboard::Up)
            {
                Y_shift+=(int)(shift_val*scale);
            } else if(event.key.code == Keyboard::Down)
            {
                Y_shift-=(int)(shift_val*scale);
            }
        }

        if (event.type == Event::Closed)
            window.close();
    }

    return 0;
}

#ifndef SSE

int FormMandelbrot(RenderWindow &window, Uint8 *pixels)
{
    // RectangleShape piece = RectangleShape(Vector2f(1/scale, 1/scale));
    RectangleShape piece = RectangleShape(Vector2f(1, 1));

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

            volatile int c = 0;
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

#ifndef NO_VID
            piece.setPosition((float) xi, (float) yi);

            piece.setFillColor(GetColor(c));
            window.draw(piece);
#endif
        }
    }   

    return 0;
}

#else

#include <immintrin.h>

const int N_BITES = 8;

int FormMandelbrot(RenderWindow &window, Uint8 *pixels)
{
    // RectangleShape piece = RectangleShape(Vector2f(1/scale, 1/scale));
    RectangleShape piece = RectangleShape(Vector2f(1, 1));

    __m256 R2_max = _mm256_set1_ps(Mandb_Initial.R_max2);                                       //__m256 _mm256_set1_ps (float a)

    int yi = 0;
    for (; yi < Mandb_Initial.w_height; yi++)
    {
        __m256 Y_SHIFT = _mm256_set1_ps(Mandb_Initial.y_min + Y_shift*Mandb_Initial.dy*scale);
        __m256 DY = _mm256_set1_ps(Mandb_Initial.dy*scale);
        __m256 Y0 = _mm256_set1_ps(yi);                // __m256 _mm256_setr_m128 (__m128 lo, __m128 hi)
         Y0 = _mm256_mul_ps(Y0, DY);                                                      // __m256 _mm256_mul_ps (__m256 a, __m256 b)
         Y0 = _mm256_add_ps(Y0, Y_SHIFT);                                                 // __m256 _mm256_add_ps (__m256 a, __m256 b)

        int xi = 0;
        for(; xi < Mandb_Initial.w_width; xi+=N_BITES)
        {
            __m256 X_SHIFT = _mm256_set1_ps(Mandb_Initial.x_min + X_shift*Mandb_Initial.dx*scale);
            __m256 DX = _mm256_set1_ps(Mandb_Initial.dx*scale);
            __m256 X0 = _mm256_set_ps(xi, xi+1, xi+2, xi+3, xi+4, xi+5, xi+6, xi+7);                // __m256 _mm256_setr_m128 (__m128 lo, __m128 hi)
             X0 = _mm256_mul_ps(X0, DX);                                                      // __m256 _mm256_mul_ps (__m256 a, __m256 b)
             X0 = _mm256_add_ps(X0, X_SHIFT);                                                 // __m256 _mm256_add_ps (__m256 a, __m256 b)

                                                                                                    //__m256 _mm256_set1_ps (float a)                                                                                
            __m256 X = X0;                                                                          //__m256 _mm256_set1_ps (float a)
            __m256 Y = Y0; 

            __m256 c   = _mm256_setzero_ps();                                                //__m256 _mm256_setzero_ps (void)
            __m256 cmp = _mm256_set1_ps(1);                                              // __m256i _mm256_set1_epi32 (int a) - set 1
            
            // __m256i N = _mm256_set1_epi32(Mandb_Initial.N_max);                      //__m256 _mm256_set1_ps (float a)
            // int mask = 1; 
                                                                                    //__m256i _mm256_blend_epi32 (__m256i a, __m256i b, const int imm8)
            for(int i = 0; i < Mandb_Initial.N_max; i++)
            {
                __m256 X2 = _mm256_mul_ps(X, X);                                   //__m256 _mm256_mul_ps (__m256 a, __m256 b)
                __m256 Y2 = _mm256_mul_ps(Y, Y);                                   //__m256 _mm256_mul_ps (__m256 a, __m256 b)
                __m256 R2 = _mm256_add_ps(X2, Y2);                                 //__m256 _mm256_add_ps (__m256 a, __m256 b)

                 cmp = _mm256_cmp_ps (R2, R2_max, EPS);                                                        
                                                                                   //__m256 _mm256_cmp_ps (__m256 a, __m256 b, const int imm8)
                int mask  =_mm256_movemask_ps (cmp);                               //int _mm256_movemask_ps (__m256 a)                                 
                // printf("%b", mask);

                if (!mask)
                    break;

                __m256 XY = _mm256_mul_ps(X, Y); 
                 XY = _mm256_add_ps (XY, XY);                                 // __m256 _mm256_add_ps (__m256 a, __m256 b)

                 X = _mm256_sub_ps (X2, Y2);                                  //__m256 _mm256_sub_ps (__m256 a, __m256 b)
                 X = _mm256_add_ps (X, X0);                                   //__m256 _mm256_add_ps (__m256 a, __m256 b)
                 Y = _mm256_add_ps (XY, Y0);
                                                                                    //__m256 _mm256_add_ps (__m256 a, __m256 b)
                 c = _mm256_add_ps(c, cmp);                                   //int _mm256_movemask_ps (__m256 a) 
            
                // for (int counter = 0; counter < N_BITES; counter++)
                // {
                //     float c_what = ((float *)&c)[N_BITES - counter];
                //     printf("%f ", c_what);
                // }
                // printf("\n");
                // sleep(1);
            } ;

#ifndef NO_VID

            for (int counter = 0; counter < N_BITES; counter++)
            {
                float c_single = ((float *)&c)[N_BITES - counter];

                piece.setPosition((float) (xi+counter), (float) (yi));

                piece.setFillColor(GetColor((int)c_single));
                window.draw(piece);
            }
#endif

        }
    }   


    return 0;   
}

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