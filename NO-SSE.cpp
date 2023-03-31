#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <cassert>
// #include "./AppUtils.h"

#include "NO-SSE.h"

const int EPS = 0.0001;
static float scale = 1;                                        //number of pixels in 1 rectangle

int main()
{
    RenderWindow window(VideoMode(Mandb_Initial.w_width, Mandb_Initial.w_height), "Mandelbrot");

    // Uint8 pixels[4*Mandb_Initial.num_pixels] = {};

    // Image img;
    // img.create(Mandb_Initial.w_width, Mandb_Initial.w_height, pixels);
    // texture.loadFromImage(img);

    Texture texture;
    Sprite sprite(texture);

    while(window.isOpen())
    {
        window.clear();

        // window.draw(sprite);
        Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window

            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                window.close(); 
            if (event.type == Event::Closed)
                window.close();
        }
    
        // Test(window);
        FormMandelbrot(window);
        window.display();
    }

    return 0;
}

int FormMandelbrot(RenderWindow &window)
{
    // Vector2 size = Vector2((float)Mandb_Initial.w_width, (float)Mandb_Initial.w_height);
    // RectangleShape screen = RectangleShape();
    // screen.setSize(size);

    RectangleShape piece = RectangleShape(Vector2f(1 , 1));

    int yi = 0;
    for (; yi < Mandb_Initial.w_height; yi++)
    {
        float Y0 = Mandb_Initial.y_min + yi*Mandb_Initial.dy;

        int xi = 0;
        for(; xi < Mandb_Initial.w_width; xi++)
        {
            float X0 = Mandb_Initial.x_min + xi*Mandb_Initial.dx;

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
