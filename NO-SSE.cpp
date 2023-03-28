#include <stdlib.h>
#include <time.h>
#include <cassert>
// #include "./AppUtils.h"

#include "NO-SSE.h"

// using namespace sf;

const int w_width   = 800;
const int w_height  = 600;
const int num_pixels = w_height*w_width;

int main()
{
    Uint8 pixels[4*num_pixels] = {};


    RenderWindow window(VideoMode(w_width, w_height), "Mandelbrot");        //updatewindow

    for (int counter = 0; counter <= num_pixels*4; counter+=4)
    {
        Calculate(pixels, num_pixels, counter);
        // texture.update(pixels);
        // Check_Window(&window, &sprite);

    }

    Image img;
    img.create(w_width, w_height, pixels);

    Texture texture;
    texture.loadFromImage(img);
    Sprite sprite(texture);

    while(window.isOpen())
    {
        window.clear();

        window.draw(    sprite);
        window.display();

        Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window

            if(event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
                window.close(); 
            if (event.type == Event::Closed)
                window.close();
        }
    }

    return 0;
}

int Calculate(Uint8 * pixels, int num_pixels, int current)
{
    int c = current%256;

    Color color(255-c, (c%2)*64, c);

    pixels[current] = (Uint8) color.r;
    pixels[current+1] = (Uint8) color.g;
    pixels[current+2] = (Uint8)color.b;
    pixels[current+3] = (Uint8)color.r;

    return 0;
}

int Draw_Fractal(Uint8 * pixels, int num_pixels, Sprite *sprite)
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