# A simple ising model implementation (in C)
A simple enough implementation of the ising model in C. The parameters
to the model, such as the size of the board, maximum number of sweeps
to execute, and temperature of the system, is configured through the
`#define` macros at the head of `ising.c`. Yeah, yeah, I'll change it
someday.

The program outputs a series of ~.ppm~ frames that can be piped to a
video encoder such as ~x264~:

``` shell
./ising | x264 --fps 60 -o video.mp4 /dev/stdin
```

Then you get a nice ol' video.
![ising model!](video.gif)
