

# The drws-lib.
<img src="https://raw.githubusercontent.com/tallHouse64/drws-lib/refs/heads/main/drws-lib.png" width="210" height="210" alt="The logo for the drws-lib library." />

Drws is Welsh for door and D is for draw.

The point of this library is to be the most cross platform library ever, as much as possible. If it has a screen I want to support it, (not saying I will).

Important note, this project is in C, there is no C++, but I would like to add support for it to work in C++.

Drws-lib is a collection of single header libraries. d.h, devents.h and dplatform.h are the core of drwslib. They have as few dependencies as possible. So far the core only uses stdlib.h, which can be turned off.

Drws-lib also has platform specific code separated from the core in the platform folder. One header file in the platform folder supports one platform sdld.h supports sdl2, ndsd.h supports nds (DS support is not working yet). Note that dplatform.h is core, but right now it is in the platform folder.

You can use drwslib to make programs, including games. It is similar to SDL, but not nearly as good.

Documentation can be found in the header file libraries themselves. You can use ctrl + F to find any function, structure, enum and read it's documentation above it. Note that there may be more than one use of the name you search for, you are looking for the definition which starts at the farthest left margin.

# d.h
d.h is part of the drwslib core.

This handles graphics. You can create and free surfaces, fill rectangles, scale copy part of one surface to part of another with scaling, use stb_image to load images.

So far there are six blendmodes supported, here are screenshots of them being tested.

<img src="https://raw.githubusercontent.com/tallHouse64/drws-lib/refs/heads/main/surfcopyscale-blendmode-test-screenshot-1.png" alt="A screenshot showing the first four supported blendmodes, no blending, normal, additive and multiplication blending."/>

<img src="https://raw.githubusercontent.com/tallHouse64/drws-lib/refs/heads/main/surfcopyscale-blendmode-test-screenshot-2.png" alt="A screenshot showing the fith and sixth supported blendmodes, subtraction and division blending."/>

You can use d.h by itself which you may want to do, it would mean you can do graphics operations on the CPU with very little dependencies. You would not be able to take event input using drws-lib without devents.h, dplatform.h and at least one platform library.

d.h only relies on stdlib.h, this can be turned off if calloc and free are redefined.

d.h has another optional dependency that is turned off by default, stb_image.h. It can be used to load images onto a surface but it doesn't save them. This can be turned on by adding the line #define D_ALLOW_STB_IMAGE before implementing the library.

This library can be implemented in your project by adding the line #define D_IMPLEMENTATION before the line #include"d.h". You need to make sure that the library is only implemented in one file, every other file would have the line #include"d.h" without #define D_IMPLEMENTATION.

# devents.h
This is a single header file library for taking inputs, so far from the mouse and keyboard.

This library gives useful event functions and even has an event queue, but it does not take events itself from the device. Instead it has a D_CauseEvent() function which can be used by platform libraries like sdld.h, that way it can receive events without having any platform specific code at all!

This library can be used by itself and only uses stdlib.h which can be turned of like d.h (you would have to redefine calloc and free).

devents.h now supports custom events, use D_RegisterCustomEvent() to make your own event.type number.

This library can be implemented in your project using #define DEVENTS_IMPLEMENTATION

# dplatform.h
This library is part of the core, but it is only function prototypes that are implemented by a platform library. This way the the platform libraries don't have to have a copy of the prototypes which would be unnecessary data duplication which can lead to bugs.

# Supported platforms
Because d.h can't output to a display and devents.h can't receive events by itself, there are platform specific header files which let you output and input with the display, mouse and keyboard.

These libraries can be implemented in your project using #define D_PLATFORM_IMPLEMENTATION

In the platform folder there is:
- sdld.h
  - A working single header file library, it uses SDL2 for display and input.
- ndsd.h
  - An unfinished (not working yet) single header library that is on the way for the DS using nds.h.

The idea is that all the code for input and output on a platform is in a single header in the platform folder. That way the core d.h, devents.h and dplatform.h are free to have as few dependencies as possible.

I also want to add more platforms like IPOD, PSP. Who knows if that will happen, I want it to though.

# Examples
So far there is one example of drwslib being used.
## CerialBoxSnow
https://github.com/tallHouse64/CerealBoxSnow

It uses an older version of the library and needs updating, plus more features but it works! 

I'm very happy with how it turned out.

