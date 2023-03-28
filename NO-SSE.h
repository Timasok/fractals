#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;

int Calculate(Uint8 * pixels, int num_pixels, int current);
int Draw_Fractal(Uint8 * pixels, int num_pixels, Sprite *sprite);
int Check_Window(Window *window, Sprite *sprite);