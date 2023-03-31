#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
// #include <SFML/Rect.hpp>

using namespace sf;

int Test(RenderWindow &window);
int FormMandelbrot(RenderWindow &window);
int Draw_Fractal(Uint8 * pixels, Sprite *sprite);
int Check_Window(Window *window, Sprite *sprite);
float GetFPS(Clock &clock, RenderWindow &window, float lastTime);

static struct {

    const int N_max = 256;
    const float R_max = 10.0;
    const float R_max2 = R_max*R_max;

    // const int w_width   = 800;
    // const int w_height  = 600;

    const int w_width   = 1000;
    const int w_height  = 1000;

    const int num_pixels = w_height*w_width;

    const float x_max =  2.0;
    const float x_min = -2.0;
    const float y_max =  2.0;
    const float y_min = -2.0;

    float dx = (x_max - x_min)/w_width;
    float dy = (y_max - y_min)/w_height;

} Mandb_Initial;