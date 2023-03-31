#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cassert>
// #include "./AppUtils.h"

#include "NO-SSE.h"

const int EPS        = 0.0001;
static float scale   = 1;                                        //number of pixels in 1 rectangle
static int X_shift   = 0;
static int Y_shift   = 0;
static int shift_val = 10;

int main()
{
    RenderWindow window(VideoMode(Mandb_Initial.w_width, Mandb_Initial.w_height), "Mandelbrot");

    // Uint8 pixels[4*Mandb_Initial.num_pixels] = {};

    // Image img;
    // img.create(Mandb_Initial.w_width, Mandb_Initial.w_height, pixels);
    // texture.loadFromImage(img);

    Clock clock;

    Texture texture;
    Sprite sprite(texture);

    float lastTime = 0;
    while(window.isOpen())
    {
        window.clear();
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
                    X_shift-=shift_val;
                } else if(event.key.code == Keyboard::Right)
                {
                    X_shift+=shift_val;
                } else if(event.key.code == Keyboard::Up)
                {
                   Y_shift-=shift_val;
                } else if(event.key.code == Keyboard::Down)
                {
                    Y_shift+=shift_val;
                }
            }

            if (event.type == Event::Closed)
                window.close();
        }
    
        FormMandelbrot(window);
        GetFPS(clock, window, lastTime);

        window.display();
    }

    return 0;
}

int FormMandelbrot(RenderWindow &window)
{
    // Vector2 size = Vector2((float)Mandb_Initial.w_width, (float)Mandb_Initial.w_height);
    // RectangleShape screen = RectangleShape();
    // screen.setSize(size);

    // RectangleShape piece = RectangleShape(Vector2f(1/scale, 1/scale));
    RectangleShape piece = RectangleShape(Vector2f(1, 1));

    int yi = 0;
    for (; yi < Mandb_Initial.w_height; yi++)
    {
        float Y0 = Mandb_Initial.y_min + (Y_shift+yi)*Mandb_Initial.dy*scale;

        int xi = 0;
        for(; xi < Mandb_Initial.w_width; xi++)
        {
            float X0 = Mandb_Initial.x_min + (X_shift + xi)*Mandb_Initial.dx*scale;

            float X  = X0;
            float Y  = Y0; 

            float R2 = X*X + Y*Y;
            int c = 0;

            while (c < Mandb_Initial.N_max && R2 < Mandb_Initial.R_max2)
            // while (c < Mandb_Initial.N_max && R2 - Mandb_Initial.R_max2 < EPS)
            {
                float X2  = X*X;
                float Y2  = Y*Y;
                float XY  = X*Y + X*Y; 

                X = X2 - Y2 + X0;
                Y = XY + Y0;

                R2 = X2 + Y2;

                c++;
            }
            
            Color col = Color(100, 100, 100, 255);

            if (c != Mandb_Initial.N_max)
            {
                col = Color(144*c, 255 - c, abs(101 - c), c*255);
            }

            piece.setPosition((float) xi, (float) yi);

            piece.setFillColor(col);
            // piece.setFillColor();

            // printf("(%d, %d)\n", xi, yi);

            window.draw(piece);

        //extract into separate function
            // pixels[4*xi*yi+0] = col.r;
            // pixels[4*xi*yi+1] = col.g;
            // pixels[4*xi*yi+2] = col.b;
            // pixels[4*xi*yi+3] = col.a;

        }
    }   

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

float GetFPS(Clock &clock, RenderWindow &window, float lastTime)
{
    float currentTime = clock.restart().asSeconds();
    float fps = 1.f / (currentTime - lastTime);
    printf("FPS = %g\n", fps);

    lastTime = currentTime;
    
    return fps;
}

int Draw_Fractal(Uint8 * pixels, Sprite *sprite)
{

    return 0;
}

int Check_Window(Window *window, Sprite *sprite)
{
//     while((*window).isOpen())
//     {
//         (*window).clear();

//         (*window).draw(sprite);
//         (*window).display();

//         Event event;
//         while ((*window).pollEvent(event))
//         {
//             if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
//                 (*window).close(); 
//             // "close requested" event: we close the window
//             if (event.type == Event::Closed)
//                 (*window).close();
//         }
//     }

    return 0;
}