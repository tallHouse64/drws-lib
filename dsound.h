
/* This is the sound library of drws-lib.
 */

typedef struct D_SoundFormat {
    /* Frequency in Hertz, samples per second. */
    D_uint32 freq;

    /* 0 for little endian, 1 for big endian. */
    int bigEndian;

    int bitsPerSample;
} D_SoundFormat;

typedef struct D_Sound {
    D_SoundFormat format;
    int channels;
    int samples;
    void * data;
} D_Sound;
