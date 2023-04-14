# Mandelbrot

This project is a work on optimization using SSE and AVX intrinsics. The algorithm used for this project is Mandelbrot fractal.

The project is written on C++ using SFML library. 

![Mandelbrot](img/Mandelbrot_set.png)

## Optimization results

We display pixels on the screen in a loop point by point. That's why the drawing process slowed down SSE optimizations. 

What is a SSE optimization? 
>A non-compiler optimization where we replace simple operations with inline functions. Inline functions turn into CPU instructions. Usually they are used to vectorize and parallelize repeatable calculations.  

In this alghoritm we group pixels by 4 32-bit chunks and calculate their colours simultaneously.
This CPU supports Intel SSE and AVX-2 intrinsics.

After various measurements we can get the following statistics below. (O-flags, and display modes). the main values at this table are: ...

| Optimization |        | -O2  |  -O3   | -Ofast |
| :----------: | :--:   | :--: | :----: | :----: |
|    no_sse    | [6.15] | 11.1 |  11.2  | 11.6   |
| no_sse + vid | 1.43   | 1.81 |  1.77  | 1.65   |
| sse 128-bit  | 8.62   | 39.6 |  40.3  | [42.6] |
| sse + vid    | 1.69   | 1.85 |  2.01  | 2.14   |

We can conclude that compiler optimizations together with SIMD-instructions makes it possible to achieve acceleration by 7 times.
We can also verify the slowness of my chosen method of drawing (display every pixel in cycle).

# Control

If you want to run this program at your pc, you will need to know the control of this program.

* Escape - exit from current process

* \= - zoom in

* \- - zoom out

* arrows (← → ↑ ↓) - moving the camera