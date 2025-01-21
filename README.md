

# The drwslib.
Drws is Welsh for door and D is for draw.
Important note, this project is in C, there is no C++, but I would like to add support for it to work in C++.
The point of this library is to be the most cross platform library ever, as much as possible. If it has a screen I want to support it, (not sayong I will). It is a gorup of single header librarys with as few dependancies as possible, d.h has one optional dependacy on stdlib.h.
The collection of libraries are drwslib, d.h and devents.h are the core of drwslib. Everything in platform is for platform specific input and output.
You can use drwslib to make programs, including games. It is similar to SDL, but not nearly as good.

# d.h
d.h is the core of drwslib. 
This handles graphics. You can create and free surfaces, fill rectangles, scale copy part of one surface to part of another, use stb_image to load iamges.
You can use d.h by itself which you may want to do, it would mean you can't output to a display or take event input. It would mean the library only needs stdlib.h which you can turn off and redefine calloc and free.
d.h has another optional dependancy that is turned off by default, stb_image.h. It can be used to load images onto a surface but it doesn't save them.

# devents.h
This is a single header file library for taking inputs, so far only from the mouse.
This library gives usful event functions and even has an event queue, but it does not take events itself from the device. Instead it has a D_CauseEvent() function which can be used by platform librarys like sdld.h, that way it can recive events without having any platform specific code at all!
This library can be used by itself and only uses stdlib.h which can be turned of like d.h (you would have to redefine calloc and free).

# Supported platforms
Because d.h can't output to a display, there are platform specific header files (so far just one works) which let you output and input with the display, mouse (so far just the display and mouse). Keybaord input is on the way.

In the platfom folder there is:
- sdld.h
  - A working single header file library, it uses SDL2 for display and input.
- ndsd.h
  - An unfinished (not working yet) single header library that is on the way for the DS using nds.h.

The idea is that all the code for input and output on a platform is in a single header in the platform folder. That way the core d.h and devents.h are free to have as few dependancies as possible.
I also want to add more platforms like IPOD, PSP. Who knows if that will happen, I want it to though.

# Examples
So far there is one example of drwslib being used.
## CerialBoxSnow
https://github.com/tallHouse64/CerealBoxSnow

It uses an older version of the library and needs updating, plus more features but it works! 
I'm very happy with how it turned out.

