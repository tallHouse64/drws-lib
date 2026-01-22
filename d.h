
/*
 * The d graphics lib
 *
 * project started Tue 12/11/2024
 *
 * The purpose of this library is to make
 *  games/programs that are very cross platform.
 *  As many platforms as possible, this is the
 *  main goal of the library. Think Windows, Mac,
 *  Linux, NDS, TI calcs, IPOD, PSP. So far,
 *  Windows, Linux, Web and Nintendo DS are
 *  supported. This way anyone can play games I
 *  make no matter what device they have. This is
 *  why the library is a group of single header
 *  files and has as few dependencies as
 *  possible, all dependencies (with few
 *  exceptions) and platform specific code are
 *  separated away into the platform single
 *  header file libraries (sdld.h for sdl2 and
 *  ndsd.h for DS, the letter d means driver) one
 *  file per platform, I also have chosen to make
 *  it possible to remove all drws-lib core
 *  dependencies using C defines, (you can give
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
 *  thanks to Sean Barrett and everyone else who
 *  made that library, it just works.
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

#ifndef D_double
#define D_double double
#endif

#ifndef D_CALLOC
#define D_CALLOC calloc
#endif

#ifndef D_REALLOC
#define D_REALLOC realloc
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
/*                                                                            32bits                  16bits                 8bits*/


/* This macro multiplies two complex numbers and
 *  returns the real part of the result. */
#define D_COMPLEXMULTR(r1, c1, r2, c2) (((r1) * (r2)) - ((c1) * (c2)))

/* This macro multiplies two complex numbers and
 *  returns the imaginary part of the result. */
#define D_COMPLEXMULTC(r1, c1, r2, c2) (((r1) * (c2)) + ((c1) * (r2)))


/* D_SurfFlags are for storing information about
 *  a surface. They can be combined with bitwise
 *  OR "|".
 */
typedef enum D_SurfFlags {

    /* On if the surface was created by
     *  D_CreateSurfFrom(). */
    D_SURF_PREALLOCATED = 0x1,

    /* On if the surface was created by
     *  D_CreateSubsurf(). */
    D_SURF_SUBSURF      = 0x2

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
    int bitDepth; /*in bits*/
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

    /*Num of bytes between each row of pixels*/
    int pitch;

    /* The part of the surface that is safe to
     *  draw to, usually the whole surface. */
    D_Rect safeArea;

    int outId;
    D_uint8 alphaMod;
    D_BLENDMODE blendMode;
    D_SurfFlags flags;
    D_OutSurfFlags outSurfFlags;
    D_PixFormat format;
} D_Surf;

/*function prototypes*/

/*If you want to see the comments for each function to thair implementations*/

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
D_Surf * D_CreateSurfFrom(int w, int h, int pitch, D_Rect * safeRect, D_PixFormat format, void * pix);
D_Surf * D_CreateSubsurf(D_Surf * outer, D_Rect * where);
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

#endif
/* endif D_H */

/* function defs */
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

    /*If rgb masks are the same, (meaning black and white) average them. */
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
    /*make sure each rgba is betwee 255 and 0 */
    r = (r > 255) ? 255 : ((r < 0) ? 0 : r);
    g = (g > 255) ? 255 : ((g < 0) ? 0 : g);
    b = (b > 255) ? 255 : ((b < 0) ? 0 : b);
    a = (a > 255) ? 255 : ((a < 0) ? 0 : a);


    /*(f.rMask >> f.rShift) is the max number that the pixel format's r can store not necessarily 255, 0 is the min*/

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
 * returns: 0 on success.
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

    return 0;
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
    s->pitch = 0;

    s->safeArea.x = 0;
    s->safeArea.y = 0;
    s->safeArea.w = w;
    s->safeArea.h = h;

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
 * pitch: The number of bytes between each row
 *  (BYTES not pixels).
 * safeRect: What part of the surface is safe to
 *  draw to, use D_NULL unless you know part of
 *  the surface is not safe to read/write to.
 *  Passing D_NULL means the whole surface is
 *  safe to draw to.
 * format: The format of the pixel data.
 * pix: A pointer to the pixel data to put in the surface.
 */
D_Surf * D_CreateSurfFrom(int w, int h, int pitch, D_Rect * safeRect, D_PixFormat format, void * pix){
    D_Surf * s = D_CALLOC(1, sizeof(D_Surf));
    if(s == D_NULL){
        return D_NULL;
    };

    s->pix = pix;
    s->w = w;
    s->h = h;
    s->pitch = pitch;

    if(safeRect == D_NULL){
        s->safeArea.x = 0;
        s->safeArea.y = 0;
        s->safeArea.w = w;
        s->safeArea.h = h;
    }else{
        s->safeArea = *safeRect;
    };

    s->outId = -1;
    s->alphaMod = 255;
    s->blendMode = D_BLENDMODE_NORMAL;
    s->flags = D_SURF_PREALLOCATED;
    s->outSurfFlags = 0;
    s->format = format;
    return s;
};

/* This function creates a surface using part of
 *  (a smaller rectangle of) the pixel data from
 *  another surface.
 *
 * This function is useful for situations where
 *  you would create a surface, draw to it, then
 *  copy it to the screen (another surface).
 *  Using this function would mean drawing to the
 *  surface would just draw to the screen
 *  directly (even though you are drawing to what
 *  seems like a separate surface). This should
 *  save memory and time spent copying.
 *
 * Bear in mind that, if you use this function as
 *  an alternative to D_SurfCopyScale(), you
 *  won't be able to scale the surface. A subsurf
 *  can only "mount" pixels 1 to 1.
 *
 * Internally this function uses
 *  D_CreateSurfFrom() on the outer pixel data.
 *
 * It is safe to pass null into "outer", the
 *  function would do nothing and return null.
 *
 * It is also safe to pass null into "where", the
 *  created subsurf would cover the entire outer
 *  surface.
 *
 * A subsurf created by this function can be
 *  freed using D_FreeSurf().
 *
 * outer: The outer surface to use pixel data
 *  from.
 * where: The rectangle that the subsurf should
 *  cover on the outer surface.
 * returns: The created subsurface on success or
 *  null on failure.
 */
D_Surf * D_CreateSubsurf(D_Surf * outer, D_Rect * where){

    if(outer == D_NULL){
        return D_NULL;
    };


    /* "where2" is the same as "where" except
     *  safe (not null).*/
    D_Rect where2 = {0};
    if(where == D_NULL){
        where2.x = 0;
        where2.y = 0;
        where2.w = outer->w;
        where2.h = outer->h;
    }else{
        where2 = *where;
    };


    D_Rect innerSafeArea = where2;

    D_ClipRect(outer->safeArea.x, outer->safeArea.y, outer->safeArea.w, outer->safeArea.h, &innerSafeArea);


    /* Make innerSafeArea relative to inner. */
    innerSafeArea.x = innerSafeArea.x - where2.x;
    innerSafeArea.y = innerSafeArea.y - where2.y;


    D_Surf * inner =
    D_CreateSurfFrom(where2.w,
                     where2.h,
                     ((outer->w - where2.w) * (D_BITDEPTHTOBYTES(outer->format.bitDepth))) + outer->pitch,
                     &innerSafeArea,
                     outer->format,
                     (((D_uint8 *)outer->pix) + (((where2.y * outer->w) + where2.x) * (D_BITDEPTHTOBYTES(outer->format.bitDepth))) + (outer->pitch * where2.y)));


    if(inner != D_NULL){

        /* Turn on the subsurf flag */
        inner->flags = inner->flags | D_SURF_SUBSURF;

    };


    return inner;
};

/* This function can move a subsurface to
 *  somewhere else on the same outer surface. You
 *  can use it like D_CreateSubsurf() except you
 *  pass the inner surface also.
 *
 * This function does not change the width or
 *  height of the inner surface, it only changes
 *  it's position on the outer surface (where.w
 *  and where.h are ignored). If you need to
 *  change the width or height you need to free
 *  the subsurf and recreate it with
 *  D_CreateSubsurf().
 *
 * It is safe to pass null into "where", the
 *  function would use 0, 0 for the x and y
 *  position and work normally.
 *
 * It is safe to pass null for outer and inner,
 *  the function would set an error, do nothing
 *  and return -1. Use D_GetError() for more
 *  details.
 *
 * If the inner subsurface was not created with
 *  D_CreateSubSurf(), the function would set and
 *  error, return -2 and do nothing. If you know
 *  what you are doing and want to ignore this
 *  error, you can turn on the D_SURF_SUBSURF
 *  flag (inner->flags = inner->flags |
 *  D_SURF_SUBSURF).
 *
 * If this function detects that the inner
 *  surface is not a subsurface of the outer
 *  surface, it would set error (use D_GetError()
 *  for details), return -3 and do nothing.
 *
 * outer: The outer surface that inner was
 *  created on.
 * inner: The inner surface to move.
 * where: A rectangle of where the inner surface
 *  should move to on outer (width and height are
 *  ignored, read above).
 */
int D_ReconfigureSubsurf(D_Surf * outer, D_Surf * inner, D_Rect * where){

    if(inner == D_NULL || outer == D_NULL){
        D_SetError("Drws-lib D_ReconfigureSubsurf(): The inner or outer surface (or both) are null.");
        return -1;
    };

    /* Is the subsurf flag set? */
    if(!(inner->flags & D_SURF_SUBSURF)){
        D_SetError("Drws-lib D_ReconfigureSubsurf(): The inner surface is not a subsurface (was it created by D_CreateSubsurf()?), set D_SURF_SUBSURF on the inner surface to ignore.");
        return -2;
    };

    /* Is the inner pix pointer within the outer
     *  pixel data? */
    if( !( ((D_uint8 *)(inner->pix)) >= ((D_uint8 *)(outer->pix)) &&
           ((D_uint8 *)(inner->pix)) <
           (((D_uint8 *)(outer->pix)) + (outer->w * outer->h * (D_BITDEPTHTOBYTES(outer->format.bitDepth))) + (outer->pitch * outer->h))
           )
       ){
        D_SetError("Drws-lib D_ReconfigureSubSurf(): The inner surface is not a subsurface of the outer surface.");
        return -3;
    };

    /* where2 is the same as where except it
     *  can't be null. */
    D_Rect where2 = {0, 0, 0, 0};
    if(where != D_NULL){
        where2 = *where;
    };


    D_Rect innerSafeArea = where2;

    D_ClipRect(outer->safeArea.x, outer->safeArea.y, outer->safeArea.w, outer->safeArea.h, &innerSafeArea);

    /* Make innerSafeArea relative to inner. */
    innerSafeArea.x = innerSafeArea.x - where2.x;
    innerSafeArea.y = innerSafeArea.y - where2.y;

    inner->safeArea = innerSafeArea;


    inner->pix = (((D_uint8 *)outer->pix) + (((where2.y * outer->w) + where2.x) * (D_BITDEPTHTOBYTES(outer->format.bitDepth))) + (outer->pitch * where2.y));

    return 0;
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
    /*todo: deal with errors */

    /* If the surface pixel data is not
     *  preallocated. */
    if(!(s->flags & D_SURF_PREALLOCATED)){

        /*Free the pixel data*/
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
    /* This works by multiplying fractions.
     *
     *  sr    sa    sr*sa    dr    255-sa   dr*(255-sa)
     *  --- * --- = -----    --- * ------ = -----------
     *  255   255   255^2    255   255      255^2
     *
     *  sr*sa   dr*(255-sa)   r
     *  ----- + ----------- = ---
     *  255^2   255^2         255
     */

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
    /* The equation for dstRGB in 0-255 form.
     *
     *  dstRGB     srcRGB   srcA     dstRGB
     *  ------ = ( ------ * ---- ) + ------
     *   255        255     255       255
     */

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
    /*
     * dstRGB     srcRGB   dstRGB       dstRGB           srcA
     * ------ = ( ------ * ------ ) + ( ------ * ( 255 - ---- ))
     *  255        255      255          255             255
     */

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
    /* This is the equation in 0 to 255 form.
     *
     *  dstRGB   dstRGB   srcRGB   srcA
     *  ------ = ------ ( ------ * ---- )
     *   255      255      255     255
     */

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
    /*
     *
     *                            (srcRGB + 1)
     *  dstRGB = min( W, dstRGB / ------------ )
     *                                 256
     *
     * Rearrange so information is not lost in
     *  dividing by 256.
     *
     *                                256
     *  dstRGB = min( W, dstRGB * ( ---------- ) )
     *                             srcRGB + 1
     *
     *                     dstRGB * 256
     *  dstRGB = min( W, ( ------------ ) )
     *                      srcRGB + 1
     *
     * W here means white, r: 255 g: 255 b: 255.
     *
     * Factor in srcA.
     *
     *                       dstRGB * 256       srcA       dstRGB   255 - srcA
     *  dstRGB = ( min( W, ( ------------ ) ) * ---- ) + ( ------ * ---------- )
     *                        srcRGB + 1        255         255        255
     *
     * This page was a great help for this:
     * https://www.linuxtopia.org/online_books/graphics_tools/gimp_advanced_guide/gimp_guide_node55_002.html
     */

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

    /*Clip inner x */
    if(inner->x < x){
        inner->w -= x - inner->x;
        inner->x = x;
    }else if(inner->x > x + w){
        inner->x = (x + w);/* - 1;*/
    };

    /*Clip inner w */
    if(inner->x + inner->w > x + w){
        inner->w = (x + w) - inner->x;
        /*inner->w = w; */
    };
    if(inner->w < 0){
        inner->w = 0;
    };

    /*Clip inner y */
    if(inner->y < y){
        inner->h -= y - inner->y;
        inner->y = y;
    }else if(inner->y > y + h){
        inner->y = (y + h);/* - 1;*/
    };

    /*Clip inner h */
    if(inner->y + inner->h > y + h){
        inner->h = (y + h) - inner->y;
        /*inner->h = h;*/
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
    }else{
        temp = *rect;
    };

    D_ClipRect(s->safeArea.x, s->safeArea.y, s->safeArea.w, s->safeArea.h, &temp);


    int x = temp.x;
    int y = temp.y;

    /*printf("x: %d y: %d\n", x, y);*/

    /* If this needs optimising, have 3 loops so
     *  the switch can be outside them instead of
     *  inside.
     */
    while(y < temp.y + temp.h){
        x = temp.x;
        /*x = (temp.x < 0) ? 0 : temp.x;*/
        while(x < temp.x + temp.w){
            switch(D_BITDEPTHTOBYTES(s->format.bitDepth)){
                case 4:
                    /*((D_uint32 *)(s->pix))[(y * s->w) + x] = col;*/
                    *((D_uint32 *)(((D_uint8 *)(s->pix)) + ((((y * s->w) + x) * 4) + (s->pitch * y)))) = col;
                    /*printf("32 bitdepth\n");*/
                    break;
                case 2:
                    /*((D_uint16 *)(s->pix))[(y * s->w) + x] = col;*/
                    *((D_uint16 *)(((D_uint8 *)(s->pix)) + ((((y * s->w) + x) * 2) + (s->pitch * y)))) = col;
                    /*printf("16 bitdepth\n");*/
                    break;
                case 1:
                    /*((D_uint8 *)(s->pix))[(y * s->w) + x] = col;*/
                    *((D_uint8  *)(((D_uint8 *)(s->pix)) + ((((y * s->w) + x)    ) + (s->pitch * y)))) = col;
                    /*printf("8 bitdepth\n");*/
                    break;
                default:

                    D_SetError("Drws-lib D_FillRect(): Bit depth not supported.");

                    return -1;
                    break;
            };
            x++;
        };
        y++;
    };

    return 0;
};

/* This function draws a line between two points
 *  on a surface.
 *
 * Note that thickness is not implemented and the
 *  line always gets drawn with a thickness of 1.
 *
 * At the moment, this function only supports
 *  surfaces with a bit depth of 32.
 *
 * The example below draws a green line on a
 *  surface.
 *
 * Example:
 *  D_Surf * surf = D_CreateSurf(640, 480, D_FindPixFormat(0xFF, 0xFF00, 0xFF0000, 0xFF000000, 32));
 *  D_Point a = {10, 10};
 *  D_Point b = {100, 70};
 *  D_DrawLine(surf, &a, &b, 1, D_rgbaToFormat(surf->format, 0, 255, 0, 255));
 *
 * Like D_FillRect(), to pass a colour into this
 *  function you need D_rgbaToFormat(). Its
 *  return value can be passed into col.
 *
 * It is safe to pass null for s, a, and b. The
 *  function would do nothing and return -1.
 *
 * If thickness is less than 1, the function does
 *  nothing and returns -2.
 *
 * s: The surface to draw onto.
 * a: A point on the surface to draw between.
 * b: Another point on the surface to draw
 *  between.
 * thickness: The thickness to draw the line.
 * col: The colour to draw the line.
 */
int D_DrawLine(D_Surf * s, D_Point * a, D_Point * b, int thickness, D_uint32 col){

    int x = 0;
    int y = 0;

    int xLimit = 0;
    int yLimit = 0;

    /* Thickness counter */
    int thickCount = 0;

    D_Point * temp = D_NULL;

    /* We need to make copies of a and b that can
     *  be changed without affecting the original
     *  values passed into the function. They get
     *  copied later in the function. Bear in
     *  mind the pointers may get swaped (read
     *  below). */
    D_Point a2 = {0};
    D_Point b2 = {0};

    if(s == D_NULL || a == D_NULL || b == D_NULL){
        return -1;
    };

    if(thickness < 1){
        return -2;
    };

    /* Swap pointers to A and B if the line is
     *  more than 45 degrees anticlockwise from
     *  the x axis (comment out the statement to
     *  see what happens and understand it
     *  better). */
    if(-(b->y - a->y) > (b->x - a->x)){
        temp = a;
        a = b;
        b = temp;
    };

    if((b->x - a->x) > (b->y - a->y)){

        /* Copy Points a and b, while moving them
         *  down by half the thickness. */
        a2.x = a->x;
        a2.y = a->y + (thickness / 2);

        b2.x = b->x;
        b2.y = b->y + (thickness / 2);

        /* Edge case which would involve a
         *  division by 0 */
        if(b2.x == a2.x){
            /* Do nothing */
            return 0;
        };

        if(a2.x >= s->safeArea.x){
            x = a2.x;
        }else{
            x = s->safeArea.x;
        };

        /* Set the xLimit to b2.x or the right
         *  edge of the safe area, whichever is
         *  smaller (leftmost). */
        if(b2.x < s->safeArea.x + s->safeArea.w){
            xLimit = b2.x;
        }else{
            xLimit = s->safeArea.x + s->safeArea.w;
        };

        /* At this point, a pixel should not be
         *  drawn to the right of the x limit for
         *  memory safety but yLimit can be
         *  ignored. (Also don't draw on the
         *  xLimit). */

        /* For each column of pixels between A
         *  and B. */
        for(; x < xLimit; x++){

            y = ((((x - a2.x) * (b2.y - a2.y)) / (b2.x - a2.x)) + a2.y);

            /* If the pixel is outside the safe
             *  area (off the bottom) then set
             *  thickCount so it never draws
             *  below the safe area.*/
            if(y >= s->safeArea.y + s->safeArea.h){
                thickCount = (y - (s->safeArea.y + s->safeArea.h)) + 1;
            }else{
                thickCount = 0;
            };

            /* Draw the pixels for this column */
            for(; thickCount < thickness && y - thickCount >= s->safeArea.y; thickCount++){
                *((D_uint32 *)(((D_uint8 *)(s->pix)) + ((((y - thickCount) * s->w) + x) * 4) + (s->pitch * (y - thickCount)))) = col;
            };
        };

    }else{

        /* Edge case which would involve a
         *  division by 0 */
        if(b->y == a->y){
            /* Do nothing */
            return 0;
        };

        if(a->y >= s->safeArea.y){
            y = a->y;
        }else{
            y = s->safeArea.y;
        };

        /* Set the yLimit to b->y or the bottom
         *  edge of the safe area, whichever is
         *  smaller (above). */
        if(b->y < s->safeArea.y + s->safeArea.h){
            yLimit = b->y;
        }else{
            yLimit = s->safeArea.y + s->safeArea.h;
        };

        /* At this point, a pixel should not be
         *  drawn below the y limit for memory
         *  safety but xLimit can be ignored.
         *  (Also don't draw on the yLimit). */

        /* For each row of pixels between A
         *  and B. */
        for(; y < yLimit; y++){

            x = ((((y - a->y) * (b->x - a->x)) / (b->y - a->y)) + a->x);

            /* If the pixel is outside the safe
             *  area then don't draw it (skip to
             *  the next one). */
            if(x < s->safeArea.x || x >= s->safeArea.x + s->safeArea.w){
                continue;
            };

            /* Draw the pixel */
            *((D_uint32 *)(((D_uint8 *)(s->pix)) + (((y * s->w) + x) * 4) + (s->pitch * y))) = col;
        };
    };

    return 0;
};

/* This macro is for the D_SurfCopyScale()
 *  function. It's the loop that copies pixels.
 *  The reason it's a macro is to stop code
 *  duplication (9 times).
 *
 * Don't try to edit the macro directly (your
 *  changes might get removed accidentally).
 *  Instead edit the code below (which is much
 *  more readable) and copy paste it into this
 *  macro, removing all the newlines, tabs and
 *  comments.
 *
 * This macro is only intended for use in
 *  D_SurfCopyScale() and uses local variables in
 *  it.
 *
 * Make sure that srcType and dstType are the
 *  correct data type:
 *  D_uint32 if the bit depth is 32.
 *  D_uint16 if the bit depth is 16.
 *  D_uint8 if the bit depth is 8.
 *
 * Purposely giving an incorrect data type for
 *  srcType or dstType may not do what you expect
 *  because the macro also uses bit depth
 *  information directly from s1 and s2 in
 *  D_SurfCopyScale().
 *
 * srcType: The data type to cast source pixel
 *  data to (read above).
 * dstType: The data type to cast destination
 *  pixel data to (read above).
 * returns: Void.
 */
#define D_D_SCSLOOP(srcType, dstType) {while(dstY < lr2.y + lr2.h){srcY = ((((dstY - sr2.y) * sr1.h) / sr2.h) + sr1.y);if(srcY < lr1.y){dstY++;continue;}else if(srcY >= lr1.y + lr1.h){break;};dstX = lr2.x;while(dstX < lr2.x + lr2.w){srcX = ((((dstX - sr2.x) * sr1.w) / sr2.w) + sr1.x);if(srcX < lr1.x){dstX++;continue;}else if(srcX >= lr1.x + lr1.w){break;};D_FormatTorgba(*((srcType *)(((D_uint8 *)(s1->pix)) + ((((srcY * s1->w) + srcX) * (D_BITDEPTHTOBYTES(s1->format.bitDepth))) + (s1->pitch * srcY)))),s1->format,&sr, &sg, &sb, &sa);D_FormatTorgba(*((dstType *)(((D_uint8 *)(s2->pix)) + ((((dstY * s2->w) + dstX) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * dstY)))),s2->format,&dr, &dg, &db, &da);sa = (sa * s1->alphaMod) / 255;D_Blend(s1->blendMode, sr, sg, sb, sa, dr, dg, db, da, &rr, &rg, &rb, &ra);*((dstType *)(((D_uint8 *)(s2->pix)) + ((((dstY * s2->w) + dstX) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * dstY)))) = D_rgbaToFormat(s2->format, rr, rg, rb, ra);dstX++;};dstY++;};}

#if 0

    /* Edit this code below instead of the macro
     *  above, then copy it onto the macro
     *  (remove the old macro code first) and
     *  remove all newlines, tabs and comments.
     */

    {while(dstY < lr2.y + lr2.h){
        srcY = ((((dstY - sr2.y) * sr1.h) / sr2.h) + sr1.y);

        /*If above the limit area (on s1), skip*/
        if(srcY < lr1.y){
            dstY++;
            continue;

        /*If below the limit area (on s1), stop*/
        }else if(srcY >= lr1.y + lr1.h){
            break;
        };

        dstX = lr2.x;
        while(dstX < lr2.x + lr2.w){
            srcX = ((((dstX - sr2.x) * sr1.w) / sr2.w) + sr1.x);

            /* If to the left of limit area (on
             *  s1), skip. */
            if(srcX < lr1.x){
                dstX++;
                continue;

            /* If to the right of limit area (on
             *  s1), stop this line. */
            }else if(srcX >= lr1.x + lr1.w){
                break;
            };

            /* Get source colour from pixel */
            D_FormatTorgba(
                *((srcType *)(((D_uint8 *)(s1->pix)) + ((((srcY * s1->w) + srcX) * (D_BITDEPTHTOBYTES(s1->format.bitDepth))) + (s1->pitch * srcY)))),
                s1->format,
                &sr, &sg, &sb, &sa
            );

            /* Get destination colour from pixel
             */
            D_FormatTorgba(
                *((dstType *)(((D_uint8 *)(s2->pix)) + ((((dstY * s2->w) + dstX) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * dstY)))),
                s2->format,
                &dr, &dg, &db, &da
            );

            /* Multiply in alpha mod */
            sa = (sa * s1->alphaMod) / 255;

            D_Blend(s1->blendMode, sr, sg, sb, sa, dr, dg, db, da, &rr, &rg, &rb, &ra);

            /* Write the result colour to s2 */
            *((dstType *)(((D_uint8 *)(s2->pix)) + ((((dstY * s2->w) + dstX) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * dstY)))) =
            D_rgbaToFormat(s2->format, rr, rg, rb, ra);

            dstX++;
        };

        dstY++;
    };}

#endif


/* This function copies one surface onto another,
 *  it can copy part of the source to part of the
 *  destination.
 *
 * For now, this function can only copy between
 *  surfaces with the same format and must have a
 *  bit depth of 32.
 *
 * It is safe to pass null for s1 and s2, the
 *  function would do nothing and return -1.
 *
 * s1: The surface to copy from.
 * r1: What part of s1 to copy, pass D_NULL for
 *  the whole of s1.
 * s2: The surface to copy to.
 * r2: Where to copy onto s2. Pass D_NULL to copy
 *  onto the whole of s2.
 * returns: 0 on success or a negative number on
 *  failure.
 */
int D_SurfCopyScale(D_Surf * s1, D_Rect * r1, D_Surf * s2, D_Rect * r2){

    if(s1 == D_NULL || s2 == D_NULL){
        return -1;
    };


    /* sr1 means size rect 1, it's the same as r1
     *  except it can't be null. */
    D_Rect sr1 = {0};
    if(r1 == D_NULL){
        sr1.x = 0;
        sr1.y = 0;
        sr1.w = s1->w;
        sr1.h = s1->h;
    }else{
        sr1 = *r1;
    };


    /* sr2 means size rect 2, it's the same as r2
     *  except it can't be null. */
    D_Rect sr2 = {0};
    if(r2 == D_NULL){
        sr2.x = 0;
        sr2.y = 0;
        sr2.w = s2->w;
        sr2.h = s2->h;
    }else{
        sr2 = *r2;
    };

    /* lr1 means "limit rect 1". It is the same
     *  as sr1 except clipped to s1->safeArea.
     *  This function should not read pixels
     *  outside lr1. The reason lr2 exists is
     *  because clipping sr1 would cause
     *  stretching in ways the user of this
     *  function may not want. This also applies
     *  to lr2 being a copy of sr2 clipped to
     *  s2->safeArea. */
    D_Rect lr1 = sr1;
    D_ClipRect(s1->safeArea.x, s1->safeArea.y, s1->safeArea.w, s1->safeArea.h, &lr1);

    D_Rect lr2 = sr2;
    D_ClipRect(s2->safeArea.x, s2->safeArea.y, s2->safeArea.w, s2->safeArea.h, &lr2);


    /* Source pixel colour */
    int sr = 0;
    int sg = 0;
    int sb = 0;
    int sa = 0;

    /* Destination pixel colour */
    int dr = 0;
    int dg = 0;
    int db = 0;
    int da = 0;

    /* Result pixel colour */
    int rr = 0;
    int rg = 0;
    int rb = 0;
    int ra = 0;

    /* Loop through the pixels of the destination
     *  surface. Left to right, top to bottom. */
    int dstX = lr2.x;
    int dstY = lr2.y;
    int srcX = 0;
    int srcY = 0;

    switch(D_BITDEPTHTOBYTES(s1->format.bitDepth)){

        case 4:
            switch(D_BITDEPTHTOBYTES(s2->format.bitDepth)){
                case 4:
                    D_D_SCSLOOP(D_uint32, D_uint32);
                    break;
                case 2:
                    D_D_SCSLOOP(D_uint32, D_uint16);
                    break;
                case 1:
                    D_D_SCSLOOP(D_uint32, D_uint8);
                    break;
            };
            break;

        case 2:
            switch(D_BITDEPTHTOBYTES(s2->format.bitDepth)){
                case 4:
                    D_D_SCSLOOP(D_uint16, D_uint32);
                    break;
                case 2:
                    D_D_SCSLOOP(D_uint16, D_uint16);
                    break;
                case 1:
                    D_D_SCSLOOP(D_uint16, D_uint8);
                    break;
            };
            break;

        case 1:
            switch(D_BITDEPTHTOBYTES(s2->format.bitDepth)){
                case 4:
                    D_D_SCSLOOP(D_uint8, D_uint32);
                    break;
                case 2:
                    D_D_SCSLOOP(D_uint8, D_uint16);
                    break;
                case 1:
                    D_D_SCSLOOP(D_uint8, D_uint8);
                    break;
            };
            break;
    };

    return 0;
};

/* Similar to D_D_SCSLOOP(), this macro copies
 *  data for D_SurfCopyScaleRot(). It's purpose
 *  is to use any source and destination pixel
 *  type, reducing code duplication (it would
 *  otherwise have to be copied 9 times).
 *
 * This macro is clearly unreadable, instead edit
 *  the commented code below this macro and
 *  replace the macro removing all newlines and
 *  comments.
 *
 * srcType: The type to cast source pixel data
 *  to.
 * dstType: The type to cast destination pixel
 *  data to.
 */
#define D_D_SCSRLOOP(srcType, dstType) {if((deg < 45) || (deg >= 135 && deg < 225) || (deg >= 315)){while(yProg < (botly - toply)){dstX = toplx + (-slope * yProg);xProg = 0;srcY = (yProg * sr1.h) / (botly - toply);if(flipV){srcY = (sr1.h - srcY) - 1;};srcY = srcY + sr1.y;lineShiftHappened = lastDstX != dstX;lastDstX = dstX;if(srcY < s1->safeArea.y){yProg++;continue;};if(srcY >= s1->safeArea.y + s1->safeArea.h){yProg++;continue;};while(xProg < (toprx - toplx)){dstY = toply + (slope * xProg) + yProg;srcX = (xProg * sr1.w) / (toprx - toplx);if(flipH){srcX = (sr1.w - srcX) - 1;};srcX = srcX + sr1.x;if(srcX < s1->safeArea.x){dstX++;xProg++;continue;};if(srcX >= s1->safeArea.x + s1->safeArea.w){dstX++;xProg++;continue;};if(dstY < (s2->safeArea.y + s2->safeArea.h) && dstY >= s2->safeArea.y && dstX < (s2->safeArea.x + s2->safeArea.w) && dstX >= s2->safeArea.x){D_FormatTorgba(*((srcType *)(((D_uint8 *)s1->pix) + (((srcY * s1->w) + srcX) * (D_BITDEPTHTOBYTES(s1->format.bitDepth))) + (s1->pitch * srcY))),s1->format, &sr, &sg, &sb, &sa);D_FormatTorgba(*((dstType *)(((D_uint8 *)s2->pix) + (((dstY * s2->w) + dstX) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * dstY))),s2->format, &dr, &dg, &db, &da);D_Blend(s1->blendMode, sr, sg, sb, sa, dr, dg, db, da, &rr, &rg, &rb, &ra);col = D_rgbaToFormat(s2->format, rr, rg, rb, ra);*((dstType *)(((D_uint8 *)s2->pix) + (((dstY * s2->w) + dstX) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * dstY))) = col;if(dstY != lastDstY && lineShiftHappened){if(deg <= 45 || (deg >= 180 && deg <= 225)){if((dstY - 1) < (s2->safeArea.y + s2->safeArea.h) && (dstY - 1) >= s2->safeArea.y && dstX < (s2->safeArea.x + s2->safeArea.w) && dstX >= s2->safeArea.x){*((dstType *)(((D_uint8 *)s2->pix) + ((((dstY - 1) * s2->w) + dstX) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * (dstY - 1)))) = col;};}else{if(dstY < (s2->safeArea.y + s2->safeArea.h) && dstY >= s2->safeArea.y && (dstX - 1) < (s2->safeArea.x + s2->safeArea.w) && (dstX - 1) >= s2->safeArea.x){*((dstType *)(((D_uint8 *)s2->pix) + (((dstY * s2->w) + (dstX - 1)) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * dstY))) = col;};};};};lastDstY = dstY;dstX++;xProg++;};yProg++;};}else{slope = (toprx - toplx) / (topry - toply);while(xProg < (toplx - botlx)){srcY = (xProg * sr1.h) / (toplx - botlx);if(flipV){srcY = (sr1.h - srcY) - 1;};srcY = srcY + sr1.y;if(srcY < s1->safeArea.y){xProg++;continue;};if(srcY >= s1->safeArea.y + s1->safeArea.h){xProg++;continue;};dstY = toply + (slope * xProg); lineShiftHappened = (dstY != lastDstY); lastDstY = dstY; yProg = 0; while(yProg < (topry - toply)){srcX = (yProg * sr1.w) / (topry - toply);if(flipH){srcX = (sr1.w - srcX) - 1;};srcX = srcX + sr1.x;if(srcX < s1->safeArea.x){dstY++;yProg++;continue;};if(srcX >= s1->safeArea.x + s1->safeArea.w){dstY++;yProg++;continue;};dstX = toplx + (slope * yProg) - xProg;if(dstY < (s2->safeArea.y + s2->safeArea.h) && dstY >= s2->safeArea.y && dstX < (s2->safeArea.x + s2->safeArea.w) && dstX >= s2->safeArea.x){D_FormatTorgba(*((srcType *)(((D_uint8 *)s1->pix) + (((srcY * s1->w) + srcX) * (D_BITDEPTHTOBYTES(s1->format.bitDepth))) + (s1->pitch * srcY))),s1->format, &sr, &sg, &sb, &sa);D_FormatTorgba(*((dstType *)(((D_uint8 *)s2->pix) + (((dstY * s2->w) + dstX) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * dstY))),s2->format, &dr, &dg, &db, &da);D_Blend(s1->blendMode, sr, sg, sb, sa, dr, dg, db, da, &rr, &rg, &rb, &ra);col = D_rgbaToFormat(s2->format, rr, rg, rb, ra);*((dstType *)(((D_uint8 *)s2->pix) + (((dstY * s2->w) + dstX) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * dstY))) = col;if(lineShiftHappened && dstX != lastDstX){if(deg <= 90 || (deg >= 225 && deg <= 270)){if((dstY - 1) < (s2->safeArea.y + s2->safeArea.h) && (dstY - 1) >= s2->safeArea.y && dstX < (s2->safeArea.x + s2->safeArea.w) && dstX >= s2->safeArea.x){*((dstType *)(((D_uint8 *)s2->pix) + ((((dstY - 1) * s2->w) + dstX) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * (dstY - 1)))) = col;};}else{if(dstY < (s2->safeArea.y + s2->safeArea.h) && dstY >= s2->safeArea.y && (dstX + 1) < (s2->safeArea.x + s2->safeArea.w) && (dstX + 1) >= s2->safeArea.x){*((dstType *)(((D_uint8 *)s2->pix) + (((dstY * s2->w) + (dstX + 1)) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * dstY))) = col;};};};};lastDstX = dstX;dstY++;yProg++;};xProg++;};};}

#if 0

    /* The code below is the readable version of
     *  the code above, to edit the above macro
     *  edit this code below and replace the
     *  macro with it removing any comments and
     *  newlines. Read the comment above the
     *  macro.*/

    {if((deg < 45) || (deg >= 135 && deg < 225) || (deg >= 315)){
        while(yProg < (botly - toply)){

            dstX = toplx + (-slope * yProg);

            xProg = 0;
            srcY = (yProg * sr1.h) / (botly - toply);

            if(flipV){
                srcY = (sr1.h - srcY) - 1;
            };

            srcY = srcY + sr1.y;

            lineShiftHappened = lastDstX != dstX;
            lastDstX = dstX;


            /* Two if statements to stop data
             *  getting read unsafely. */
            if(srcY < s1->safeArea.y){
                yProg++;
                continue;
            };
            if(srcY >= s1->safeArea.y + s1->safeArea.h){
                yProg++;
                continue;
            };


            while(xProg < (toprx - toplx)){

                dstY = toply + (slope * xProg) + yProg;


                srcX = (xProg * sr1.w) / (toprx - toplx);

                if(flipH){
                    srcX = (sr1.w - srcX) - 1;
                };

                srcX = srcX + sr1.x;


                /* Two more if statements to stop
                 *  data getting read unsafely.*/
                if(srcX < s1->safeArea.x){
                    dstX++;
                    xProg++;
                    continue;
                };
                if(srcX >= s1->safeArea.x + s1->safeArea.w){
                    dstX++;
                    xProg++;
                    continue;
                };


                if(dstY < (s2->safeArea.y + s2->safeArea.h) && dstY >= s2->safeArea.y && dstX < (s2->safeArea.x + s2->safeArea.w) && dstX >= s2->safeArea.x){
                    D_FormatTorgba(*((srcType *)(((D_uint8 *)s1->pix) + (((srcY * s1->w) + srcX) * (D_BITDEPTHTOBYTES(s1->format.bitDepth))) + (s1->pitch * srcY))),
                                s1->format, &sr, &sg, &sb, &sa);

                    D_FormatTorgba(*((dstType *)(((D_uint8 *)s2->pix) + (((dstY * s2->w) + dstX) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * dstY))),
                                   s2->format, &dr, &dg, &db, &da);

                    D_Blend(s1->blendMode, sr, sg, sb, sa, dr, dg, db, da, &rr, &rg, &rb, &ra);

                    col = D_rgbaToFormat(s2->format, rr, rg, rb, ra);

                    *((dstType *)(((D_uint8 *)s2->pix) + (((dstY * s2->w) + dstX) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * dstY))) = col;

                    /* Fill in missing pixels
                     *  (comment out the below
                     *  conditional code to see
                     *  the holes). */
                    if(dstY != lastDstY && lineShiftHappened){

                        if(deg <= 45 || (deg >= 180 && deg <= 225)){
                            if((dstY - 1) < (s2->safeArea.y + s2->safeArea.h) && (dstY - 1) >= s2->safeArea.y && dstX < (s2->safeArea.x + s2->safeArea.w) && dstX >= s2->safeArea.x){
                                *((dstType *)(((D_uint8 *)s2->pix) + ((((dstY - 1) * s2->w) + dstX) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * (dstY - 1)))) = col;
                            };
                        }else{
                            if(dstY < (s2->safeArea.y + s2->safeArea.h) && dstY >= s2->safeArea.y && (dstX - 1) < (s2->safeArea.x + s2->safeArea.w) && (dstX - 1) >= s2->safeArea.x){
                                *((dstType *)(((D_uint8 *)s2->pix) + (((dstY * s2->w) + (dstX - 1)) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * dstY))) = col;
                            };
                        };
                    };

                };

                lastDstY = dstY;

                dstX++;
                xProg++;
            };

            yProg++;
        };
    }else{

        /* Get the inverted slope */
        slope = (toprx - toplx) / (topry - toply);


        while(xProg < (toplx - botlx)){

            srcY = (xProg * sr1.h) / (toplx - botlx);

            if(flipV){
                srcY = (sr1.h - srcY) - 1;
            };

            srcY = srcY + sr1.y;

            /* Two if statements to stop data
             *  getting read unsafely. */
            if(srcY < s1->safeArea.y){
                xProg++;
                continue;
            };
            if(srcY >= s1->safeArea.y + s1->safeArea.h){
                xProg++;
                continue;
            };


            dstY = toply + (slope * xProg);

            lineShiftHappened = (dstY != lastDstY);

            lastDstY = dstY;
            yProg = 0;
            while(yProg < (topry - toply)){

                srcX = (yProg * sr1.w) / (topry - toply);

                if(flipH){
                    srcX = (sr1.w - srcX) - 1;
                };

                srcX = srcX + sr1.x;


                /* Two more if statements to stop
                 *  data getting read unsafely.*/
                if(srcX < s1->safeArea.x){
                    dstY++;
                    yProg++;
                    continue;
                };
                if(srcX >= s1->safeArea.x + s1->safeArea.w){
                    dstY++;
                    yProg++;
                    continue;
                };


                dstX = toplx + (slope * yProg) - xProg;


                if(dstY < (s2->safeArea.y + s2->safeArea.h) && dstY >= s2->safeArea.y && dstX < (s2->safeArea.x + s2->safeArea.w) && dstX >= s2->safeArea.x){
                    D_FormatTorgba(*((srcType *)(((D_uint8 *)s1->pix) + (((srcY * s1->w) + srcX) * (D_BITDEPTHTOBYTES(s1->format.bitDepth))) + (s1->pitch * srcY))),
                                s1->format, &sr, &sg, &sb, &sa);

                    D_FormatTorgba(*((dstType *)(((D_uint8 *)s2->pix) + (((dstY * s2->w) + dstX) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * dstY))),
                                   s2->format, &dr, &dg, &db, &da);

                    D_Blend(s1->blendMode, sr, sg, sb, sa, dr, dg, db, da, &rr, &rg, &rb, &ra);

                    col = D_rgbaToFormat(s2->format, rr, rg, rb, ra);

                    *((dstType *)(((D_uint8 *)s2->pix) + (((dstY * s2->w) + dstX) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * dstY))) = col;


                    /* Fill in missing pixels
                     *  (comment out the below
                     *  conditional code to see
                     *  the holes). */
                    if(lineShiftHappened && dstX != lastDstX){

                        if(deg <= 90 || (deg >= 225 && deg <= 270)){
                            if((dstY - 1) < (s2->safeArea.y + s2->safeArea.h) && (dstY - 1) >= s2->safeArea.y && dstX < (s2->safeArea.x + s2->safeArea.w) && dstX >= s2->safeArea.x){
                                *((dstType *)(((D_uint8 *)s2->pix) + ((((dstY - 1) * s2->w) + dstX) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * (dstY - 1)))) = col;
                            };
                        }else{
                            if(dstY < (s2->safeArea.y + s2->safeArea.h) && dstY >= s2->safeArea.y && (dstX + 1) < (s2->safeArea.x + s2->safeArea.w) && (dstX + 1) >= s2->safeArea.x){
                                *((dstType *)(((D_uint8 *)s2->pix) + (((dstY * s2->w) + (dstX + 1)) * (D_BITDEPTHTOBYTES(s2->format.bitDepth))) + (s2->pitch * dstY))) = col;
                            };};
                    };
                };

                lastDstX = dstX;

                dstY++;
                yProg++;
            };

            xProg++;
        };
    };}

#endif

/* This function does the same thing as
 *  D_SurfCopyScale() except it can also rotate
 *  the image data.
 *
 * This function ignores any precision in "deg"
 *  that is smaller that a hundredth 1/100.
 *
 * Note that centre is relative to r2.
 *
 * s1: The source surface to copy from.
 * r1: Which part of s1 to copy.
 * s2: The destination surface to copy to.
 * r2: Which part of s2 to write to.
 * centre: The centre of rotation to rotate the
 *  image around while copying (this point is
 *  relative to r2).
 * deg: The number of degrees to rotate the
 *  image.
 * flipV: Pass 1 (or any non-zero) to flip the
 *  image vertically, pass 0 for no vertical
 *  flip.
 * flipH: Pass 1 (or any non-zero) to flip the
 *  image horizontally, pass 0 for no horizontal
 *  flip.
 * returns: 0 on success or a negative number on
 *  failure.
 */
int D_SurfCopyScaleRot(D_Surf * s1, D_Rect * r1, D_Surf * s2, D_Rect * r2, D_Point * centre, D_double deg, int flipV, int flipH){

    /* This function does not use trigonometry
     *  functions, instead it can rotate points
     *  by multiplying complex numbers. To be
     *  able to understand and update this
     *  function, you will need some
     *  understanding of complex numbers and the
     *  complex plane (watching one youtube video
     *  may be enough depending on your maths
     *  skill level).
     *
     * Please bear in mind that to simplify
     *  implementation, degrees are used to
     *  measure angles.
     *
     * Also bear in mind that the "first"and
     *  "second" numbers are just two complex
     *  numbers on the complex plane, the purpose
     *  of the first number is to rotate the
     *  second one by one degree when multiplied,
     *  the second number could be anything.
     *
     * Multiplying a complex number by any other
     *  complex number has two effects:
     *
     * - The second number's distance to the
     *  origin gets scaled by the first number's
     *  distance to the origin.
     *
     * - The second number's angle between it and
     *  the real axis gets added to by the first
     *  number's angle between it and the origin.
     *
     * The first effect isn't needed and can be
     *  made of no effect by ensuring the
     *  distance between the origin and the first
     *  number is 1.
     *
     * The second effect of rotation is what we
     *  need, to make it useful, the angle
     *  between the first number and the real
     *  axis should be 1.
     *
     *                      point P
     *   |              _.-X
     *   |dist = 1 _.-''   |
     *   |    _.-''        |
     *   |.-''\  1 deg     |
     * --o-----|-----------|-----Real axis
     *   |
     *   |
     *  Imaginary axis
     *
     * After doing some trigonometry by hand, I
     *  found the value of the point P (it's
     *  position).
     *
     * P = 0.999847695156 + i 0.0174524064373
     *
     * The real and imaginary parts of this
     *  number are stored separately in pR and
     *  pC.
     *
     * Any x, y coordinate can be interpreted as
     *  a complex number and multiplied by p to
     *  rotate it 1 degree anticlockwise.
     *
     * Another trick is to negate the imaginary
     *  part of p to go clockwise.
     *
     * Now the parameter "deg" can be converted
     *  to a complex number using P so a rotation
     *  can be made by multiplying by one number.
     *  This new number is degR and degC.
     */

    if(s1 == D_NULL || s2 == D_NULL){
        return -1;
    };

    /* sr1 is the safe version of r1 that can't
     *  be null. */
    D_Rect sr1 = {0, 0, s1->w, s1->h};
    if(r1 != D_NULL){
        sr1 = *r1;
    };

    /* sr2 is the safe version of r2 that can't
     *  be null. */
    D_Rect sr2 = {0, 0, s2->w, s2->h};
    if(r2 != D_NULL){
        sr2 = *r2;
    };

    /* scen is the safe version of center that
     *  can't be null. */
    D_Point scen = {sr2.x + (sr2.w / 2), sr2.y + (sr2.h / 2)};
    if(centre != D_NULL){
        scen = *centre;
    };

    /* lr1 means "limit rect 1". It is the same
     *  as sr1 except clipped to s1->safeArea.
     *  This function should not read pixels
     *  outside lr1. The reason lr2 exists is
     *  because clipping sr1 would cause
     *  stretching in ways the user of this
     *  function may not want. This also applies
     *  to lr2 being a copy of sr2 clipped to
     *  s2->safeArea. */
    D_Rect lr1 = sr1;
    D_ClipRect(s1->safeArea.x, s1->safeArea.y, s1->safeArea.w, s1->safeArea.h, &lr1);

    D_Rect lr2 = sr2;
    D_ClipRect(s2->safeArea.x, s2->safeArea.y, s2->safeArea.w, s2->safeArea.h, &lr2);

    /* Cancel extra unnecessary rotations. */
    while(deg > 360){
        deg = deg - 360;
    };

    /* Cancel extra unnecessary negative
     *  rotations. */
    while(deg < 0){
        deg = deg + 360;
    };

    /* Note that this pR and pC rotate a point by
     *  0.01 degrees, not 1 degree. */
    const D_double pR = 0.999999984769;
    const D_double pC = 0.000174532924313;

    D_double temp = 0;

    D_double degR = 1;
    D_double degC = 0;

    /* Convert deg from degrees to a point on the
     *  complex plane */
    D_double i = 0;
    while(i < deg){

        /* Add one degree to degR and degC */
        temp = D_COMPLEXMULTR(degR, degC, pR, pC);
        degC = D_COMPLEXMULTC(degR, degC, pR, pC);
        degR = temp;

        i += 0.01;
    };



    /* Top left x and top left y*/
    D_double toplx = sr2.x;
    D_double toply = sr2.y;

    /* In case the rectangle is upside-down, flip
     *  the rectangle. */
    if(deg >= 135 && deg < 315){

        /* Notice this point is on the opposite
         *  side of the rectangle. */
        toplx = sr2.x + sr2.w;
        toply = sr2.y + sr2.h;
    };

    /* Make toplx, toply relative to centre
     *  (necessary for rotation). */
    toplx = toplx - (sr2.x + scen.x);
    toply = toply - (sr2.y + scen.y);

    /* Rotate toplx, toply "deg" number of
     *  degrees */
    temp = D_COMPLEXMULTR(toplx, toply, degR, degC);
    toply = D_COMPLEXMULTC(toplx, toply, degR, degC);
    toplx = temp;

    /* Make toplx, toply absolute again (relative
     *  to s2)*/
    toplx = toplx + (sr2.x + scen.x);
    toply = toply + (sr2.y + scen.y);

    /* Uncomment to see where toplx, toply are */
    /*D_Rect testtopl = {(int)(toplx - 4), (int)(toply - 4), 8, 8};
    D_FillRect(s2, &testtopl, D_rgbaToFormat(s2->format, 255, 240, 200, 255));*/



    /* Top right x, y */
    D_double toprx = sr2.x + sr2.w;
    D_double topry = sr2.y;

    /* In case the rectangle is upside-down, flip
     *  the rectangle. */
    if(deg >= 135 && deg < 315){

        /* Notice this point is on the opposite
         *  side of the rectangle. */
        toprx = sr2.x;
        topry = sr2.y + sr2.h;
    };

    /* Make toprx, topry relative to centre
     *  (necessary for rotation). */
    toprx = toprx - (sr2.x + scen.x);
    topry = topry - (sr2.y + scen.y);

    /* Rotate toprx, topry "deg" number of
     *  degrees */
    temp = D_COMPLEXMULTR(toprx, topry, degR, degC);
    topry = D_COMPLEXMULTC(toprx, topry, degR, degC);
    toprx = temp;

    /* Make toplx, toply absolute again (relative
     *  to s2)*/
    toprx = toprx + (sr2.x + scen.x);
    topry = topry + (sr2.y + scen.y);

    /* Uncomment to see where toprx, topry are */
    /*D_Rect testtopr = {(int)(toprx - 4), (int)(topry - 4), 8, 8};
    D_FillRect(s2, &testtopr, D_rgbaToFormat(s2->format, 255, 240, 200, 255));*/



    /* bottom left x, y */
    D_double botlx = sr2.x;
    D_double botly = sr2.y + sr2.h;

    /* In case the rectangle is upside-down, flip
     *  the rectangle. */
    if(deg >= 135 && deg < 315){

        /* Notice this point is on the opposite
         *  side of the rectangle. */
        botlx = sr2.x + sr2.w;
        botly = sr2.y;
    };

    /* Make botlx, botly relative to centre
     *  (necessary for rotation). */
    botlx = botlx - (sr2.x + scen.x);
    botly = botly - (sr2.y + scen.y);

    /* Rotate botlx, botly "deg" number of
     *  degrees */
    temp = D_COMPLEXMULTR(botlx, botly, degR, degC);
    botly = D_COMPLEXMULTC(botlx, botly, degR, degC);
    botlx = temp;

    /* Make botlx, botly absolute again (relative
     *  to s2)*/
    botlx = botlx + (sr2.x + scen.x);
    botly = botly + (sr2.y + scen.y);

    /* Uncomment to see where botlx, botly are */
    /*D_Rect testbotl = {(int)(botlx - 4), (int)(botly - 4), 8, 8};
    D_FillRect(s2, &testbotl, D_rgbaToFormat(s2->format, 255, 240, 200, 255));*/


    /* In case the rectangle is upside-down, flip
     *  the rectangle. */
    if(deg >= 135 && deg < 315){
        flipH = !flipH;
        flipV = !flipV;
    };

    /* Source pixel colour */
    int sr = 0;
    int sg = 0;
    int sb = 0;
    int sa = 0;

    /* Destination pixel colour */
    int dr = 0;
    int dg = 0;
    int db = 0;
    int da = 0;

    /* Result pixel colour */
    int rr = 0;
    int rg = 0;
    int rb = 0;
    int ra = 0;


    int dstX = 0;
    int dstY = toply;
    int lastDstY = toply;
    int lastDstX = 0;

    /* Set to non-zero every time a line gets
     *  drawn to the left of the previous one,
     *  otherwise 0.*/
    int lineShiftHappened = 0;

    int srcX = sr1.x;
    int srcY = sr1.y;

    /* This is x progress, every time a pixel
     *  gets drawn, it increments. Think of it as
     *  srcX except before rotation and relative
     *  to sr2.x (it ranges between 0 and toprx -
     *  toplx).*/
    int xProg = 0;
    int yProg = 0;

    /* slope is the slope of the line between
     *  toplx, toply and toprx, topry. Note that
     *  this slope is negative compared to what
     *  you would traditionally think. */
    D_double slope = (topry - toply) / (toprx - toplx);

    D_uint32 col = 0;


    switch(D_BITDEPTHTOBYTES(s1->format.bitDepth)){
        case 4:

            switch(D_BITDEPTHTOBYTES(s2->format.bitDepth)){
                case 4:
                    D_D_SCSRLOOP(D_uint32, D_uint32);
                    break;
                case 2:
                    D_D_SCSRLOOP(D_uint32, D_uint16);
                    break;
                case 1:
                    D_D_SCSRLOOP(D_uint32, D_uint8);
                    break;
            };

            break;
        case 2:

            switch(D_BITDEPTHTOBYTES(s2->format.bitDepth)){
                case 4:
                    D_D_SCSRLOOP(D_uint16, D_uint32);
                    break;
                case 2:
                    D_D_SCSRLOOP(D_uint16, D_uint16);
                    break;
                case 1:
                    D_D_SCSRLOOP(D_uint16, D_uint8);
                    break;
            };

            break;
        case 1:

            switch(D_BITDEPTHTOBYTES(s2->format.bitDepth)){
                case 4:
                    D_D_SCSRLOOP(D_uint8, D_uint32);
                    break;
                case 2:
                    D_D_SCSRLOOP(D_uint8, D_uint16);
                    break;
                case 1:
                    D_D_SCSRLOOP(D_uint8, D_uint8);
                    break;
            };

            break;
    };


    return 0;
};

/* This finds the number position of where a
 *  character is on a character map.
 *
 * The width and height of a character on the
 *  font map are the same, it's the surface's
 *  width divided by 9. font->w / 9.
 *
 * Also the result x and y need to be multiplied
 *  by font->w / 9. This way they become real
 *  pixel coordinates that are relative to the
 *  the top left of the surface.
 *
 * This tool (https://stmn.itch.io/font2bitmap)
 *  is great for converting a font to a png image
 *  for this function. If you use this tool,
 *  these are some good default options:
 * - Per row: 9
 * - Grid width: 30
 * - Grid height: 30
 * - Font size: 24
 * - String: ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 0123456789.,;:$#'!"/?%&()@ ^*-_+=|\{}[]<>~`
 *
 * The only important options are a "Per row" of
 *  9 and the string.
 *
 * c: The character.
 * x: Gets filled in with the char x position on
 *  a font map.
 * y: Gets filled in with the char y position on
 *  a font map.
 * returns: 0 on success or -1 if the character is
 *  not recognised by the function.
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
        case ' ': n = 26; break;

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

        case '^': n = 81; break;
        case '*': n = 82; break;
        case '-': n = 83; break;
        case '_': n = 84; break;
        case '+': n = 85; break;
        case '=': n = 86; break;
        case '|': n = 87; break;
        case '\\': n = 88; break;
        case '{': n = 89; break;
        case '}': n = 90; break;
        case '[': n = 91; break;
        case ']': n = 92; break;
        case '<': n = 93; break;
        case '>': n = 94; break;
        case '~': n = 95; break;
        case '`': n = 96; break;

        default:  n = -1; break;
    };
    /*ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 0123456789.,;:$#'!"/?%&()@ ^*-_+=|\{}[]<>~` */

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

    /*Run D_SetError() when implemented.*/

#endif
/* endif D_ALLOW_STB_IMAGE */

    return s;
};

#endif
/* endif D_ALREADY_IMPLEMENTED */

#endif
/* endif D_IMPLEMENTATION */
