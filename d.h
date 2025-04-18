
/*
 * The d graphics lib
 *
 * project started Tue 12/11/2024
 *
 * The purpose of this library is to make
 *  gmaes/programs that are very cross platform.
 *  As many platforms as possible, this is the
 *  main goal of the library. Think Windows, Mac,
 *  Linux, NDS, TI calcs, IPOD, PSP. Only Windows
 *  and Linux are tested and work so far. This
 *  way anyone can play games I make no matter
 *  what device they have. This is why the
 *  library is a group of single header files and
 *  has as few dependancies as possible, all
 *  dependencies (with few exeptions) and
 *  platform specific code are separated away
 *  into the platform single header file
 *  libraries (sdld.h for sdl2 and ndsd.h for DS)
 *  one file per platform, I also have chosen to
 *  make it possible to remove all drws-lib core
 *  dependancies using C defines, (you can give
 *  your own calloc and free for this library to
 *  use). Also it would be great to make a game
 *  engine with this library, even better if the
 *  engine itself runs on the library and works
 *  on everything it supports.
 *
 * You can use this lib to create surfaces, draw
 *  to them and copy one surface to another with at
 *  least 3 pixel formats (You can use any bit masks
 *  to "make" a format but only ABGR8888, NDS format
 *  and B&W format are tested for so far).
 *
 * This library can use stb image, to include it
 *  define D_ALLOW_STB_IMAGE. Then you can use
 *  D_LoadImage(), just pass it a file path. Big
 *  thanks to Sean and the people who made that
 *  library, it just works.
 *
 * Things to add.
 * I hoping to add sound out. This way the
 *  library can be used to make games and other
 *  programs. I also want to add custom blending.
 *
 * Using stdlib
 *  This library uses calloc, you can turn this off.
 *  To do that define D_DONT_USE_STDLIB and define
 *  D_CALLOC as the name of an equivalent function
 *  to use instead. You would also have to define
 *  D_FREE as something equivalent.
 *
 * Limitations, this library only supports bit depth
 *  in sizes that are 8, 16 and 32 bits. If you want
 *  24 you just have to use 32 and ignore the other 8.
 *  When you use D_FindPixForm() you can give it
 *  any bitdepth that is 32 or less but each pixel
 *  would get stored with the same or next bigger
 *  number in the sequenc 8, 16, 32.
 *
 */

#ifndef D_H
#define D_H

#ifndef D_DONT_USE_STDLIB
#include<stdlib.h>
#endif

#ifdef D_ALLOW_STB_IMAGE
#include"stb_image.h"
#endif

#ifndef D_MAX_OUT_SURFS
#define D_MAX_OUT_SURFS 64
#endif

#ifndef D_uint32
#define D_uint32 unsigned int
#endif

#ifndef D_uint16
#define D_uint16 unsigned short
#endif

#ifndef D_uint8
#define D_uint8 unsigned char
#endif

#ifndef D_CALLOC
#define D_CALLOC calloc
#endif

#ifndef D_FREE
#define D_FREE free
#endif

#ifndef D_NULL
#define D_NULL 0x0
#endif

/* This converts a bit depth number
 *  to a number of bytes needed to
 *  store a pixel, it only returns
 *  4, 2 and 1 as succesful results
 *  because the this lib only supports
 *  surfaces with a bpp (bit per pixel)
 *  of 32, 16 and 8. You can still
 *  have a surface use 24 bpp, it just
 *  means that you have to use the
 *  next biggest supported bpp which
 *  would be 32 and just not use the
 *  other 8.
 *
 * If you pass a bitdepth that is bigger
 *  than 32 it returns a -1 (meaning
 *  error). If you pass a bitdepth of
 *  0 or less it returns -2 for error.
 *
 * If this needs optimising for speed,
 *  you can remove the error checks for
 *  bigger than 32 and less than 0.
 *
 * bitDepth: The bitDepth to convert to bytes (not exactly, read above)
 * returns: The bitDepth converted to bytes.
 */
#define D_BITDEPTHTOBYTES(bitDepth) ((bitDepth) > 32) ? -1 : (((bitDepth) > 16) ? 4 : (((bitDepth) > 8) ? 2 : ((bitDepth) > 0) ? 1 : -2 ))
//                                                                            32bits                  16bits                 8bits

/* D_SurfFlags are for storing qualities of a
 *  surface. They can be combined bitwise "|"
 *  together.
 */
typedef enum D_SurfFlags {
    D_SURF_PREALLOCATED = 0x1
} D_SurfFlags;

/* D_OutSurfFlags are used to store qualities of
 *  a surface used for output like weather it's
 *  fullscreen. Bitwise OR "|" can be used to
 *  combine flags like
 *  "D_OUTSURFRESIZABLE | D_OUTSURFFULLSCREEN".
 */
typedef enum D_OutSurfFlags {
    D_OUTSURFRESIZABLE = 0x01,
    D_OUTSURFFULLSCREEN = 0x02
} D_OutSurfFlags;

/* D_BLENDMODE flags are used to store how a
 *  source surface should be copied to another.
 *  It can be used to enable and disable alpha
 *  blending on a surface.
 *
 * If you don't know which one to use, you
 *  probably want D_BLENDMODE_NORMAL.
 */
typedef enum D_BLENDMODE {
    D_BLENDMODE_NONE = 0,
    D_BLENDMODE_NORMAL,
    D_BLENDMODE_ADD,
    D_BLENDMODE_MULTIPLY,
    D_BLENDMODE_SUBTRACT,
    D_BLENDMODE_DIVIDE
} D_BLENDMODE;

/* This uses masks for rgba
 *
 * MaskShift means how far bitshifted the
 *  first 1 is from the right
 *  eg "0111 1000" shift is 3
 *
 * MaskLen means how many 1s are in the mask
 *  eg "0001 1110" len is 4
 *
 * Every Masklen and MaskShift are in bits not bytes
 *
 * Warning data duplicatio (for speed) only within this
 *  struct, remeber this when you change it's data.
 */
typedef struct D_PixFormat {
    int rMaskShift;
    int rMaskLen;
    int gMaskShift;
    int gMaskLen;
    int bMaskShift;
    int bMaskLen;
    int aMaskShift;
    int aMaskLen;
    D_uint32 rMask;
    D_uint32 gMask;
    D_uint32 bMask;
    D_uint32 aMask;
    int bitDepth; //in bits
} D_PixFormat;

typedef struct D_Rect {
    int x, y, w, h;
} D_Rect;

typedef struct D_Point {
    int x, y;
} D_Point;

typedef struct D_Surf {
    void * pix;
    int w, h;
    int outId;
    D_uint8 alphaMod;
    D_BLENDMODE blendMode;
    D_SurfFlags flags;
    D_OutSurfFlags outSurfFlags;
    D_PixFormat format;
} D_Surf;

//function prototypes

//If you want to see the comments for each function to thair implementations

void D_SetError(const char * error);
const char * D_GetError(void);
int D_PointInRect(D_Point * p, D_Rect * r);
int D_GetMaskShift(D_uint32 m);
int D_GetMaskLen(D_uint32 m);
D_PixFormat D_FindPixFormat(D_uint32 rMask, D_uint32 gMask, D_uint32 bMask, D_uint32 aMask, int bitDepth);
D_uint32 D_RawrgbaToFormat(D_PixFormat f, int r, int g, int b, int a);
D_uint32 D_rgbaToFormat(D_PixFormat f, int r, int g, int b, int a);
int D_RawFormatTorgba(D_uint32 p, D_PixFormat f, int * r, int * g, int * b, int * a);
int D_FormatTorgba(D_uint32 p, D_PixFormat f, int * r, int * g, int * b, int * a);
D_uint32 D_ConvertPixel(D_PixFormat from, D_PixFormat to, D_uint32 p);
D_Surf * D_CreateSurf(int w, int h, D_PixFormat format);
D_Surf * D_CreateSurfFrom(int w, int h, D_PixFormat format, void * pix);
int D_FreeSurf(D_Surf * s);
int D_BlendNone(int sr, int sg, int sb, int sa, int dr, int dg, int db, int da, int * r, int * g, int * b, int * a);
int D_BlendNormal(int sr, int sg, int sb, int sa, int dr, int dg, int db, int da, int * r, int * g, int * b, int * a);
int D_ClipRect(int x, int y, int w, int h, D_Rect * inner);
int D_FillRect(D_Surf * s, D_Rect * rect, D_uint32 col);
int D_SurfCopyScale(D_Surf * s1, D_Rect * r1, D_Surf * s2, D_Rect * r2);
int D_CharToMap(char c, int * x, int * y);
int D_PrintToSurf(D_Surf * s, D_Surf * font, D_Point * p, int height, int extraSpacing, char * t);
int D_FindExtremePoints(D_Point * p, int numPoints, int * highest, int * lowest);
int D_LineFindY(D_Point * a, D_Point * b, int x, int * y);
D_Surf * D_LoadImage(char * path);

#endif // D_H


//function defs
#ifdef D_IMPLEMENTATION
#ifndef D_ALREADY_IMPLEMENTED
#define D_ALREADY_IMPLEMENTED

const char D_D_NoError[] = "";
const char * D_ErrorString = D_D_NoError;

/* This function can be used to set the error
 *  that is returned by D_GetError(). When it is
 *  called the old error string is removed.
 *
 * This function does not copy the string, make
 *  sure the string will stay allocated after
 *  your function returns.
 *
 * error: The string to set the current error to.
 */
void D_SetError(const char * error){
    D_ErrorString = error;
};

/* This function can be used after running a
 *  function to see if an error happened. Read
 *  the documentation of a function to see if it
 *  will set an error before using it.
 *
 * returns: A string of the last error set.
 */
const char * D_GetError(void){
    return D_ErrorString;
};

/* This checks if a point is in a rectangle and returns 1
 *  if it is, otherwise it returns 0. If p or r are null
 *  then it returns 0 meaning false.
 *
 *  p: The point to check if it is in the rectangle.
 *  r: The rectangle to check if the point p is in it.
 *  returns: 1 if the point is inside, 0 if not. 0 is also returned on error.
 */
int D_PointInRect(D_Point * p, D_Rect * r){
    if(p == D_NULL || r == D_NULL){
        return 0;
    };

    if(p->x >= r->x && p->y >= r->y && p->x < (r->x + r->w) && p->y < (r->y + r->h)){
        return 1;
    };

    return 0;
};

/*
 * This is for finding the number of 0s
 *  in a bitmask before the first 1. It is
 *  intende only for bitmasks that only
 *  have one consecutive list of 1s.
 *
 * m: The bitmask
 * returns: Number of 0s before the first 1
 */
int D_GetMaskShift(D_uint32 m){
    int i = 0;

    while(i < 32 && !((m >> i) & 1)){
        i++;
    };

    if(i == 32){
        return -1;
    };

    return i;
};

/*
 * This finds the length of a consecutive
 *  list of 1s in a bitmask.
 *
 * m: The bitmask.
 * returns: The length of the consecutive list of 1s in the mask
 */
int D_GetMaskLen(D_uint32 m){
    int s = D_GetMaskShift(m);

    if(s < 0){
        return -1;
    };

    int i = s;

    while(i < 32 && ((m >> i) & 1)){
        i++;
    };

    return i-s;
};

/* This returns a pixel format with the bitmasks
 *  and bitdepth. It's name uses the word "find"
 *  because it does not alloca memory, It just
 *  returns a struct.
 *
 * The bitmasks need to have only one grou of
 *  consecuti 1s, the rest need to be 0s. Otherwise
 *  there is undefined behavior.
 *
 * The bitdepth can be anything between 1 and 32,
 *  including 1 and 32, but the pixels only get
 *  stored in siz 8, 16 and 32. This means if you
 *  want a bitdepth of 24, the pixels would be
 *  stored with 32 bits and 8 of them won't be used.
 *  This a limitation of the library, but if you
 *  need it I encourage you to write your own
 *  one-time-use surface converting function to
 *  get it into the format you want.
 *
 * If your not sure what bitmasks and bitdepth to use,
 *  just copy this:
 *  D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32)
 *  It's ABGR8888 format.
 *
 * rMask, gMask, bMask, aMask: The masks that are used in the format.
 * bitDepth: the number of bits to use to store one pixel's data.
 */
D_PixFormat D_FindPixFormat(D_uint32 rMask, D_uint32 gMask, D_uint32 bMask, D_uint32 aMask, int bitDepth){
    D_PixFormat f = {0};

    f.rMaskShift = D_GetMaskShift(rMask);
    f.gMaskShift = D_GetMaskShift(gMask);
    f.bMaskShift = D_GetMaskShift(bMask);
    f.aMaskShift = D_GetMaskShift(aMask);

    f.rMaskLen = D_GetMaskLen(rMask);
    f.gMaskLen = D_GetMaskLen(gMask);
    f.bMaskLen = D_GetMaskLen(bMask);
    f.aMaskLen = D_GetMaskLen(aMask);

    f.rMask = rMask;
    f.gMask = gMask;
    f.bMask = bMask;
    f.aMask = aMask;

    f.bitDepth = bitDepth;

    return f;
};

/* You probably want D_rgbaToFormat() (see it's comment) because
 *  this takes raw rgba numbers and moves them into the format,
 *  255 would stay 255 even if it's colour chann has a bit mask
 *  of "0111 0000" meaning that it does not scale 255 down to
 *  the bit mask's maximum number (in this case) 7.
 *
 * This converts a colour from rgba to a pixel format (it
 *  converts the colour to a pixel), which can then be written
 *  to a surface. Remember that if you give it 0x32BE in red for
 *  example but the format's red bit mask is 0x00FF0000 it will
 *  just discar the overflow (in this case 32) and store
 *  0x00BE0000.
 *
 * Also if you pass a format that has the same mask for r, g and b;
 *  it avaerages them. This way it converts the colour to black
 *  and white better than it would otherwise.
 *
 * Maybe remove the below.
 * Another thing this function does is: if the alpha mask is 0
 *  (meaning there is no alpha mask), then a will always be set to
 *  255. If you don't like this behavior then you can just check the
 *  alpha mask before/after running this function and "correct" the
 *  behavior.
 *
 * If you want to write a pixel to a surface you can get it's
 *  format and create the pixel using this function.
 *  Eg:
 *
 *   D_Surf * s = D_CreateSurf(640, 480, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32));
 *   D_uint32 pixel = D_rgbaToFormat(s->format, 0, 255, 0, 255); //make a green pixel
 *   ((D_uint32 *)(s->pix))[(10 * s->w) + 5] = pixel; //write the pixel to y:10 x:5
 *   D_FreeSurf(s);
 *
 * todo: Test the above.
 *
 * f: The format to convert the colour to.
 * r: The red part of the colour.
 * g: The green part of the colour.
 * b: The blue part of the colour.
 * a: The alpha part of the colour.
 * returns: The colour in a pixel format.
 */
D_uint32 D_RawrgbaToFormat(D_PixFormat f, int r, int g, int b, int a){
    D_uint32 col = 0;

    //If rgb masks are the same, (meaning black and white) average them.
    if((f.rMask == f.gMask) && (f.gMask == f.bMask)){
        r = (g = (b = ((r + g + b) / 3)));
    };

    col = (r << f.rMaskShift) & f.rMask;
    col |= (g << f.gMaskShift) & f.gMask;
    col |= (b << f.bMaskShift) & f.bMask;
    col |= (a << f.aMaskShift) & f.aMask;

    return col;
};

/* This turns an rgba colour in 0-255 for each channel into a
 *  format that can be written to a surf, scaling it down to
 *  get the same colour (at least close enough) to fit in the format.
 *
 *  You can think of the return value as a pixel that can be copied
 *  into the place of another pixel on a surface, this is why
 *  D_FillRect() takes in a "pixel" as col (for colour).
 *
 * This example is almost the same as the one for D_RawrgbaToFormat,
 *  they do almost the same thing, but use D_rgbaToFormat() unless you
 *  know the difference.
 *
 * Because this function uses D_RawrgbaToFormat(), it has similar
 *  behavior. The following is copied from there:
 *  If the alpha mask is 0
 *  (meaning there is no alpha mask), then a will always be set to
 *  255. If you don't like this behavior then you can just check the
 *  alpha mask before/after running this function and "correct" the
 *  behavior.
 *
 * Eg:
 *   D_Surf * s = D_CreateSurf(640, 480, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32));
 *   D_uint32 pixel = D_rgbaToFormat(s->format, 0, 255, 0, 255); //"make" a green pixel
 *   ((D_uint32 *)(s->pix))[(10 * s->w) + 5] = pixel; //write the pixel to y:10 x:5
 *   D_FreeSurf(s);
 *   s = D_NULL;
 *
 * todo: Make sure the below is true.
 *
 * Warning, the paragraph below may be false.
 *
 * Also, if you use a format that has equal r, g, and b bitmasks
 *  then the colour you put in this function would be averagd,
 *  they would get ORed together (bitwise |). This is also true
 *  if you use the same bitmask for rgba also.
 */
D_uint32 D_rgbaToFormat(D_PixFormat f, int r, int g, int b, int a){
    //make sure each rgba is betwee 255 and 0
    r = (r > 255) ? 255 : ((r < 0) ? 0 : r);
    g = (g > 255) ? 255 : ((g < 0) ? 0 : g);
    b = (b > 255) ? 255 : ((b < 0) ? 0 : b);
    a = (a > 255) ? 255 : ((a < 0) ? 0 : a);


    //(f.rMask >> f.rShift) is the max number that the pixel format's r can store not necessarily 255, 0 is the min

    return D_RawrgbaToFormat(f, (r * (f.rMask >> f.rMaskShift)) / (255), (g * (f.gMask >> f.gMaskShift)) / (255), (b * (f.bMask >> f.bMaskShift)) / (255), (a * (f.aMask >> f.aMaskShift)) / (255));
};

/* Unless you know what this does, you probably
 *  need D_FormatTorgba().
 *
 * This does the opposite of D_RawrgbaToFormat(),
 *  it takes in a pixel p and it's format f, then
 *  it finds it's raw rgba colour but not in
 *  0-255 form, instead it's in the pixel
 *  format's form. For example in "ABBB BBGG GGGR
 *  RRRR" format r, g and b would be 0-31 and a
 *  would be 0-1. This is where D_FormatTorgba()
 *  is different, it converts these numbers to
 *  0-255 instead.
 *
 * Remember, if a pixel format you put in this
 *  function has 0 for an alpa mask, a would
 *  always be 0 and may be invisab. (0 for rgb
 *  masks would do a similar thing).
 *
 * p: The pixel. (You can take it from a surf)
 * f: The format of the pixel (usually
 *  surf->format)
 * r: A pointer to fill in with red part of the
 *  colour 0-?. Format dependant (This is why you
 *  probably want D_FormatTorgba()).
 * g: A pointer to fill in with green part of the
 *  colour 0-?. Format dependant.
 * b: A pointer to fill in with blue part of the
 *  colour 0-?. Format dependant.
 * a: A pointer to fill in with alpha part of the
 *  colour 0-?. Format dependant.
 */
int D_RawFormatTorgba(D_uint32 p, D_PixFormat f, int * r, int * g, int * b, int * a){

    if(r != D_NULL){
        *r = ((p & f.rMask) >> f.rMaskShift);
    };

    if(g != D_NULL){
        *g = ((p & f.gMask) >> f.gMaskShift);
    };

    if(b != D_NULL){
        *b = ((p & f.bMask) >> f.bMaskShift);
    };

    if(a != D_NULL){
        *a = ((p & f.aMask) >> f.aMaskShift);
    };

    return 0;
};

/* This takes in a pixel and finds it's rgba values. It
 *  also takes in the pixels format to find them. The rgba
 *  values are in 0-255 form (which D_RawFormatTorgba()
 *  doesn't do).
 *
 * Also, if the alpha mask is 0 (meaning the pixel format
 *  has no alpha), then the function fills in the a pointer
 *  with 255 (if the a pointer is not null). This is because
 *  I think that when a surface has no alpha component, it
 *  implies that the whole surface has alpha on full.
 *
 * Example:
 *
 *  #include<stdio.h>
 *  #include"../d.h"
 *
 *  int main(){
 *      int r = 5, g = 5, b = 5, a = 5; //These are 5 to show D_FormatTorgba() works.
 *      D_Surf * s = D_CreateSurf(640, 480, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32));
 *
 *      D_Rect rect = {5, 5, 630, 470};
 *      D_FillRect(s, &rect, D_rgbaToFormat(s->format, 100, 200, 100, 255));
 *
 *      D_FormatTorgba(((D_uint32 *)(s->pix))[10], s->format, &r, &g, &b, &a);
 *      printf("Colour: r: %d, g: %d, b: %d, a: %d.\n", r, g, b, a); //Should print Colour: r: 100, g: 200, b: 100, a: 255.
 *  };
 *
 *
 * todo: Test the example.
 *
 * p: The pixel. (You can take it from a surf)
 * f: The format of the pixel (usually surf->format)
 * r: A pointer to fill in with red part of the colour 0-255.
 * g: A pointer to fill in with green part of the colour 0-255.
 * b: A pointer to fill in with blue part of the colour 0-255.
 * a: A pointer to fill in with alpha part of the colour 0-255.
 */
int D_FormatTorgba(D_uint32 p, D_PixFormat f, int * r, int * g, int * b, int * a){
    D_RawFormatTorgba(p, f, r, g, b, a);

    if(r != D_NULL){
        if((f.rMask >> f.rMaskShift) != 0){
            *r = (*r * 255) / (f.rMask >> f.rMaskShift);
        }else{
            *r = 0;
        };
    };

    if(g != D_NULL){
        if((f.gMask >> f.gMaskShift) != 0){
            *g = (*g * 255) / (f.gMask >> f.gMaskShift);
        }else{
            *g = 0;
        };
    };

    if(b != D_NULL){
        if((f.bMask >> f.bMaskShift) != 0){
            *b = (*b * 255) / (f.bMask >> f.bMaskShift);
        }else{
            *b = 0;
        };
    };

    if(a != D_NULL){
        if((f.aMask >> f.aMaskShift) != 0){
            *a = (*a * 255) / (f.aMask >> f.aMaskShift);
        }else{
            *a = 255;
        };
    };
};

/* This just convers a pixel from one format to another. It
 *  returns the pixel in the new format.
 *
 * from: The format of the pixel to convert from.
 * to: The new format to convert the pixel to.
 * p: The old pixel.
 * returns: The new pixel in the new format "to".
 */
D_uint32 D_ConvertPixel(D_PixFormat from, D_PixFormat to, D_uint32 p){
    int r = 0, g = 0, b = 0, a = 0;
    D_FormatTorgba(p, from, &r, &g, &b, &a);

    return D_rgbaToFormat(to, r, g, b, a);
};

/* Does what it says. This creates a surface
 *  (shortened to surf). W and h are width and
 *  height. Format is what format the rgba values
 *  are arranged in and thair sizes, if your not
 *  sure what this should be just use
 *  D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32)
 *  in the place of format. D_CreateSurf()
 *  returns an address (pointer) to the surface
 *  or null on error.
 *
 * You can use D_SurfCopyScale() to copy part of
 *  one surface to another and D_FillRect() to
 *  fill an area with a colour.
 *
 * Free the surface with D_FreeSurf();
 *
 * Example:
 *  D_Surf * s = D_CreateSurf(640, 480, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32));
 *
 * w: The width of the surface.
 * h: The height of the surface.
 * format: The pixel format of the surface.
 * Returns: The address of the created surface.
 */
D_Surf * D_CreateSurf(int w, int h, D_PixFormat format){
    D_Surf * s = D_CALLOC(1, sizeof(D_Surf));
    if(s == D_NULL){
        return D_NULL;
    };

    s->pix = D_CALLOC(w * h, D_BITDEPTHTOBYTES(format.bitDepth));
    if(s->pix == D_NULL){
        D_FREE(s);
        s = D_NULL;
        return D_NULL;
    };

    s->w = w;
    s->h = h;
    s->outId = -1;
    s->alphaMod = 255;
    s->blendMode = D_BLENDMODE_NORMAL;
    s->flags = 0;
    s->outSurfFlags = 0;
    s->format = format;
    return s;
};

/* This function can be used to create a surface
 *  with pixel data that is already allocated,
 *  which is passed into it with a void pointer.
 *
 * The pix pointer must point to allocated memory
 *  that has a length in bytes that is at least
 *  w * h * bitDepthInBytes. Otherwise you may
 *  get a segfault.
 *
 * The surface can be freed with D_FreeSurf().
 *
 * w: The width of the surface.
 * h: The height of the surface.
 * format: The format of the pixel data.
 * pix: A pointer to the pixel data to put in the surface.
 */
D_Surf * D_CreateSurfFrom(int w, int h, D_PixFormat format, void * pix){
    D_Surf * s = D_CALLOC(1, sizeof(D_Surf));
    if(s == D_NULL){
        return D_NULL;
    };

    s->pix = pix;
    s->w = w;
    s->h = h;
    s->outId = -1;
    s->alphaMod = 255;
    s->blendMode = D_BLENDMODE_NORMAL;
    s->flags = D_SURF_PREALLOCATED;
    s->outSurfFlags = 0;
    s->format = format;
    return s;
};

/* This frees a surface created with
 *  D_CreateSurf() or D_CreateSurfFrom(). If the
 *  surface is preallocated (made using
 *  D_CreateSurfaceFrom()), it only frees the
 *  surface struct but not the allocated
 *  preallocated pixel data.
 *
 * s: The surface to free.
 */
int D_FreeSurf(D_Surf * s){
    //todo: deal with errors

    //If the surface pixel data is not preallocated
    if(!(s->flags & D_SURF_PREALLOCATED)){

        //Free the pixel data
        D_FREE(s->pix);
    };

    D_FREE(s);

    return 0;
};

/* This function does "none" blending, it just
 *  fills in rgba with source rgba and does not
 *  use destination rgba. Destination rgba is
 *  there to make sure the function has the same
 *  parameters as other blend functions like
 *  D_BlendNormal().
 *
 * sr, sg, sb, sa: Source rgba values to blend with.
 * dr, dg, db, da: Destination rgba values to blend with.
 * r, g, b, a: Pointers to fill with the result of blending.
 * returns: Always 0.
 */
int D_BlendNone(int sr, int sg, int sb, int sa, int dr, int dg, int db, int da, int * r, int * g, int * b, int * a){
    *r = sr;
    *g = sg;
    *b = sb;
    *a = sa;
    return 0;
};

/* This function takes in src rgba, dst rgba then
 *  blends them with normal alpha blending and
 *  writes the result to the rgba pointers.
 *
 * Remember in the eqations below the RGBA values
 *  are between 0 and 1, not 0 and 255. I used
 *  fractions to translate them into equations
 *  that and use 0 to 255.
 *
 * dstRGB = (srcRGB * srcA) + (dstRGB * (1-srcA))
 * dstA = srcA + (dstA * (1-srcA))
 *
 * sr, sg, sb, sa: Source rgba values to blend with.
 * dr, dg, db, da: Destination rgba values to blend with.
 * r, g, b, a: Pointers to fill with the result of blending.
 * returns: Always 0.
 */
int D_BlendNormal(int sr, int sg, int sb, int sa, int dr, int dg, int db, int da, int * r, int * g, int * b, int * a){
    //This works by multiplying fractions.
    //
    // sr    sa    sr*sa    dr    255-sa   dr*(255-sa)
    // --- * --- = -----    --- * ------ = -----------
    // 255   255   255^2    255   255      255^2
    //
    // sr*sa   dr*(255-sa)   r
    // ----- + ----------- = ---
    // 255^2   255^2         255

    *r = ((sr * sa) / 255) + ((dr * (255 - sa)) / 255);
    *g = ((sg * sa) / 255) + ((dg * (255 - sa)) / 255);
    *b = ((sb * sa) / 255) + ((db * (255 - sa)) / 255);
    *a = sa + ((da * (255 - sa)) / 255);
    return 0;
};

/* This function combines two colours using
 *  additive blending. It takes in the colours as
 *  rgba values between 0 and 255. The r, g, b, a
 *  pointers are filled in with the result
 *  colour.
 *
 * This is the equation:
 *  dstRGB = (srcRGB * srcA) + dstRGB
 *  dstA = dstA
 *
 * sr, sg, sb, sa: Source rgba values to blend with.
 * dr, dg, db, da: Destination rgba values to blend with.
 * r, g, b, a: Pointers to fill with the result of blending.
 * returns: Always 0.
 */
int D_BlendAdd(int sr, int sg, int sb, int sa, int dr, int dg, int db, int da, int * r, int * g, int * b, int * a){
    //The equation for dstRGB in 0-255 form.
    //
    // dstRGB     srcRGB   srcA     dstRGB
    // ------ = ( ------ * ---- ) + ------
    //  255        255     255       255

    *r = ((sr * sa) / 255) + dr;
    if(*r > 255){*r = 255;};

    *g = ((sg * sa) / 255) + dg;
    if(*g > 255){*g = 255;};

    *b = ((sb * sa) / 255) + db;
    if(*b > 255){*b = 255;};

    *a = da;
};

/* This function combines two colours using
 *  multiplication blending. It takes in the
 *  colours as rgba values between 0 and 255. The
 *  r, g, b, a pointers are filled in with the
 *  result colour.
 *
 * This is the equation:
 *  dstRGB = (srcRGB * dstRGB) + (dstRGB * (1-srcA))
 *  dstA = dstA
 *
 * sr, sg, sb, sa: Source rgba values to blend with.
 * dr, dg, db, da: Destination rgba values to blend with.
 * r, g, b, a: Pointers to fill with the result of blending.
 * returns: Always 0.
 */
int D_BlendMultiply(int sr, int sg, int sb, int sa, int dr, int dg, int db, int da, int * r, int * g, int * b, int * a){
    //
    // dstRGB     srcRGB   dstRGB       dstRGB           srcA
    // ------ = ( ------ * ------ ) + ( ------ * ( 255 - ---- ))
    //  255        255      255          255             255

    *r = ((sr * dr) / 255) + (( dr * (255 - sa) ) / 255);
    if(*r > 255){*r = 255;};

    *g = ((sg * dg) / 255) + (( dg * (255 - sa) ) / 255);
    if(*g > 255){*g = 255;};


    *b = ((sb * db) / 255) + (( db * (255 - sa) ) / 255);
    if(*b > 255){*b = 255;};

    *a = da;
};

/* This function blends two colours, subtracting
 *  them. It takes in the colours as rgba values
 *  between 0 and 255. The r, g, b, a pointers
 *  are filled with the result colour.
 *
 * dstRGB = dstRGB - (srcRGB * srcA)
 * dstA = dstA
 *
 * sr, sg, sb, sa: Source rgba values to blend with.
 * dr, dg, db, da: Destination rgba values to blend with.
 * r, g, b, a: Pointers to fill with the result of blending.
 * returns: Always 0.
 */
int D_BlendSubtract(int sr, int sg, int sb, int sa, int dr, int dg, int db, int da, int * r, int * g, int * b, int * a){
    //This is the equation in 0 to 255 form.
    //
    // dstRGB   dstRGB   srcRGB   srcA
    // ------ = ------ ( ------ * ---- )
    //  255      255      255     255

    *r = (dr - ((sr * sa) / 255));
    if(*r < 0){*r = 0;};

    *g = (dg - ((sg * sa) / 255));
    if(*g < 0){*g = 0;};

    *b = (db - ((sb * sa) / 255));
    if(*b < 0){*b = 0;};

    *a = da;

};

/*
 *
 */
int D_BlendDivide(int sr, int sg, int sb, int sa, int dr, int dg, int db, int da, int * r, int * g, int * b, int * a){
    //
    //
    //                           (srcRGB + 1)
    // dstRGB = min( W, dstRGB / ------------ )
    //                                256
    //
    //Rearrange so information is not lost in
    // dividing by 256.
    //
    //                                256
    // dstRGB = min( W, dstRGB * ( ---------- ) )
    //                             srcRGB + 1
    //
    //                    dstRGB * 256
    // dstRGB = min( W, ( ------------ ) )
    //                     srcRGB + 1
    //
    // W here means white, r: 255 g: 255 b: 255.
    //
    //Factor in srcA.
    //
    //                      dstRGB * 256       srcA       dstRGB   255 - srcA
    // dstRGB = ( min( W, ( ------------ ) ) * ---- ) + ( ------ * ---------- )
    //                       srcRGB + 1        255         255        255
    //
    //This page was a great help for this:
    // https://www.linuxtopia.org/online_books/graphics_tools/gimp_advanced_guide/gimp_guide_node55_002.html

    *r = (dr * 256) / (sr + 1);
    if(*r > 255){*r = 255;};
    *r = ((*r * sa) / 255) + ((dr * (255 - sa)) / 255);

    *g = (dg * 256) / (sg + 1);
    if(*g > 255){*g = 255;};
    *g = ((*g * sa) / 255) + ((dg * (255 - sa)) / 255);

    *b = (db * 256) / (sb + 1);
    if(*b > 255){*b = 255;};
    *b = ((*b * sa) / 255) + ((db * (255 - sa)) / 255);

    *a = da;
};

/* This function blends colours using a
 *  blendmode. The pointers r, g, b and a are
 *  filled in with the result colour. It uses
 *  other blend functions inside like
 *  D_BlendNormal().
 *
 * blend: The blendmode to blend the colours
 *  with.
 * sr: Source red.
 * sg: Source green.
 * sb: Source blue.
 * sa: Source alpha.
 * dr: Destination red.
 * dg: Destination green.
 * db: Destination blue.
 * da: Destination alpha.
 * r: Filled in with result red.
 * g: Filled in with result green.
 * b: Filled in with result blue.
 * a: Filled in with result alpha.
 */
int D_Blend(D_BLENDMODE blend, int sr, int sg, int sb, int sa, int dr, int dg, int db, int da, int * r, int * g, int * b, int * a){
    switch(blend){
        case D_BLENDMODE_NONE:
            D_BlendNone(sr, sg, sb, sa, dr, dg, db, da, r, g, b, a);
            break;
        case D_BLENDMODE_NORMAL:
            D_BlendNormal(sr, sg, sb, sa, dr, dg, db, da, r, g, b, a);
            break;
        case D_BLENDMODE_MULTIPLY:
            D_BlendMultiply(sr, sg, sb, sa, dr, dg, db, da, r, g, b, a);
            break;
        case D_BLENDMODE_ADD:
            D_BlendAdd(sr, sg, sb, sa, dr, dg, db, da, r, g, b, a);
            break;
        case D_BLENDMODE_SUBTRACT:
            D_BlendSubtract(sr, sg, sb, sa, dr, dg, db, da, r, g, b, a);
            break;
        case D_BLENDMODE_DIVIDE:
            D_BlendDivide(sr, sg, sb, sa, dr, dg, db, da, r, g, b, a);
            break;
    };
    return 0;
};

/* This function sets the alpha modulation number
 *  of a surface. This number can be between 0
 *  and 255.
 *
 * While blending two surfaces (copying one onto
 *  another) this alphaMod number is multiplied
 *  by the source pixels. Think of it as the
 *  source surface's opacity. Use 255 to make it
 *  fully opaque and 0 to make it fully
 *  transparent.
 *
 * s: The surface to change the alpha modulation
 *  of.
 * alphaMod: The new aplha modulation number, can
 *  be 0 to 255. Think of it as the surface's
 *  opacity.
 */
void D_SetSurfAlphaMod(D_Surf * s, D_uint8 alphaMod){
    s->alphaMod = alphaMod;
    return;
};

/* Cut off any sides of an inner rect that reach out of
 *  another rect (given by it's x, y, w, h).
 *
 * The reaon the outside rect is given by it's x, y, w, h
 *  is because it makes code a little cleaner. You don't
 *  need to create a rect if you dont have one, otherwise
 *  you would have to dedicate an entire new line to
 *  "D_Rect r = {10, 10, 20, 20};". If you do have a rect
 *  you can just pass it's members one by one, it's a
 *  trade off. (Worked well for D_SurfCopyScale()).
 *
 * todo: Make safe for when inner is completely outside rect.
 *
 * x: The x of the outer rect.
 * y: The y of the outer rect.
 * w: The width of the outer rect.
 * h: The height of the outer rect.
 * inner: A rect to cut the sides of if they reach out of an outer rect.
 */
int D_ClipRect(int x, int y, int w, int h, D_Rect * inner){

    //Clip inner x
    if(inner->x < x){
        inner->w -= x - inner->x;
        inner->x = x;
    }else if(inner->x > x + w){
        inner->x = (x + w);// - 1;
    };

    //Clip inner w
    if(inner->x + inner->w > x + w){
        inner->w = (x + w) - inner->x;
        //inner->w = w;
    };
    if(inner->w < 0){
        inner->w = 0;
    };

    //Clip inner y
    if(inner->y < y){
        inner->h -= y - inner->y;
        inner->y = y;
    }else if(inner->y > y + h){
        inner->y = (y + h);// - 1;
    };

    //Clip inner h
    if(inner->y + inner->h > y + h){
        inner->h = (y + h) - inner->y;
        //inner->h = h;
    };
    if(inner->h < 0){
        inner->h = 0;
    };

    return 0;
};

/*
 * D_FillRect fills a rectangle on a surf with a
 *  colour (col). Use D_rgbaToFormat() and pass it's
 *  return to col. You can pass D_NULL to rect to make
 *  it fill the whole surf.
 *
 *
 * Example:
 *
 *  D_Surf * s = D_CreateSurf(64, 32, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32));
 *  D _Rect r = {5, 5, 22, 22};
 *  D_FillRect(s, &r, D_rgbaToFormat(s->format, 100, 255, 100, 255));
 *
 * todo: Test the example.
 * todo: Make safe (if s is null).
 *
 * s: The surf to to draw on
 * rect: The rect to fill, can be null (or D_NULL) to
 *  fill the whole surf
 * col: The colour to fill the surf with. Use
 *  D_rgbaToABGR() and pass it's return to col (to make it easier)
 * returns: 0 on success.
 *
 */
int D_FillRect(D_Surf * s, D_Rect * rect, D_uint32 col){

    D_Rect temp = {0};
    if(rect == D_NULL){
        temp.w = s->w;
        temp.h = s->h;
        rect = &temp;
    }else{
        D_ClipRect(0, 0, s->w, s->h, rect);
    };

    int x = rect->x;
    int y = rect->y;

    //printf("x: %d y: %d\n", x, y);

    //If this needs optimising, have 3 loops so the switch
    //can be outside them instead of inside
    while(y < rect->y + rect->h){
        x = rect->x;
        //x = (rect->x < 0) ? 0 : rect->x;
        while(x < rect->x + rect->w){
            switch(D_BITDEPTHTOBYTES(s->format.bitDepth)){
                case 4:
                    ((D_uint32 *)(s->pix))[(y * s->w) + x] = col;
                    //printf("32 bitdepth\n");
                    break;
                case 2:
                    ((D_uint16 *)(s->pix))[(y * s->w) + x] = col;
                    //printf("16 bitdepth\n");
                    break;
                case 1:
                    ((D_uint8 *)(s->pix))[(y * s->w) + x] = col;
                    //printf("8 bitdepth\n");
                    break;
                default:
                    //Maybe add error message here, like "bitDepth not supported."
                    //Like SDL's SDL_GetError()
                    return -1;
                    break;
            };
            x++;
        };
        y++;
    };

    return 0;
};

/* This macro is used for D_SurfCopyScale(), it
 *  may change or be removed at any time.
 *
 * First the destination pixel's rgba and put
 *  them in dr, dg, db, da.
 *
 * Then take the source pixel's rgba and put them
 *  in sr, sg, sb, sa.
 *
 * Then multiply the source surface's alphaMod
 *  with sa and store that in sa.
 *
 * Then blend the source and destination pixels
 *  rgba values using the source surface's blend
 *  mode, putting those new values in the rgba
 *  variables.
 *
 * Finally write the blended values to the
 *  destination pixel.
 */
#define D_D_SCSPIXEL(from, to) {D_FormatTorgba((to)[(y * s2->w) + x], s2->format, &dr, &dg, &db, &da); D_FormatTorgba((from)[(((((y - r2->y) * r1->h) / r2->h) + r1->y) * s1->w) + ((((x - r2->x) * r1->w) / r2->w) + r1->x)], s1->format, &sr, &sg, &sb, &sa); sa = (sa * s1->alphaMod) / 255; D_Blend(s1->blendMode, sr, sg, sb, sa, dr, dg, db, da, &r, &g, &b, &a); (to)[(y * s2->w) + x] = D_rgbaToFormat(s2->format, r, g, b, a);}

//#define D_D_SCSPIXEL(from, to) (to)[(y * s2->w) + x] = D_ConvertPixel(s1->format, s2->format, (from)[(((((y - r2->y) * r1->h) / r2->h) + r1->y) * s1->w) + ((((x - r2->x) * r1->w) / r2->w) + r1->x)])

/*
 * D_SurfCopyScale copies part of surface 1 (the part
 *  inside r1) to surface 2 within r2. It also streches
 *  what it reads from s1 (in r1) to fill r2, it scales.
 *(to)[(y * s2->w) + x]
 * It is safe for r2 to be anywhere, off of any side of
 *  s2.
 *
 * todo: make it all safe (dont read/write outside of
 *  s1 or s2 and make use all the pointe are not null)
 */
int D_SurfCopyScale(D_Surf * s1, D_Rect * r1, D_Surf * s2, D_Rect * r2){

    if(s1 == D_NULL || s2 == D_NULL){
        return -1;
    };

    //If r1 is null, make an r1 for the whole surface
    //If r1 is not null make a copy of r1 without
    // changing r1 and clip the copy to inside of s1
    // then point r1 to the copy
    D_Rect temp1 = {0};
    if(r1 == D_NULL){
        temp1.w = s1->w;
        temp1.h = s1->h;
        r1 = &temp1;
    };

    //same as above except for r2 and s2
    D_Rect temp2 = {0};
    if(r2 == D_NULL){
        temp2.w = s2->w;
        temp2.h = s2->h;
        r2 = &temp2;
    };


    //This cycles through s2 pixels left to right top
    //to bottom within r2 asking what colour goes here

    int x = r2->x;
    int y = r2->y;

    //Temp storage for each pixels colour while blending (used in D_D_SCSPIXEL()).
    int sr = 0;
    int sg = 0;
    int sb = 0;
    int sa = 0;

    int dr = 0;
    int dg = 0;
    int db = 0;
    int da = 0;

    int r = 0;
    int g = 0;
    int b = 0;
    int a = 0;

    int s2ByteDepth = D_BITDEPTHTOBYTES(s2->format.bitDepth);
    int s1ByteDepth = D_BITDEPTHTOBYTES(s1->format.bitDepth);

    while(y < r2->y + r2->h && y < s2->h){

        if(y < 0){
            y = 0;
        };

        //Safety! If y is off the bottom of s2, break
        if(y >= s2->h){
            break;
        };

        x = r2->x;
        while(x < r2->x + r2->w && x < s2->w){

            if(x < 0){
                x = 0;
            };

            //if the x is off the right of s2 then
            //break and start drawing the next line
            if(x >= s2->w){
                break;
            };

            switch(s2ByteDepth){
                case 4:

                    switch(s1ByteDepth){
                        case 4: //The line below is copied meaning there are 9 of them below. The only differences are what the pointe are cast to.
                            D_D_SCSPIXEL((D_uint32 *)(s1->pix), (D_uint32 *)(s2->pix));
                            //((D_uint32 *)(s2->pix))[(y * s2->w) + x] = D_ConvertPixel(s1->format, s2->format, ((D_uint32 *)(s1->pix))[(((((y - r2->y) * r1->h) / r2->h) + r1->y) * s1->w) + ((((x - r2->x) * r1->w) / r2->w) + r1->x)]); //old, it was repeated for all 9
                            break;
                        case 2:
                            D_D_SCSPIXEL((D_uint16 *)(s1->pix), (D_uint32 *)(s2->pix));
                            break;
                        case 1:
                            D_D_SCSPIXEL((D_uint8 *)(s1->pix), (D_uint32 *)(s2->pix));
                        default:
                            //Error s2 bitDepth not supported
                            break;
                    };

                    break;
                case 2:

                    switch(s1ByteDepth){
                        case 4:
                            D_D_SCSPIXEL((D_uint32 *)(s1->pix), (D_uint16 *)(s2->pix));
                            break;
                        case 2:
                            D_D_SCSPIXEL((D_uint16 *)(s1->pix), (D_uint16 *)(s2->pix));
                            break;
                        case 1:
                            D_D_SCSPIXEL((D_uint8 *)(s1->pix), (D_uint16 *)(s2->pix));
                        default:
                            //Error s2 bitDepth not supported
                            break;
                    };

                    break;
                case 1:

                    switch(s1ByteDepth){
                        case 4:
                            D_D_SCSPIXEL((D_uint32 *)(s1->pix), (D_uint8 *)(s2->pix));
                            break;
                        case 2:
                            D_D_SCSPIXEL((D_uint16 *)(s1->pix), (D_uint8 *)(s2->pix));
                            break;
                        case 1:
                            D_D_SCSPIXEL((D_uint8 *)(s1->pix), (D_uint8 *)(s2->pix));
                        default:
                            //Error s2 bitDepth not supported
                            break;
                    };

                default:
                    //Error s1 bitdepth not supported (it's possible s2 bitdepth is also not supported)
                    break;
            };

            //((D_SurfInt *)(s2->pix))[(y * s2->w) + x] = ((D_SurfInt *)(s1->pix))[(((((y - r2->y) * r1->h) / r2->h) + r1->y) * s1->w) + ((((x - r2->x) * r1->w) / r2->w) + r1->x)]; //Old

            //(((y - r2->y) / r2->h) * r1->h) + r1->y | (((x - r2->x) / r2->w) * r1->w) + r1->x

            x++;
        };

        y++;
    };

    return 0;
};

/* This finds the number position of where a char
 *  is on a charicter map.
 *
 * The width and height of a charicter on the
 *  font map are the same, it's the surface's
 *  width devided by 9. font->w / 9.
 *
 * Also the result x and y need to be multiplied
 *  by font->w / 9. This way they become real
 *  coords that are the top left of the
 *  charicter.
 *
 * c: The charicter.
 * x: Gets filled in with the char x position on a font map.
 * y: Gets filled in with the char y position on a font map.
 * returns: 0 on sucess.
 */
int D_CharToMap(char c, int * x, int * y){
    int n = -1;

    switch(c){
        case 'A': n = 0; break; case 'a': n = 27; break;
        case 'B': n = 1; break; case 'b': n = 28; break;
        case 'C': n = 2; break; case 'c': n = 29; break;
        case 'D': n = 3; break; case 'd': n = 30; break;
        case 'E': n = 4; break; case 'e': n = 31; break;
        case 'F': n = 5; break; case 'f': n = 32; break;
        case 'G': n = 6; break; case 'g': n = 33; break;
        case 'H': n = 7; break; case 'h': n = 34; break;
        case 'I': n = 8; break; case 'i': n = 35; break;
        case 'J': n = 9; break; case 'j': n = 36; break;
        case 'K': n = 10; break; case 'k': n = 37; break;
        case 'L': n = 11; break; case 'l': n = 38; break;
        case 'M': n = 12; break; case 'm': n = 39; break;
        case 'N': n = 13; break; case 'n': n = 40; break;
        case 'O': n = 14; break; case 'o': n = 41; break;
        case 'P': n = 15; break; case 'p': n = 42; break;
        case 'Q': n = 16; break; case 'q': n = 43; break;
        case 'R': n = 17; break; case 'r': n = 44; break;
        case 'S': n = 18; break; case 's': n = 45; break;
        case 'T': n = 19; break; case 't': n = 46; break;
        case 'U': n = 20; break; case 'u': n = 47; break;
        case 'V': n = 21; break; case 'v': n = 48; break;
        case 'W': n = 22; break; case 'w': n = 49; break;
        case 'X': n = 23; break; case 'x': n = 50; break;
        case 'Y': n = 24; break; case 'y': n = 51; break;
        case 'Z': n = 25; break; case 'z': n = 52; break;

        case '0': n = 54; break;
        case '1': n = 55; break;
        case '2': n = 56; break;
        case '3': n = 57; break;
        case '4': n = 58; break;
        case '5': n = 59; break;
        case '6': n = 60; break;
        case '7': n = 61; break;
        case '8': n = 62; break;
        case '9': n = 63; break;

        case '.': n = 64; break;
        case ',': n = 65; break;
        case ';': n = 66; break;
        case ':': n = 67; break;
        case '$': n = 68; break;
        case '#': n = 69; break;
        case '\'': n = 70; break;
        case '!': n = 71; break;
        case '"': n = 72; break;
        case '/': n = 73; break;
        case '?': n = 74; break;
        case '%': n = 75; break;
        case '&': n = 76; break;
        case '(': n = 77; break;
        case ')': n = 78; break;
        case '@': n = 79; break;
    };

    if(n == -1){
        return -1;
    };

    *x = n % 9;
    *y = n / 9;

    return 0;
};

/* This writes text to a surface, it is very
 *  simple, mono-space only.
 *
 * The reason this text support is so simple and
 *  doesn't use tff fonts is because it would be
 *  too much to maintain.
 *
 * s: The surface to write the string t to.
 * font: A charicter map as a surface.
 * p: A point on surface s of where to start
 *  writing (top left of first charicter).
 * height: The height to draw the characters,
 *  characters are sqaures (width == height).
 * extraSpacing: Extra space to put between
 *  letters, in pixels. Can be negative.
 * t: The text, a string to write.
 */
int D_PrintToSurf(D_Surf * s, D_Surf * font, D_Point * p, int height, int extraSpacing, char * t){
    int i = 0;
    D_Rect fontRect = {0, 0, font->w / 9, font->w / 9};
    D_Rect sRect = {p->x, p->y, height, height};

    while(t[i] != '\0' && sRect.x < s->w){
        if(D_CharToMap(t[i], &fontRect.x, &fontRect.y) < 0){
            sRect.x += (sRect.w + extraSpacing);
            i++;
            continue;
        };

        fontRect.x *= fontRect.w;
        fontRect.y *= fontRect.h;

        D_SurfCopyScale(font, &fontRect, s, &sRect);
        sRect.x += (sRect.w + extraSpacing);
        i++;
    };

    return 0;
};

/* This function finds the heighest and lowest
 *  points in an array of points.
 *
 * This function assumes that as y gets smaller,
 *  you go up the page. A negative y means you're
 *  above the origin.
 *
 * p: An array of points to find the highest and
 *  lowest of. It is safe to pass null, but the
 *  function would return -2.
 * numPoints: The number of points in the array
 *  (can aslo just be the number to test).
 * highest: Gets filled in with the index of the
 *  highest point (smallest y). Can be null.
 * lowest: Gets filled in with the indes of the
 *  lowest point (biggest y). Can be null.
 * returns:  0 on success, negative number
 *  otherwise.
 */
int D_FindExtremePoints(D_Point * p, int numPoints, int * highest, int * lowest){
    if(p == D_NULL){
        return -2;
    };

    if(numPoints < 1){
        return -1;
    };

    int tempHighest;
    if(highest == D_NULL){
        highest = &tempHighest;
    };

    int tempLowest;
    if(lowest == D_NULL){
        lowest = &tempLowest;
    };

    *highest = 0;
    *lowest = 0;

    int i = 1; //1 on purpose

    while(i < numPoints){

        if(p[i].y < p[*highest].y){
            *highest = i;
        };

        if(p[i].y > p[*lowest].y){
            *lowest = i;
        };

        i++;
    };

    return 0;
};

/* This function takes in a stright line equation
 *  and finds y for any x value. The stright line
 *  equation is in the form of two points a and
 *  b.
 *
 * a: A point on the line.
 * b: Anonther point on the line.
 * x: The x position to find the y of.
 * y: Gets filled in with the y positon found.
 * returns: 0 on success, negative number otherwise.
 */
int D_LineFindY(D_Point * a, D_Point * b, int x, int * y){

    if(a == D_NULL || b == D_NULL || y == D_NULL){
        return -1;
    };

    if((b->x - a->x) == 0){
        return -2;
    };

    //Notes and workings out for this are in
    // D_LineFindY-notes.txt


    //*y = (((((float)b->y) - a->y) / (((float)b->x) - a->x)) * x) + (a->y - (((((float)b->y) - a->y) / (((float)b->x) - a->x)) * a->x));
    //*y = (((b->y - a->y) * x) * b->x - a->x) + (((a->y * (b->x - a->x)) - ((b->y - a->y) * a->x)) * b->x - a->x) / (b->x - a->x) * (b->x - a->x); //lol

    *y = (((b->y - a->y) * x) / (b->x - a->x)) + (a->y - ( ( (b->y - a->y) * a->x ) / (b->x - a->x) ) );

    return 0;
};

/* This function draws a triangle with any three
 *  points to a surface. Don't expect it to be
 *  fast enough for 3D.
 *
 * s: A surface to draw the tri to.
 * p: A pointer to an array of at least 3
 *  D_Points, the rest are ignored.
 */
/*int D_FillTri(D_Surf * s, D_Point * p){

    //Remember these are indexes in p

    int highest = -1;
    int lowest = -1;
    int mid = 0; //0 on purpose


    D_FindExtremePoints(p, 3, &highest, &lowest);


    //Find which point in p is the middle
    // (we know the highest and lowest)

    if(highest == 0 || lowest == 0){
        mid++;

        if(highest == 1 || lowest == 1){
            mid++;
        };
    };


    //Is mid on the right side of the straight
    // line equation made by the points higest
    // and lowest
    if(){};
};*/

/*
 * This loads an image using stb_image and creates a
 *  surface, which it then returns. You can free the
 *  surface with D_FreeSurf(). The surface is always
 *  in ABGR8888 format.
 *
 * todo: test if this works on big endian.
 *
 * path: The filename/filepath that of the image eg "pic.bmp" or "C:/users/me/pictures/tom.png"
 * returns: A pointer to a created surface, always in ABGR8888 format.
 */
D_Surf * D_LoadImage(char * path){

    D_Surf * s = D_NULL;

#ifdef D_ALLOW_STB_IMAGE
    int w = 0, h = 0, n = 0;

    void * dat = stbi_load(path, &w, &h, &n, 4);

    s = D_CreateSurf(w, h, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32));

    int i = 0;
    while(i < w*h){
        ((D_uint32 *)(s->pix))[i] = ((D_uint32 *)dat)[i];
        i++;
    };


    stbi_image_free(dat);
    dat = D_NULL;

#else

    //Run D_SetError() when implemented.

#endif // D_ALLOW_STB_IMAGE

    return s;
};

#endif // D_ALREADY_IMPLEMENTED
#endif // D_IMPLEMENTATION
