#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

int Calculate(Uint8 * pixels);
int Draw_Fractal(Uint8 * pixels, Sprite *sprite);
int Check_Window(Window *window, Sprite *sprite);


static struct {

    const int N_max = 10;
    const float R_max = 100.0;
    const float R_max2 = R_max*R_max;

    const int w_width   = 800;
    const int w_height  = 600;
    const int num_pixels = w_height*w_width;

    const float x_max =  2.0;
    const float x_min = -2.0;
    const float y_max =  2.0;
    const float y_min = -2.0;

    float dx = (x_max - x_min)/w_width;
    float dy = (y_max - y_min)/w_height;

} Mandb_Initial;