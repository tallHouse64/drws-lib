
/* This is the sound library of drws-lib.
 *
 * The "driver" library functions that can be
 *  used in drws-lib closely map to SDL
 *  functions, only SDL "driver" files would use
 *  the associated SDL functions.
 *
 * For the best compatibility, it is recommended
 *  that you only use 16 bit PCM audio.
 */

typedef struct D_SoundFormat {
    /* Frequency in Hertz, samples per second. */
    D_uint32 freq;

    /* 0 for little endian, 1 for big endian. */
    int bigEndian;

    int channels;

    int silence;

    int bitsPerSample;

    /* Buffer size in sample frames, for opening
     *  audio outputs (devices) */
    int bufferSize;
} D_SoundFormat;

typedef struct D_Sound {
    D_SoundFormat format;

    /* Like SDL, this is sample frames (which is
     *  total samples divided by channels). */
    int samples;
    void * data;
} D_Sound;

typedef D_AudioOutputId int
