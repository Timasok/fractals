# Research topic
Using intrinsic functions for optimization.

# Algorithm and software tools

Here is a picture of Mandelbrot fractal created by our program.

![Mandelbrot](img/Mandelbrot_set.png)

This algorithm is often used to estimate the computational speed of hardware.

Note:
SFML is used as a graphics library.

## Optimization results

What kinds of optimization were used in this work?
* SIMD-instructions, such as Intel SSE intrinsics.
* Compiler optimization flags such as -O2, -O3, -Ofast.

Note:
Our CPU(intel core i3) supports SSE and AVX2 intrinsics. We used 128-bit arrays.//TODO

We measured FPS of our algorithm using
>sf::Clock 

It is relevant to examine FPS in different computation modes. Here are the iterations of each mode:
1. Calculate the pixels of the picture.
2. Calculate the pixels of the picture and display them.
3. Repeatedly calculate the pixels of the picture and display them once.


The table below shows the FPS measured for different optimization modes. 

After various measurements we can get the following statistics below. (O-flags, and display modes). the main values at this table are below.

| Computation modes | No flags    |     -O2     |     -O3     |     -Ofast    |
| :---------------: | :----------:| :---------: | :---------: | :----------:  |
|    1 + no_sse     | * 6.15 | 1x | 11.1 | 1.8x | 11.2 | 1.8x |  11.6  | 1.9x |
|    2 + no_sse     |   1.43 | 1x | 1.81 | 1.8x | 1.77 | 1.8x |  1.65  | 1.8x |
|    1 + sse        |   8.62 | 1x | 39.6 | 1.8x | 40.3 | 1.8x | **42.6 | 1.8x |
<!-- | sse + vid    |   1.69   | 1.85 |  2.01  | 2.14   | -->

We can conclude that compiler optimizations together with SIMD-instructions make it possible to achieve acceleration by 7 times.
We can also verify the slowness of my chosen method of drawing (display every pixel in cycle).

# Control

If you want to run this program at your pc, you will need to know the control of this program.

* Escape - exit from current process

* \= - zoom in

* \- - zoom out

* arrows (← → ↑ ↓) - moving the camera