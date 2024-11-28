
# so_long

Welcome to so_long, a 2D game written in C which runs both on Mac and Linux!

## Requirements

-   A C compiler (such as GCC)
-   on Linux, Libraries: libXext, libX11 are necessary
-   Skip this step on school Pc, as it's allready installed. 
    To install these dependencies on other Linux Pc, run:
    
`sudo apt-get update && sudo apt-get install xorg libxext-dev zlib1g-dev libbsd-dev`

-   on Mac, compiling flags are: -framework OpenGL -framework AppKit

    Makefile will automatically detect OS and set Flags.

    The mlx_destroy_display function is only available on Linux, that's why src/event_linux.c has 1 more line than src/event_mac.c . So that Valgrind will not have any memory leak.

## Installation

1.  Clone the repository to your local machine:

`git clone https://github.com/hu8813/so_long.git` 

2.  Navigate to the repository directory:

`cd so_long` 

3.  Compile the game using the Makefile:

`make` 

This will create an executable file called `so_long`.

## Running the game

To start the game, simply run the executable with a path to map file as parameter:

`make test`  OR  `./so_long maps/map.ber` 

## Controls

-   Use the W A S D keys to move the player character
-   Press the ESC or click (X) to exit

![An example screenshot of so_long](screenshot.png)


## Useful Resources

The MinilibX mlx library is a simple X Window System graphics library that is often used in educational contexts to teach basic graphics programming in C. Here are a few resources that may be helpful for learning about and using the MinilibX mlx library:

-   [42 Docs Minilibx Documentation](https://harm-smits.github.io/42docs/libs/minilibx/introduction.html)
