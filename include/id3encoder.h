
#ifndef ID3ENCODER_H
#define ID3ENCODER_H

#ifdef __cplusplus
extern "C" {
#endif

#define DRMP3_STRINGIFY(x)      #x
#define DRMP3_XSTRINGIFY(x)     DRMP3_STRINGIFY(x)

#define DRMP3_VERSION_MAJOR     0
#define DRMP3_VERSION_MINOR     6
#define DRMP3_VERSION_REVISION  15
#define DRMP3_VERSION_STRING    DRMP3_XSTRINGIFY(DRMP3_VERSION_MAJOR) "." DRMP3_XSTRINGIFY(DRMP3_VERSION_MINOR) "." DRMP3_XSTRINGIFY(DRMP3_VERSION_REVISION)

#include <stddef.h> /* For size_t. */

/* Sized types. Prefer built-in types. Fall back to stdint. */
#ifdef _MSC_VER
    #if defined(__clang__)
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wlanguage-extension-token"
        #pragma GCC diagnostic ignored "-Wlong-long"        
        #pragma GCC diagnostic ignored "-Wc++11-long-long"
    #endif
    typedef   signed __int8  drmp3_int8;
    typedef unsigned __int8  drmp3_uint8;
    typedef   signed __int16 drmp3_int16;
    typedef unsigned __int16 drmp3_uint16;
    typedef   signed __int32 drmp3_int32;
    typedef unsigned __int32 drmp3_uint32;
    typedef   signed __int64 drmp3_int64;
    typedef unsigned __int64 drmp3_uint64;
    #if defined(__clang__)
        #pragma GCC diagnostic pop
    #endif
#else
    #include <stdint.h>
    typedef int8_t           drmp3_int8;
    typedef uint8_t          drmp3_uint8;
    typedef int16_t          drmp3_int16;
    typedef uint16_t         drmp3_uint16;
    typedef int32_t          drmp3_int32;
    typedef uint32_t         drmp3_uint32;
    typedef int64_t          drmp3_int64;
    typedef uint64_t         drmp3_uint64;
#endif
typedef drmp3_uint8          drmp3_bool8;
typedef drmp3_uint32         drmp3_bool32;
#define DRMP3_TRUE           1
#define DRMP3_FALSE          0

#if !defined(DRMP3_API)
    #if defined(DRMP3_DLL)
        #if defined(_WIN32)
            #define DRMP3_DLL_IMPORT  __declspec(dllimport)
            #define DRMP3_DLL_EXPORT  __declspec(dllexport)
            #define DRMP3_DLL_PRIVATE static
        #else
            #if defined(__GNUC__) && __GNUC__ >= 4
                #define DRMP3_DLL_IMPORT  __attribute__((visibility("default")))
                #define DRMP3_DLL_EXPORT  __attribute__((visibility("default")))
                #define DRMP3_DLL_PRIVATE __attribute__((visibility("hidden")))
            #else
                #define DRMP3_DLL_IMPORT
                #define DRMP3_DLL_EXPORT
                #define DRMP3_DLL_PRIVATE static
            #endif
        #endif

        #if defined(DR_MP3_IMPLEMENTATION) || defined(DRMP3_IMPLEMENTATION)
            #define DRMP3_API  DRMP3_DLL_EXPORT
        #else
            #define DRMP3_API  DRMP3_DLL_IMPORT
        #endif
        #define DRMP3_PRIVATE DRMP3_DLL_PRIVATE
    #else
        #define DRMP3_API extern
        #define DRMP3_PRIVATE static
    #endif
#endif

typedef drmp3_int32 drmp3_result;
#define DRMP3_SUCCESS                        0
#define DRMP3_ERROR                         -1   /* A generic error. */
#define DRMP3_INVALID_ARGS                  -2
#define DRMP3_INVALID_OPERATION             -3
#define DRMP3_OUT_OF_MEMORY                 -4
#define DRMP3_OUT_OF_RANGE                  -5
#define DRMP3_ACCESS_DENIED                 -6
#define DRMP3_DOES_NOT_EXIST                -7
#define DRMP3_ALREADY_EXISTS                -8
#define DRMP3_TOO_MANY_OPEN_FILES           -9
#define DRMP3_INVALID_FILE                  -10
#define DRMP3_TOO_BIG                       -11
#define DRMP3_PATH_TOO_LONG                 -12
#define DRMP3_NAME_TOO_LONG                 -13
#define DRMP3_NOT_DIRECTORY                 -14
#define DRMP3_IS_DIRECTORY                  -15
#define DRMP3_DIRECTORY_NOT_EMPTY           -16
#define DRMP3_END_OF_FILE                   -17
#define DRMP3_NO_SPACE                      -18
#define DRMP3_BUSY                          -19
#define DRMP3_IO_ERROR                      -20
#define DRMP3_INTERRUPT                     -21
#define DRMP3_UNAVAILABLE                   -22
#define DRMP3_ALREADY_IN_USE                -23
#define DRMP3_BAD_ADDRESS                   -24
#define DRMP3_BAD_SEEK                      -25
#define DRMP3_BAD_PIPE                      -26
#define DRMP3_DEADLOCK                      -27
#define DRMP3_TOO_MANY_LINKS                -28
#define DRMP3_NOT_IMPLEMENTED               -29
#define DRMP3_NO_MESSAGE                    -30
#define DRMP3_BAD_MESSAGE                   -31
#define DRMP3_NO_DATA_AVAILABLE             -32
#define DRMP3_INVALID_DATA                  -33
#define DRMP3_TIMEOUT                       -34
#define DRMP3_NO_NETWORK                    -35
#define DRMP3_NOT_UNIQUE                    -36
#define DRMP3_NOT_SOCKET                    -37
#define DRMP3_NO_ADDRESS                    -38
#define DRMP3_BAD_PROTOCOL                  -39
#define DRMP3_PROTOCOL_UNAVAILABLE          -40
#define DRMP3_PROTOCOL_NOT_SUPPORTED        -41
#define DRMP3_PROTOCOL_FAMILY_NOT_SUPPORTED -42
#define DRMP3_ADDRESS_FAMILY_NOT_SUPPORTED  -43
#define DRMP3_SOCKET_NOT_SUPPORTED          -44
#define DRMP3_CONNECTION_RESET              -45
#define DRMP3_ALREADY_CONNECTED             -46
#define DRMP3_NOT_CONNECTED                 -47
#define DRMP3_CONNECTION_REFUSED            -48
#define DRMP3_NO_HOST                       -49
#define DRMP3_IN_PROGRESS                   -50
#define DRMP3_CANCELLED                     -51
#define DRMP3_MEMORY_ALREADY_MAPPED         -52
#define DRMP3_AT_END                        -53


#define DRMP3_MAX_PCM_FRAMES_PER_MP3_FRAME  1152
#define DRMP3_MAX_SAMPLES_PER_FRAME         (DRMP3_MAX_PCM_FRAMES_PER_MP3_FRAME*2)

#ifdef _MSC_VER
    #define DRMP3_INLINE __forceinline
#elif defined(__GNUC__)
    /*
    I've had a bug report where GCC is emitting warnings about functions possibly not being inlineable. This warning happens when
    the __attribute__((always_inline)) attribute is defined without an "inline" statement. I think therefore there must be some
    case where "__inline__" is not always defined, thus the compiler emitting these warnings. When using -std=c89 or -ansi on the
    command line, we cannot use the "inline" keyword and instead need to use "__inline__". In an attempt to work around this issue
    I am using "__inline__" only when we're compiling in strict ANSI mode.
    */
    #if defined(__STRICT_ANSI__)
        #define DRMP3_INLINE __inline__ __attribute__((always_inline))
    #else
        #define DRMP3_INLINE inline __attribute__((always_inline))
    #endif
#else
    #define DRMP3_INLINE
#endif


DRMP3_API void drmp3_version(drmp3_uint32* pMajor, drmp3_uint32* pMinor, drmp3_uint32* pRevision);
DRMP3_API const char* drmp3_version_string(void);


/*
Low Level Push API
==================
*/
typedef struct
{
    int frame_bytes, channels, hz, layer, bitrate_kbps;
} drmp3dec_frame_info;

typedef struct
{
    float mdct_overlap[2][9*32], qmf_state[15*2*32];
    int reserv, free_format_bytes;
    drmp3_uint8 header[4], reserv_buf[511];
} drmp3dec;

/* Initializes a low level decoder. */
DRMP3_API void drmp3dec_init(drmp3dec *dec);

/* Reads a frame from a low level decoder. */
DRMP3_API int drmp3dec_decode_frame(drmp3dec *dec, const drmp3_uint8 *mp3, int mp3_bytes, void *pcm, drmp3dec_frame_info *info);

/* Helper for converting between f32 and s16. */
DRMP3_API void drmp3dec_f32_to_s16(const float *in, drmp3_int16 *out, size_t num_samples);



/*
Main API (Pull API)
===================
*/
#ifndef DRMP3_DEFAULT_CHANNELS
#define DRMP3_DEFAULT_CHANNELS      2
#endif
#ifndef DRMP3_DEFAULT_SAMPLE_RATE
#define DRMP3_DEFAULT_SAMPLE_RATE   44100
#endif


typedef enum
{
    drmp3_seek_origin_start,
    drmp3_seek_origin_current
} drmp3_seek_origin;

typedef struct
{
    drmp3_uint64 seekPosInBytes;        /* Points to the first byte of an MP3 frame. */
    drmp3_uint64 pcmFrameIndex;         /* The index of the PCM frame this seek point targets. */
    drmp3_uint16 mp3FramesToDiscard;    /* The number of whole MP3 frames to be discarded before pcmFramesToDiscard. */
    drmp3_uint16 pcmFramesToDiscard;    /* The number of leading samples to read and discard. These are discarded after mp3FramesToDiscard. */
} drmp3_seek_point;

/*
Callback for when data is read. Return value is the number of bytes actually read.

pUserData   [in]  The user data that was passed to drmp3_init(), drmp3_open() and family.
pBufferOut  [out] The output buffer.
bytesToRead [in]  The number of bytes to read.

Returns the number of bytes actually read.

A return value of less than bytesToRead indicates the end of the stream. Do _not_ return from this callback until
either the entire bytesToRead is filled or you have reached the end of the stream.
*/
typedef size_t (* drmp3_read_proc)(void* pUserData, void* pBufferOut, size_t bytesToRead);

/*
Callback for when data needs to be seeked.

pUserData [in] The user data that was passed to drmp3_init(), drmp3_open() and family.
offset    [in] The number of bytes to move, relative to the origin. Will never be negative.
origin    [in] The origin of the seek - the current position or the start of the stream.

Returns whether or not the seek was successful.

Whether or not it is relative to the beginning or current position is determined by the "origin" parameter which
will be either drmp3_seek_origin_start or drmp3_seek_origin_current.
*/
typedef drmp3_bool32 (* drmp3_seek_proc)(void* pUserData, int offset, drmp3_seek_origin origin);

typedef struct
{
    void* pUserData;
    void* (* onMalloc)(size_t sz, void* pUserData);
    void* (* onRealloc)(void* p, size_t sz, void* pUserData);
    void  (* onFree)(void* p, void* pUserData);
} drmp3_allocation_callbacks;

typedef struct
{
    drmp3_uint32 channels;
    drmp3_uint32 sampleRate;
} drmp3_config;

typedef struct
{
    drmp3dec decoder;
    drmp3dec_frame_info frameInfo;
    drmp3_uint32 channels;
    drmp3_uint32 sampleRate;
    drmp3_read_proc onRead;
    drmp3_seek_proc onSeek;
    void* pUserData;
    drmp3_allocation_callbacks allocationCallbacks;
    drmp3_uint32 mp3FrameChannels;      /* The number of channels in the currently loaded MP3 frame. Internal use only. */
    drmp3_uint32 mp3FrameSampleRate;    /* The sample rate of the currently loaded MP3 frame. Internal use only. */
    drmp3_uint32 pcmFramesConsumedInMP3Frame;
    drmp3_uint32 pcmFramesRemainingInMP3Frame;
    drmp3_uint8 pcmFrames[sizeof(float)*DRMP3_MAX_SAMPLES_PER_FRAME];  /* <-- Multipled by sizeof(float) to ensure there's enough room for DR_MP3_FLOAT_OUTPUT. */
    drmp3_uint64 currentPCMFrame;       /* The current PCM frame, globally, based on the output sample rate. Mainly used for seeking. */
    drmp3_uint64 streamCursor;          /* The current byte the decoder is sitting on in the raw stream. */
    drmp3_seek_point* pSeekPoints;      /* NULL by default. Set with drmp3_bind_seek_table(). Memory is owned by the client. dr_mp3 will never attempt to free this pointer. */
    drmp3_uint32 seekPointCount;        /* The number of items in pSeekPoints. When set to 0 assumes to no seek table. Defaults to zero. */
    size_t dataSize;
    size_t dataCapacity;
    size_t dataConsumed;
    drmp3_uint8* pData;
    drmp3_bool32 atEnd : 1;
    struct
    {
        const drmp3_uint8* pData;
        size_t dataSize;
        size_t currentReadPos;
    } memory;   /* Only used for decoders that were opened against a block of memory. */
} drmp3;

/*
Initializes an MP3 decoder.

onRead    [in]           The function to call when data needs to be read from the client.
onSeek    [in]           The function to call when the read position of the client data needs to move.
pUserData [in, optional] A pointer to application defined data that will be passed to onRead and onSeek.

Returns true if successful; false otherwise.

Close the loader with drmp3_uninit().

See also: drmp3_init_file(), drmp3_init_memory(), drmp3_uninit()
*/
DRMP3_API drmp3_bool32 drmp3_init(drmp3* pMP3, drmp3_read_proc onRead, drmp3_seek_proc onSeek, void* pUserData, const drmp3_allocation_callbacks* pAllocationCallbacks);

/*
Initializes an MP3 decoder from a block of memory.

This does not create a copy of the data. It is up to the application to ensure the buffer remains valid for
the lifetime of the drmp3 object.

The buffer should contain the contents of the entire MP3 file.
*/
DRMP3_API drmp3_bool32 drmp3_init_memory(drmp3* pMP3, const void* pData, size_t dataSize, const drmp3_allocation_callbacks* pAllocationCallbacks);

#ifndef DR_MP3_NO_STDIO
/*
Initializes an MP3 decoder from a file.

This holds the internal FILE object until drmp3_uninit() is called. Keep this in mind if you're caching drmp3
objects because the operating system may restrict the number of file handles an application can have open at
any given time.
*/
DRMP3_API drmp3_bool32 drmp3_init_file(drmp3* pMP3, const char* pFilePath, const drmp3_allocation_callbacks* pAllocationCallbacks);
DRMP3_API drmp3_bool32 drmp3_init_file_w(drmp3* pMP3, const wchar_t* pFilePath, const drmp3_allocation_callbacks* pAllocationCallbacks);
#endif

/*
Uninitializes an MP3 decoder.
*/
DRMP3_API void drmp3_uninit(drmp3* pMP3);

/*
Reads PCM frames as interleaved 32-bit IEEE floating point PCM.

Note that framesToRead specifies the number of PCM frames to read, _not_ the number of MP3 frames.
*/
DRMP3_API drmp3_uint64 drmp3_read_pcm_frames_f32(drmp3* pMP3, drmp3_uint64 framesToRead, float* pBufferOut);

/*
Reads PCM frames as interleaved signed 16-bit integer PCM.

Note that framesToRead specifies the number of PCM frames to read, _not_ the number of MP3 frames.
*/
DRMP3_API drmp3_uint64 drmp3_read_pcm_frames_s16(drmp3* pMP3, drmp3_uint64 framesToRead, drmp3_int16* pBufferOut);

/*
Seeks to a specific frame.

Note that this is _not_ an MP3 frame, but rather a PCM frame.
*/
DRMP3_API drmp3_bool32 drmp3_seek_to_pcm_frame(drmp3* pMP3, drmp3_uint64 frameIndex);

/*
Calculates the total number of PCM frames in the MP3 stream. Cannot be used for infinite streams such as internet
radio. Runs in linear time. Returns 0 on error.
*/
DRMP3_API drmp3_uint64 drmp3_get_pcm_frame_count(drmp3* pMP3);

/*
Calculates the total number of MP3 frames in the MP3 stream. Cannot be used for infinite streams such as internet
radio. Runs in linear time. Returns 0 on error.
*/
DRMP3_API drmp3_uint64 drmp3_get_mp3_frame_count(drmp3* pMP3);

/*
Calculates the total number of MP3 and PCM frames in the MP3 stream. Cannot be used for infinite streams such as internet
radio. Runs in linear time. Returns 0 on error.

This is equivalent to calling drmp3_get_mp3_frame_count() and drmp3_get_pcm_frame_count() except that it's more efficient.
*/
DRMP3_API drmp3_bool32 drmp3_get_mp3_and_pcm_frame_count(drmp3* pMP3, drmp3_uint64* pMP3FrameCount, drmp3_uint64* pPCMFrameCount);

/*
Calculates the seekpoints based on PCM frames. This is slow.

pSeekpoint count is a pointer to a uint32 containing the seekpoint count. On input it contains the desired count.
On output it contains the actual count. The reason for this design is that the client may request too many
seekpoints, in which case dr_mp3 will return a corrected count.

Note that seektable seeking is not quite sample exact when the MP3 stream contains inconsistent sample rates.
*/
DRMP3_API drmp3_bool32 drmp3_calculate_seek_points(drmp3* pMP3, drmp3_uint32* pSeekPointCount, drmp3_seek_point* pSeekPoints);

/*
Binds a seek table to the decoder.

This does _not_ make a copy of pSeekPoints - it only references it. It is up to the application to ensure this
remains valid while it is bound to the decoder.

Use drmp3_calculate_seek_points() to calculate the seek points.
*/
DRMP3_API drmp3_bool32 drmp3_bind_seek_table(drmp3* pMP3, drmp3_uint32 seekPointCount, drmp3_seek_point* pSeekPoints);


/*
Opens an decodes an entire MP3 stream as a single operation.

On output pConfig will receive the channel count and sample rate of the stream.

Free the returned pointer with drmp3_free().
*/
DRMP3_API float* drmp3_open_and_read_pcm_frames_f32(drmp3_read_proc onRead, drmp3_seek_proc onSeek, void* pUserData, drmp3_config* pConfig, drmp3_uint64* pTotalFrameCount, const drmp3_allocation_callbacks* pAllocationCallbacks);
DRMP3_API drmp3_int16* drmp3_open_and_read_pcm_frames_s16(drmp3_read_proc onRead, drmp3_seek_proc onSeek, void* pUserData, drmp3_config* pConfig, drmp3_uint64* pTotalFrameCount, const drmp3_allocation_callbacks* pAllocationCallbacks);

DRMP3_API float* drmp3_open_memory_and_read_pcm_frames_f32(const void* pData, size_t dataSize, drmp3_config* pConfig, drmp3_uint64* pTotalFrameCount, const drmp3_allocation_callbacks* pAllocationCallbacks);
DRMP3_API drmp3_int16* drmp3_open_memory_and_read_pcm_frames_s16(const void* pData, size_t dataSize, drmp3_config* pConfig, drmp3_uint64* pTotalFrameCount, const drmp3_allocation_callbacks* pAllocationCallbacks);

#ifndef DR_MP3_NO_STDIO
DRMP3_API float* drmp3_open_file_and_read_pcm_frames_f32(const char* filePath, drmp3_config* pConfig, drmp3_uint64* pTotalFrameCount, const drmp3_allocation_callbacks* pAllocationCallbacks);
DRMP3_API drmp3_int16* drmp3_open_file_and_read_pcm_frames_s16(const char* filePath, drmp3_config* pConfig, drmp3_uint64* pTotalFrameCount, const drmp3_allocation_callbacks* pAllocationCallbacks);
#endif

/*
Allocates a block of memory on the heap.
*/
DRMP3_API void* drmp3_malloc(size_t sz, const drmp3_allocation_callbacks* pAllocationCallbacks);

/*
Frees any memory that was allocated by a public drmp3 API.
*/
DRMP3_API void drmp3_free(void* p, const drmp3_allocation_callbacks* pAllocationCallbacks);

#ifdef __cplusplus
}
#endif


/************************************************************************************************************************************************************
 ************************************************************************************************************************************************************

 IMPLEMENTATION

 ************************************************************************************************************************************************************
 ************************************************************************************************************************************************************/
#if defined(DR_MP3_IMPLEMENTATION) || defined(DRMP3_IMPLEMENTATION)
#ifndef dr_mp3_c
#define dr_mp3_c

#include <stdlib.h>
#include <string.h>
#include <limits.h> /* For INT_MAX */

DRMP3_API void drmp3_version(drmp3_uint32* pMajor, drmp3_uint32* pMinor, drmp3_uint32* pRevision)
{
    if (pMajor) {
        *pMajor = DRMP3_VERSION_MAJOR;
    }

    if (pMinor) {
        *pMinor = DRMP3_VERSION_MINOR;
    }

    if (pRevision) {
        *pRevision = DRMP3_VERSION_REVISION;
    }
}

DRMP3_API const char* drmp3_version_string(void)
{
    return DRMP3_VERSION_STRING;
}

/* Disable SIMD when compiling with TCC for now. */
#if defined(__TINYC__)
#define DR_MP3_NO_SIMD
#endif

#define DRMP3_OFFSET_PTR(p, offset) ((void*)((drmp3_uint8*)(p) + (offset)))

#define DRMP3_MAX_FREE_FORMAT_FRAME_SIZE  2304    /* more than ISO spec's */
#ifndef DRMP3_MAX_FRAME_SYNC_MATCHES
#define DRMP3_MAX_FRAME_SYNC_MATCHES      10
#endif

#define DRMP3_MAX_L3_FRAME_PAYLOAD_BYTES  DRMP3_MAX_FREE_FORMAT_FRAME_SIZE /* MUST be >= 320000/8/32000*1152 = 1440 */

#define DRMP3_MAX_BITRESERVOIR_BYTES      511
#define DRMP3_SHORT_BLOCK_TYPE            2
#define DRMP3_STOP_BLOCK_TYPE             3
#define DRMP3_MODE_MONO                   3
#define DRMP3_MODE_JOINT_STEREO           1
#define DRMP3_HDR_SIZE                    4
#define DRMP3_HDR_IS_MONO(h)              (((h[3]) & 0xC0) == 0xC0)
#define DRMP3_HDR_IS_MS_STEREO(h)         (((h[3]) & 0xE0) == 0x60)
#define DRMP3_HDR_IS_FREE_FORMAT(h)       (((h[2]) & 0xF0) == 0)
#define DRMP3_HDR_IS_CRC(h)               (!((h[1]) & 1))
#define DRMP3_HDR_TEST_PADDING(h)         ((h[2]) & 0x2)
#define DRMP3_HDR_TEST_MPEG1(h)           ((h[1]) & 0x8)
#define DRMP3_HDR_TEST_NOT_MPEG25(h)      ((h[1]) & 0x10)
#define DRMP3_HDR_TEST_I_STEREO(h)        ((h[3]) & 0x10)
#define DRMP3_HDR_TEST_MS_STEREO(h)       ((h[3]) & 0x20)
#define DRMP3_HDR_GET_STEREO_MODE(h)      (((h[3]) >> 6) & 3)
#define DRMP3_HDR_GET_STEREO_MODE_EXT(h)  (((h[3]) >> 4) & 3)
#define DRMP3_HDR_GET_LAYER(h)            (((h[1]) >> 1) & 3)
#define DRMP3_HDR_GET_BITRATE(h)          ((h[2]) >> 4)
#define DRMP3_HDR_GET_SAMPLE_RATE(h)      (((h[2]) >> 2) & 3)
#define DRMP3_HDR_GET_MY_SAMPLE_RATE(h)   (DRMP3_HDR_GET_SAMPLE_RATE(h) + (((h[1] >> 3) & 1) + ((h[1] >> 4) & 1))*3)
#define DRMP3_HDR_IS_FRAME_576(h)         ((h[1] & 14) == 2)
#define DRMP3_HDR_IS_LAYER_1(h)           ((h[1] & 6) == 6)

#define DRMP3_BITS_DEQUANTIZER_OUT        -1
#define DRMP3_MAX_SCF                     (255 + DRMP3_BITS_DEQUANTIZER_OUT*4 - 210)
#define DRMP3_MAX_SCFI                    ((DRMP3_MAX_SCF + 3) & ~3)

#define DRMP3_MIN(a, b)           ((a) > (b) ? (b) : (a))
#define DRMP3_MAX(a, b)           ((a) < (b) ? (b) : (a))

#if !defined(DR_MP3_NO_SIMD)

#if !defined(DR_MP3_ONLY_SIMD) && (defined(_M_X64) || defined(_M_ARM64) || defined(__x86_64__) || defined(__aarch64__))
/* x64 always have SSE2, arm64 always have neon, no need for generic code */
#define DR_MP3_ONLY_SIMD
#endif

#if ((defined(_MSC_VER) && _MSC_VER >= 1400) && (defined(_M_IX86) || defined(_M_X64))) || ((defined(__i386__) || defined(__x86_64__)) && defined(__SSE2__))
#if defined(_MSC_VER)
#include <intrin.h>
#endif
#include <emmintrin.h>
#define DRMP3_HAVE_SSE 1
#define DRMP3_HAVE_SIMD 1
#define DRMP3_VSTORE _mm_storeu_ps
#define DRMP3_VLD _mm_loadu_ps
#define DRMP3_VSET _mm_set1_ps
#define DRMP3_VADD _mm_add_ps
#define DRMP3_VSUB _mm_sub_ps
#define DRMP3_VMUL _mm_mul_ps
#define DRMP3_VMAC(a, x, y) _mm_add_ps(a, _mm_mul_ps(x, y))
#define DRMP3_VMSB(a, x, y) _mm_sub_ps(a, _mm_mul_ps(x, y))
#define DRMP3_VMUL_S(x, s)  _mm_mul_ps(x, _mm_set1_ps(s))
#define DRMP3_VREV(x) _mm_shuffle_ps(x, x, _MM_SHUFFLE(0, 1, 2, 3))
typedef __m128 drmp3_f4;
#if defined(_MSC_VER) || defined(DR_MP3_ONLY_SIMD)
#define drmp3_cpuid __cpuid
#else
static __inline__ __attribute__((always_inline)) void drmp3_cpuid(int CPUInfo[], const int InfoType)
{
#if defined(__PIC__)
    __asm__ __volatile__(
#if defined(__x86_64__)
        "push %%rbx\n"
        "cpuid\n"
        "xchgl %%ebx, %1\n"
        "pop  %%rbx\n"
#else
        "xchgl %%ebx, %1\n"
        "cpuid\n"
        "xchgl %%ebx, %1\n"
#endif
        : "=a" (CPUInfo[0]), "=r" (CPUInfo[1]), "=c" (CPUInfo[2]), "=d" (CPUInfo[3])
        : "a" (InfoType));
#else
    __asm__ __volatile__(
        "cpuid"
        : "=a" (CPUInfo[0]), "=b" (CPUInfo[1]), "=c" (CPUInfo[2]), "=d" (CPUInfo[3])
        : "a" (InfoType));
#endif
}
#endif
static int drmp3_have_simd(void)
{
#ifdef DR_MP3_ONLY_SIMD
    return 1;
#else
    static int g_have_simd;
    int CPUInfo[4];
#ifdef MINIMP3_TEST
    static int g_counter;
    if (g_counter++ > 100)
        return 0;
#endif
    if (g_have_simd)
        goto end;
    drmp3_cpuid(CPUInfo, 0);
    if (CPUInfo[0] > 0)
    {
        drmp3_cpuid(CPUInfo, 1);
        g_have_simd = (CPUInfo[3] & (1 << 26)) + 1; /* SSE2 */
        return g_have_simd - 1;
    }

end:
    return g_have_simd - 1;
#endif
}
#elif defined(__ARM_NEON) || defined(__aarch64__)
#include <arm_neon.h>
#define DRMP3_HAVE_SSE 0
#define DRMP3_HAVE_SIMD 1
#define DRMP3_VSTORE vst1q_f32
#define DRMP3_VLD vld1q_f32
#define DRMP3_VSET vmovq_n_f32
#define DRMP3_VADD vaddq_f32
#define DRMP3_VSUB vsubq_f32
#define DRMP3_VMUL vmulq_f32
#define DRMP3_VMAC(a, x, y) vmlaq_f32(a, x, y)
#define DRMP3_VMSB(a, x, y) vmlsq_f32(a, x, y)
#define DRMP3_VMUL_S(x, s)  vmulq_f32(x, vmovq_n_f32(s))
#define DRMP3_VREV(x) vcombine_f32(vget_high_f32(vrev64q_f32(x)), vget_low_f32(vrev64q_f32(x)))
typedef float32x4_t drmp3_f4;
static int drmp3_have_simd(void)
{   /* TODO: detect neon for !DR_MP3_ONLY_SIMD */
    return 1;
}
#else
#define DRMP3_HAVE_SSE 0
#define DRMP3_HAVE_SIMD 0
#ifdef DR_MP3_ONLY_SIMD
#error DR_MP3_ONLY_SIMD used, but SSE/NEON not enabled
#endif
#endif

#else

#define DRMP3_HAVE_SIMD 0

#endif

#if defined(__ARM_ARCH) && (__ARM_ARCH >= 6) && !defined(__aarch64__)
#define DRMP3_HAVE_ARMV6 1
static __inline__ __attribute__((always_inline)) drmp3_int32 drmp3_clip_int16_arm(int32_t a)
{
    drmp3_int32 x = 0;
    __asm__ ("ssat %0, #16, %1" : "=r"(x) : "r"(a));
    return x;
}
#endif


typedef struct
{
    const drmp3_uint8 *buf;
    int pos, limit;
} drmp3_bs;

typedef struct
{
    float scf[3*64];
    drmp3_uint8 total_bands, stereo_bands, bitalloc[64], scfcod[64];
} drmp3_L12_scale_info;

typedef struct
{
    drmp3_uint8 tab_offset, code_tab_width, band_count;
} drmp3_L12_subband_alloc;

typedef struct
{
    const drmp3_uint8 *sfbtab;
    drmp3_uint16 part_23_length, big_values, scalefac_compress;
    drmp3_uint8 global_gain, block_type, mixed_block_flag, n_long_sfb, n_short_sfb;
    drmp3_uint8 table_select[3], region_count[3], subblock_gain[3];
    drmp3_uint8 preflag, scalefac_scale, count1_table, scfsi;
} drmp3_L3_gr_info;

typedef struct
{
    drmp3_bs bs;
    drmp3_uint8 maindata[DRMP3_MAX_BITRESERVOIR_BYTES + DRMP3_MAX_L3_FRAME_PAYLOAD_BYTES];
    drmp3_L3_gr_info gr_info[4];
    float grbuf[2][576], scf[40], syn[18 + 15][2*32];
    drmp3_uint8 ist_pos[2][39];
} drmp3dec_scratch;

static void drmp3_bs_init(drmp3_bs *bs, const drmp3_uint8 *data, int bytes)
{
    bs->buf   = data;
    bs->pos   = 0;
    bs->limit = bytes*8;
}

static drmp3_uint32 drmp3_bs_get_bits(drmp3_bs *bs, int n)
{
    drmp3_uint32 next, cache = 0, s = bs->pos & 7;
    int shl = n + s;
    const drmp3_uint8 *p = bs->buf + (bs->pos >> 3);
    if ((bs->pos += n) > bs->limit)
        return 0;
    next = *p++ & (255 >> s);
    while ((shl -= 8) > 0)
    {
        cache |= next << shl;
        next = *p++;
    }
    return cache | (next >> -shl);
}

static int drmp3_hdr_valid(const drmp3_uint8 *h)
{
    return h[0] == 0xff &&
        ((h[1] & 0xF0) == 0xf0 || (h[1] & 0xFE) == 0xe2) &&
        (DRMP3_HDR_GET_LAYER(h) != 0) &&
        (DRMP3_HDR_GET_BITRATE(h) != 15) &&
        (DRMP3_HDR_GET_SAMPLE_RATE(h) != 3);
}

static int drmp3_hdr_compare(const drmp3_uint8 *h1, const drmp3_uint8 *h2)
{
    return drmp3_hdr_valid(h2) &&
        ((h1[1] ^ h2[1]) & 0xFE) == 0 &&
        ((h1[2] ^ h2[2]) & 0x0C) == 0 &&
        !(DRMP3_HDR_IS_FREE_FORMAT(h1) ^ DRMP3_HDR_IS_FREE_FORMAT(h2));
}

static unsigned drmp3_hdr_bitrate_kbps(const drmp3_uint8 *h)
{
    static const drmp3_uint8 halfrate[2][3][15] = {
        { { 0,4,8,12,16,20,24,28,32,40,48,56,64,72,80 }, { 0,4,8,12,16,20,24,28,32,40,48,56,64,72,80 }, { 0,16,24,28,32,40,48,56,64,72,80,88,96,112,128 } },
        { { 0,16,20,24,28,32,40,48,56,64,80,96,112,128,160 }, { 0,16,24,28,32,40,48,56,64,80,96,112,128,160,192 }, { 0,16,32,48,64,80,96,112,128,144,160,176,192,208,224 } },
    };
    return 2*halfrate[!!DRMP3_HDR_TEST_MPEG1(h)][DRMP3_HDR_GET_LAYER(h) - 1][DRMP3_HDR_GET_BITRATE(h)];
}

static unsigned drmp3_hdr_sample_rate_hz(const drmp3_uint8 *h)
{
    static const unsigned g_hz[3] = { 44100, 48000, 32000 };
    return g_hz[DRMP3_HDR_GET_SAMPLE_RATE(h)] >> (int)!DRMP3_HDR_TEST_MPEG1(h) >> (int)!DRMP3_HDR_TEST_NOT_MPEG25(h);
}

static unsigned drmp3_hdr_frame_samples(const drmp3_uint8 *h)
{
    return DRMP3_HDR_IS_LAYER_1(h) ? 384 : (1152 >> (int)DRMP3_HDR_IS_FRAME_576(h));
}

static int drmp3_hdr_frame_bytes(const drmp3_uint8 *h, int free_format_size)
{
    int frame_bytes = drmp3_hdr_frame_samples(h)*drmp3_hdr_bitrate_kbps(h)*125/drmp3_hdr_sample_rate_hz(h);
    if (DRMP3_HDR_IS_LAYER_1(h))
    {
        frame_bytes &= ~3; /* slot align */
    }
    return frame_bytes ? frame_bytes : free_format_size;
}

static int drmp3_hdr_padding(const drmp3_uint8 *h)
{
    return DRMP3_HDR_TEST_PADDING(h) ? (DRMP3_HDR_IS_LAYER_1(h) ? 4 : 1) : 0;
}

#ifndef DR_MP3_ONLY_MP3
static const drmp3_L12_subband_alloc *drmp3_L12_subband_alloc_table(const drmp3_uint8 *hdr, drmp3_L12_scale_info *sci)
{
    const drmp3_L12_subband_alloc *alloc;
    int mode = DRMP3_HDR_GET_STEREO_MODE(hdr);
    int nbands, stereo_bands = (mode == DRMP3_MODE_MONO) ? 0 : (mode == DRMP3_MODE_JOINT_STEREO) ? (DRMP3_HDR_GET_STEREO_MODE_EXT(hdr) << 2) + 4 : 32;

    if (DRMP3_HDR_IS_LAYER_1(hdr))
    {
        static const drmp3_L12_subband_alloc g_alloc_L1[] = { { 76, 4, 32 } };
        alloc = g_alloc_L1;
        nbands = 32;
    } else if (!DRMP3_HDR_TEST_MPEG1(hdr))
    {
        static const drmp3_L12_subband_alloc g_alloc_L2M2[] = { { 60, 4, 4 }, { 44, 3, 7 }, { 44, 2, 19 } };
        alloc = g_alloc_L2M2;
        nbands = 30;
    } else
    {
        static const drmp3_L12_subband_alloc g_alloc_L2M1[] = { { 0, 4, 3 }, { 16, 4, 8 }, { 32, 3, 12 }, { 40, 2, 7 } };
        int sample_rate_idx = DRMP3_HDR_GET_SAMPLE_RATE(hdr);
        unsigned kbps = drmp3_hdr_bitrate_kbps(hdr) >> (int)(mode != DRMP3_MODE_MONO);
        if (!kbps) /* free-format */
        {
            kbps = 192;
        }

        alloc = g_alloc_L2M1;
        nbands = 27;
        if (kbps < 56)
        {
            static const drmp3_L12_subband_alloc g_alloc_L2M1_lowrate[] = { { 44, 4, 2 }, { 44, 3, 10 } };
            alloc = g_alloc_L2M1_lowrate;
            nbands = sample_rate_idx == 2 ? 12 : 8;
        } else if (kbps >= 96 && sample_rate_idx != 1)
        {
            nbands = 30;
        }
    }

    sci->total_bands = (drmp3_uint8)nbands;
    sci->stereo_bands = (drmp3_uint8)DRMP3_MIN(stereo_bands, nbands);

    return alloc;
}

static void drmp3_L12_read_scalefactors(drmp3_bs *bs, drmp3_uint8 *pba, drmp3_uint8 *scfcod, int bands, float *scf)
{
    static const float g_deq_L12[18*3] = {
#define DRMP3_DQ(x) 9.53674316e-07f/x, 7.56931807e-07f/x, 6.00777173e-07f/x
        DRMP3_DQ(3),DRMP3_DQ(7),DRMP3_DQ(15),DRMP3_DQ(31),DRMP3_DQ(63),DRMP3_DQ(127),DRMP3_DQ(255),DRMP3_DQ(511),DRMP3_DQ(1023),DRMP3_DQ(2047),DRMP3_DQ(4095),DRMP3_DQ(8191),DRMP3_DQ(16383),DRMP3_DQ(32767),DRMP3_DQ(65535),DRMP3_DQ(3),DRMP3_DQ(5),DRMP3_DQ(9)
    };
    int i, m;
    for (i = 0; i < bands; i++)
    {
        float s = 0;
        int ba = *pba++;
        int mask = ba ? 4 + ((19 >> scfcod[i]) & 3) : 0;
        for (m = 4; m; m >>= 1)
        {
            if (mask & m)
            {
                int b = drmp3_bs_get_bits(bs, 6);
                s = g_deq_L12[ba*3 - 6 + b % 3]*(int)(1 << 21 >> b/3);
            }
            *scf++ = s;
        }
    }
}

static void drmp3_L12_read_scale_info(const drmp3_uint8 *hdr, drmp3_bs *bs, drmp3_L12_scale_info *sci)
{
    static const drmp3_uint8 g_bitalloc_code_tab[] = {
        0,17, 3, 4, 5,6,7, 8,9,10,11,12,13,14,15,16,
        0,17,18, 3,19,4,5, 6,7, 8, 9,10,11,12,13,16,
        0,17,18, 3,19,4,5,16,
        0,17,18,16,
        0,17,18,19, 4,5,6, 7,8, 9,10,11,12,13,14,15,
        0,17,18, 3,19,4,5, 6,7, 8, 9,10,11,12,13,14,
        0, 2, 3, 4, 5,6,7, 8,9,10,11,12,13,14,15,16
    };
    const drmp3_L12_subband_alloc *subband_alloc = drmp3_L12_subband_alloc_table(hdr, sci);

    int i, k = 0, ba_bits = 0;
    const drmp3_uint8 *ba_code_tab = g_bitalloc_code_tab;

    for (i = 0; i < sci->total_bands; i++)
    {
        drmp3_uint8 ba;
        if (i == k)
        {
            k += subband_alloc->band_count;
            ba_bits = subband_alloc->code_tab_width;
            ba_code_tab = g_bitalloc_code_tab + subband_alloc->tab_offset;
            subband_alloc++;
        }
        ba = ba_code_tab[drmp3_bs_get_bits(bs, ba_bits)];
        sci->bitalloc[2*i] = ba;
        if (i < sci->stereo_bands)
        {
            ba = ba_code_tab[drmp3_bs_get_bits(bs, ba_bits)];
        }
        sci->bitalloc[2*i + 1] = sci->stereo_bands ? ba : 0;
    }

    for (i = 0; i < 2*sci->total_bands; i++)
    {
        sci->scfcod[i] = (drmp3_uint8)(sci->bitalloc[i] ? DRMP3_HDR_IS_LAYER_1(hdr) ? 2 : drmp3_bs_get_bits(bs, 2) : 6);
    }

    drmp3_L12_read_scalefactors(bs, sci->bitalloc, sci->scfcod, sci->total_bands*2, sci->scf);

    for (i = sci->stereo_bands; i < sci->total_bands; i++)
    {
        sci->bitalloc[2*i + 1] = 0;
    }
}

static int drmp3_L12_dequantize_granule(float *grbuf, drmp3_bs *bs, drmp3_L12_scale_info *sci, int group_size)
{
    int i, j, k, choff = 576;
    for (j = 0; j < 4; j++)
    {
        float *dst = grbuf + group_size*j;
        for (i = 0; i < 2*sci->total_bands; i++)
        {
            int ba = sci->bitalloc[i];
            if (ba != 0)
            {
                if (ba < 17)
                {
                    int half = (1 << (ba - 1)) - 1;
                    for (k = 0; k < group_size; k++)
                    {
                        dst[k] = (float)((int)drmp3_bs_get_bits(bs, ba) - half);
                    }
                } else
                {
                    unsigned mod = (2 << (ba - 17)) + 1;    /* 3, 5, 9 */
                    unsigned code = drmp3_bs_get_bits(bs, mod + 2 - (mod >> 3));  /* 5, 7, 10 */
                    for (k = 0; k < group_size; k++, code /= mod)
                    {
                        dst[k] = (float)((int)(code % mod - mod/2));
                    }
                }
            }
            dst += choff;
            choff = 18 - choff;
        }
    }
    return group_size*4;
}

static void drmp3_L12_apply_scf_384(drmp3_L12_scale_info *sci, const float *scf, float *dst)
{
    int i, k;
    memcpy(dst + 576 + sci->stereo_bands*18, dst + sci->stereo_bands*18, (sci->total_bands - sci->stereo_bands)*18*sizeof(float));
    for (i = 0; i < sci->total_bands; i++, dst += 18, scf += 6)
    {
        for (k = 0; k < 12; k++)
        {
            dst[k + 0]   *= scf[0];
            dst[k + 576] *= scf[3];
        }
    }
}
#endif

static int drmp3_L3_read_side_info(drmp3_bs *bs, drmp3_L3_gr_info *gr, const drmp3_uint8 *hdr)
{
    static const drmp3_uint8 g_scf_long[8][23] = {
        { 6,6,6,6,6,6,8,10,12,14,16,20,24,28,32,38,46,52,60,68,58,54,0 },
        { 12,12,12,12,12,12,16,20,24,28,32,40,48,56,64,76,90,2,2,2,2,2,0 },
        { 6,6,6,6,6,6,8,10,12,14,16,20,24,28,32,38,46,52,60,68,58,54,0 },
        { 6,6,6,6,6,6,8,10,12,14,16,18,22,26,32,38,46,54,62,70,76,36,0 },
        { 6,6,6,6,6,6,8,10,12,14,16,20,24,28,32,38,46,52,60,68,58,54,0 },
        { 4,4,4,4,4,4,6,6,8,8,10,12,16,20,24,28,34,42,50,54,76,158,0 },
        { 4,4,4,4,4,4,6,6,6,8,10,12,16,18,22,28,34,40,46,54,54,192,0 },
        { 4,4,4,4,4,4,6,6,8,10,12,16,20,24,30,38,46,56,68,84,102,26,0 }
    };
    static const drmp3_uint8 g_scf_short[8][40] = {
        { 4,4,4,4,4,4,4,4,4,6,6,6,8,8,8,10,10,10,12,12,12,14,14,14,18,18,18,24,24,24,30,30,30,40,40,40,18,18,18,0 },
        { 8,8,8,8,8,8,8,8,8,12,12,12,16,16,16,20,20,20,24,24,24,28,28,28,36,36,36,2,2,2,2,2,2,2,2,2,26,26,26,0 },
        { 4,4,4,4,4,4,4,4,4,6,6,6,6,6,6,8,8,8,10,10,10,14,14,14,18,18,18,26,26,26,32,32,32,42,42,42,18,18,18,0 },
        { 4,4,4,4,4,4,4,4,4,6,6,6,8,8,8,10,10,10,12,12,12,14,14,14,18,18,18,24,24,24,32,32,32,44,44,44,12,12,12,0 },
        { 4,4,4,4,4,4,4,4,4,6,6,6,8,8,8,10,10,10,12,12,12,14,14,14,18,18,18,24,24,24,30,30,30,40,40,40,18,18,18,0 },
        { 4,4,4,4,4,4,4,4,4,4,4,4,6,6,6,8,8,8,10,10,10,12,12,12,14,14,14,18,18,18,22,22,22,30,30,30,56,56,56,0 },
        { 4,4,4,4,4,4,4,4,4,4,4,4,6,6,6,6,6,6,10,10,10,12,12,12,14,14,14,16,16,16,20,20,20,26,26,26,66,66,66,0 },
        { 4,4,4,4,4,4,4,4,4,4,4,4,6,6,6,8,8,8,12,12,12,16,16,16,20,20,20,26,26,26,34,34,34,42,42,42,12,12,12,0 }
    };
    static const drmp3_uint8 g_scf_mixed[8][40] = {
        { 6,6,6,6,6,6,6,6,6,8,8,8,10,10,10,12,12,12,14,14,14,18,18,18,24,24,24,30,30,30,40,40,40,18,18,18,0 },
        { 12,12,12,4,4,4,8,8,8,12,12,12,16,16,16,20,20,20,24,24,24,28,28,28,36,36,36,2,2,2,2,2,2,2,2,2,26,26,26,0 },
        { 6,6,6,6,6,6,6,6,6,6,6,6,8,8,8,10,10,10,14,14,14,18,18,18,26,26,26,32,32,32,42,42,42,18,18,18,0 },
        { 6,6,6,6,6,6,6,6,6,8,8,8,10,10,10,12,12,12,14,14,14,18,18,18,24,24,24,32,32,32,44,44,44,12,12,12,0 },
        { 6,6,6,6,6,6,6,6,6,8,8,8,10,10,10,12,12,12,14,14,14,18,18,18,24,24,24,30,30,30,40,40,40,18,18,18,0 },
        { 4,4,4,4,4,4,6,6,4,4,4,6,6,6,8,8,8,10,10,10,12,12,12,14,14,14,18,18,18,22,22,22,30,30,30,56,56,56,0 },
        { 4,4,4,4,4,4,6,6,4,4,4,6,6,6,6,6,6,10,10,10,12,12,12,14,14,14,16,16,16,20,20,20,26,26,26,66,66,66,0 },
        { 4,4,4,4,4,4,6,6,4,4,4,6,6,6,8,8,8,12,12,12,16,16,16,20,20,20,26,26,26,34,34,34,42,42,42,12,12,12,0 }
    };

    unsigned tables, scfsi = 0;
    int main_data_begin, part_23_sum = 0;
    int gr_count = DRMP3_HDR_IS_MONO(hdr) ? 1 : 2;
    int sr_idx = DRMP3_HDR_GET_MY_SAMPLE_RATE(hdr); sr_idx -= (sr_idx != 0);

    if (DRMP3_HDR_TEST_MPEG1(hdr))
    {
        gr_count *= 2;
        main_data_begin = drmp3_bs_get_bits(bs, 9);
        scfsi = drmp3_bs_get_bits(bs, 7 + gr_count);
    } else
    {
        main_data_begin = drmp3_bs_get_bits(bs, 8 + gr_count) >> gr_count;
    }

    do
    {
        if (DRMP3_HDR_IS_MONO(hdr))
        {
            scfsi <<= 4;
        }
        gr->part_23_length = (drmp3_uint16)drmp3_bs_get_bits(bs, 12);
        part_23_sum += gr->part_23_length;
        gr->big_values = (drmp3_uint16)drmp3_bs_get_bits(bs,  9);
        if (gr->big_values > 288)
        {
            return -1;
        }
        gr->global_gain = (drmp3_uint8)drmp3_bs_get_bits(bs, 8);
        gr->scalefac_compress = (drmp3_uint16)drmp3_bs_get_bits(bs, DRMP3_HDR_TEST_MPEG1(hdr) ? 4 : 9);
        gr->sfbtab = g_scf_long[sr_idx];
        gr->n_long_sfb  = 22;
        gr->n_short_sfb = 0;
        if (drmp3_bs_get_bits(bs, 1))
        {
            gr->block_type = (drmp3_uint8)drmp3_bs_get_bits(bs, 2);
            if (!gr->block_type)
            {
                return -1;
            }
            gr->mixed_block_flag = (drmp3_uint8)drmp3_bs_get_bits(bs, 1);
            gr->region_count[0] = 7;
            gr->region_count[1] = 255;
            if (gr->block_type == DRMP3_SHORT_BLOCK_TYPE)
            {
                scfsi &= 0x0F0F;
                if (!gr->mixed_block_flag)
                {
                    gr->region_count[0] = 8;
                    gr->sfbtab = g_scf_short[sr_idx];
                    gr->n_long_sfb = 0;
                    gr->n_short_sfb = 39;
                } else
                {
                    gr->sfbtab = g_scf_mixed[sr_idx];
                    gr->n_long_sfb = DRMP3_HDR_TEST_MPEG1(hdr) ? 8 : 6;
                    gr->n_short_sfb = 30;
                }
            }
            tables = drmp3_bs_get_bits(bs, 10);
            tables <<= 5;
            gr->subblock_gain[0] = (drmp3_uint8)drmp3_bs_get_bits(bs, 3);
            gr->subblock_gain[1] = (drmp3_uint8)drmp3_bs_get_bits(bs, 3);
            gr->subblock_gain[2] = (drmp3_uint8)drmp3_bs_get_bits(bs, 3);
        } else
        {
            gr->block_type = 0;
            gr->mixed_block_flag = 0;
            tables = drmp3_bs_get_bits(bs, 15);
            gr->region_count[0] = (drmp3_uint8)drmp3_bs_get_bits(bs, 4);
            gr->region_count[1] = (drmp3_uint8)drmp3_bs_get_bits(bs, 3);
            gr->region_count[2] = 255;
        }
        gr->table_select[0] = (drmp3_uint8)(tables >> 10);
        gr->table_select[1] = (drmp3_uint8)((tables >> 5) & 31);
        gr->table_select[2] = (drmp3_uint8)((tables) & 31);
        gr->preflag = (drmp3_uint8)(DRMP3_HDR_TEST_MPEG1(hdr) ? drmp3_bs_get_bits(bs, 1) : (gr->scalefac_compress >= 500));
        gr->scalefac_scale = (drmp3_uint8)drmp3_bs_get_bits(bs, 1);
        gr->count1_table = (drmp3_uint8)drmp3_bs_get_bits(bs, 1);
        gr->scfsi = (drmp3_uint8)((scfsi >> 12) & 15);
        scfsi <<= 4;
        gr++;
    } while(--gr_count);

    if (part_23_sum + bs->pos > bs->limit + main_data_begin*8)
    {
        return -1;
    }

    return main_data_begin;
}

static void drmp3_L3_read_scalefactors(drmp3_uint8 *scf, drmp3_uint8 *ist_pos, const drmp3_uint8 *scf_size, const drmp3_uint8 *scf_count, drmp3_bs *bitbuf, int scfsi)
{
    int i, k;
    for (i = 0; i < 4 && scf_count[i]; i++, scfsi *= 2)
    {
        int cnt = scf_count[i];
        if (scfsi & 8)
        {
            memcpy(scf, ist_pos, cnt);
        } else
        {
            int bits = scf_size[i];
            if (!bits)
            {
                memset(scf, 0, cnt);
                memset(ist_pos, 0, cnt);
            } else
            {
                int max_scf = (scfsi < 0) ? (1 << bits) - 1 : -1;
                for (k = 0; k < cnt; k++)
                {
                    int s = drmp3_bs_get_bits(bitbuf, bits);
                    ist_pos[k] = (drmp3_uint8)(s == max_scf ? -1 : s);
                    scf[k] = (drmp3_uint8)s;
                }
            }
        }
        ist_pos += cnt;
        scf += cnt;
    }
    scf[0] = scf[1] = scf[2] = 0;
}

static float drmp3_L3_ldexp_q2(float y, int exp_q2)
{
    static const float g_expfrac[4] = { 9.31322575e-10f,7.83145814e-10f,6.58544508e-10f,5.53767716e-10f };
    int e;
    do
    {
        e = DRMP3_MIN(30*4, exp_q2);
        y *= g_expfrac[e & 3]*(1 << 30 >> (e >> 2));
    } while ((exp_q2 -= e) > 0);
    return y;
}

static void drmp3_L3_decode_scalefactors(const drmp3_uint8 *hdr, drmp3_uint8 *ist_pos, drmp3_bs *bs, const drmp3_L3_gr_info *gr, float *scf, int ch)
{
    static const drmp3_uint8 g_scf_partitions[3][28] = {
        { 6,5,5, 5,6,5,5,5,6,5, 7,3,11,10,0,0, 7, 7, 7,0, 6, 6,6,3, 8, 8,5,0 },
        { 8,9,6,12,6,9,9,9,6,9,12,6,15,18,0,0, 6,15,12,0, 6,12,9,6, 6,18,9,0 },
        { 9,9,6,12,9,9,9,9,9,9,12,6,18,18,0,0,12,12,12,0,12, 9,9,6,15,12,9,0 }
    };
    const drmp3_uint8 *scf_partition = g_scf_partitions[!!gr->n_short_sfb + !gr->n_long_sfb];
    drmp3_uint8 scf_size[4], iscf[40];
    int i, scf_shift = gr->scalefac_scale + 1, gain_exp, scfsi = gr->scfsi;
    float gain;

    if (DRMP3_HDR_TEST_MPEG1(hdr))
    {
        static const drmp3_uint8 g_scfc_decode[16] = { 0,1,2,3, 12,5,6,7, 9,10,11,13, 14,15,18,19 };
        int part = g_scfc_decode[gr->scalefac_compress];
        scf_size[1] = scf_size[0] = (drmp3_uint8)(part >> 2);
        scf_size[3] = scf_size[2] = (drmp3_uint8)(part & 3);
    } else
    {
        static const drmp3_uint8 g_mod[6*4] = { 5,5,4,4,5,5,4,1,4,3,1,1,5,6,6,1,4,4,4,1,4,3,1,1 };
        int k, modprod, sfc, ist = DRMP3_HDR_TEST_I_STEREO(hdr) && ch;
        sfc = gr->scalefac_compress >> ist;
        for (k = ist*3*4; sfc >= 0; sfc -= modprod, k += 4)
        {
            for (modprod = 1, i = 3; i >= 0; i--)
            {
                scf_size[i] = (drmp3_uint8)(sfc / modprod % g_mod[k + i]);
                modprod *= g_mod[k + i];
            }
        }
        scf_partition += k;
        scfsi = -16;
    }
    drmp3_L3_read_scalefactors(iscf, ist_pos, scf_size, scf_partition, bs, scfsi);

    if (gr->n_short_sfb)
    {
        int sh = 3 - scf_shift;
        for (i = 0; i < gr->n_short_sfb; i += 3)
        {
            iscf[gr->n_long_sfb + i + 0] = (drmp3_uint8)(iscf[gr->n_long_sfb + i + 0] + (gr->subblock_gain[0] << sh));
            iscf[gr->n_long_sfb + i + 1] = (drmp3_uint8)(iscf[gr->n_long_sfb + i + 1] + (gr->subblock_gain[1] << sh));
            iscf[gr->n_long_sfb + i + 2] = (drmp3_uint8)(iscf[gr->n_long_sfb + i + 2] + (gr->subblock_gain[2] << sh));
        }
    } else if (gr->preflag)
    {
        static const drmp3_uint8 g_preamp[10] = { 1,1,1,1,2,2,3,3,3,2 };
        for (i = 0; i < 10; i++)
        {
            iscf[11 + i] = (drmp3_uint8)(iscf[11 + i] + g_preamp[i]);
        }
    }

    gain_exp = gr->global_gain + DRMP3_BITS_DEQUANTIZER_OUT*4 - 210 - (DRMP3_HDR_IS_MS_STEREO(hdr) ? 2 : 0);
    gain = drmp3_L3_ldexp_q2(1 << (DRMP3_MAX_SCFI/4),  DRMP3_MAX_SCFI - gain_exp);
    for (i = 0; i < (int)(gr->n_long_sfb + gr->n_short_sfb); i++)
    {
        scf[i] = drmp3_L3_ldexp_q2(gain, iscf[i] << scf_shift);
    }
}

static const float g_drmp3_pow43[129 + 16] = {
    0,-1,-2.519842f,-4.326749f,-6.349604f,-8.549880f,-10.902724f,-13.390518f,-16.000000f,-18.720754f,-21.544347f,-24.463781f,-27.473142f,-30.567351f,-33.741992f,-36.993181f,
    0,1,2.519842f,4.326749f,6.349604f,8.549880f,10.902724f,13.390518f,16.000000f,18.720754f,21.544347f,24.463781f,27.473142f,30.567351f,33.741992f,36.993181f,40.317474f,43.711787f,47.173345f,50.699631f,54.288352f,57.937408f,61.644865f,65.408941f,69.227979f,73.100443f,77.024898f,81.000000f,85.024491f,89.097188f,93.216975f,97.382800f,101.593667f,105.848633f,110.146801f,114.487321f,118.869381f,123.292209f,127.755065f,132.257246f,136.798076f,141.376907f,145.993119f,150.646117f,155.335327f,160.060199f,164.820202f,169.614826f,174.443577f,179.305980f,184.201575f,189.129918f,194.090580f,199.083145f,204.107210f,209.162385f,214.248292f,219.364564f,224.510845f,229.686789f,234.892058f,240.126328f,245.389280f,250.680604f,256.000000f,261.347174f,266.721841f,272.123723f,277.552547f,283.008049f,288.489971f,293.998060f,299.532071f,305.091761f,310.676898f,316.287249f,321.922592f,327.582707f,333.267377f,338.976394f,344.709550f,350.466646f,356.247482f,362.051866f,367.879608f,373.730522f,379.604427f,385.501143f,391.420496f,397.362314f,403.326427f,409.312672f,415.320884f,421.350905f,427.402579f,433.475750f,439.570269f,445.685987f,451.822757f,457.980436f,464.158883f,470.357960f,476.577530f,482.817459f,489.077615f,495.357868f,501.658090f,507.978156f,514.317941f,520.677324f,527.056184f,533.454404f,539.871867f,546.308458f,552.764065f,559.238575f,565.731879f,572.243870f,578.774440f,585.323483f,591.890898f,598.476581f,605.080431f,611.702349f,618.342238f,625.000000f,631.675540f,638.368763f,645.079578f
};

static float drmp3_L3_pow_43(int x)
{
    float frac;
    int sign, mult = 256;

    if (x < 129)
    {
        return g_drmp3_pow43[16 + x];
    }

    if (x < 1024)
    {
        mult = 16;
        x <<= 3;
    }

    sign = 2*x & 64;
    frac = (float)((x & 63) - sign) / ((x & ~63) + sign);
    return g_drmp3_pow43[16 + ((x + sign) >> 6)]*(1.f + frac*((4.f/3) + frac*(2.f/9)))*mult;
}

static void drmp3_L3_huffman(float *dst, drmp3_bs *bs, const drmp3_L3_gr_info *gr_info, const float *scf, int layer3gr_limit)
{
    static const drmp3_int16 tabs[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        785,785,785,785,784,784,784,784,513,513,513,513,513,513,513,513,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,
        -255,1313,1298,1282,785,785,785,785,784,784,784,784,769,769,769,769,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,290,288,
        -255,1313,1298,1282,769,769,769,769,529,529,529,529,529,529,529,529,528,528,528,528,528,528,528,528,512,512,512,512,512,512,512,512,290,288,
        -253,-318,-351,-367,785,785,785,785,784,784,784,784,769,769,769,769,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,819,818,547,547,275,275,275,275,561,560,515,546,289,274,288,258,
        -254,-287,1329,1299,1314,1312,1057,1057,1042,1042,1026,1026,784,784,784,784,529,529,529,529,529,529,529,529,769,769,769,769,768,768,768,768,563,560,306,306,291,259,
        -252,-413,-477,-542,1298,-575,1041,1041,784,784,784,784,769,769,769,769,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,-383,-399,1107,1092,1106,1061,849,849,789,789,1104,1091,773,773,1076,1075,341,340,325,309,834,804,577,577,532,532,516,516,832,818,803,816,561,561,531,531,515,546,289,289,288,258,
        -252,-429,-493,-559,1057,1057,1042,1042,529,529,529,529,529,529,529,529,784,784,784,784,769,769,769,769,512,512,512,512,512,512,512,512,-382,1077,-415,1106,1061,1104,849,849,789,789,1091,1076,1029,1075,834,834,597,581,340,340,339,324,804,833,532,532,832,772,818,803,817,787,816,771,290,290,290,290,288,258,
        -253,-349,-414,-447,-463,1329,1299,-479,1314,1312,1057,1057,1042,1042,1026,1026,785,785,785,785,784,784,784,784,769,769,769,769,768,768,768,768,-319,851,821,-335,836,850,805,849,341,340,325,336,533,533,579,579,564,564,773,832,578,548,563,516,321,276,306,291,304,259,
        -251,-572,-733,-830,-863,-879,1041,1041,784,784,784,784,769,769,769,769,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,-511,-527,-543,1396,1351,1381,1366,1395,1335,1380,-559,1334,1138,1138,1063,1063,1350,1392,1031,1031,1062,1062,1364,1363,1120,1120,1333,1348,881,881,881,881,375,374,359,373,343,358,341,325,791,791,1123,1122,-703,1105,1045,-719,865,865,790,790,774,774,1104,1029,338,293,323,308,-799,-815,833,788,772,818,803,816,322,292,307,320,561,531,515,546,289,274,288,258,
        -251,-525,-605,-685,-765,-831,-846,1298,1057,1057,1312,1282,785,785,785,785,784,784,784,784,769,769,769,769,512,512,512,512,512,512,512,512,1399,1398,1383,1367,1382,1396,1351,-511,1381,1366,1139,1139,1079,1079,1124,1124,1364,1349,1363,1333,882,882,882,882,807,807,807,807,1094,1094,1136,1136,373,341,535,535,881,775,867,822,774,-591,324,338,-671,849,550,550,866,864,609,609,293,336,534,534,789,835,773,-751,834,804,308,307,833,788,832,772,562,562,547,547,305,275,560,515,290,290,
        -252,-397,-477,-557,-622,-653,-719,-735,-750,1329,1299,1314,1057,1057,1042,1042,1312,1282,1024,1024,785,785,785,785,784,784,784,784,769,769,769,769,-383,1127,1141,1111,1126,1140,1095,1110,869,869,883,883,1079,1109,882,882,375,374,807,868,838,881,791,-463,867,822,368,263,852,837,836,-543,610,610,550,550,352,336,534,534,865,774,851,821,850,805,593,533,579,564,773,832,578,578,548,548,577,577,307,276,306,291,516,560,259,259,
        -250,-2107,-2507,-2764,-2909,-2974,-3007,-3023,1041,1041,1040,1040,769,769,769,769,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,-767,-1052,-1213,-1277,-1358,-1405,-1469,-1535,-1550,-1582,-1614,-1647,-1662,-1694,-1726,-1759,-1774,-1807,-1822,-1854,-1886,1565,-1919,-1935,-1951,-1967,1731,1730,1580,1717,-1983,1729,1564,-1999,1548,-2015,-2031,1715,1595,-2047,1714,-2063,1610,-2079,1609,-2095,1323,1323,1457,1457,1307,1307,1712,1547,1641,1700,1699,1594,1685,1625,1442,1442,1322,1322,-780,-973,-910,1279,1278,1277,1262,1276,1261,1275,1215,1260,1229,-959,974,974,989,989,-943,735,478,478,495,463,506,414,-1039,1003,958,1017,927,942,987,957,431,476,1272,1167,1228,-1183,1256,-1199,895,895,941,941,1242,1227,1212,1135,1014,1014,490,489,503,487,910,1013,985,925,863,894,970,955,1012,847,-1343,831,755,755,984,909,428,366,754,559,-1391,752,486,457,924,997,698,698,983,893,740,740,908,877,739,739,667,667,953,938,497,287,271,271,683,606,590,712,726,574,302,302,738,736,481,286,526,725,605,711,636,724,696,651,589,681,666,710,364,467,573,695,466,466,301,465,379,379,709,604,665,679,316,316,634,633,436,436,464,269,424,394,452,332,438,363,347,408,393,448,331,422,362,407,392,421,346,406,391,376,375,359,1441,1306,-2367,1290,-2383,1337,-2399,-2415,1426,1321,-2431,1411,1336,-2447,-2463,-2479,1169,1169,1049,1049,1424,1289,1412,1352,1319,-2495,1154,1154,1064,1064,1153,1153,416,390,360,404,403,389,344,374,373,343,358,372,327,357,342,311,356,326,1395,1394,1137,1137,1047,1047,1365,1392,1287,1379,1334,1364,1349,1378,1318,1363,792,792,792,792,1152,1152,1032,1032,1121,1121,1046,1046,1120,1120,1030,1030,-2895,1106,1061,1104,849,849,789,789,1091,1076,1029,1090,1060,1075,833,833,309,324,532,532,832,772,818,803,561,561,531,560,515,546,289,274,288,258,
        -250,-1179,-1579,-1836,-1996,-2124,-2253,-2333,-2413,-2477,-2542,-2574,-2607,-2622,-2655,1314,1313,1298,1312,1282,785,785,785,785,1040,1040,1025,1025,768,768,768,768,-766,-798,-830,-862,-895,-911,-927,-943,-959,-975,-991,-1007,-1023,-1039,-1055,-1070,1724,1647,-1103,-1119,1631,1767,1662,1738,1708,1723,-1135,1780,1615,1779,1599,1677,1646,1778,1583,-1151,1777,1567,1737,1692,1765,1722,1707,1630,1751,1661,1764,1614,1736,1676,1763,1750,1645,1598,1721,1691,1762,1706,1582,1761,1566,-1167,1749,1629,767,766,751,765,494,494,735,764,719,749,734,763,447,447,748,718,477,506,431,491,446,476,461,505,415,430,475,445,504,399,460,489,414,503,383,474,429,459,502,502,746,752,488,398,501,473,413,472,486,271,480,270,-1439,-1455,1357,-1471,-1487,-1503,1341,1325,-1519,1489,1463,1403,1309,-1535,1372,1448,1418,1476,1356,1462,1387,-1551,1475,1340,1447,1402,1386,-1567,1068,1068,1474,1461,455,380,468,440,395,425,410,454,364,467,466,464,453,269,409,448,268,432,1371,1473,1432,1417,1308,1460,1355,1446,1459,1431,1083,1083,1401,1416,1458,1445,1067,1067,1370,1457,1051,1051,1291,1430,1385,1444,1354,1415,1400,1443,1082,1082,1173,1113,1186,1066,1185,1050,-1967,1158,1128,1172,1097,1171,1081,-1983,1157,1112,416,266,375,400,1170,1142,1127,1065,793,793,1169,1033,1156,1096,1141,1111,1155,1080,1126,1140,898,898,808,808,897,897,792,792,1095,1152,1032,1125,1110,1139,1079,1124,882,807,838,881,853,791,-2319,867,368,263,822,852,837,866,806,865,-2399,851,352,262,534,534,821,836,594,594,549,549,593,593,533,533,848,773,579,579,564,578,548,563,276,276,577,576,306,291,516,560,305,305,275,259,
        -251,-892,-2058,-2620,-2828,-2957,-3023,-3039,1041,1041,1040,1040,769,769,769,769,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,256,-511,-527,-543,-559,1530,-575,-591,1528,1527,1407,1526,1391,1023,1023,1023,1023,1525,1375,1268,1268,1103,1103,1087,1087,1039,1039,1523,-604,815,815,815,815,510,495,509,479,508,463,507,447,431,505,415,399,-734,-782,1262,-815,1259,1244,-831,1258,1228,-847,-863,1196,-879,1253,987,987,748,-767,493,493,462,477,414,414,686,669,478,446,461,445,474,429,487,458,412,471,1266,1264,1009,1009,799,799,-1019,-1276,-1452,-1581,-1677,-1757,-1821,-1886,-1933,-1997,1257,1257,1483,1468,1512,1422,1497,1406,1467,1496,1421,1510,1134,1134,1225,1225,1466,1451,1374,1405,1252,1252,1358,1480,1164,1164,1251,1251,1238,1238,1389,1465,-1407,1054,1101,-1423,1207,-1439,830,830,1248,1038,1237,1117,1223,1148,1236,1208,411,426,395,410,379,269,1193,1222,1132,1235,1221,1116,976,976,1192,1162,1177,1220,1131,1191,963,963,-1647,961,780,-1663,558,558,994,993,437,408,393,407,829,978,813,797,947,-1743,721,721,377,392,844,950,828,890,706,706,812,859,796,960,948,843,934,874,571,571,-1919,690,555,689,421,346,539,539,944,779,918,873,932,842,903,888,570,570,931,917,674,674,-2575,1562,-2591,1609,-2607,1654,1322,1322,1441,1441,1696,1546,1683,1593,1669,1624,1426,1426,1321,1321,1639,1680,1425,1425,1305,1305,1545,1668,1608,1623,1667,1592,1638,1666,1320,1320,1652,1607,1409,1409,1304,1304,1288,1288,1664,1637,1395,1395,1335,1335,1622,1636,1394,1394,1319,1319,1606,1621,1392,1392,1137,1137,1137,1137,345,390,360,375,404,373,1047,-2751,-2767,-2783,1062,1121,1046,-2799,1077,-2815,1106,1061,789,789,1105,1104,263,355,310,340,325,354,352,262,339,324,1091,1076,1029,1090,1060,1075,833,833,788,788,1088,1028,818,818,803,803,561,561,531,531,816,771,546,546,289,274,288,258,
        -253,-317,-381,-446,-478,-509,1279,1279,-811,-1179,-1451,-1756,-1900,-2028,-2189,-2253,-2333,-2414,-2445,-2511,-2526,1313,1298,-2559,1041,1041,1040,1040,1025,1025,1024,1024,1022,1007,1021,991,1020,975,1019,959,687,687,1018,1017,671,671,655,655,1016,1015,639,639,758,758,623,623,757,607,756,591,755,575,754,559,543,543,1009,783,-575,-621,-685,-749,496,-590,750,749,734,748,974,989,1003,958,988,973,1002,942,987,957,972,1001,926,986,941,971,956,1000,910,985,925,999,894,970,-1071,-1087,-1102,1390,-1135,1436,1509,1451,1374,-1151,1405,1358,1480,1420,-1167,1507,1494,1389,1342,1465,1435,1450,1326,1505,1310,1493,1373,1479,1404,1492,1464,1419,428,443,472,397,736,526,464,464,486,457,442,471,484,482,1357,1449,1434,1478,1388,1491,1341,1490,1325,1489,1463,1403,1309,1477,1372,1448,1418,1433,1476,1356,1462,1387,-1439,1475,1340,1447,1402,1474,1324,1461,1371,1473,269,448,1432,1417,1308,1460,-1711,1459,-1727,1441,1099,1099,1446,1386,1431,1401,-1743,1289,1083,1083,1160,1160,1458,1445,1067,1067,1370,1457,1307,1430,1129,1129,1098,1098,268,432,267,416,266,400,-1887,1144,1187,1082,1173,1113,1186,1066,1050,1158,1128,1143,1172,1097,1171,1081,420,391,1157,1112,1170,1142,1127,1065,1169,1049,1156,1096,1141,1111,1155,1080,1126,1154,1064,1153,1140,1095,1048,-2159,1125,1110,1137,-2175,823,823,1139,1138,807,807,384,264,368,263,868,838,853,791,867,822,852,837,866,806,865,790,-2319,851,821,836,352,262,850,805,849,-2399,533,533,835,820,336,261,578,548,563,577,532,532,832,772,562,562,547,547,305,275,560,515,290,290,288,258 };
    static const drmp3_uint8 tab32[] = { 130,162,193,209,44,28,76,140,9,9,9,9,9,9,9,9,190,254,222,238,126,94,157,157,109,61,173,205};
    static const drmp3_uint8 tab33[] = { 252,236,220,204,188,172,156,140,124,108,92,76,60,44,28,12 };
    static const drmp3_int16 tabindex[2*16] = { 0,32,64,98,0,132,180,218,292,364,426,538,648,746,0,1126,1460,1460,1460,1460,1460,1460,1460,1460,1842,1842,1842,1842,1842,1842,1842,1842 };
    static const drmp3_uint8 g_linbits[] =  { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,3,4,6,8,10,13,4,5,6,7,8,9,11,13 };

#define DRMP3_PEEK_BITS(n)    (bs_cache >> (32 - n))
#define DRMP3_FLUSH_BITS(n)   { bs_cache <<= (n); bs_sh += (n); }
#define DRMP3_CHECK_BITS      while (bs_sh >= 0) { bs_cache |= (drmp3_uint32)*bs_next_ptr++ << bs_sh; bs_sh -= 8; }
#define DRMP3_BSPOS           ((bs_next_ptr - bs->buf)*8 - 24 + bs_sh)

    float one = 0.0f;
    int ireg = 0, big_val_cnt = gr_info->big_values;
    const drmp3_uint8 *sfb = gr_info->sfbtab;
    const drmp3_uint8 *bs_next_ptr = bs->buf + bs->pos/8;
    drmp3_uint32 bs_cache = (((bs_next_ptr[0]*256u + bs_next_ptr[1])*256u + bs_next_ptr[2])*256u + bs_next_ptr[3]) << (bs->pos & 7);
    int pairs_to_decode, np, bs_sh = (bs->pos & 7) - 8;
    bs_next_ptr += 4;

    while (big_val_cnt > 0)
    {
        int tab_num = gr_info->table_select[ireg];
        int sfb_cnt = gr_info->region_count[ireg++];
        const drmp3_int16 *codebook = tabs + tabindex[tab_num];
        int linbits = g_linbits[tab_num];
        if (linbits)
        {
            do
            {
                np = *sfb++ / 2;
                pairs_to_decode = DRMP3_MIN(big_val_cnt, np);
                one = *scf++;
                do
                {
                    int j, w = 5;
                    int leaf = codebook[DRMP3_PEEK_BITS(w)];
                    while (leaf < 0)
                    {
                        DRMP3_FLUSH_BITS(w);
                        w = leaf & 7;
                        leaf = codebook[DRMP3_PEEK_BITS(w) - (leaf >> 3)];
                    }
                    DRMP3_FLUSH_BITS(leaf >> 8);

                    for (j = 0; j < 2; j++, dst++, leaf >>= 4)
                    {
                        int lsb = leaf & 0x0F;
                        if (lsb == 15)
                        {
                            lsb += DRMP3_PEEK_BITS(linbits);
                            DRMP3_FLUSH_BITS(linbits);
                            DRMP3_CHECK_BITS;
                            *dst = one*drmp3_L3_pow_43(lsb)*((drmp3_int32)bs_cache < 0 ? -1: 1);
                        } else
                        {
                            *dst = g_drmp3_pow43[16 + lsb - 16*(bs_cache >> 31)]*one;
                        }
                        DRMP3_FLUSH_BITS(lsb ? 1 : 0);
                    }
                    DRMP3_CHECK_BITS;
                } while (--pairs_to_decode);
            } while ((big_val_cnt -= np) > 0 && --sfb_cnt >= 0);
        } else
        {
            do
            {
                np = *sfb++ / 2;
                pairs_to_decode = DRMP3_MIN(big_val_cnt, np);
                one = *scf++;
                do
                {
                    int j, w = 5;
                    int leaf = codebook[DRMP3_PEEK_BITS(w)];
                    while (leaf < 0)
                    {
                        DRMP3_FLUSH_BITS(w);
                        w = leaf & 7;
                        leaf = codebook[DRMP3_PEEK_BITS(w) - (leaf >> 3)];
                    }
                    DRMP3_FLUSH_BITS(leaf >> 8);

                    for (j = 0; j < 2; j++, dst++, leaf >>= 4)
                    {
                        int lsb = leaf & 0x0F;
                        *dst = g_drmp3_pow43[16 + lsb - 16*(bs_cache >> 31)]*one;
                        DRMP3_FLUSH_BITS(lsb ? 1 : 0);
                    }
                    DRMP3_CHECK_BITS;
                } while (--pairs_to_decode);
            } while ((big_val_cnt -= np) > 0 && --sfb_cnt >= 0);
        }
    }

    for (np = 1 - big_val_cnt;; dst += 4)
    {
        const drmp3_uint8 *codebook_count1 = (gr_info->count1_table) ? tab33 : tab32;
        int leaf = codebook_count1[DRMP3_PEEK_BITS(4)];
        if (!(leaf & 8))
        {
            leaf = codebook_count1[(leaf >> 3) + (bs_cache << 4 >> (32 - (leaf & 3)))];
        }
        DRMP3_FLUSH_BITS(leaf & 7);
        if (DRMP3_BSPOS > layer3gr_limit)
        {
            break;
        }
#define DRMP3_RELOAD_SCALEFACTOR  if (!--np) { np = *sfb++/2; if (!np) break; one = *scf++; }
#define DRMP3_DEQ_COUNT1(s) if (leaf & (128 >> s)) { dst[s] = ((drmp3_int32)bs_cache < 0) ? -one : one; DRMP3_FLUSH_BITS(1) }
        DRMP3_RELOAD_SCALEFACTOR;
        DRMP3_DEQ_COUNT1(0);
        DRMP3_DEQ_COUNT1(1);
        DRMP3_RELOAD_SCALEFACTOR;
        DRMP3_DEQ_COUNT1(2);
        DRMP3_DEQ_COUNT1(3);
        DRMP3_CHECK_BITS;
    }

    bs->pos = layer3gr_limit;
}

static void drmp3_L3_midside_stereo(float *left, int n)
{
    int i = 0;
    float *right = left + 576;
#if DRMP3_HAVE_SIMD
    if (drmp3_have_simd()) for (; i < n - 3; i += 4)
    {
        drmp3_f4 vl = DRMP3_VLD(left + i);
        drmp3_f4 vr = DRMP3_VLD(right + i);
        DRMP3_VSTORE(left + i, DRMP3_VADD(vl, vr));
        DRMP3_VSTORE(right + i, DRMP3_VSUB(vl, vr));
    }
#endif
    for (; i < n; i++)
    {
        float a = left[i];
        float b = right[i];
        left[i] = a + b;
        right[i] = a - b;
    }
}

static void drmp3_L3_intensity_stereo_band(float *left, int n, float kl, float kr)
{
    int i;
    for (i = 0; i < n; i++)
    {
        left[i + 576] = left[i]*kr;
        left[i] = left[i]*kl;
    }
}

static void drmp3_L3_stereo_top_band(const float *right, const drmp3_uint8 *sfb, int nbands, int max_band[3])
{
    int i, k;

    max_band[0] = max_band[1] = max_band[2] = -1;

    for (i = 0; i < nbands; i++)
    {
        for (k = 0; k < sfb[i]; k += 2)
        {
            if (right[k] != 0 || right[k + 1] != 0)
            {
                max_band[i % 3] = i;
                break;
            }
        }
        right += sfb[i];
    }
}

static void drmp3_L3_stereo_process(float *left, const drmp3_uint8 *ist_pos, const drmp3_uint8 *sfb, const drmp3_uint8 *hdr, int max_band[3], int mpeg2_sh)
{
    static const float g_pan[7*2] = { 0,1,0.21132487f,0.78867513f,0.36602540f,0.63397460f,0.5f,0.5f,0.63397460f,0.36602540f,0.78867513f,0.21132487f,1,0 };
    unsigned i, max_pos = DRMP3_HDR_TEST_MPEG1(hdr) ? 7 : 64;

    for (i = 0; sfb[i]; i++)
    {
        unsigned ipos = ist_pos[i];
        if ((int)i > max_band[i % 3] && ipos < max_pos)
        {
            float kl, kr, s = DRMP3_HDR_TEST_MS_STEREO(hdr) ? 1.41421356f : 1;
            if (DRMP3_HDR_TEST_MPEG1(hdr))
            {
                kl = g_pan[2*ipos];
                kr = g_pan[2*ipos + 1];
            } else
            {
                kl = 1;
                kr = drmp3_L3_ldexp_q2(1, (ipos + 1) >> 1 << mpeg2_sh);
                if (ipos & 1)
                {
                    kl = kr;
                    kr = 1;
                }
            }
            drmp3_L3_intensity_stereo_band(left, sfb[i], kl*s, kr*s);
        } else if (DRMP3_HDR_TEST_MS_STEREO(hdr))
        {
            drmp3_L3_midside_stereo(left, sfb[i]);
        }
        left += sfb[i];
    }
}

static void drmp3_L3_intensity_stereo(float *left, drmp3_uint8 *ist_pos, const drmp3_L3_gr_info *gr, const drmp3_uint8 *hdr)
{
    int max_band[3], n_sfb = gr->n_long_sfb + gr->n_short_sfb;
    int i, max_blocks = gr->n_short_sfb ? 3 : 1;

    drmp3_L3_stereo_top_band(left + 576, gr->sfbtab, n_sfb, max_band);
    if (gr->n_long_sfb)
    {
        max_band[0] = max_band[1] = max_band[2] = DRMP3_MAX(DRMP3_MAX(max_band[0], max_band[1]), max_band[2]);
    }
    for (i = 0; i < max_blocks; i++)
    {
        int default_pos = DRMP3_HDR_TEST_MPEG1(hdr) ? 3 : 0;
        int itop = n_sfb - max_blocks + i;
        int prev = itop - max_blocks;
        ist_pos[itop] = (drmp3_uint8)(max_band[i] >= prev ? default_pos : ist_pos[prev]);
    }
    drmp3_L3_stereo_process(left, ist_pos, gr->sfbtab, hdr, max_band, gr[1].scalefac_compress & 1);
}

static void drmp3_L3_reorder(float *grbuf, float *scratch, const drmp3_uint8 *sfb)
{
    int i, len;
    float *src = grbuf, *dst = scratch;

    for (;0 != (len = *sfb); sfb += 3, src += 2*len)
    {
        for (i = 0; i < len; i++, src++)
        {
            *dst++ = src[0*len];
            *dst++ = src[1*len];
            *dst++ = src[2*len];
        }
    }
    memcpy(grbuf, scratch, (dst - scratch)*sizeof(float));
}

static void drmp3_L3_antialias(float *grbuf, int nbands)
{
    static const float g_aa[2][8] = {
        {0.85749293f,0.88174200f,0.94962865f,0.98331459f,0.99551782f,0.99916056f,0.99989920f,0.99999316f},
        {0.51449576f,0.47173197f,0.31337745f,0.18191320f,0.09457419f,0.04096558f,0.01419856f,0.00369997f}
    };

    for (; nbands > 0; nbands--, grbuf += 18)
    {
        int i = 0;
#if DRMP3_HAVE_SIMD
        if (drmp3_have_simd()) for (; i < 8; i += 4)
        {
            drmp3_f4 vu = DRMP3_VLD(grbuf + 18 + i);
            drmp3_f4 vd = DRMP3_VLD(grbuf + 14 - i);
            drmp3_f4 vc0 = DRMP3_VLD(g_aa[0] + i);
            drmp3_f4 vc1 = DRMP3_VLD(g_aa[1] + i);
            vd = DRMP3_VREV(vd);
            DRMP3_VSTORE(grbuf + 18 + i, DRMP3_VSUB(DRMP3_VMUL(vu, vc0), DRMP3_VMUL(vd, vc1)));
            vd = DRMP3_VADD(DRMP3_VMUL(vu, vc1), DRMP3_VMUL(vd, vc0));
            DRMP3_VSTORE(grbuf + 14 - i, DRMP3_VREV(vd));
        }
#endif
#ifndef DR_MP3_ONLY_SIMD
        for(; i < 8; i++)
        {
            float u = grbuf[18 + i];
            float d = grbuf[17 - i];
            grbuf[18 + i] = u*g_aa[0][i] - d*g_aa[1][i];
            grbuf[17 - i] = u*g_aa[1][i] + d*g_aa[0][i];
        }
#endif
    }
}

static void drmp3_L3_dct3_9(float *y)
{
    float s0, s1, s2, s3, s4, s5, s6, s7, s8, t0, t2, t4;

    s0 = y[0]; s2 = y[2]; s4 = y[4]; s6 = y[6]; s8 = y[8];
    t0 = s0 + s6*0.5f;
    s0 -= s6;
    t4 = (s4 + s2)*0.93969262f;
    t2 = (s8 + s2)*0.76604444f;
    s6 = (s4 - s8)*0.17364818f;
    s4 += s8 - s2;

    s2 = s0 - s4*0.5f;
    y[4] = s4 + s0;
    s8 = t0 - t2 + s6;
    s0 = t0 - t4 + t2;
    s4 = t0 + t4 - s6;

    s1 = y[1]; s3 = y[3]; s5 = y[5]; s7 = y[7];

    s3 *= 0.86602540f;
    t0 = (s5 + s1)*0.98480775f;
    t4 = (s5 - s7)*0.34202014f;
    t2 = (s1 + s7)*0.64278761f;
    s1 = (s1 - s5 - s7)*0.86602540f;

    s5 = t0 - s3 - t2;
    s7 = t4 - s3 - t0;
    s3 = t4 + s3 - t2;

    y[0] = s4 - s7;
    y[1] = s2 + s1;
    y[2] = s0 - s3;
    y[3] = s8 + s5;
    y[5] = s8 - s5;
    y[6] = s0 + s3;
    y[7] = s2 - s1;
    y[8] = s4 + s7;
}

static void drmp3_L3_imdct36(float *grbuf, float *overlap, const float *window, int nbands)
{
    int i, j;
    static const float g_twid9[18] = {
        0.73727734f,0.79335334f,0.84339145f,0.88701083f,0.92387953f,0.95371695f,0.97629601f,0.99144486f,0.99904822f,0.67559021f,0.60876143f,0.53729961f,0.46174861f,0.38268343f,0.30070580f,0.21643961f,0.13052619f,0.04361938f
    };

    for (j = 0; j < nbands; j++, grbuf += 18, overlap += 9)
    {
        float co[9], si[9];
        co[0] = -grbuf[0];
        si[0] = grbuf[17];
        for (i = 0; i < 4; i++)
        {
            si[8 - 2*i] =   grbuf[4*i + 1] - grbuf[4*i + 2];
            co[1 + 2*i] =   grbuf[4*i + 1] + grbuf[4*i + 2];
            si[7 - 2*i] =   grbuf[4*i + 4] - grbuf[4*i + 3];
            co[2 + 2*i] = -(grbuf[4*i + 3] + grbuf[4*i + 4]);
        }
        drmp3_L3_dct3_9(co);
        drmp3_L3_dct3_9(si);

        si[1] = -si[1];
        si[3] = -si[3];
        si[5] = -si[5];
        si[7] = -si[7];

        i = 0;

#if DRMP3_HAVE_SIMD
        if (drmp3_have_simd()) for (; i < 8; i += 4)
        {
            drmp3_f4 vovl = DRMP3_VLD(overlap + i);
            drmp3_f4 vc = DRMP3_VLD(co + i);
            drmp3_f4 vs = DRMP3_VLD(si + i);
            drmp3_f4 vr0 = DRMP3_VLD(g_twid9 + i);
            drmp3_f4 vr1 = DRMP3_VLD(g_twid9 + 9 + i);
            drmp3_f4 vw0 = DRMP3_VLD(window + i);
            drmp3_f4 vw1 = DRMP3_VLD(window + 9 + i);
            drmp3_f4 vsum = DRMP3_VADD(DRMP3_VMUL(vc, vr1), DRMP3_VMUL(vs, vr0));
            DRMP3_VSTORE(overlap + i, DRMP3_VSUB(DRMP3_VMUL(vc, vr0), DRMP3_VMUL(vs, vr1)));
            DRMP3_VSTORE(grbuf + i, DRMP3_VSUB(DRMP3_VMUL(vovl, vw0), DRMP3_VMUL(vsum, vw1)));
            vsum = DRMP3_VADD(DRMP3_VMUL(vovl, vw1), DRMP3_VMUL(vsum, vw0));
            DRMP3_VSTORE(grbuf + 14 - i, DRMP3_VREV(vsum));
        }
#endif
        for (; i < 9; i++)
        {
            float ovl  = overlap[i];
            float sum  = co[i]*g_twid9[9 + i] + si[i]*g_twid9[0 + i];
            overlap[i] = co[i]*g_twid9[0 + i] - si[i]*g_twid9[9 + i];
            grbuf[i]      = ovl*window[0 + i] - sum*window[9 + i];
            grbuf[17 - i] = ovl*window[9 + i] + sum*window[0 + i];
        }
    }
}

static void drmp3_L3_idct3(float x0, float x1, float x2, float *dst)
{
    float m1 = x1*0.86602540f;
    float a1 = x0 - x2*0.5f;
    dst[1] = x0 + x2;
    dst[0] = a1 + m1;
    dst[2] = a1 - m1;
}

static void drmp3_L3_imdct12(float *x, float *dst, float *overlap)
{
    static const float g_twid3[6] = { 0.79335334f,0.92387953f,0.99144486f, 0.60876143f,0.38268343f,0.13052619f };
    float co[3], si[3];
    int i;

    drmp3_L3_idct3(-x[0], x[6] + x[3], x[12] + x[9], co);
    drmp3_L3_idct3(x[15], x[12] - x[9], x[6] - x[3], si);
    si[1] = -si[1];

    for (i = 0; i < 3; i++)
    {
        float ovl  = overlap[i];
        float sum  = co[i]*g_twid3[3 + i] + si[i]*g_twid3[0 + i];
        overlap[i] = co[i]*g_twid3[0 + i] - si[i]*g_twid3[3 + i];
        dst[i]     = ovl*g_twid3[2 - i] - sum*g_twid3[5 - i];
        dst[5 - i] = ovl*g_twid3[5 - i] + sum*g_twid3[2 - i];
    }
}

static void drmp3_L3_imdct_short(float *grbuf, float *overlap, int nbands)
{
    for (;nbands > 0; nbands--, overlap += 9, grbuf += 18)
    {
        float tmp[18];
        memcpy(tmp, grbuf, sizeof(tmp));
        memcpy(grbuf, overlap, 6*sizeof(float));
        drmp3_L3_imdct12(tmp, grbuf + 6, overlap + 6);
        drmp3_L3_imdct12(tmp + 1, grbuf + 12, overlap + 6);
        drmp3_L3_imdct12(tmp + 2, overlap, overlap + 6);
    }
}

static void drmp3_L3_change_sign(float *grbuf)
{
    int b, i;
    for (b = 0, grbuf += 18; b < 32; b += 2, grbuf += 36)
        for (i = 1; i < 18; i += 2)
            grbuf[i] = -grbuf[i];
}

static void drmp3_L3_imdct_gr(float *grbuf, float *overlap, unsigned block_type, unsigned n_long_bands)
{
    static const float g_mdct_window[2][18] = {
        { 0.99904822f,0.99144486f,0.97629601f,0.95371695f,0.92387953f,0.88701083f,0.84339145f,0.79335334f,0.73727734f,0.04361938f,0.13052619f,0.21643961f,0.30070580f,0.38268343f,0.46174861f,0.53729961f,0.60876143f,0.67559021f },
        { 1,1,1,1,1,1,0.99144486f,0.92387953f,0.79335334f,0,0,0,0,0,0,0.13052619f,0.38268343f,0.60876143f }
    };
    if (n_long_bands)
    {
        drmp3_L3_imdct36(grbuf, overlap, g_mdct_window[0], n_long_bands);
        grbuf += 18*n_long_bands;
        overlap += 9*n_long_bands;
    }
    if (block_type == DRMP3_SHORT_BLOCK_TYPE)
        drmp3_L3_imdct_short(grbuf, overlap, 32 - n_long_bands);
    else
        drmp3_L3_imdct36(grbuf, overlap, g_mdct_window[block_type == DRMP3_STOP_BLOCK_TYPE], 32 - n_long_bands);
}

static void drmp3_L3_save_reservoir(drmp3dec *h, drmp3dec_scratch *s)
{
    int pos = (s->bs.pos + 7)/8u;
    int remains = s->bs.limit/8u - pos;
    if (remains > DRMP3_MAX_BITRESERVOIR_BYTES)
    {
        pos += remains - DRMP3_MAX_BITRESERVOIR_BYTES;
        remains = DRMP3_MAX_BITRESERVOIR_BYTES;
    }
    if (remains > 0)
    {
        memmove(h->reserv_buf, s->maindata + pos, remains);
    }
    h->reserv = remains;
}

static int drmp3_L3_restore_reservoir(drmp3dec *h, drmp3_bs *bs, drmp3dec_scratch *s, int main_data_begin)
{
    int frame_bytes = (bs->limit - bs->pos)/8;
    int bytes_have = DRMP3_MIN(h->reserv, main_data_begin);
    memcpy(s->maindata, h->reserv_buf + DRMP3_MAX(0, h->reserv - main_data_begin), DRMP3_MIN(h->reserv, main_data_begin));
    memcpy(s->maindata + bytes_have, bs->buf + bs->pos/8, frame_bytes);
    drmp3_bs_init(&s->bs, s->maindata, bytes_have + frame_bytes);
    return h->reserv >= main_data_begin;
}

static void drmp3_L3_decode(drmp3dec *h, drmp3dec_scratch *s, drmp3_L3_gr_info *gr_info, int nch)
{
    int ch;

    for (ch = 0; ch < nch; ch++)
    {
        int layer3gr_limit = s->bs.pos + gr_info[ch].part_23_length;
        drmp3_L3_decode_scalefactors(h->header, s->ist_pos[ch], &s->bs, gr_info + ch, s->scf, ch);
        drmp3_L3_huffman(s->grbuf[ch], &s->bs, gr_info + ch, s->scf, layer3gr_limit);
    }

    if (DRMP3_HDR_TEST_I_STEREO(h->header))
    {
        drmp3_L3_intensity_stereo(s->grbuf[0], s->ist_pos[1], gr_info, h->header);
    } else if (DRMP3_HDR_IS_MS_STEREO(h->header))
    {
        drmp3_L3_midside_stereo(s->grbuf[0], 576);
    }

    for (ch = 0; ch < nch; ch++, gr_info++)
    {
        int aa_bands = 31;
        int n_long_bands = (gr_info->mixed_block_flag ? 2 : 0) << (int)(DRMP3_HDR_GET_MY_SAMPLE_RATE(h->header) == 2);

        if (gr_info->n_short_sfb)
        {
            aa_bands = n_long_bands - 1;
            drmp3_L3_reorder(s->grbuf[ch] + n_long_bands*18, s->syn[0], gr_info->sfbtab + gr_info->n_long_sfb);
        }

        drmp3_L3_antialias(s->grbuf[ch], aa_bands);
        drmp3_L3_imdct_gr(s->grbuf[ch], h->mdct_overlap[ch], gr_info->block_type, n_long_bands);
        drmp3_L3_change_sign(s->grbuf[ch]);
    }
}

static void drmp3d_DCT_II(float *grbuf, int n)
{
    static const float g_sec[24] = {
        10.19000816f,0.50060302f,0.50241929f,3.40760851f,0.50547093f,0.52249861f,2.05778098f,0.51544732f,0.56694406f,1.48416460f,0.53104258f,0.64682180f,1.16943991f,0.55310392f,0.78815460f,0.97256821f,0.58293498f,1.06067765f,0.83934963f,0.62250412f,1.72244716f,0.74453628f,0.67480832f,5.10114861f
    };
    int i, k = 0;
#if DRMP3_HAVE_SIMD
    if (drmp3_have_simd()) for (; k < n; k += 4)
    {
        drmp3_f4 t[4][8], *x;
        float *y = grbuf + k;

        for (x = t[0], i = 0; i < 8; i++, x++)
        {
            drmp3_f4 x0 = DRMP3_VLD(&y[i*18]);
            drmp3_f4 x1 = DRMP3_VLD(&y[(15 - i)*18]);
            drmp3_f4 x2 = DRMP3_VLD(&y[(16 + i)*18]);
            drmp3_f4 x3 = DRMP3_VLD(&y[(31 - i)*18]);
            drmp3_f4 t0 = DRMP3_VADD(x0, x3);
            drmp3_f4 t1 = DRMP3_VADD(x1, x2);
            drmp3_f4 t2 = DRMP3_VMUL_S(DRMP3_VSUB(x1, x2), g_sec[3*i + 0]);
            drmp3_f4 t3 = DRMP3_VMUL_S(DRMP3_VSUB(x0, x3), g_sec[3*i + 1]);
            x[0] = DRMP3_VADD(t0, t1);
            x[8] = DRMP3_VMUL_S(DRMP3_VSUB(t0, t1), g_sec[3*i + 2]);
            x[16] = DRMP3_VADD(t3, t2);
            x[24] = DRMP3_VMUL_S(DRMP3_VSUB(t3, t2), g_sec[3*i + 2]);
        }
        for (x = t[0], i = 0; i < 4; i++, x += 8)
        {
            drmp3_f4 x0 = x[0], x1 = x[1], x2 = x[2], x3 = x[3], x4 = x[4], x5 = x[5], x6 = x[6], x7 = x[7], xt;
            xt = DRMP3_VSUB(x0, x7); x0 = DRMP3_VADD(x0, x7);
            x7 = DRMP3_VSUB(x1, x6); x1 = DRMP3_VADD(x1, x6);
            x6 = DRMP3_VSUB(x2, x5); x2 = DRMP3_VADD(x2, x5);
            x5 = DRMP3_VSUB(x3, x4); x3 = DRMP3_VADD(x3, x4);
            x4 = DRMP3_VSUB(x0, x3); x0 = DRMP3_VADD(x0, x3);
            x3 = DRMP3_VSUB(x1, x2); x1 = DRMP3_VADD(x1, x2);
            x[0] = DRMP3_VADD(x0, x1);
            x[4] = DRMP3_VMUL_S(DRMP3_VSUB(x0, x1), 0.70710677f);
            x5 = DRMP3_VADD(x5, x6);
            x6 = DRMP3_VMUL_S(DRMP3_VADD(x6, x7), 0.70710677f);
            x7 = DRMP3_VADD(x7, xt);
            x3 = DRMP3_VMUL_S(DRMP3_VADD(x3, x4), 0.70710677f);
            x5 = DRMP3_VSUB(x5, DRMP3_VMUL_S(x7, 0.198912367f)); /* rotate by PI/8 */
            x7 = DRMP3_VADD(x7, DRMP3_VMUL_S(x5, 0.382683432f));
            x5 = DRMP3_VSUB(x5, DRMP3_VMUL_S(x7, 0.198912367f));
            x0 = DRMP3_VSUB(xt, x6); xt = DRMP3_VADD(xt, x6);
            x[1] = DRMP3_VMUL_S(DRMP3_VADD(xt, x7), 0.50979561f);
            x[2] = DRMP3_VMUL_S(DRMP3_VADD(x4, x3), 0.54119611f);
            x[3] = DRMP3_VMUL_S(DRMP3_VSUB(x0, x5), 0.60134488f);
            x[5] = DRMP3_VMUL_S(DRMP3_VADD(x0, x5), 0.89997619f);
            x[6] = DRMP3_VMUL_S(DRMP3_VSUB(x4, x3), 1.30656302f);
            x[7] = DRMP3_VMUL_S(DRMP3_VSUB(xt, x7), 2.56291556f);
        }

        if (k > n - 3)
        {
#if DRMP3_HAVE_SSE
#define DRMP3_VSAVE2(i, v) _mm_storel_pi((__m64 *)(void*)&y[i*18], v)
#else
#define DRMP3_VSAVE2(i, v) vst1_f32((float32_t *)&y[i*18],  vget_low_f32(v))
#endif
            for (i = 0; i < 7; i++, y += 4*18)
            {
                drmp3_f4 s = DRMP3_VADD(t[3][i], t[3][i + 1]);
                DRMP3_VSAVE2(0, t[0][i]);
                DRMP3_VSAVE2(1, DRMP3_VADD(t[2][i], s));
                DRMP3_VSAVE2(2, DRMP3_VADD(t[1][i], t[1][i + 1]));
                DRMP3_VSAVE2(3, DRMP3_VADD(t[2][1 + i], s));
            }
            DRMP3_VSAVE2(0, t[0][7]);
            DRMP3_VSAVE2(1, DRMP3_VADD(t[2][7], t[3][7]));
            DRMP3_VSAVE2(2, t[1][7]);
            DRMP3_VSAVE2(3, t[3][7]);
        } else
        {
#define DRMP3_VSAVE4(i, v) DRMP3_VSTORE(&y[i*18], v)
            for (i = 0; i < 7; i++, y += 4*18)
            {
                drmp3_f4 s = DRMP3_VADD(t[3][i], t[3][i + 1]);
                DRMP3_VSAVE4(0, t[0][i]);
                DRMP3_VSAVE4(1, DRMP3_VADD(t[2][i], s));
                DRMP3_VSAVE4(2, DRMP3_VADD(t[1][i], t[1][i + 1]));
                DRMP3_VSAVE4(3, DRMP3_VADD(t[2][1 + i], s));
            }
            DRMP3_VSAVE4(0, t[0][7]);
            DRMP3_VSAVE4(1, DRMP3_VADD(t[2][7], t[3][7]));
            DRMP3_VSAVE4(2, t[1][7]);
            DRMP3_VSAVE4(3, t[3][7]);
        }
    } else
#endif
#ifdef DR_MP3_ONLY_SIMD
    {}
#else
    for (; k < n; k++)
    {
        float t[4][8], *x, *y = grbuf + k;

        for (x = t[0], i = 0; i < 8; i++, x++)
        {
            float x0 = y[i*18];
            float x1 = y[(15 - i)*18];
            float x2 = y[(16 + i)*18];
            float x3 = y[(31 - i)*18];
            float t0 = x0 + x3;
            float t1 = x1 + x2;
            float t2 = (x1 - x2)*g_sec[3*i + 0];
            float t3 = (x0 - x3)*g_sec[3*i + 1];
            x[0] = t0 + t1;
            x[8] = (t0 - t1)*g_sec[3*i + 2];
            x[16] = t3 + t2;
            x[24] = (t3 - t2)*g_sec[3*i + 2];
        }
        for (x = t[0], i = 0; i < 4; i++, x += 8)
        {
            float x0 = x[0], x1 = x[1], x2 = x[2], x3 = x[3], x4 = x[4], x5 = x[5], x6 = x[6], x7 = x[7], xt;
            xt = x0 - x7; x0 += x7;
            x7 = x1 - x6; x1 += x6;
            x6 = x2 - x5; x2 += x5;
            x5 = x3 - x4; x3 += x4;
            x4 = x0 - x3; x0 += x3;
            x3 = x1 - x2; x1 += x2;
            x[0] = x0 + x1;
            x[4] = (x0 - x1)*0.70710677f;
            x5 =  x5 + x6;
            x6 = (x6 + x7)*0.70710677f;
            x7 =  x7 + xt;
            x3 = (x3 + x4)*0.70710677f;
            x5 -= x7*0.198912367f;  /* rotate by PI/8 */
            x7 += x5*0.382683432f;
            x5 -= x7*0.198912367f;
            x0 = xt - x6; xt += x6;
            x[1] = (xt + x7)*0.50979561f;
            x[2] = (x4 + x3)*0.54119611f;
            x[3] = (x0 - x5)*0.60134488f;
            x[5] = (x0 + x5)*0.89997619f;
            x[6] = (x4 - x3)*1.30656302f;
            x[7] = (xt - x7)*2.56291556f;

        }
        for (i = 0; i < 7; i++, y += 4*18)
        {
            y[0*18] = t[0][i];
            y[1*18] = t[2][i] + t[3][i] + t[3][i + 1];
            y[2*18] = t[1][i] + t[1][i + 1];
            y[3*18] = t[2][i + 1] + t[3][i] + t[3][i + 1];
        }
        y[0*18] = t[0][7];
        y[1*18] = t[2][7] + t[3][7];
        y[2*18] = t[1][7];
        y[3*18] = t[3][7];
    }
#endif
}

#ifndef DR_MP3_FLOAT_OUTPUT
typedef drmp3_int16 drmp3d_sample_t;

static drmp3_int16 drmp3d_scale_pcm(float sample)
{
    drmp3_int16 s;
#if DRMP3_HAVE_ARMV6
    drmp3_int32 s32 = (drmp3_int32)(sample + .5f);
    s32 -= (s32 < 0);
    s = (drmp3_int16)drmp3_clip_int16_arm(s32);
#else
    if (sample >=  32766.5) return (drmp3_int16) 32767;
    if (sample <= -32767.5) return (drmp3_int16)-32768;
    s = (drmp3_int16)(sample + .5f);
    s -= (s < 0);   /* away from zero, to be compliant */
#endif
    return s;
}
#else
typedef float drmp3d_sample_t;

static float drmp3d_scale_pcm(float sample)
{
    return sample*(1.f/32768.f);
}
#endif

static void drmp3d_synth_pair(drmp3d_sample_t *pcm, int nch, const float *z)
{
    float a;
    a  = (z[14*64] - z[    0]) * 29;
    a += (z[ 1*64] + z[13*64]) * 213;
    a += (z[12*64] - z[ 2*64]) * 459;
    a += (z[ 3*64] + z[11*64]) * 2037;
    a += (z[10*64] - z[ 4*64]) * 5153;
    a += (z[ 5*64] + z[ 9*64]) * 6574;
    a += (z[ 8*64] - z[ 6*64]) * 37489;
    a +=  z[ 7*64]             * 75038;
    pcm[0] = drmp3d_scale_pcm(a);

    z += 2;
    a  = z[14*64] * 104;
    a += z[12*64] * 1567;
    a += z[10*64] * 9727;
    a += z[ 8*64] * 64019;
    a += z[ 6*64] * -9975;
    a += z[ 4*64] * -45;
    a += z[ 2*64] * 146;
    a += z[ 0*64] * -5;
    pcm[16*nch] = drmp3d_scale_pcm(a);
}

static void drmp3d_synth(float *xl, drmp3d_sample_t *dstl, int nch, float *lins)
{
    int i;
    float *xr = xl + 576*(nch - 1);
    drmp3d_sample_t *dstr = dstl + (nch - 1);

    static const float g_win[] = {
        -1,26,-31,208,218,401,-519,2063,2000,4788,-5517,7134,5959,35640,-39336,74992,
        -1,24,-35,202,222,347,-581,2080,1952,4425,-5879,7640,5288,33791,-41176,74856,
        -1,21,-38,196,225,294,-645,2087,1893,4063,-6237,8092,4561,31947,-43006,74630,
        -1,19,-41,190,227,244,-711,2085,1822,3705,-6589,8492,3776,30112,-44821,74313,
        -1,17,-45,183,228,197,-779,2075,1739,3351,-6935,8840,2935,28289,-46617,73908,
        -1,16,-49,176,228,153,-848,2057,1644,3004,-7271,9139,2037,26482,-48390,73415,
        -2,14,-53,169,227,111,-919,2032,1535,2663,-7597,9389,1082,24694,-50137,72835,
        -2,13,-58,161,224,72,-991,2001,1414,2330,-7910,9592,70,22929,-51853,72169,
        -2,11,-63,154,221,36,-1064,1962,1280,2006,-8209,9750,-998,21189,-53534,71420,
        -2,10,-68,147,215,2,-1137,1919,1131,1692,-8491,9863,-2122,19478,-55178,70590,
        -3,9,-73,139,208,-29,-1210,1870,970,1388,-8755,9935,-3300,17799,-56778,69679,
        -3,8,-79,132,200,-57,-1283,1817,794,1095,-8998,9966,-4533,16155,-58333,68692,
        -4,7,-85,125,189,-83,-1356,1759,605,814,-9219,9959,-5818,14548,-59838,67629,
        -4,7,-91,117,177,-106,-1428,1698,402,545,-9416,9916,-7154,12980,-61289,66494,
        -5,6,-97,111,163,-127,-1498,1634,185,288,-9585,9838,-8540,11455,-62684,65290
    };
    float *zlin = lins + 15*64;
    const float *w = g_win;

    zlin[4*15]     = xl[18*16];
    zlin[4*15 + 1] = xr[18*16];
    zlin[4*15 + 2] = xl[0];
    zlin[4*15 + 3] = xr[0];

    zlin[4*31]     = xl[1 + 18*16];
    zlin[4*31 + 1] = xr[1 + 18*16];
    zlin[4*31 + 2] = xl[1];
    zlin[4*31 + 3] = xr[1];

    drmp3d_synth_pair(dstr, nch, lins + 4*15 + 1);
    drmp3d_synth_pair(dstr + 32*nch, nch, lins + 4*15 + 64 + 1);
    drmp3d_synth_pair(dstl, nch, lins + 4*15);
    drmp3d_synth_pair(dstl + 32*nch, nch, lins + 4*15 + 64);

#if DRMP3_HAVE_SIMD
    if (drmp3_have_simd()) for (i = 14; i >= 0; i--)
    {
#define DRMP3_VLOAD(k) drmp3_f4 w0 = DRMP3_VSET(*w++); drmp3_f4 w1 = DRMP3_VSET(*w++); drmp3_f4 vz = DRMP3_VLD(&zlin[4*i - 64*k]); drmp3_f4 vy = DRMP3_VLD(&zlin[4*i - 64*(15 - k)]);
#define DRMP3_V0(k) { DRMP3_VLOAD(k) b =               DRMP3_VADD(DRMP3_VMUL(vz, w1), DRMP3_VMUL(vy, w0)) ; a =               DRMP3_VSUB(DRMP3_VMUL(vz, w0), DRMP3_VMUL(vy, w1));  }
#define DRMP3_V1(k) { DRMP3_VLOAD(k) b = DRMP3_VADD(b, DRMP3_VADD(DRMP3_VMUL(vz, w1), DRMP3_VMUL(vy, w0))); a = DRMP3_VADD(a, DRMP3_VSUB(DRMP3_VMUL(vz, w0), DRMP3_VMUL(vy, w1))); }
#define DRMP3_V2(k) { DRMP3_VLOAD(k) b = DRMP3_VADD(b, DRMP3_VADD(DRMP3_VMUL(vz, w1), DRMP3_VMUL(vy, w0))); a = DRMP3_VADD(a, DRMP3_VSUB(DRMP3_VMUL(vy, w1), DRMP3_VMUL(vz, w0))); }
        drmp3_f4 a, b;
        zlin[4*i]     = xl[18*(31 - i)];
        zlin[4*i + 1] = xr[18*(31 - i)];
        zlin[4*i + 2] = xl[1 + 18*(31 - i)];
        zlin[4*i + 3] = xr[1 + 18*(31 - i)];
        zlin[4*i + 64] = xl[1 + 18*(1 + i)];
        zlin[4*i + 64 + 1] = xr[1 + 18*(1 + i)];
        zlin[4*i - 64 + 2] = xl[18*(1 + i)];
        zlin[4*i - 64 + 3] = xr[18*(1 + i)];

        DRMP3_V0(0) DRMP3_V2(1) DRMP3_V1(2) DRMP3_V2(3) DRMP3_V1(4) DRMP3_V2(5) DRMP3_V1(6) DRMP3_V2(7)

        {
#ifndef DR_MP3_FLOAT_OUTPUT
#if DRMP3_HAVE_SSE
            static const drmp3_f4 g_max = { 32767.0f, 32767.0f, 32767.0f, 32767.0f };
            static const drmp3_f4 g_min = { -32768.0f, -32768.0f, -32768.0f, -32768.0f };
            __m128i pcm8 = _mm_packs_epi32(_mm_cvtps_epi32(_mm_max_ps(_mm_min_ps(a, g_max), g_min)),
                                           _mm_cvtps_epi32(_mm_max_ps(_mm_min_ps(b, g_max), g_min)));
            dstr[(15 - i)*nch] = (drmp3_int16)_mm_extract_epi16(pcm8, 1);
            dstr[(17 + i)*nch] = (drmp3_int16)_mm_extract_epi16(pcm8, 5);
            dstl[(15 - i)*nch] = (drmp3_int16)_mm_extract_epi16(pcm8, 0);
            dstl[(17 + i)*nch] = (drmp3_int16)_mm_extract_epi16(pcm8, 4);
            dstr[(47 - i)*nch] = (drmp3_int16)_mm_extract_epi16(pcm8, 3);
            dstr[(49 + i)*nch] = (drmp3_int16)_mm_extract_epi16(pcm8, 7);
            dstl[(47 - i)*nch] = (drmp3_int16)_mm_extract_epi16(pcm8, 2);
            dstl[(49 + i)*nch] = (drmp3_int16)_mm_extract_epi16(pcm8, 6);
#else
            int16x4_t pcma, pcmb;
            a = DRMP3_VADD(a, DRMP3_VSET(0.5f));
            b = DRMP3_VADD(b, DRMP3_VSET(0.5f));
            pcma = vqmovn_s32(vqaddq_s32(vcvtq_s32_f32(a), vreinterpretq_s32_u32(vcltq_f32(a, DRMP3_VSET(0)))));
            pcmb = vqmovn_s32(vqaddq_s32(vcvtq_s32_f32(b), vreinterpretq_s32_u32(vcltq_f32(b, DRMP3_VSET(0)))));
            vst1_lane_s16(dstr + (15 - i)*nch, pcma, 1);
            vst1_lane_s16(dstr + (17 + i)*nch, pcmb, 1);
            vst1_lane_s16(dstl + (15 - i)*nch, pcma, 0);
            vst1_lane_s16(dstl + (17 + i)*nch, pcmb, 0);
            vst1_lane_s16(dstr + (47 - i)*nch, pcma, 3);
            vst1_lane_s16(dstr + (49 + i)*nch, pcmb, 3);
            vst1_lane_s16(dstl + (47 - i)*nch, pcma, 2);
            vst1_lane_s16(dstl + (49 + i)*nch, pcmb, 2);
#endif
#else
            static const drmp3_f4 g_scale = { 1.0f/32768.0f, 1.0f/32768.0f, 1.0f/32768.0f, 1.0f/32768.0f };
            a = DRMP3_VMUL(a, g_scale);
            b = DRMP3_VMUL(b, g_scale);
#if DRMP3_HAVE_SSE
            _mm_store_ss(dstr + (15 - i)*nch, _mm_shuffle_ps(a, a, _MM_SHUFFLE(1, 1, 1, 1)));
            _mm_store_ss(dstr + (17 + i)*nch, _mm_shuffle_ps(b, b, _MM_SHUFFLE(1, 1, 1, 1)));
            _mm_store_ss(dstl + (15 - i)*nch, _mm_shuffle_ps(a, a, _MM_SHUFFLE(0, 0, 0, 0)));
            _mm_store_ss(dstl + (17 + i)*nch, _mm_shuffle_ps(b, b, _MM_SHUFFLE(0, 0, 0, 0)));
            _mm_store_ss(dstr + (47 - i)*nch, _mm_shuffle_ps(a, a, _MM_SHUFFLE(3, 3, 3, 3)));
            _mm_store_ss(dstr + (49 + i)*nch, _mm_shuffle_ps(b, b, _MM_SHUFFLE(3, 3, 3, 3)));
            _mm_store_ss(dstl + (47 - i)*nch, _mm_shuffle_ps(a, a, _MM_SHUFFLE(2, 2, 2, 2)));
            _mm_store_ss(dstl + (49 + i)*nch, _mm_shuffle_ps(b, b, _MM_SHUFFLE(2, 2, 2, 2)));
#else
            vst1q_lane_f32(dstr + (15 - i)*nch, a, 1);
            vst1q_lane_f32(dstr + (17 + i)*nch, b, 1);
            vst1q_lane_f32(dstl + (15 - i)*nch, a, 0);
            vst1q_lane_f32(dstl + (17 + i)*nch, b, 0);
            vst1q_lane_f32(dstr + (47 - i)*nch, a, 3);
            vst1q_lane_f32(dstr + (49 + i)*nch, b, 3);
            vst1q_lane_f32(dstl + (47 - i)*nch, a, 2);
            vst1q_lane_f32(dstl + (49 + i)*nch, b, 2);
#endif
#endif /* DR_MP3_FLOAT_OUTPUT */
        }
    } else
#endif
#ifdef DR_MP3_ONLY_SIMD
    {}
#else
    for (i = 14; i >= 0; i--)
    {
#define DRMP3_LOAD(k) float w0 = *w++; float w1 = *w++; float *vz = &zlin[4*i - k*64]; float *vy = &zlin[4*i - (15 - k)*64];
#define DRMP3_S0(k) { int j; DRMP3_LOAD(k); for (j = 0; j < 4; j++) b[j]  = vz[j]*w1 + vy[j]*w0, a[j]  = vz[j]*w0 - vy[j]*w1; }
#define DRMP3_S1(k) { int j; DRMP3_LOAD(k); for (j = 0; j < 4; j++) b[j] += vz[j]*w1 + vy[j]*w0, a[j] += vz[j]*w0 - vy[j]*w1; }
#define DRMP3_S2(k) { int j; DRMP3_LOAD(k); for (j = 0; j < 4; j++) b[j] += vz[j]*w1 + vy[j]*w0, a[j] += vy[j]*w1 - vz[j]*w0; }
        float a[4], b[4];

        zlin[4*i]     = xl[18*(31 - i)];
        zlin[4*i + 1] = xr[18*(31 - i)];
        zlin[4*i + 2] = xl[1 + 18*(31 - i)];
        zlin[4*i + 3] = xr[1 + 18*(31 - i)];
        zlin[4*(i + 16)]   = xl[1 + 18*(1 + i)];
        zlin[4*(i + 16) + 1] = xr[1 + 18*(1 + i)];
        zlin[4*(i - 16) + 2] = xl[18*(1 + i)];
        zlin[4*(i - 16) + 3] = xr[18*(1 + i)];

        DRMP3_S0(0) DRMP3_S2(1) DRMP3_S1(2) DRMP3_S2(3) DRMP3_S1(4) DRMP3_S2(5) DRMP3_S1(6) DRMP3_S2(7)

        dstr[(15 - i)*nch] = drmp3d_scale_pcm(a[1]);
        dstr[(17 + i)*nch] = drmp3d_scale_pcm(b[1]);
        dstl[(15 - i)*nch] = drmp3d_scale_pcm(a[0]);
        dstl[(17 + i)*nch] = drmp3d_scale_pcm(b[0]);
        dstr[(47 - i)*nch] = drmp3d_scale_pcm(a[3]);
        dstr[(49 + i)*nch] = drmp3d_scale_pcm(b[3]);
        dstl[(47 - i)*nch] = drmp3d_scale_pcm(a[2]);
        dstl[(49 + i)*nch] = drmp3d_scale_pcm(b[2]);
    }
#endif
}

static void drmp3d_synth_granule(float *qmf_state, float *grbuf, int nbands, int nch, drmp3d_sample_t *pcm, float *lins)
{
    int i;
    for (i = 0; i < nch; i++)
    {
        drmp3d_DCT_II(grbuf + 576*i, nbands);
    }

    memcpy(lins, qmf_state, sizeof(float)*15*64);

    for (i = 0; i < nbands; i += 2)
    {
        drmp3d_synth(grbuf + i, pcm + 32*nch*i, nch, lins + i*64);
    }
#ifndef DR_MP3_NONSTANDARD_BUT_LOGICAL
    if (nch == 1)
    {
        for (i = 0; i < 15*64; i += 2)
        {
            qmf_state[i] = lins[nbands*64 + i];
        }
    } else
#endif
    {
        memcpy(qmf_state, lins + nbands*64, sizeof(float)*15*64);
    }
}

static int drmp3d_match_frame(const drmp3_uint8 *hdr, int mp3_bytes, int frame_bytes)
{
    int i, nmatch;
    for (i = 0, nmatch = 0; nmatch < DRMP3_MAX_FRAME_SYNC_MATCHES; nmatch++)
    {
        i += drmp3_hdr_frame_bytes(hdr + i, frame_bytes) + drmp3_hdr_padding(hdr + i);
        if (i + DRMP3_HDR_SIZE > mp3_bytes)
            return nmatch > 0;
        if (!drmp3_hdr_compare(hdr, hdr + i))
            return 0;
    }
    return 1;
}

static int drmp3d_find_frame(const drmp3_uint8 *mp3, int mp3_bytes, int *free_format_bytes, int *ptr_frame_bytes)
{
    int i, k;
    for (i = 0; i < mp3_bytes - DRMP3_HDR_SIZE; i++, mp3++)
    {
        if (drmp3_hdr_valid(mp3))
        {
            int frame_bytes = drmp3_hdr_frame_bytes(mp3, *free_format_bytes);
            int frame_and_padding = frame_bytes + drmp3_hdr_padding(mp3);

            for (k = DRMP3_HDR_SIZE; !frame_bytes && k < DRMP3_MAX_FREE_FORMAT_FRAME_SIZE && i + 2*k < mp3_bytes - DRMP3_HDR_SIZE; k++)
            {
                if (drmp3_hdr_compare(mp3, mp3 + k))
                {
                    int fb = k - drmp3_hdr_padding(mp3);
                    int nextfb = fb + drmp3_hdr_padding(mp3 + k);
                    if (i + k + nextfb + DRMP3_HDR_SIZE > mp3_bytes || !drmp3_hdr_compare(mp3, mp3 + k + nextfb))
                        continue;
                    frame_and_padding = k;
                    frame_bytes = fb;
                    *free_format_bytes = fb;
                }
            }

            if ((frame_bytes && i + frame_and_padding <= mp3_bytes &&
                drmp3d_match_frame(mp3, mp3_bytes - i, frame_bytes)) ||
                (!i && frame_and_padding == mp3_bytes))
            {
                *ptr_frame_bytes = frame_and_padding;
                return i;
            }
            *free_format_bytes = 0;
        }
    }
    *ptr_frame_bytes = 0;
    return mp3_bytes;
}

DRMP3_API void drmp3dec_init(drmp3dec *dec)
{
    dec->header[0] = 0;
}

DRMP3_API int drmp3dec_decode_frame(drmp3dec *dec, const drmp3_uint8 *mp3, int mp3_bytes, void *pcm, drmp3dec_frame_info *info)
{
    int i = 0, igr, frame_size = 0, success = 1;
    const drmp3_uint8 *hdr;
    drmp3_bs bs_frame[1];
    drmp3dec_scratch scratch;

    if (mp3_bytes > 4 && dec->header[0] == 0xff && drmp3_hdr_compare(dec->header, mp3))
    {
        frame_size = drmp3_hdr_frame_bytes(mp3, dec->free_format_bytes) + drmp3_hdr_padding(mp3);
        if (frame_size != mp3_bytes && (frame_size + DRMP3_HDR_SIZE > mp3_bytes || !drmp3_hdr_compare(mp3, mp3 + frame_size)))
        {
            frame_size = 0;
        }
    }
    if (!frame_size)
    {
        memset(dec, 0, sizeof(drmp3dec));
        i = drmp3d_find_frame(mp3, mp3_bytes, &dec->free_format_bytes, &frame_size);
        if (!frame_size || i + frame_size > mp3_bytes)
        {
            info->frame_bytes = i;
            return 0;
        }
    }

    hdr = mp3 + i;
    memcpy(dec->header, hdr, DRMP3_HDR_SIZE);
    info->frame_bytes = i + frame_size;
    info->channels = DRMP3_HDR_IS_MONO(hdr) ? 1 : 2;
    info->hz = drmp3_hdr_sample_rate_hz(hdr);
    info->layer = 4 - DRMP3_HDR_GET_LAYER(hdr);
    info->bitrate_kbps = drmp3_hdr_bitrate_kbps(hdr);

    drmp3_bs_init(bs_frame, hdr + DRMP3_HDR_SIZE, frame_size - DRMP3_HDR_SIZE);
    if (DRMP3_HDR_IS_CRC(hdr))
    {
        drmp3_bs_get_bits(bs_frame, 16);
    }

    if (info->layer == 3)
    {
        int main_data_begin = drmp3_L3_read_side_info(bs_frame, scratch.gr_info, hdr);
        if (main_data_begin < 0 || bs_frame->pos > bs_frame->limit)
        {
            drmp3dec_init(dec);
            return 0;
        }
        success = drmp3_L3_restore_reservoir(dec, bs_frame, &scratch, main_data_begin);
        if (success && pcm != NULL)
        {
            for (igr = 0; igr < (DRMP3_HDR_TEST_MPEG1(hdr) ? 2 : 1); igr++, pcm = DRMP3_OFFSET_PTR(pcm, sizeof(drmp3d_sample_t)*576*info->channels))
            {
                memset(scratch.grbuf[0], 0, 576*2*sizeof(float));
                drmp3_L3_decode(dec, &scratch, scratch.gr_info + igr*info->channels, info->channels);
                drmp3d_synth_granule(dec->qmf_state, scratch.grbuf[0], 18, info->channels, (drmp3d_sample_t*)pcm, scratch.syn[0]);
            }
        }
        drmp3_L3_save_reservoir(dec, &scratch);
    } else
    {
#ifdef DR_MP3_ONLY_MP3
        return 0;
#else
        drmp3_L12_scale_info sci[1];

        if (pcm == NULL) {
            return drmp3_hdr_frame_samples(hdr);
        }

        drmp3_L12_read_scale_info(hdr, bs_frame, sci);

        memset(scratch.grbuf[0], 0, 576*2*sizeof(float));
        for (i = 0, igr = 0; igr < 3; igr++)
        {
            if (12 == (i += drmp3_L12_dequantize_granule(scratch.grbuf[0] + i, bs_frame, sci, info->layer | 1)))
            {
                i = 0;
                drmp3_L12_apply_scf_384(sci, sci->scf + igr, scratch.grbuf[0]);
                drmp3d_synth_granule(dec->qmf_state, scratch.grbuf[0], 12, info->channels, (drmp3d_sample_t*)pcm, scratch.syn[0]);
                memset(scratch.grbuf[0], 0, 576*2*sizeof(float));
                pcm = DRMP3_OFFSET_PTR(pcm, sizeof(drmp3d_sample_t)*384*info->channels);
            }
            if (bs_frame->pos > bs_frame->limit)
            {
                drmp3dec_init(dec);
                return 0;
            }
        }
#endif
    }

    return success*drmp3_hdr_frame_samples(dec->header);
}

DRMP3_API void drmp3dec_f32_to_s16(const float *in, drmp3_int16 *out, size_t num_samples)
{
    size_t i = 0;
#if DRMP3_HAVE_SIMD
    size_t aligned_count = num_samples & ~7;
    for(; i < aligned_count; i+=8)
    {
        drmp3_f4 scale = DRMP3_VSET(32768.0f);
        drmp3_f4 a = DRMP3_VMUL(DRMP3_VLD(&in[i  ]), scale);
        drmp3_f4 b = DRMP3_VMUL(DRMP3_VLD(&in[i+4]), scale);
#if DRMP3_HAVE_SSE
        drmp3_f4 s16max = DRMP3_VSET( 32767.0f);
        drmp3_f4 s16min = DRMP3_VSET(-32768.0f);
        __m128i pcm8 = _mm_packs_epi32(_mm_cvtps_epi32(_mm_max_ps(_mm_min_ps(a, s16max), s16min)),
                                        _mm_cvtps_epi32(_mm_max_ps(_mm_min_ps(b, s16max), s16min)));
        out[i  ] = (drmp3_int16)_mm_extract_epi16(pcm8, 0);
        out[i+1] = (drmp3_int16)_mm_extract_epi16(pcm8, 1);
        out[i+2] = (drmp3_int16)_mm_extract_epi16(pcm8, 2);
        out[i+3] = (drmp3_int16)_mm_extract_epi16(pcm8, 3);
        out[i+4] = (drmp3_int16)_mm_extract_epi16(pcm8, 4);
        out[i+5] = (drmp3_int16)_mm_extract_epi16(pcm8, 5);
        out[i+6] = (drmp3_int16)_mm_extract_epi16(pcm8, 6);
        out[i+7] = (drmp3_int16)_mm_extract_epi16(pcm8, 7);
#else
        int16x4_t pcma, pcmb;
        a = DRMP3_VADD(a, DRMP3_VSET(0.5f));
        b = DRMP3_VADD(b, DRMP3_VSET(0.5f));
        pcma = vqmovn_s32(vqaddq_s32(vcvtq_s32_f32(a), vreinterpretq_s32_u32(vcltq_f32(a, DRMP3_VSET(0)))));
        pcmb = vqmovn_s32(vqaddq_s32(vcvtq_s32_f32(b), vreinterpretq_s32_u32(vcltq_f32(b, DRMP3_VSET(0)))));
        vst1_lane_s16(out+i  , pcma, 0);
        vst1_lane_s16(out+i+1, pcma, 1);
        vst1_lane_s16(out+i+2, pcma, 2);
        vst1_lane_s16(out+i+3, pcma, 3);
        vst1_lane_s16(out+i+4, pcmb, 0);
        vst1_lane_s16(out+i+5, pcmb, 1);
        vst1_lane_s16(out+i+6, pcmb, 2);
        vst1_lane_s16(out+i+7, pcmb, 3);
#endif
    }
#endif
    for(; i < num_samples; i++)
    {
        float sample = in[i] * 32768.0f;
        if (sample >=  32766.5)
            out[i] = (drmp3_int16) 32767;
        else if (sample <= -32767.5)
            out[i] = (drmp3_int16)-32768;
        else
        {
            short s = (drmp3_int16)(sample + .5f);
            s -= (s < 0);   /* away from zero, to be compliant */
            out[i] = s;
        }
    }
}



/************************************************************************************************************************************************************

 Main Public API

 ************************************************************************************************************************************************************/
#include <math.h>   /* For sin() and exp(). */

#if defined(SIZE_MAX)
    #define DRMP3_SIZE_MAX  SIZE_MAX
#else
    #if defined(_WIN64) || defined(_LP64) || defined(__LP64__)
        #define DRMP3_SIZE_MAX  ((drmp3_uint64)0xFFFFFFFFFFFFFFFF)
    #else
        #define DRMP3_SIZE_MAX  0xFFFFFFFF
    #endif
#endif

/* Options. */
#ifndef DRMP3_SEEK_LEADING_MP3_FRAMES
#define DRMP3_SEEK_LEADING_MP3_FRAMES   2
#endif

#define DRMP3_MIN_DATA_CHUNK_SIZE   16384

/* The size in bytes of each chunk of data to read from the MP3 stream. minimp3 recommends at least 16K, but in an attempt to reduce data movement I'm making this slightly larger. */
#ifndef DRMP3_DATA_CHUNK_SIZE
#define DRMP3_DATA_CHUNK_SIZE  DRMP3_MIN_DATA_CHUNK_SIZE*4
#endif


/* Standard library stuff. */
#ifndef DRMP3_ASSERT
#include <assert.h>
#define DRMP3_ASSERT(expression) assert(expression)
#endif
#ifndef DRMP3_COPY_MEMORY
#define DRMP3_COPY_MEMORY(dst, src, sz) memcpy((dst), (src), (sz))
#endif
#ifndef DRMP3_ZERO_MEMORY
#define DRMP3_ZERO_MEMORY(p, sz) memset((p), 0, (sz))
#endif
#define DRMP3_ZERO_OBJECT(p) DRMP3_ZERO_MEMORY((p), sizeof(*(p)))
#ifndef DRMP3_MALLOC
#define DRMP3_MALLOC(sz) malloc((sz))
#endif
#ifndef DRMP3_REALLOC
#define DRMP3_REALLOC(p, sz) realloc((p), (sz))
#endif
#ifndef DRMP3_FREE
#define DRMP3_FREE(p) free((p))
#endif

#define DRMP3_COUNTOF(x)        (sizeof(x) / sizeof(x[0]))
#define DRMP3_CLAMP(x, lo, hi)  (DRMP3_MAX(lo, DRMP3_MIN(x, hi)))

#ifndef DRMP3_PI_D
#define DRMP3_PI_D    3.14159265358979323846264
#endif

#define DRMP3_DEFAULT_RESAMPLER_LPF_ORDER   2

static DRMP3_INLINE float drmp3_mix_f32(float x, float y, float a)
{
    return x*(1-a) + y*a;
}
static DRMP3_INLINE float drmp3_mix_f32_fast(float x, float y, float a)
{
    float r0 = (y - x);
    float r1 = r0*a;
    return x + r1;
    /*return x + (y - x)*a;*/
}


/*
Greatest common factor using Euclid's algorithm iteratively.
*/
static DRMP3_INLINE drmp3_uint32 drmp3_gcf_u32(drmp3_uint32 a, drmp3_uint32 b)
{
    for (;;) {
        if (b == 0) {
            break;
        } else {
            drmp3_uint32 t = a;
            a = b;
            b = t % a;
        }
    }

    return a;
}


static DRMP3_INLINE double drmp3_sin(double x)
{
    /* TODO: Implement custom sin(x). */
    return sin(x);
}

static DRMP3_INLINE double drmp3_exp(double x)
{
    /* TODO: Implement custom exp(x). */
    return exp(x);
}

static DRMP3_INLINE double drmp3_cos(double x)
{
    return drmp3_sin((DRMP3_PI_D*0.5) - x);
}


static void* drmp3__malloc_default(size_t sz, void* pUserData)
{
    (void)pUserData;
    return DRMP3_MALLOC(sz);
}

static void* drmp3__realloc_default(void* p, size_t sz, void* pUserData)
{
    (void)pUserData;
    return DRMP3_REALLOC(p, sz);
}

static void drmp3__free_default(void* p, void* pUserData)
{
    (void)pUserData;
    DRMP3_FREE(p);
}


static void* drmp3__malloc_from_callbacks(size_t sz, const drmp3_allocation_callbacks* pAllocationCallbacks)
{
    if (pAllocationCallbacks == NULL) {
        return NULL;
    }

    if (pAllocationCallbacks->onMalloc != NULL) {
        return pAllocationCallbacks->onMalloc(sz, pAllocationCallbacks->pUserData);
    }

    /* Try using realloc(). */
    if (pAllocationCallbacks->onRealloc != NULL) {
        return pAllocationCallbacks->onRealloc(NULL, sz, pAllocationCallbacks->pUserData);
    }

    return NULL;
}

static void* drmp3__realloc_from_callbacks(void* p, size_t szNew, size_t szOld, const drmp3_allocation_callbacks* pAllocationCallbacks)
{
    if (pAllocationCallbacks == NULL) {
        return NULL;
    }

    if (pAllocationCallbacks->onRealloc != NULL) {
        return pAllocationCallbacks->onRealloc(p, szNew, pAllocationCallbacks->pUserData);
    }

    /* Try emulating realloc() in terms of malloc()/free(). */
    if (pAllocationCallbacks->onMalloc != NULL && pAllocationCallbacks->onFree != NULL) {
        void* p2;

        p2 = pAllocationCallbacks->onMalloc(szNew, pAllocationCallbacks->pUserData);
        if (p2 == NULL) {
            return NULL;
        }

        if (p != NULL) {
            DRMP3_COPY_MEMORY(p2, p, szOld);
            pAllocationCallbacks->onFree(p, pAllocationCallbacks->pUserData);
        }

        return p2;
    }

    return NULL;
}

static void drmp3__free_from_callbacks(void* p, const drmp3_allocation_callbacks* pAllocationCallbacks)
{
    if (p == NULL || pAllocationCallbacks == NULL) {
        return;
    }

    if (pAllocationCallbacks->onFree != NULL) {
        pAllocationCallbacks->onFree(p, pAllocationCallbacks->pUserData);
    }
}


static drmp3_allocation_callbacks drmp3_copy_allocation_callbacks_or_defaults(const drmp3_allocation_callbacks* pAllocationCallbacks)
{
    if (pAllocationCallbacks != NULL) {
        /* Copy. */
        return *pAllocationCallbacks;
    } else {
        /* Defaults. */
        drmp3_allocation_callbacks allocationCallbacks;
        allocationCallbacks.pUserData = NULL;
        allocationCallbacks.onMalloc  = drmp3__malloc_default;
        allocationCallbacks.onRealloc = drmp3__realloc_default;
        allocationCallbacks.onFree    = drmp3__free_default;
        return allocationCallbacks;
    }
}



static size_t drmp3__on_read(drmp3* pMP3, void* pBufferOut, size_t bytesToRead)
{
    size_t bytesRead = pMP3->onRead(pMP3->pUserData, pBufferOut, bytesToRead);
    pMP3->streamCursor += bytesRead;
    return bytesRead;
}

static drmp3_bool32 drmp3__on_seek(drmp3* pMP3, int offset, drmp3_seek_origin origin)
{
    DRMP3_ASSERT(offset >= 0);

    if (!pMP3->onSeek(pMP3->pUserData, offset, origin)) {
        return DRMP3_FALSE;
    }

    if (origin == drmp3_seek_origin_start) {
        pMP3->streamCursor = (drmp3_uint64)offset;
    } else {
        pMP3->streamCursor += offset;
    }

    return DRMP3_TRUE;
}

static drmp3_bool32 drmp3__on_seek_64(drmp3* pMP3, drmp3_uint64 offset, drmp3_seek_origin origin)
{
    if (offset <= 0x7FFFFFFF) {
        return drmp3__on_seek(pMP3, (int)offset, origin);
    }


    /* Getting here "offset" is too large for a 32-bit integer. We just keep seeking forward until we hit the offset. */
    if (!drmp3__on_seek(pMP3, 0x7FFFFFFF, drmp3_seek_origin_start)) {
        return DRMP3_FALSE;
    }

    offset -= 0x7FFFFFFF;
    while (offset > 0) {
        if (offset <= 0x7FFFFFFF) {
            if (!drmp3__on_seek(pMP3, (int)offset, drmp3_seek_origin_current)) {
                return DRMP3_FALSE;
            }
            offset = 0;
        } else {
            if (!drmp3__on_seek(pMP3, 0x7FFFFFFF, drmp3_seek_origin_current)) {
                return DRMP3_FALSE;
            }
            offset -= 0x7FFFFFFF;
        }
    }

    return DRMP3_TRUE;
}


static drmp3_uint32 drmp3_decode_next_frame_ex__callbacks(drmp3* pMP3, drmp3d_sample_t* pPCMFrames)
{
    drmp3_uint32 pcmFramesRead = 0;

    DRMP3_ASSERT(pMP3 != NULL);
    DRMP3_ASSERT(pMP3->onRead != NULL);

    if (pMP3->atEnd) {
        return 0;
    }

    for (;;) {
        drmp3dec_frame_info info;

        /* minimp3 recommends doing data submission in chunks of at least 16K. If we don't have at least 16K bytes available, get more. */
        if (pMP3->dataSize < DRMP3_MIN_DATA_CHUNK_SIZE) {
            size_t bytesRead;

            /* First we need to move the data down. */
            if (pMP3->pData != NULL) {
                memmove(pMP3->pData, pMP3->pData + pMP3->dataConsumed, pMP3->dataSize);
            }

            pMP3->dataConsumed = 0;

            if (pMP3->dataCapacity < DRMP3_DATA_CHUNK_SIZE) {
                drmp3_uint8* pNewData;
                size_t newDataCap;

                newDataCap = DRMP3_DATA_CHUNK_SIZE;

                pNewData = (drmp3_uint8*)drmp3__realloc_from_callbacks(pMP3->pData, newDataCap, pMP3->dataCapacity, &pMP3->allocationCallbacks);
                if (pNewData == NULL) {
                    return 0; /* Out of memory. */
                }

                pMP3->pData = pNewData;
                pMP3->dataCapacity = newDataCap;
            }

            bytesRead = drmp3__on_read(pMP3, pMP3->pData + pMP3->dataSize, (pMP3->dataCapacity - pMP3->dataSize));
            if (bytesRead == 0) {
                if (pMP3->dataSize == 0) {
                    pMP3->atEnd = DRMP3_TRUE;
                    return 0; /* No data. */
                }
            }

            pMP3->dataSize += bytesRead;
        }

        if (pMP3->dataSize > INT_MAX) {
            pMP3->atEnd = DRMP3_TRUE;
            return 0; /* File too big. */
        }

        pcmFramesRead = drmp3dec_decode_frame(&pMP3->decoder, pMP3->pData + pMP3->dataConsumed, (int)pMP3->dataSize, pPCMFrames, &info);    /* <-- Safe size_t -> int conversion thanks to the check above. */

        /* Consume the data. */
        if (info.frame_bytes > 0) {
            pMP3->dataConsumed += (size_t)info.frame_bytes;
            pMP3->dataSize     -= (size_t)info.frame_bytes;
        }

        /* pcmFramesRead will be equal to 0 if decoding failed. If it is zero and info.frame_bytes > 0 then we have successfully decoded the frame. */
        if (pcmFramesRead > 0) {
            pcmFramesRead = drmp3_hdr_frame_samples(pMP3->decoder.header);
            pMP3->pcmFramesConsumedInMP3Frame = 0;
            pMP3->pcmFramesRemainingInMP3Frame = pcmFramesRead;
            pMP3->mp3FrameChannels = info.channels;
            pMP3->mp3FrameSampleRate = info.hz;
            break;
        } else if (info.frame_bytes == 0) {
            /* Need more data. minimp3 recommends doing data submission in 16K chunks. */
            size_t bytesRead;

            /* First we need to move the data down. */
            memmove(pMP3->pData, pMP3->pData + pMP3->dataConsumed, pMP3->dataSize);
            pMP3->dataConsumed = 0;

            if (pMP3->dataCapacity == pMP3->dataSize) {
                /* No room. Expand. */
                drmp3_uint8* pNewData;
                size_t newDataCap;

                newDataCap = pMP3->dataCapacity + DRMP3_DATA_CHUNK_SIZE;

                pNewData = (drmp3_uint8*)drmp3__realloc_from_callbacks(pMP3->pData, newDataCap, pMP3->dataCapacity, &pMP3->allocationCallbacks);
                if (pNewData == NULL) {
                    return 0; /* Out of memory. */
                }

                pMP3->pData = pNewData;
                pMP3->dataCapacity = newDataCap;
            }

            /* Fill in a chunk. */
            bytesRead = drmp3__on_read(pMP3, pMP3->pData + pMP3->dataSize, (pMP3->dataCapacity - pMP3->dataSize));
            if (bytesRead == 0) {
                pMP3->atEnd = DRMP3_TRUE;
                return 0; /* Error reading more data. */
            }

            pMP3->dataSize += bytesRead;
        }
    };

    return pcmFramesRead;
}

static drmp3_uint32 drmp3_decode_next_frame_ex__memory(drmp3* pMP3, drmp3d_sample_t* pPCMFrames)
{
    drmp3_uint32 pcmFramesRead = 0;
    drmp3dec_frame_info info;

    DRMP3_ASSERT(pMP3 != NULL);
    DRMP3_ASSERT(pMP3->memory.pData != NULL);

    if (pMP3->atEnd) {
        return 0;
    }

    pcmFramesRead = drmp3dec_decode_frame(&pMP3->decoder, pMP3->memory.pData + pMP3->memory.currentReadPos, (int)(pMP3->memory.dataSize - pMP3->memory.currentReadPos), pPCMFrames, &info);
    if (pcmFramesRead > 0) {
        pMP3->pcmFramesConsumedInMP3Frame  = 0;
        pMP3->pcmFramesRemainingInMP3Frame = pcmFramesRead;
        pMP3->mp3FrameChannels             = info.channels;
        pMP3->mp3FrameSampleRate           = info.hz;
    }

    /* Consume the data. */
    pMP3->memory.currentReadPos += (size_t)info.frame_bytes;

    return pcmFramesRead;
}

static drmp3_uint32 drmp3_decode_next_frame_ex(drmp3* pMP3, drmp3d_sample_t* pPCMFrames)
{
    if (pMP3->memory.pData != NULL && pMP3->memory.dataSize > 0) {
        return drmp3_decode_next_frame_ex__memory(pMP3, pPCMFrames);
    } else {
        return drmp3_decode_next_frame_ex__callbacks(pMP3, pPCMFrames);
    }
}

static drmp3_uint32 drmp3_decode_next_frame(drmp3* pMP3)
{
    DRMP3_ASSERT(pMP3 != NULL);
    return drmp3_decode_next_frame_ex(pMP3, (drmp3d_sample_t*)pMP3->pcmFrames);
}

#if 0
static drmp3_uint32 drmp3_seek_next_frame(drmp3* pMP3)
{
    drmp3_uint32 pcmFrameCount;

    DRMP3_ASSERT(pMP3 != NULL);

    pcmFrameCount = drmp3_decode_next_frame_ex(pMP3, NULL);
    if (pcmFrameCount == 0) {
        return 0;
    }

    /* We have essentially just skipped past the frame, so just set the remaining samples to 0. */
    pMP3->currentPCMFrame             += pcmFrameCount;
    pMP3->pcmFramesConsumedInMP3Frame  = pcmFrameCount;
    pMP3->pcmFramesRemainingInMP3Frame = 0;

    return pcmFrameCount;
}
#endif

static drmp3_bool32 drmp3_init_internal(drmp3* pMP3, drmp3_read_proc onRead, drmp3_seek_proc onSeek, void* pUserData, const drmp3_allocation_callbacks* pAllocationCallbacks)
{
    DRMP3_ASSERT(pMP3 != NULL);
    DRMP3_ASSERT(onRead != NULL);

    /* This function assumes the output object has already been reset to 0. Do not do that here, otherwise things will break. */
    drmp3dec_init(&pMP3->decoder);

    pMP3->onRead = onRead;
    pMP3->onSeek = onSeek;
    pMP3->pUserData = pUserData;
    pMP3->allocationCallbacks = drmp3_copy_allocation_callbacks_or_defaults(pAllocationCallbacks);

    if (pMP3->allocationCallbacks.onFree == NULL || (pMP3->allocationCallbacks.onMalloc == NULL && pMP3->allocationCallbacks.onRealloc == NULL)) {
        return DRMP3_FALSE;    /* Invalid allocation callbacks. */
    }

    /* Decode the first frame to confirm that it is indeed a valid MP3 stream. */
    if (!drmp3_decode_next_frame(pMP3)) {
        drmp3_uninit(pMP3);
        return DRMP3_FALSE; /* Not a valid MP3 stream. */
    }

    pMP3->channels   = pMP3->mp3FrameChannels;
    pMP3->sampleRate = pMP3->mp3FrameSampleRate;

    return DRMP3_TRUE;
}

DRMP3_API drmp3_bool32 drmp3_init(drmp3* pMP3, drmp3_read_proc onRead, drmp3_seek_proc onSeek, void* pUserData, const drmp3_allocation_callbacks* pAllocationCallbacks)
{
    if (pMP3 == NULL || onRead == NULL) {
        return DRMP3_FALSE;
    }

    DRMP3_ZERO_OBJECT(pMP3);
    return drmp3_init_internal(pMP3, onRead, onSeek, pUserData, pAllocationCallbacks);
}


static size_t drmp3__on_read_memory(void* pUserData, void* pBufferOut, size_t bytesToRead)
{
    drmp3* pMP3 = (drmp3*)pUserData;
    size_t bytesRemaining;

    DRMP3_ASSERT(pMP3 != NULL);
    DRMP3_ASSERT(pMP3->memory.dataSize >= pMP3->memory.currentReadPos);

    bytesRemaining = pMP3->memory.dataSize - pMP3->memory.currentReadPos;
    if (bytesToRead > bytesRemaining) {
        bytesToRead = bytesRemaining;
    }

    if (bytesToRead > 0) {
        DRMP3_COPY_MEMORY(pBufferOut, pMP3->memory.pData + pMP3->memory.currentReadPos, bytesToRead);
        pMP3->memory.currentReadPos += bytesToRead;
    }

    return bytesToRead;
}

static drmp3_bool32 drmp3__on_seek_memory(void* pUserData, int byteOffset, drmp3_seek_origin origin)
{
    drmp3* pMP3 = (drmp3*)pUserData;

    DRMP3_ASSERT(pMP3 != NULL);

    if (origin == drmp3_seek_origin_current) {
        if (byteOffset > 0) {
            if (pMP3->memory.currentReadPos + byteOffset > pMP3->memory.dataSize) {
                byteOffset = (int)(pMP3->memory.dataSize - pMP3->memory.currentReadPos);  /* Trying to seek too far forward. */
            }
        } else {
            if (pMP3->memory.currentReadPos < (size_t)-byteOffset) {
                byteOffset = -(int)pMP3->memory.currentReadPos;  /* Trying to seek too far backwards. */
            }
        }

        /* This will never underflow thanks to the clamps above. */
        pMP3->memory.currentReadPos += byteOffset;
    } else {
        if ((drmp3_uint32)byteOffset <= pMP3->memory.dataSize) {
            pMP3->memory.currentReadPos = byteOffset;
        } else {
            pMP3->memory.currentReadPos = pMP3->memory.dataSize;  /* Trying to seek too far forward. */
        }
    }

    return DRMP3_TRUE;
}

DRMP3_API drmp3_bool32 drmp3_init_memory(drmp3* pMP3, const void* pData, size_t dataSize, const drmp3_allocation_callbacks* pAllocationCallbacks)
{
    if (pMP3 == NULL) {
        return DRMP3_FALSE;
    }

    DRMP3_ZERO_OBJECT(pMP3);

    if (pData == NULL || dataSize == 0) {
        return DRMP3_FALSE;
    }

    pMP3->memory.pData = (const drmp3_uint8*)pData;
    pMP3->memory.dataSize = dataSize;
    pMP3->memory.currentReadPos = 0;

    return drmp3_init_internal(pMP3, drmp3__on_read_memory, drmp3__on_seek_memory, pMP3, pAllocationCallbacks);
}


#ifndef DR_MP3_NO_STDIO
#include <stdio.h>
#include <wchar.h>      /* For wcslen(), wcsrtombs() */

/* drmp3_result_from_errno() is only used inside DR_MP3_NO_STDIO for now. Move this out if it's ever used elsewhere. */
#include <errno.h>
static drmp3_result drmp3_result_from_errno(int e)
{
    switch (e)
    {
        case 0: return DRMP3_SUCCESS;
    #ifdef EPERM
        case EPERM: return DRMP3_INVALID_OPERATION;
    #endif
    #ifdef ENOENT
        case ENOENT: return DRMP3_DOES_NOT_EXIST;
    #endif
    #ifdef ESRCH
        case ESRCH: return DRMP3_DOES_NOT_EXIST;
    #endif
    #ifdef EINTR
        case EINTR: return DRMP3_INTERRUPT;
    #endif
    #ifdef EIO
        case EIO: return DRMP3_IO_ERROR;
    #endif
    #ifdef ENXIO
        case ENXIO: return DRMP3_DOES_NOT_EXIST;
    #endif
    #ifdef E2BIG
        case E2BIG: return DRMP3_INVALID_ARGS;
    #endif
    #ifdef ENOEXEC
        case ENOEXEC: return DRMP3_INVALID_FILE;
    #endif
    #ifdef EBADF
        case EBADF: return DRMP3_INVALID_FILE;
    #endif
    #ifdef ECHILD
        case ECHILD: return DRMP3_ERROR;
    #endif
    #ifdef EAGAIN
        case EAGAIN: return DRMP3_UNAVAILABLE;
    #endif
    #ifdef ENOMEM
        case ENOMEM: return DRMP3_OUT_OF_MEMORY;
    #endif
    #ifdef EACCES
        case EACCES: return DRMP3_ACCESS_DENIED;
    #endif
    #ifdef EFAULT
        case EFAULT: return DRMP3_BAD_ADDRESS;
    #endif
    #ifdef ENOTBLK
        case ENOTBLK: return DRMP3_ERROR;
    #endif
    #ifdef EBUSY
        case EBUSY: return DRMP3_BUSY;
    #endif
    #ifdef EEXIST
        case EEXIST: return DRMP3_ALREADY_EXISTS;
    #endif
    #ifdef EXDEV
        case EXDEV: return DRMP3_ERROR;
    #endif
    #ifdef ENODEV
        case ENODEV: return DRMP3_DOES_NOT_EXIST;
    #endif
    #ifdef ENOTDIR
        case ENOTDIR: return DRMP3_NOT_DIRECTORY;
    #endif
    #ifdef EISDIR
        case EISDIR: return DRMP3_IS_DIRECTORY;
    #endif
    #ifdef EINVAL
        case EINVAL: return DRMP3_INVALID_ARGS;
    #endif
    #ifdef ENFILE
        case ENFILE: return DRMP3_TOO_MANY_OPEN_FILES;
    #endif
    #ifdef EMFILE
        case EMFILE: return DRMP3_TOO_MANY_OPEN_FILES;
    #endif
    #ifdef ENOTTY
        case ENOTTY: return DRMP3_INVALID_OPERATION;
    #endif
    #ifdef ETXTBSY
        case ETXTBSY: return DRMP3_BUSY;
    #endif
    #ifdef EFBIG
        case EFBIG: return DRMP3_TOO_BIG;
    #endif
    #ifdef ENOSPC
        case ENOSPC: return DRMP3_NO_SPACE;
    #endif
    #ifdef ESPIPE
        case ESPIPE: return DRMP3_BAD_SEEK;
    #endif
    #ifdef EROFS
        case EROFS: return DRMP3_ACCESS_DENIED;
    #endif
    #ifdef EMLINK
        case EMLINK: return DRMP3_TOO_MANY_LINKS;
    #endif
    #ifdef EPIPE
        case EPIPE: return DRMP3_BAD_PIPE;
    #endif
    #ifdef EDOM
        case EDOM: return DRMP3_OUT_OF_RANGE;
    #endif
    #ifdef ERANGE
        case ERANGE: return DRMP3_OUT_OF_RANGE;
    #endif
    #ifdef EDEADLK
        case EDEADLK: return DRMP3_DEADLOCK;
    #endif
    #ifdef ENAMETOOLONG
        case ENAMETOOLONG: return DRMP3_PATH_TOO_LONG;
    #endif
    #ifdef ENOLCK
        case ENOLCK: return DRMP3_ERROR;
    #endif
    #ifdef ENOSYS
        case ENOSYS: return DRMP3_NOT_IMPLEMENTED;
    #endif
    #ifdef ENOTEMPTY
        case ENOTEMPTY: return DRMP3_DIRECTORY_NOT_EMPTY;
    #endif
    #ifdef ELOOP
        case ELOOP: return DRMP3_TOO_MANY_LINKS;
    #endif
    #ifdef ENOMSG
        case ENOMSG: return DRMP3_NO_MESSAGE;
    #endif
    #ifdef EIDRM
        case EIDRM: return DRMP3_ERROR;
    #endif
    #ifdef ECHRNG
        case ECHRNG: return DRMP3_ERROR;
    #endif
    #ifdef EL2NSYNC
        case EL2NSYNC: return DRMP3_ERROR;
    #endif
    #ifdef EL3HLT
        case EL3HLT: return DRMP3_ERROR;
    #endif
    #ifdef EL3RST
        case EL3RST: return DRMP3_ERROR;
    #endif
    #ifdef ELNRNG
        case ELNRNG: return DRMP3_OUT_OF_RANGE;
    #endif
    #ifdef EUNATCH
        case EUNATCH: return DRMP3_ERROR;
    #endif
    #ifdef ENOCSI
        case ENOCSI: return DRMP3_ERROR;
    #endif
    #ifdef EL2HLT
        case EL2HLT: return DRMP3_ERROR;
    #endif
    #ifdef EBADE
        case EBADE: return DRMP3_ERROR;
    #endif
    #ifdef EBADR
        case EBADR: return DRMP3_ERROR;
    #endif
    #ifdef EXFULL
        case EXFULL: return DRMP3_ERROR;
    #endif
    #ifdef ENOANO
        case ENOANO: return DRMP3_ERROR;
    #endif
    #ifdef EBADRQC
        case EBADRQC: return DRMP3_ERROR;
    #endif
    #ifdef EBADSLT
        case EBADSLT: return DRMP3_ERROR;
    #endif
    #ifdef EBFONT
        case EBFONT: return DRMP3_INVALID_FILE;
    #endif
    #ifdef ENOSTR
        case ENOSTR: return DRMP3_ERROR;
    #endif
    #ifdef ENODATA
        case ENODATA: return DRMP3_NO_DATA_AVAILABLE;
    #endif
    #ifdef ETIME
        case ETIME: return DRMP3_TIMEOUT;
    #endif
    #ifdef ENOSR
        case ENOSR: return DRMP3_NO_DATA_AVAILABLE;
    #endif
    #ifdef ENONET
        case ENONET: return DRMP3_NO_NETWORK;
    #endif
    #ifdef ENOPKG
        case ENOPKG: return DRMP3_ERROR;
    #endif
    #ifdef EREMOTE
        case EREMOTE: return DRMP3_ERROR;
    #endif
    #ifdef ENOLINK
        case ENOLINK: return DRMP3_ERROR;
    #endif
    #ifdef EADV
        case EADV: return DRMP3_ERROR;
    #endif
    #ifdef ESRMNT
        case ESRMNT: return DRMP3_ERROR;
    #endif
    #ifdef ECOMM
        case ECOMM: return DRMP3_ERROR;
    #endif
    #ifdef EPROTO
        case EPROTO: return DRMP3_ERROR;
    #endif
    #ifdef EMULTIHOP
        case EMULTIHOP: return DRMP3_ERROR;
    #endif
    #ifdef EDOTDOT
        case EDOTDOT: return DRMP3_ERROR;
    #endif
    #ifdef EBADMSG
        case EBADMSG: return DRMP3_BAD_MESSAGE;
    #endif
    #ifdef EOVERFLOW
        case EOVERFLOW: return DRMP3_TOO_BIG;
    #endif
    #ifdef ENOTUNIQ
        case ENOTUNIQ: return DRMP3_NOT_UNIQUE;
    #endif
    #ifdef EBADFD
        case EBADFD: return DRMP3_ERROR;
    #endif
    #ifdef EREMCHG
        case EREMCHG: return DRMP3_ERROR;
    #endif
    #ifdef ELIBACC
        case ELIBACC: return DRMP3_ACCESS_DENIED;
    #endif
    #ifdef ELIBBAD
        case ELIBBAD: return DRMP3_INVALID_FILE;
    #endif
    #ifdef ELIBSCN
        case ELIBSCN: return DRMP3_INVALID_FILE;
    #endif
    #ifdef ELIBMAX
        case ELIBMAX: return DRMP3_ERROR;
    #endif
    #ifdef ELIBEXEC
        case ELIBEXEC: return DRMP3_ERROR;
    #endif
    #ifdef EILSEQ
        case EILSEQ: return DRMP3_INVALID_DATA;
    #endif
    #ifdef ERESTART
        case ERESTART: return DRMP3_ERROR;
    #endif
    #ifdef ESTRPIPE
        case ESTRPIPE: return DRMP3_ERROR;
    #endif
    #ifdef EUSERS
        case EUSERS: return DRMP3_ERROR;
    #endif
    #ifdef ENOTSOCK
        case ENOTSOCK: return DRMP3_NOT_SOCKET;
    #endif
    #ifdef EDESTADDRREQ
        case EDESTADDRREQ: return DRMP3_NO_ADDRESS;
    #endif
    #ifdef EMSGSIZE
        case EMSGSIZE: return DRMP3_TOO_BIG;
    #endif
    #ifdef EPROTOTYPE
        case EPROTOTYPE: return DRMP3_BAD_PROTOCOL;
    #endif
    #ifdef ENOPROTOOPT
        case ENOPROTOOPT: return DRMP3_PROTOCOL_UNAVAILABLE;
    #endif
    #ifdef EPROTONOSUPPORT
        case EPROTONOSUPPORT: return DRMP3_PROTOCOL_NOT_SUPPORTED;
    #endif
    #ifdef ESOCKTNOSUPPORT
        case ESOCKTNOSUPPORT: return DRMP3_SOCKET_NOT_SUPPORTED;
    #endif
    #ifdef EOPNOTSUPP
        case EOPNOTSUPP: return DRMP3_INVALID_OPERATION;
    #endif
    #ifdef EPFNOSUPPORT
        case EPFNOSUPPORT: return DRMP3_PROTOCOL_FAMILY_NOT_SUPPORTED;
    #endif
    #ifdef EAFNOSUPPORT
        case EAFNOSUPPORT: return DRMP3_ADDRESS_FAMILY_NOT_SUPPORTED;
    #endif
    #ifdef EADDRINUSE
        case EADDRINUSE: return DRMP3_ALREADY_IN_USE;
    #endif
    #ifdef EADDRNOTAVAIL
        case EADDRNOTAVAIL: return DRMP3_ERROR;
    #endif
    #ifdef ENETDOWN
        case ENETDOWN: return DRMP3_NO_NETWORK;
    #endif
    #ifdef ENETUNREACH
        case ENETUNREACH: return DRMP3_NO_NETWORK;
    #endif
    #ifdef ENETRESET
        case ENETRESET: return DRMP3_NO_NETWORK;
    #endif
    #ifdef ECONNABORTED
        case ECONNABORTED: return DRMP3_NO_NETWORK;
    #endif
    #ifdef ECONNRESET
        case ECONNRESET: return DRMP3_CONNECTION_RESET;
    #endif
    #ifdef ENOBUFS
        case ENOBUFS: return DRMP3_NO_SPACE;
    #endif
    #ifdef EISCONN
        case EISCONN: return DRMP3_ALREADY_CONNECTED;
    #endif
    #ifdef ENOTCONN
        case ENOTCONN: return DRMP3_NOT_CONNECTED;
    #endif
    #ifdef ESHUTDOWN
        case ESHUTDOWN: return DRMP3_ERROR;
    #endif
    #ifdef ETOOMANYREFS
        case ETOOMANYREFS: return DRMP3_ERROR;
    #endif
    #ifdef ETIMEDOUT
        case ETIMEDOUT: return DRMP3_TIMEOUT;
    #endif
    #ifdef ECONNREFUSED
        case ECONNREFUSED: return DRMP3_CONNECTION_REFUSED;
    #endif
    #ifdef EHOSTDOWN
        case EHOSTDOWN: return DRMP3_NO_HOST;
    #endif
    #ifdef EHOSTUNREACH
        case EHOSTUNREACH: return DRMP3_NO_HOST;
    #endif
    #ifdef EALREADY
        case EALREADY: return DRMP3_IN_PROGRESS;
    #endif
    #ifdef EINPROGRESS
        case EINPROGRESS: return DRMP3_IN_PROGRESS;
    #endif
    #ifdef ESTALE
        case ESTALE: return DRMP3_INVALID_FILE;
    #endif
    #ifdef EUCLEAN
        case EUCLEAN: return DRMP3_ERROR;
    #endif
    #ifdef ENOTNAM
        case ENOTNAM: return DRMP3_ERROR;
    #endif
    #ifdef ENAVAIL
        case ENAVAIL: return DRMP3_ERROR;
    #endif
    #ifdef EISNAM
        case EISNAM: return DRMP3_ERROR;
    #endif
    #ifdef EREMOTEIO
        case EREMOTEIO: return DRMP3_IO_ERROR;
    #endif
    #ifdef EDQUOT
        case EDQUOT: return DRMP3_NO_SPACE;
    #endif
    #ifdef ENOMEDIUM
        case ENOMEDIUM: return DRMP3_DOES_NOT_EXIST;
    #endif
    #ifdef EMEDIUMTYPE
        case EMEDIUMTYPE: return DRMP3_ERROR;
    #endif
    #ifdef ECANCELED
        case ECANCELED: return DRMP3_CANCELLED;
    #endif
    #ifdef ENOKEY
        case ENOKEY: return DRMP3_ERROR;
    #endif
    #ifdef EKEYEXPIRED
        case EKEYEXPIRED: return DRMP3_ERROR;
    #endif
    #ifdef EKEYREVOKED
        case EKEYREVOKED: return DRMP3_ERROR;
    #endif
    #ifdef EKEYREJECTED
        case EKEYREJECTED: return DRMP3_ERROR;
    #endif
    #ifdef EOWNERDEAD
        case EOWNERDEAD: return DRMP3_ERROR;
    #endif
    #ifdef ENOTRECOVERABLE
        case ENOTRECOVERABLE: return DRMP3_ERROR;
    #endif
    #ifdef ERFKILL
        case ERFKILL: return DRMP3_ERROR;
    #endif
    #ifdef EHWPOISON
        case EHWPOISON: return DRMP3_ERROR;
    #endif
        default: return DRMP3_ERROR;
    }
}

static drmp3_result drmp3_fopen(FILE** ppFile, const char* pFilePath, const char* pOpenMode)
{
#if _MSC_VER && _MSC_VER >= 1400
    errno_t err;
#endif

    if (ppFile != NULL) {
        *ppFile = NULL;  /* Safety. */
    }

    if (pFilePath == NULL || pOpenMode == NULL || ppFile == NULL) {
        return DRMP3_INVALID_ARGS;
    }

#if _MSC_VER && _MSC_VER >= 1400
    err = fopen_s(ppFile, pFilePath, pOpenMode);
    if (err != 0) {
        return drmp3_result_from_errno(err);
    }
#else
#if defined(_WIN32) || defined(__APPLE__)
    *ppFile = fopen(pFilePath, pOpenMode);
#else
    #if defined(_FILE_OFFSET_BITS) && _FILE_OFFSET_BITS == 64 && defined(_LARGEFILE64_SOURCE)
        *ppFile = fopen64(pFilePath, pOpenMode);
    #else
        *ppFile = fopen(pFilePath, pOpenMode);
    #endif
#endif
    if (*ppFile == NULL) {
        drmp3_result result = drmp3_result_from_errno(errno);
        if (result == DRMP3_SUCCESS) {
            result = DRMP3_ERROR;   /* Just a safety check to make sure we never ever return success when pFile == NULL. */
        }

        return result;
    }
#endif

    return DRMP3_SUCCESS;
}

/*
_wfopen() isn't always available in all compilation environments.

    * Windows only.
    * MSVC seems to support it universally as far back as VC6 from what I can tell (haven't checked further back).
    * MinGW-64 (both 32- and 64-bit) seems to support it.
    * MinGW wraps it in !defined(__STRICT_ANSI__).

This can be reviewed as compatibility issues arise. The preference is to use _wfopen_s() and _wfopen() as opposed to the wcsrtombs()
fallback, so if you notice your compiler not detecting this properly I'm happy to look at adding support.
*/
#if defined(_WIN32)
    #if defined(_MSC_VER) || defined(__MINGW64__) || !defined(__STRICT_ANSI__)
        #define DRMP3_HAS_WFOPEN
    #endif
#endif

static drmp3_result drmp3_wfopen(FILE** ppFile, const wchar_t* pFilePath, const wchar_t* pOpenMode, const drmp3_allocation_callbacks* pAllocationCallbacks)
{
    if (ppFile != NULL) {
        *ppFile = NULL;  /* Safety. */
    }

    if (pFilePath == NULL || pOpenMode == NULL || ppFile == NULL) {
        return DRMP3_INVALID_ARGS;
    }

#if defined(DRMP3_HAS_WFOPEN)
    {
        /* Use _wfopen() on Windows. */
    #if defined(_MSC_VER) && _MSC_VER >= 1400
        errno_t err = _wfopen_s(ppFile, pFilePath, pOpenMode);
        if (err != 0) {
            return drmp3_result_from_errno(err);
        }
    #else
        *ppFile = _wfopen(pFilePath, pOpenMode);
        if (*ppFile == NULL) {
            return drmp3_result_from_errno(errno);
        }
    #endif
        (void)pAllocationCallbacks;
    }
#else
    /*
    Use fopen() on anything other than Windows. Requires a conversion. This is annoying because fopen() is locale specific. The only real way I can
    think of to do this is with wcsrtombs(). Note that wcstombs() is apparently not thread-safe because it uses a static global mbstate_t object for
    maintaining state. I've checked this with -std=c89 and it works, but if somebody get's a compiler error I'll look into improving compatibility.
    */
    {
        mbstate_t mbs;
        size_t lenMB;
        const wchar_t* pFilePathTemp = pFilePath;
        char* pFilePathMB = NULL;
        char pOpenModeMB[32] = {0};

        /* Get the length first. */
        DRMP3_ZERO_OBJECT(&mbs);
        lenMB = wcsrtombs(NULL, &pFilePathTemp, 0, &mbs);
        if (lenMB == (size_t)-1) {
            return drmp3_result_from_errno(errno);
        }

        pFilePathMB = (char*)drmp3__malloc_from_callbacks(lenMB + 1, pAllocationCallbacks);
        if (pFilePathMB == NULL) {
            return DRMP3_OUT_OF_MEMORY;
        }

        pFilePathTemp = pFilePath;
        DRMP3_ZERO_OBJECT(&mbs);
        wcsrtombs(pFilePathMB, &pFilePathTemp, lenMB + 1, &mbs);

        /* The open mode should always consist of ASCII characters so we should be able to do a trivial conversion. */
        {
            size_t i = 0;
            for (;;) {
                if (pOpenMode[i] == 0) {
                    pOpenModeMB[i] = '\0';
                    break;
                }

                pOpenModeMB[i] = (char)pOpenMode[i];
                i += 1;
            }
        }

        *ppFile = fopen(pFilePathMB, pOpenModeMB);

        drmp3__free_from_callbacks(pFilePathMB, pAllocationCallbacks);
    }

    if (*ppFile == NULL) {
        return DRMP3_ERROR;
    }
#endif

    return DRMP3_SUCCESS;
}



static size_t drmp3__on_read_stdio(void* pUserData, void* pBufferOut, size_t bytesToRead)
{
    return fread(pBufferOut, 1, bytesToRead, (FILE*)pUserData);
}

static drmp3_bool32 drmp3__on_seek_stdio(void* pUserData, int offset, drmp3_seek_origin origin)
{
    return fseek((FILE*)pUserData, offset, (origin == drmp3_seek_origin_current) ? SEEK_CUR : SEEK_SET) == 0;
}

DRMP3_API drmp3_bool32 drmp3_init_file(drmp3* pMP3, const char* pFilePath, const drmp3_allocation_callbacks* pAllocationCallbacks)
{
    FILE* pFile;
    if (drmp3_fopen(&pFile, pFilePath, "rb") != DRMP3_SUCCESS) {
        return DRMP3_FALSE;
    }

    return drmp3_init(pMP3, drmp3__on_read_stdio, drmp3__on_seek_stdio, (void*)pFile, pAllocationCallbacks);
}

DRMP3_API drmp3_bool32 drmp3_init_file_w(drmp3* pMP3, const wchar_t* pFilePath, const drmp3_allocation_callbacks* pAllocationCallbacks)
{
    FILE* pFile;
    if (drmp3_wfopen(&pFile, pFilePath, L"rb", pAllocationCallbacks) != DRMP3_SUCCESS) {
        return DRMP3_FALSE;
    }

    return drmp3_init(pMP3, drmp3__on_read_stdio, drmp3__on_seek_stdio, (void*)pFile, pAllocationCallbacks);
}
#endif

DRMP3_API void drmp3_uninit(drmp3* pMP3)
{
    if (pMP3 == NULL) {
        return;
    }
    
#ifndef DR_MP3_NO_STDIO
    if (pMP3->onRead == drmp3__on_read_stdio) {
        fclose((FILE*)pMP3->pUserData);
    }
#endif

    drmp3__free_from_callbacks(pMP3->pData, &pMP3->allocationCallbacks);
}

#if defined(DR_MP3_FLOAT_OUTPUT)
static void drmp3_f32_to_s16(drmp3_int16* dst, const float* src, drmp3_uint64 sampleCount)
{
    drmp3_uint64 i;
    drmp3_uint64 i4;
    drmp3_uint64 sampleCount4;

    /* Unrolled. */
    i = 0;
    sampleCount4 = sampleCount >> 2;
    for (i4 = 0; i4 < sampleCount4; i4 += 1) {
        float x0 = src[i+0];
        float x1 = src[i+1];
        float x2 = src[i+2];
        float x3 = src[i+3];

        x0 = ((x0 < -1) ? -1 : ((x0 > 1) ? 1 : x0));
        x1 = ((x1 < -1) ? -1 : ((x1 > 1) ? 1 : x1));
        x2 = ((x2 < -1) ? -1 : ((x2 > 1) ? 1 : x2));
        x3 = ((x3 < -1) ? -1 : ((x3 > 1) ? 1 : x3));

        x0 = x0 * 32767.0f;
        x1 = x1 * 32767.0f;
        x2 = x2 * 32767.0f;
        x3 = x3 * 32767.0f;

        dst[i+0] = (drmp3_int16)x0;
        dst[i+1] = (drmp3_int16)x1;
        dst[i+2] = (drmp3_int16)x2;
        dst[i+3] = (drmp3_int16)x3;

        i += 4;
    }

    /* Leftover. */
    for (; i < sampleCount; i += 1) {
        float x = src[i];
        x = ((x < -1) ? -1 : ((x > 1) ? 1 : x));    /* clip */
        x = x * 32767.0f;                           /* -1..1 to -32767..32767 */

        dst[i] = (drmp3_int16)x;
    }
}
#endif

#if !defined(DR_MP3_FLOAT_OUTPUT)
static void drmp3_s16_to_f32(float* dst, const drmp3_int16* src, drmp3_uint64 sampleCount)
{
    drmp3_uint64 i;
    for (i = 0; i < sampleCount; i += 1) {
        float x = (float)src[i];
        x = x * 0.000030517578125f;         /* -32768..32767 to -1..0.999969482421875 */
        dst[i] = x;
    }
}
#endif


static drmp3_uint64 drmp3_read_pcm_frames_raw(drmp3* pMP3, drmp3_uint64 framesToRead, void* pBufferOut)
{
    drmp3_uint64 totalFramesRead = 0;

    DRMP3_ASSERT(pMP3 != NULL);
    DRMP3_ASSERT(pMP3->onRead != NULL);

    while (framesToRead > 0) {
        drmp3_uint32 framesToConsume = (drmp3_uint32)DRMP3_MIN(pMP3->pcmFramesRemainingInMP3Frame, framesToRead);
        if (pBufferOut != NULL) {
        #if defined(DR_MP3_FLOAT_OUTPUT)
            /* f32 */
            float* pFramesOutF32 = (float*)DRMP3_OFFSET_PTR(pBufferOut,          sizeof(float) * totalFramesRead                   * pMP3->channels);
            float* pFramesInF32  = (float*)DRMP3_OFFSET_PTR(&pMP3->pcmFrames[0], sizeof(float) * pMP3->pcmFramesConsumedInMP3Frame * pMP3->mp3FrameChannels);
            DRMP3_COPY_MEMORY(pFramesOutF32, pFramesInF32, sizeof(float) * framesToConsume * pMP3->channels);
        #else
            /* s16 */
            drmp3_int16* pFramesOutS16 = (drmp3_int16*)DRMP3_OFFSET_PTR(pBufferOut,          sizeof(drmp3_int16) * totalFramesRead                   * pMP3->channels);
            drmp3_int16* pFramesInS16  = (drmp3_int16*)DRMP3_OFFSET_PTR(&pMP3->pcmFrames[0], sizeof(drmp3_int16) * pMP3->pcmFramesConsumedInMP3Frame * pMP3->mp3FrameChannels);
            DRMP3_COPY_MEMORY(pFramesOutS16, pFramesInS16, sizeof(drmp3_int16) * framesToConsume * pMP3->channels);
        #endif
        }

        pMP3->currentPCMFrame              += framesToConsume;
        pMP3->pcmFramesConsumedInMP3Frame  += framesToConsume;
        pMP3->pcmFramesRemainingInMP3Frame -= framesToConsume;
        totalFramesRead                    += framesToConsume;
        framesToRead                       -= framesToConsume;

        if (framesToRead == 0) {
            break;
        }

        DRMP3_ASSERT(pMP3->pcmFramesRemainingInMP3Frame == 0);

        /*
        At this point we have exhausted our in-memory buffer so we need to re-fill. Note that the sample rate may have changed
        at this point which means we'll also need to update our sample rate conversion pipeline.
        */
        if (drmp3_decode_next_frame(pMP3) == 0) {
            break;
        }
    }

    return totalFramesRead;
}


DRMP3_API drmp3_uint64 drmp3_read_pcm_frames_f32(drmp3* pMP3, drmp3_uint64 framesToRead, float* pBufferOut)
{
    if (pMP3 == NULL || pMP3->onRead == NULL) {
        return 0;
    }

#if defined(DR_MP3_FLOAT_OUTPUT)
    /* Fast path. No conversion required. */
    return drmp3_read_pcm_frames_raw(pMP3, framesToRead, pBufferOut);
#else
    /* Slow path. Convert from s16 to f32. */
    {
        drmp3_int16 pTempS16[8192];
        drmp3_uint64 totalPCMFramesRead = 0;

        while (totalPCMFramesRead < framesToRead) {
            drmp3_uint64 framesJustRead;
            drmp3_uint64 framesRemaining = framesToRead - totalPCMFramesRead;
            drmp3_uint64 framesToReadNow = DRMP3_COUNTOF(pTempS16) / pMP3->channels;
            if (framesToReadNow > framesRemaining) {
                framesToReadNow = framesRemaining;
            }

            framesJustRead = drmp3_read_pcm_frames_raw(pMP3, framesToReadNow, pTempS16);
            if (framesJustRead == 0) {
                break;
            }

            drmp3_s16_to_f32((float*)DRMP3_OFFSET_PTR(pBufferOut, sizeof(float) * totalPCMFramesRead * pMP3->channels), pTempS16, framesJustRead * pMP3->channels);
            totalPCMFramesRead += framesJustRead;
        }

        return totalPCMFramesRead;
    }
#endif
}

DRMP3_API drmp3_uint64 drmp3_read_pcm_frames_s16(drmp3* pMP3, drmp3_uint64 framesToRead, drmp3_int16* pBufferOut)
{
    if (pMP3 == NULL || pMP3->onRead == NULL) {
        return 0;
    }

#if !defined(DR_MP3_FLOAT_OUTPUT)
    /* Fast path. No conversion required. */
    return drmp3_read_pcm_frames_raw(pMP3, framesToRead, pBufferOut);
#else
    /* Slow path. Convert from f32 to s16. */
    {
        float pTempF32[4096];
        drmp3_uint64 totalPCMFramesRead = 0;

        while (totalPCMFramesRead < framesToRead) {
            drmp3_uint64 framesJustRead;
            drmp3_uint64 framesRemaining = framesToRead - totalPCMFramesRead;
            drmp3_uint64 framesToReadNow = DRMP3_COUNTOF(pTempF32) / pMP3->channels;
            if (framesToReadNow > framesRemaining) {
                framesToReadNow = framesRemaining;
            }

            framesJustRead = drmp3_read_pcm_frames_raw(pMP3, framesToReadNow, pTempF32);
            if (framesJustRead == 0) {
                break;
            }

            drmp3_f32_to_s16((drmp3_int16*)DRMP3_OFFSET_PTR(pBufferOut, sizeof(drmp3_int16) * totalPCMFramesRead * pMP3->channels), pTempF32, framesJustRead * pMP3->channels);
            totalPCMFramesRead += framesJustRead;
        }

        return totalPCMFramesRead;
    }
#endif
}

static void drmp3_reset(drmp3* pMP3)
{
    DRMP3_ASSERT(pMP3 != NULL);

    pMP3->pcmFramesConsumedInMP3Frame = 0;
    pMP3->pcmFramesRemainingInMP3Frame = 0;
    pMP3->currentPCMFrame = 0;
    pMP3->dataSize = 0;
    pMP3->atEnd = DRMP3_FALSE;
    drmp3dec_init(&pMP3->decoder);
}

static drmp3_bool32 drmp3_seek_to_start_of_stream(drmp3* pMP3)
{
    DRMP3_ASSERT(pMP3 != NULL);
    DRMP3_ASSERT(pMP3->onSeek != NULL);

    /* Seek to the start of the stream to begin with. */
    if (!drmp3__on_seek(pMP3, 0, drmp3_seek_origin_start)) {
        return DRMP3_FALSE;
    }

    /* Clear any cached data. */
    drmp3_reset(pMP3);
    return DRMP3_TRUE;
}


static drmp3_bool32 drmp3_seek_forward_by_pcm_frames__brute_force(drmp3* pMP3, drmp3_uint64 frameOffset)
{
    drmp3_uint64 framesRead;

    /*
    Just using a dumb read-and-discard for now. What would be nice is to parse only the header of the MP3 frame, and then skip over leading
    frames without spending the time doing a full decode. I cannot see an easy way to do this in minimp3, however, so it may involve some
    kind of manual processing.
    */
#if defined(DR_MP3_FLOAT_OUTPUT)
    framesRead = drmp3_read_pcm_frames_f32(pMP3, frameOffset, NULL);
#else
    framesRead = drmp3_read_pcm_frames_s16(pMP3, frameOffset, NULL);
#endif
    if (framesRead != frameOffset) {
        return DRMP3_FALSE;
    }

    return DRMP3_TRUE;
}

static drmp3_bool32 drmp3_seek_to_pcm_frame__brute_force(drmp3* pMP3, drmp3_uint64 frameIndex)
{
    DRMP3_ASSERT(pMP3 != NULL);

    if (frameIndex == pMP3->currentPCMFrame) {
        return DRMP3_TRUE;
    }

    /*
    If we're moving foward we just read from where we're at. Otherwise we need to move back to the start of
    the stream and read from the beginning.
    */
    if (frameIndex < pMP3->currentPCMFrame) {
        /* Moving backward. Move to the start of the stream and then move forward. */
        if (!drmp3_seek_to_start_of_stream(pMP3)) {
            return DRMP3_FALSE;
        }
    }

    DRMP3_ASSERT(frameIndex >= pMP3->currentPCMFrame);
    return drmp3_seek_forward_by_pcm_frames__brute_force(pMP3, (frameIndex - pMP3->currentPCMFrame));
}

static drmp3_bool32 drmp3_find_closest_seek_point(drmp3* pMP3, drmp3_uint64 frameIndex, drmp3_uint32* pSeekPointIndex)
{
    drmp3_uint32 iSeekPoint;

    DRMP3_ASSERT(pSeekPointIndex != NULL);

    *pSeekPointIndex = 0;

    if (frameIndex < pMP3->pSeekPoints[0].pcmFrameIndex) {
        return DRMP3_FALSE;
    }

    /* Linear search for simplicity to begin with while I'm getting this thing working. Once it's all working change this to a binary search. */
    for (iSeekPoint = 0; iSeekPoint < pMP3->seekPointCount; ++iSeekPoint) {
        if (pMP3->pSeekPoints[iSeekPoint].pcmFrameIndex > frameIndex) {
            break;  /* Found it. */
        }

        *pSeekPointIndex = iSeekPoint;
    }

    return DRMP3_TRUE;
}

static drmp3_bool32 drmp3_seek_to_pcm_frame__seek_table(drmp3* pMP3, drmp3_uint64 frameIndex)
{
    drmp3_seek_point seekPoint;
    drmp3_uint32 priorSeekPointIndex;
    drmp3_uint16 iMP3Frame;
    drmp3_uint64 leftoverFrames;

    DRMP3_ASSERT(pMP3 != NULL);
    DRMP3_ASSERT(pMP3->pSeekPoints != NULL);
    DRMP3_ASSERT(pMP3->seekPointCount > 0);

    /* If there is no prior seekpoint it means the target PCM frame comes before the first seek point. Just assume a seekpoint at the start of the file in this case. */
    if (drmp3_find_closest_seek_point(pMP3, frameIndex, &priorSeekPointIndex)) {
        seekPoint = pMP3->pSeekPoints[priorSeekPointIndex];
    } else {
        seekPoint.seekPosInBytes     = 0;
        seekPoint.pcmFrameIndex      = 0;
        seekPoint.mp3FramesToDiscard = 0;
        seekPoint.pcmFramesToDiscard = 0;
    }

    /* First thing to do is seek to the first byte of the relevant MP3 frame. */
    if (!drmp3__on_seek_64(pMP3, seekPoint.seekPosInBytes, drmp3_seek_origin_start)) {
        return DRMP3_FALSE; /* Failed to seek. */
    }

    /* Clear any cached data. */
    drmp3_reset(pMP3);

    /* Whole MP3 frames need to be discarded first. */
    for (iMP3Frame = 0; iMP3Frame < seekPoint.mp3FramesToDiscard; ++iMP3Frame) {
        drmp3_uint32 pcmFramesRead;
        drmp3d_sample_t* pPCMFrames;

        /* Pass in non-null for the last frame because we want to ensure the sample rate converter is preloaded correctly. */
        pPCMFrames = NULL;
        if (iMP3Frame == seekPoint.mp3FramesToDiscard-1) {
            pPCMFrames = (drmp3d_sample_t*)pMP3->pcmFrames;
        }

        /* We first need to decode the next frame. */
        pcmFramesRead = drmp3_decode_next_frame_ex(pMP3, pPCMFrames);
        if (pcmFramesRead == 0) {
            return DRMP3_FALSE;
        }
    }

    /* We seeked to an MP3 frame in the raw stream so we need to make sure the current PCM frame is set correctly. */
    pMP3->currentPCMFrame = seekPoint.pcmFrameIndex - seekPoint.pcmFramesToDiscard;

    /*
    Now at this point we can follow the same process as the brute force technique where we just skip over unnecessary MP3 frames and then
    read-and-discard at least 2 whole MP3 frames.
    */
    leftoverFrames = frameIndex - pMP3->currentPCMFrame;
    return drmp3_seek_forward_by_pcm_frames__brute_force(pMP3, leftoverFrames);
}

DRMP3_API drmp3_bool32 drmp3_seek_to_pcm_frame(drmp3* pMP3, drmp3_uint64 frameIndex)
{
    if (pMP3 == NULL || pMP3->onSeek == NULL) {
        return DRMP3_FALSE;
    }

    if (frameIndex == 0) {
        return drmp3_seek_to_start_of_stream(pMP3);
    }

    /* Use the seek table if we have one. */
    if (pMP3->pSeekPoints != NULL && pMP3->seekPointCount > 0) {
        return drmp3_seek_to_pcm_frame__seek_table(pMP3, frameIndex);
    } else {
        return drmp3_seek_to_pcm_frame__brute_force(pMP3, frameIndex);
    }
}

DRMP3_API drmp3_bool32 drmp3_get_mp3_and_pcm_frame_count(drmp3* pMP3, drmp3_uint64* pMP3FrameCount, drmp3_uint64* pPCMFrameCount)
{
    drmp3_uint64 currentPCMFrame;
    drmp3_uint64 totalPCMFrameCount;
    drmp3_uint64 totalMP3FrameCount;

    if (pMP3 == NULL) {
        return DRMP3_FALSE;
    }

    /*
    The way this works is we move back to the start of the stream, iterate over each MP3 frame and calculate the frame count based
    on our output sample rate, the seek back to the PCM frame we were sitting on before calling this function.
    */

    /* The stream must support seeking for this to work. */
    if (pMP3->onSeek == NULL) {
        return DRMP3_FALSE;
    }

    /* We'll need to seek back to where we were, so grab the PCM frame we're currently sitting on so we can restore later. */
    currentPCMFrame = pMP3->currentPCMFrame;
    
    if (!drmp3_seek_to_start_of_stream(pMP3)) {
        return DRMP3_FALSE;
    }

    totalPCMFrameCount = 0;
    totalMP3FrameCount = 0;

    for (;;) {
        drmp3_uint32 pcmFramesInCurrentMP3Frame;

        pcmFramesInCurrentMP3Frame = drmp3_decode_next_frame_ex(pMP3, NULL);
        if (pcmFramesInCurrentMP3Frame == 0) {
            break;
        }

        totalPCMFrameCount += pcmFramesInCurrentMP3Frame;
        totalMP3FrameCount += 1;
    }

    /* Finally, we need to seek back to where we were. */
    if (!drmp3_seek_to_start_of_stream(pMP3)) {
        return DRMP3_FALSE;
    }

    if (!drmp3_seek_to_pcm_frame(pMP3, currentPCMFrame)) {
        return DRMP3_FALSE;
    }

    if (pMP3FrameCount != NULL) {
        *pMP3FrameCount = totalMP3FrameCount;
    }
    if (pPCMFrameCount != NULL) {
        *pPCMFrameCount = totalPCMFrameCount;
    }

    return DRMP3_TRUE;
}

DRMP3_API drmp3_uint64 drmp3_get_pcm_frame_count(drmp3* pMP3)
{
    drmp3_uint64 totalPCMFrameCount;
    if (!drmp3_get_mp3_and_pcm_frame_count(pMP3, NULL, &totalPCMFrameCount)) {
        return 0;
    }

    return totalPCMFrameCount;
}

DRMP3_API drmp3_uint64 drmp3_get_mp3_frame_count(drmp3* pMP3)
{
    drmp3_uint64 totalMP3FrameCount;
    if (!drmp3_get_mp3_and_pcm_frame_count(pMP3, &totalMP3FrameCount, NULL)) {
        return 0;
    }

    return totalMP3FrameCount;
}

static void drmp3__accumulate_running_pcm_frame_count(drmp3* pMP3, drmp3_uint32 pcmFrameCountIn, drmp3_uint64* pRunningPCMFrameCount, float* pRunningPCMFrameCountFractionalPart)
{
    float srcRatio;
    float pcmFrameCountOutF;
    drmp3_uint32 pcmFrameCountOut;

    srcRatio = (float)pMP3->mp3FrameSampleRate / (float)pMP3->sampleRate;
    DRMP3_ASSERT(srcRatio > 0);

    pcmFrameCountOutF = *pRunningPCMFrameCountFractionalPart + (pcmFrameCountIn / srcRatio);
    pcmFrameCountOut  = (drmp3_uint32)pcmFrameCountOutF;
    *pRunningPCMFrameCountFractionalPart = pcmFrameCountOutF - pcmFrameCountOut;
    *pRunningPCMFrameCount += pcmFrameCountOut;
}

typedef struct
{
    drmp3_uint64 bytePos;
    drmp3_uint64 pcmFrameIndex; /* <-- After sample rate conversion. */
} drmp3__seeking_mp3_frame_info;

DRMP3_API drmp3_bool32 drmp3_calculate_seek_points(drmp3* pMP3, drmp3_uint32* pSeekPointCount, drmp3_seek_point* pSeekPoints)
{
    drmp3_uint32 seekPointCount;
    drmp3_uint64 currentPCMFrame;
    drmp3_uint64 totalMP3FrameCount;
    drmp3_uint64 totalPCMFrameCount;

    if (pMP3 == NULL || pSeekPointCount == NULL || pSeekPoints == NULL) {
        return DRMP3_FALSE; /* Invalid args. */
    }

    seekPointCount = *pSeekPointCount;
    if (seekPointCount == 0) {
        return DRMP3_FALSE;  /* The client has requested no seek points. Consider this to be invalid arguments since the client has probably not intended this. */
    }

    /* We'll need to seek back to the current sample after calculating the seekpoints so we need to go ahead and grab the current location at the top. */
    currentPCMFrame = pMP3->currentPCMFrame;
    
    /* We never do more than the total number of MP3 frames and we limit it to 32-bits. */
    if (!drmp3_get_mp3_and_pcm_frame_count(pMP3, &totalMP3FrameCount, &totalPCMFrameCount)) {
        return DRMP3_FALSE;
    }

    /* If there's less than DRMP3_SEEK_LEADING_MP3_FRAMES+1 frames we just report 1 seek point which will be the very start of the stream. */
    if (totalMP3FrameCount < DRMP3_SEEK_LEADING_MP3_FRAMES+1) {
        seekPointCount = 1;
        pSeekPoints[0].seekPosInBytes     = 0;
        pSeekPoints[0].pcmFrameIndex      = 0;
        pSeekPoints[0].mp3FramesToDiscard = 0;
        pSeekPoints[0].pcmFramesToDiscard = 0;
    } else {
        drmp3_uint64 pcmFramesBetweenSeekPoints;
        drmp3__seeking_mp3_frame_info mp3FrameInfo[DRMP3_SEEK_LEADING_MP3_FRAMES+1];
        drmp3_uint64 runningPCMFrameCount = 0;
        float runningPCMFrameCountFractionalPart = 0;
        drmp3_uint64 nextTargetPCMFrame;
        drmp3_uint32 iMP3Frame;
        drmp3_uint32 iSeekPoint;

        if (seekPointCount > totalMP3FrameCount-1) {
            seekPointCount = (drmp3_uint32)totalMP3FrameCount-1;
        }

        pcmFramesBetweenSeekPoints = totalPCMFrameCount / (seekPointCount+1);

        /*
        Here is where we actually calculate the seek points. We need to start by moving the start of the stream. We then enumerate over each
        MP3 frame.
        */
        if (!drmp3_seek_to_start_of_stream(pMP3)) {
            return DRMP3_FALSE;
        }

        /*
        We need to cache the byte positions of the previous MP3 frames. As a new MP3 frame is iterated, we cycle the byte positions in this
        array. The value in the first item in this array is the byte position that will be reported in the next seek point.
        */

        /* We need to initialize the array of MP3 byte positions for the leading MP3 frames. */
        for (iMP3Frame = 0; iMP3Frame < DRMP3_SEEK_LEADING_MP3_FRAMES+1; ++iMP3Frame) {
            drmp3_uint32 pcmFramesInCurrentMP3FrameIn;

            /* The byte position of the next frame will be the stream's cursor position, minus whatever is sitting in the buffer. */
            DRMP3_ASSERT(pMP3->streamCursor >= pMP3->dataSize);
            mp3FrameInfo[iMP3Frame].bytePos       = pMP3->streamCursor - pMP3->dataSize;
            mp3FrameInfo[iMP3Frame].pcmFrameIndex = runningPCMFrameCount;

            /* We need to get information about this frame so we can know how many samples it contained. */
            pcmFramesInCurrentMP3FrameIn = drmp3_decode_next_frame_ex(pMP3, NULL);
            if (pcmFramesInCurrentMP3FrameIn == 0) {
                return DRMP3_FALSE; /* This should never happen. */
            }

            drmp3__accumulate_running_pcm_frame_count(pMP3, pcmFramesInCurrentMP3FrameIn, &runningPCMFrameCount, &runningPCMFrameCountFractionalPart);
        }

        /*
        At this point we will have extracted the byte positions of the leading MP3 frames. We can now start iterating over each seek point and
        calculate them.
        */
        nextTargetPCMFrame = 0;
        for (iSeekPoint = 0; iSeekPoint < seekPointCount; ++iSeekPoint) {
            nextTargetPCMFrame += pcmFramesBetweenSeekPoints;

            for (;;) {
                if (nextTargetPCMFrame < runningPCMFrameCount) {
                    /* The next seek point is in the current MP3 frame. */
                    pSeekPoints[iSeekPoint].seekPosInBytes     = mp3FrameInfo[0].bytePos;
                    pSeekPoints[iSeekPoint].pcmFrameIndex      = nextTargetPCMFrame;
                    pSeekPoints[iSeekPoint].mp3FramesToDiscard = DRMP3_SEEK_LEADING_MP3_FRAMES;
                    pSeekPoints[iSeekPoint].pcmFramesToDiscard = (drmp3_uint16)(nextTargetPCMFrame - mp3FrameInfo[DRMP3_SEEK_LEADING_MP3_FRAMES-1].pcmFrameIndex);
                    break;
                } else {
                    size_t i;
                    drmp3_uint32 pcmFramesInCurrentMP3FrameIn;

                    /*
                    The next seek point is not in the current MP3 frame, so continue on to the next one. The first thing to do is cycle the cached
                    MP3 frame info.
                    */
                    for (i = 0; i < DRMP3_COUNTOF(mp3FrameInfo)-1; ++i) {
                        mp3FrameInfo[i] = mp3FrameInfo[i+1];
                    }

                    /* Cache previous MP3 frame info. */
                    mp3FrameInfo[DRMP3_COUNTOF(mp3FrameInfo)-1].bytePos       = pMP3->streamCursor - pMP3->dataSize;
                    mp3FrameInfo[DRMP3_COUNTOF(mp3FrameInfo)-1].pcmFrameIndex = runningPCMFrameCount;

                    /*
                    Go to the next MP3 frame. This shouldn't ever fail, but just in case it does we just set the seek point and break. If it happens, it
                    should only ever do it for the last seek point.
                    */
                    pcmFramesInCurrentMP3FrameIn = drmp3_decode_next_frame_ex(pMP3, NULL);
                    if (pcmFramesInCurrentMP3FrameIn == 0) {
                        pSeekPoints[iSeekPoint].seekPosInBytes     = mp3FrameInfo[0].bytePos;
                        pSeekPoints[iSeekPoint].pcmFrameIndex      = nextTargetPCMFrame;
                        pSeekPoints[iSeekPoint].mp3FramesToDiscard = DRMP3_SEEK_LEADING_MP3_FRAMES;
                        pSeekPoints[iSeekPoint].pcmFramesToDiscard = (drmp3_uint16)(nextTargetPCMFrame - mp3FrameInfo[DRMP3_SEEK_LEADING_MP3_FRAMES-1].pcmFrameIndex);
                        break;
                    }

                    drmp3__accumulate_running_pcm_frame_count(pMP3, pcmFramesInCurrentMP3FrameIn, &runningPCMFrameCount, &runningPCMFrameCountFractionalPart);
                }
            }
        }

        /* Finally, we need to seek back to where we were. */
        if (!drmp3_seek_to_start_of_stream(pMP3)) {
            return DRMP3_FALSE;
        }
        if (!drmp3_seek_to_pcm_frame(pMP3, currentPCMFrame)) {
            return DRMP3_FALSE;
        }
    }

    *pSeekPointCount = seekPointCount;
    return DRMP3_TRUE;
}

DRMP3_API drmp3_bool32 drmp3_bind_seek_table(drmp3* pMP3, drmp3_uint32 seekPointCount, drmp3_seek_point* pSeekPoints)
{
    if (pMP3 == NULL) {
        return DRMP3_FALSE;
    }

    if (seekPointCount == 0 || pSeekPoints == NULL) {
        /* Unbinding. */
        pMP3->seekPointCount = 0;
        pMP3->pSeekPoints = NULL;
    } else {
        /* Binding. */
        pMP3->seekPointCount = seekPointCount;
        pMP3->pSeekPoints = pSeekPoints;
    }

    return DRMP3_TRUE;
}


static float* drmp3__full_read_and_close_f32(drmp3* pMP3, drmp3_config* pConfig, drmp3_uint64* pTotalFrameCount)
{
    drmp3_uint64 totalFramesRead = 0;
    drmp3_uint64 framesCapacity = 0;
    float* pFrames = NULL;
    float temp[4096];

    DRMP3_ASSERT(pMP3 != NULL);

    for (;;) {
        drmp3_uint64 framesToReadRightNow = DRMP3_COUNTOF(temp) / pMP3->channels;
        drmp3_uint64 framesJustRead = drmp3_read_pcm_frames_f32(pMP3, framesToReadRightNow, temp);
        if (framesJustRead == 0) {
            break;
        }

        /* Reallocate the output buffer if there's not enough room. */
        if (framesCapacity < totalFramesRead + framesJustRead) {
            drmp3_uint64 oldFramesBufferSize;
            drmp3_uint64 newFramesBufferSize;
            drmp3_uint64 newFramesCap;
            float* pNewFrames;

            newFramesCap = framesCapacity * 2;
            if (newFramesCap < totalFramesRead + framesJustRead) {
                newFramesCap = totalFramesRead + framesJustRead;
            }

            oldFramesBufferSize = framesCapacity * pMP3->channels * sizeof(float);
            newFramesBufferSize = newFramesCap   * pMP3->channels * sizeof(float);
            if (newFramesBufferSize > DRMP3_SIZE_MAX) {
                break;
            }

            pNewFrames = (float*)drmp3__realloc_from_callbacks(pFrames, (size_t)newFramesBufferSize, (size_t)oldFramesBufferSize, &pMP3->allocationCallbacks);
            if (pNewFrames == NULL) {
                drmp3__free_from_callbacks(pFrames, &pMP3->allocationCallbacks);
                break;
            }

            pFrames = pNewFrames;
            framesCapacity = newFramesCap;
        }

        DRMP3_COPY_MEMORY(pFrames + totalFramesRead*pMP3->channels, temp, (size_t)(framesJustRead*pMP3->channels*sizeof(float)));
        totalFramesRead += framesJustRead;

        /* If the number of frames we asked for is less that what we actually read it means we've reached the end. */
        if (framesJustRead != framesToReadRightNow) {
            break;
        }
    }

    if (pConfig != NULL) {
        pConfig->channels   = pMP3->channels;
        pConfig->sampleRate = pMP3->sampleRate;
    }

    drmp3_uninit(pMP3);

    if (pTotalFrameCount) {
        *pTotalFrameCount = totalFramesRead;
    }

    return pFrames;
}

static drmp3_int16* drmp3__full_read_and_close_s16(drmp3* pMP3, drmp3_config* pConfig, drmp3_uint64* pTotalFrameCount)
{
    drmp3_uint64 totalFramesRead = 0;
    drmp3_uint64 framesCapacity = 0;
    drmp3_int16* pFrames = NULL;
    drmp3_int16 temp[4096];

    DRMP3_ASSERT(pMP3 != NULL);

    for (;;) {
        drmp3_uint64 framesToReadRightNow = DRMP3_COUNTOF(temp) / pMP3->channels;
        drmp3_uint64 framesJustRead = drmp3_read_pcm_frames_s16(pMP3, framesToReadRightNow, temp);
        if (framesJustRead == 0) {
            break;
        }

        /* Reallocate the output buffer if there's not enough room. */
        if (framesCapacity < totalFramesRead + framesJustRead) {
            drmp3_uint64 newFramesBufferSize;
            drmp3_uint64 oldFramesBufferSize;
            drmp3_uint64 newFramesCap;
            drmp3_int16* pNewFrames;

            newFramesCap = framesCapacity * 2;
            if (newFramesCap < totalFramesRead + framesJustRead) {
                newFramesCap = totalFramesRead + framesJustRead;
            }

            oldFramesBufferSize = framesCapacity * pMP3->channels * sizeof(drmp3_int16);
            newFramesBufferSize = newFramesCap   * pMP3->channels * sizeof(drmp3_int16);
            if (newFramesBufferSize > DRMP3_SIZE_MAX) {
                break;
            }

            pNewFrames = (drmp3_int16*)drmp3__realloc_from_callbacks(pFrames, (size_t)newFramesBufferSize, (size_t)oldFramesBufferSize, &pMP3->allocationCallbacks);
            if (pNewFrames == NULL) {
                drmp3__free_from_callbacks(pFrames, &pMP3->allocationCallbacks);
                break;
            }

            pFrames = pNewFrames;
            framesCapacity = newFramesCap;
        }

        DRMP3_COPY_MEMORY(pFrames + totalFramesRead*pMP3->channels, temp, (size_t)(framesJustRead*pMP3->channels*sizeof(drmp3_int16)));
        totalFramesRead += framesJustRead;

        /* If the number of frames we asked for is less that what we actually read it means we've reached the end. */
        if (framesJustRead != framesToReadRightNow) {
            break;
        }
    }

    if (pConfig != NULL) {
        pConfig->channels   = pMP3->channels;
        pConfig->sampleRate = pMP3->sampleRate;
    }

    drmp3_uninit(pMP3);

    if (pTotalFrameCount) {
        *pTotalFrameCount = totalFramesRead;
    }

    return pFrames;
}


DRMP3_API float* drmp3_open_and_read_pcm_frames_f32(drmp3_read_proc onRead, drmp3_seek_proc onSeek, void* pUserData, drmp3_config* pConfig, drmp3_uint64* pTotalFrameCount, const drmp3_allocation_callbacks* pAllocationCallbacks)
{
    drmp3 mp3;
    if (!drmp3_init(&mp3, onRead, onSeek, pUserData, pAllocationCallbacks)) {
        return NULL;
    }

    return drmp3__full_read_and_close_f32(&mp3, pConfig, pTotalFrameCount);
}

DRMP3_API drmp3_int16* drmp3_open_and_read_pcm_frames_s16(drmp3_read_proc onRead, drmp3_seek_proc onSeek, void* pUserData, drmp3_config* pConfig, drmp3_uint64* pTotalFrameCount, const drmp3_allocation_callbacks* pAllocationCallbacks)
{
    drmp3 mp3;
    if (!drmp3_init(&mp3, onRead, onSeek, pUserData, pAllocationCallbacks)) {
        return NULL;
    }

    return drmp3__full_read_and_close_s16(&mp3, pConfig, pTotalFrameCount);
}


DRMP3_API float* drmp3_open_memory_and_read_pcm_frames_f32(const void* pData, size_t dataSize, drmp3_config* pConfig, drmp3_uint64* pTotalFrameCount, const drmp3_allocation_callbacks* pAllocationCallbacks)
{
    drmp3 mp3;
    if (!drmp3_init_memory(&mp3, pData, dataSize, pAllocationCallbacks)) {
        return NULL;
    }

    return drmp3__full_read_and_close_f32(&mp3, pConfig, pTotalFrameCount);
}

DRMP3_API drmp3_int16* drmp3_open_memory_and_read_pcm_frames_s16(const void* pData, size_t dataSize, drmp3_config* pConfig, drmp3_uint64* pTotalFrameCount, const drmp3_allocation_callbacks* pAllocationCallbacks)
{
    drmp3 mp3;
    if (!drmp3_init_memory(&mp3, pData, dataSize, pAllocationCallbacks)) {
        return NULL;
    }

    return drmp3__full_read_and_close_s16(&mp3, pConfig, pTotalFrameCount);
}


#ifndef DR_MP3_NO_STDIO
DRMP3_API float* drmp3_open_file_and_read_pcm_frames_f32(const char* filePath, drmp3_config* pConfig, drmp3_uint64* pTotalFrameCount, const drmp3_allocation_callbacks* pAllocationCallbacks)
{
    drmp3 mp3;
    if (!drmp3_init_file(&mp3, filePath, pAllocationCallbacks)) {
        return NULL;
    }

    return drmp3__full_read_and_close_f32(&mp3, pConfig, pTotalFrameCount);
}

DRMP3_API drmp3_int16* drmp3_open_file_and_read_pcm_frames_s16(const char* filePath, drmp3_config* pConfig, drmp3_uint64* pTotalFrameCount, const drmp3_allocation_callbacks* pAllocationCallbacks)
{
    drmp3 mp3;
    if (!drmp3_init_file(&mp3, filePath, pAllocationCallbacks)) {
        return NULL;
    }

    return drmp3__full_read_and_close_s16(&mp3, pConfig, pTotalFrameCount);
}
#endif

DRMP3_API void* drmp3_malloc(size_t sz, const drmp3_allocation_callbacks* pAllocationCallbacks)
{
    if (pAllocationCallbacks != NULL) {
        return drmp3__malloc_from_callbacks(sz, pAllocationCallbacks);
    } else {
        return drmp3__malloc_default(sz, NULL);
    }
}

DRMP3_API void drmp3_free(void* p, const drmp3_allocation_callbacks* pAllocationCallbacks)
{
    if (pAllocationCallbacks != NULL) {
        drmp3__free_from_callbacks(p, pAllocationCallbacks);
    } else {
        drmp3__free_default(p, NULL);
    }
}

#endif  /* dr_mp3_c */
#endif  /*DR_MP3_IMPLEMENTATION*/

#ifdef __cplusplus
extern "C" {
#endif

#define DRWAV_STRINGIFY(x)      #x
#define DRWAV_XSTRINGIFY(x)     DRWAV_STRINGIFY(x)

#define DRWAV_VERSION_MAJOR     0
#define DRWAV_VERSION_MINOR     12
#define DRWAV_VERSION_REVISION  8
#define DRWAV_VERSION_STRING    DRWAV_XSTRINGIFY(DRWAV_VERSION_MAJOR) "." DRWAV_XSTRINGIFY(DRWAV_VERSION_MINOR) "." DRWAV_XSTRINGIFY(DRWAV_VERSION_REVISION)

#include <stddef.h> /* For size_t. */

/* Sized types. Prefer built-in types. Fall back to stdint. */
#ifdef _MSC_VER
    #if defined(__clang__)
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wlanguage-extension-token"
        #pragma GCC diagnostic ignored "-Wlong-long"        
        #pragma GCC diagnostic ignored "-Wc++11-long-long"
    #endif
    typedef   signed __int8  drwav_int8;
    typedef unsigned __int8  drwav_uint8;
    typedef   signed __int16 drwav_int16;
    typedef unsigned __int16 drwav_uint16;
    typedef   signed __int32 drwav_int32;
    typedef unsigned __int32 drwav_uint32;
    typedef   signed __int64 drwav_int64;
    typedef unsigned __int64 drwav_uint64;
    #if defined(__clang__)
        #pragma GCC diagnostic pop
    #endif
#else
    #include <stdint.h>
    typedef int8_t           drwav_int8;
    typedef uint8_t          drwav_uint8;
    typedef int16_t          drwav_int16;
    typedef uint16_t         drwav_uint16;
    typedef int32_t          drwav_int32;
    typedef uint32_t         drwav_uint32;
    typedef int64_t          drwav_int64;
    typedef uint64_t         drwav_uint64;
#endif
typedef drwav_uint8          drwav_bool8;
typedef drwav_uint32         drwav_bool32;
#define DRWAV_TRUE           1
#define DRWAV_FALSE          0

#if !defined(DRWAV_API)
    #if defined(DRWAV_DLL)
        #if defined(_WIN32)
            #define DRWAV_DLL_IMPORT  __declspec(dllimport)
            #define DRWAV_DLL_EXPORT  __declspec(dllexport)
            #define DRWAV_DLL_PRIVATE static
        #else
            #if defined(__GNUC__) && __GNUC__ >= 4
                #define DRWAV_DLL_IMPORT  __attribute__((visibility("default")))
                #define DRWAV_DLL_EXPORT  __attribute__((visibility("default")))
                #define DRWAV_DLL_PRIVATE __attribute__((visibility("hidden")))
            #else
                #define DRWAV_DLL_IMPORT
                #define DRWAV_DLL_EXPORT
                #define DRWAV_DLL_PRIVATE static
            #endif
        #endif

        #if defined(DR_WAV_IMPLEMENTATION) || defined(DRWAV_IMPLEMENTATION)
            #define DRWAV_API  DRWAV_DLL_EXPORT
        #else
            #define DRWAV_API  DRWAV_DLL_IMPORT
        #endif
        #define DRWAV_PRIVATE DRWAV_DLL_PRIVATE
    #else
        #define DRWAV_API extern
        #define DRWAV_PRIVATE static
    #endif
#endif

typedef drwav_int32 drwav_result;
#define DRWAV_SUCCESS                        0
#define DRWAV_ERROR                         -1   /* A generic error. */
#define DRWAV_INVALID_ARGS                  -2
#define DRWAV_INVALID_OPERATION             -3
#define DRWAV_OUT_OF_MEMORY                 -4
#define DRWAV_OUT_OF_RANGE                  -5
#define DRWAV_ACCESS_DENIED                 -6
#define DRWAV_DOES_NOT_EXIST                -7
#define DRWAV_ALREADY_EXISTS                -8
#define DRWAV_TOO_MANY_OPEN_FILES           -9
#define DRWAV_INVALID_FILE                  -10
#define DRWAV_TOO_BIG                       -11
#define DRWAV_PATH_TOO_LONG                 -12
#define DRWAV_NAME_TOO_LONG                 -13
#define DRWAV_NOT_DIRECTORY                 -14
#define DRWAV_IS_DIRECTORY                  -15
#define DRWAV_DIRECTORY_NOT_EMPTY           -16
#define DRWAV_END_OF_FILE                   -17
#define DRWAV_NO_SPACE                      -18
#define DRWAV_BUSY                          -19
#define DRWAV_IO_ERROR                      -20
#define DRWAV_INTERRUPT                     -21
#define DRWAV_UNAVAILABLE                   -22
#define DRWAV_ALREADY_IN_USE                -23
#define DRWAV_BAD_ADDRESS                   -24
#define DRWAV_BAD_SEEK                      -25
#define DRWAV_BAD_PIPE                      -26
#define DRWAV_DEADLOCK                      -27
#define DRWAV_TOO_MANY_LINKS                -28
#define DRWAV_NOT_IMPLEMENTED               -29
#define DRWAV_NO_MESSAGE                    -30
#define DRWAV_BAD_MESSAGE                   -31
#define DRWAV_NO_DATA_AVAILABLE             -32
#define DRWAV_INVALID_DATA                  -33
#define DRWAV_TIMEOUT                       -34
#define DRWAV_NO_NETWORK                    -35
#define DRWAV_NOT_UNIQUE                    -36
#define DRWAV_NOT_SOCKET                    -37
#define DRWAV_NO_ADDRESS                    -38
#define DRWAV_BAD_PROTOCOL                  -39
#define DRWAV_PROTOCOL_UNAVAILABLE          -40
#define DRWAV_PROTOCOL_NOT_SUPPORTED        -41
#define DRWAV_PROTOCOL_FAMILY_NOT_SUPPORTED -42
#define DRWAV_ADDRESS_FAMILY_NOT_SUPPORTED  -43
#define DRWAV_SOCKET_NOT_SUPPORTED          -44
#define DRWAV_CONNECTION_RESET              -45
#define DRWAV_ALREADY_CONNECTED             -46
#define DRWAV_NOT_CONNECTED                 -47
#define DRWAV_CONNECTION_REFUSED            -48
#define DRWAV_NO_HOST                       -49
#define DRWAV_IN_PROGRESS                   -50
#define DRWAV_CANCELLED                     -51
#define DRWAV_MEMORY_ALREADY_MAPPED         -52
#define DRWAV_AT_END                        -53

/* Common data formats. */
#define DR_WAVE_FORMAT_PCM          0x1
#define DR_WAVE_FORMAT_ADPCM        0x2
#define DR_WAVE_FORMAT_IEEE_FLOAT   0x3
#define DR_WAVE_FORMAT_ALAW         0x6
#define DR_WAVE_FORMAT_MULAW        0x7
#define DR_WAVE_FORMAT_DVI_ADPCM    0x11
#define DR_WAVE_FORMAT_EXTENSIBLE   0xFFFE

/* Constants. */
#ifndef DRWAV_MAX_SMPL_LOOPS
#define DRWAV_MAX_SMPL_LOOPS        1
#endif

/* Flags to pass into drwav_init_ex(), etc. */
#define DRWAV_SEQUENTIAL            0x00000001

DRWAV_API void drwav_version(drwav_uint32* pMajor, drwav_uint32* pMinor, drwav_uint32* pRevision);
DRWAV_API const char* drwav_version_string(void);

typedef enum
{
    drwav_seek_origin_start,
    drwav_seek_origin_current
} drwav_seek_origin;

typedef enum
{
    drwav_container_riff,
    drwav_container_w64
} drwav_container;

typedef struct
{
    union
    {
        drwav_uint8 fourcc[4];
        drwav_uint8 guid[16];
    } id;

    /* The size in bytes of the chunk. */
    drwav_uint64 sizeInBytes;

    /*
    RIFF = 2 byte alignment.
    W64  = 8 byte alignment.
    */
    unsigned int paddingSize;
} drwav_chunk_header;

typedef struct
{
    /*
    The format tag exactly as specified in the wave file's "fmt" chunk. This can be used by applications
    that require support for data formats not natively supported by dr_wav.
    */
    drwav_uint16 formatTag;

    /* The number of channels making up the audio data. When this is set to 1 it is mono, 2 is stereo, etc. */
    drwav_uint16 channels;

    /* The sample rate. Usually set to something like 44100. */
    drwav_uint32 sampleRate;

    /* Average bytes per second. You probably don't need this, but it's left here for informational purposes. */
    drwav_uint32 avgBytesPerSec;

    /* Block align. This is equal to the number of channels * bytes per sample. */
    drwav_uint16 blockAlign;

    /* Bits per sample. */
    drwav_uint16 bitsPerSample;

    /* The size of the extended data. Only used internally for validation, but left here for informational purposes. */
    drwav_uint16 extendedSize;

    /*
    The number of valid bits per sample. When <formatTag> is equal to WAVE_FORMAT_EXTENSIBLE, <bitsPerSample>
    is always rounded up to the nearest multiple of 8. This variable contains information about exactly how
    many bits are valid per sample. Mainly used for informational purposes.
    */
    drwav_uint16 validBitsPerSample;

    /* The channel mask. Not used at the moment. */
    drwav_uint32 channelMask;

    /* The sub-format, exactly as specified by the wave file. */
    drwav_uint8 subFormat[16];
} drwav_fmt;

DRWAV_API drwav_uint16 drwav_fmt_get_format(const drwav_fmt* pFMT);


/*
Callback for when data is read. Return value is the number of bytes actually read.

pUserData   [in]  The user data that was passed to drwav_init() and family.
pBufferOut  [out] The output buffer.
bytesToRead [in]  The number of bytes to read.

Returns the number of bytes actually read.

A return value of less than bytesToRead indicates the end of the stream. Do _not_ return from this callback until
either the entire bytesToRead is filled or you have reached the end of the stream.
*/
typedef size_t (* drwav_read_proc)(void* pUserData, void* pBufferOut, size_t bytesToRead);

/*
Callback for when data is written. Returns value is the number of bytes actually written.

pUserData    [in]  The user data that was passed to drwav_init_write() and family.
pData        [out] A pointer to the data to write.
bytesToWrite [in]  The number of bytes to write.

Returns the number of bytes actually written.

If the return value differs from bytesToWrite, it indicates an error.
*/
typedef size_t (* drwav_write_proc)(void* pUserData, const void* pData, size_t bytesToWrite);

/*
Callback for when data needs to be seeked.

pUserData [in] The user data that was passed to drwav_init() and family.
offset    [in] The number of bytes to move, relative to the origin. Will never be negative.
origin    [in] The origin of the seek - the current position or the start of the stream.

Returns whether or not the seek was successful.

Whether or not it is relative to the beginning or current position is determined by the "origin" parameter which will be either drwav_seek_origin_start or
drwav_seek_origin_current.
*/
typedef drwav_bool32 (* drwav_seek_proc)(void* pUserData, int offset, drwav_seek_origin origin);

/*
Callback for when drwav_init_ex() finds a chunk.

pChunkUserData    [in] The user data that was passed to the pChunkUserData parameter of drwav_init_ex() and family.
onRead            [in] A pointer to the function to call when reading.
onSeek            [in] A pointer to the function to call when seeking.
pReadSeekUserData [in] The user data that was passed to the pReadSeekUserData parameter of drwav_init_ex() and family.
pChunkHeader      [in] A pointer to an object containing basic header information about the chunk. Use this to identify the chunk.
container         [in] Whether or not the WAV file is a RIFF or Wave64 container. If you're unsure of the difference, assume RIFF.
pFMT              [in] A pointer to the object containing the contents of the "fmt" chunk.

Returns the number of bytes read + seeked.

To read data from the chunk, call onRead(), passing in pReadSeekUserData as the first parameter. Do the same for seeking with onSeek(). The return value must
be the total number of bytes you have read _plus_ seeked.

Use the `container` argument to discriminate the fields in `pChunkHeader->id`. If the container is `drwav_container_riff` you should use `id.fourcc`,
otherwise you should use `id.guid`.

The `pFMT` parameter can be used to determine the data format of the wave file. Use `drwav_fmt_get_format()` to get the sample format, which will be one of the
`DR_WAVE_FORMAT_*` identifiers. 

The read pointer will be sitting on the first byte after the chunk's header. You must not attempt to read beyond the boundary of the chunk.
*/
typedef drwav_uint64 (* drwav_chunk_proc)(void* pChunkUserData, drwav_read_proc onRead, drwav_seek_proc onSeek, void* pReadSeekUserData, const drwav_chunk_header* pChunkHeader, drwav_container container, const drwav_fmt* pFMT);

typedef struct
{
    void* pUserData;
    void* (* onMalloc)(size_t sz, void* pUserData);
    void* (* onRealloc)(void* p, size_t sz, void* pUserData);
    void  (* onFree)(void* p, void* pUserData);
} drwav_allocation_callbacks;

/* Structure for internal use. Only used for loaders opened with drwav_init_memory(). */
typedef struct
{
    const drwav_uint8* data;
    size_t dataSize;
    size_t currentReadPos;
} drwav__memory_stream;

/* Structure for internal use. Only used for writers opened with drwav_init_memory_write(). */
typedef struct
{
    void** ppData;
    size_t* pDataSize;
    size_t dataSize;
    size_t dataCapacity;
    size_t currentWritePos;
} drwav__memory_stream_write;

typedef struct
{
    drwav_container container;  /* RIFF, W64. */
    drwav_uint32 format;        /* DR_WAVE_FORMAT_* */
    drwav_uint32 channels;
    drwav_uint32 sampleRate;
    drwav_uint32 bitsPerSample;
} drwav_data_format;


/* See the following for details on the 'smpl' chunk: https://sites.google.com/site/musicgapi/technical-documents/wav-file-format#smpl */
typedef struct
{
    drwav_uint32 cuePointId;
    drwav_uint32 type;
    drwav_uint32 start;
    drwav_uint32 end;
    drwav_uint32 fraction;
    drwav_uint32 playCount;
} drwav_smpl_loop;

 typedef struct
{
    drwav_uint32 manufacturer;
    drwav_uint32 product;
    drwav_uint32 samplePeriod;
    drwav_uint32 midiUnityNotes;
    drwav_uint32 midiPitchFraction;
    drwav_uint32 smpteFormat;
    drwav_uint32 smpteOffset;
    drwav_uint32 numSampleLoops;
    drwav_uint32 samplerData;
    drwav_smpl_loop loops[DRWAV_MAX_SMPL_LOOPS];
} drwav_smpl;

typedef struct
{
    /* A pointer to the function to call when more data is needed. */
    drwav_read_proc onRead;

    /* A pointer to the function to call when data needs to be written. Only used when the drwav object is opened in write mode. */
    drwav_write_proc onWrite;

    /* A pointer to the function to call when the wav file needs to be seeked. */
    drwav_seek_proc onSeek;

    /* The user data to pass to callbacks. */
    void* pUserData;

    /* Allocation callbacks. */
    drwav_allocation_callbacks allocationCallbacks;


    /* Whether or not the WAV file is formatted as a standard RIFF file or W64. */
    drwav_container container;


    /* Structure containing format information exactly as specified by the wav file. */
    drwav_fmt fmt;

    /* The sample rate. Will be set to something like 44100. */
    drwav_uint32 sampleRate;

    /* The number of channels. This will be set to 1 for monaural streams, 2 for stereo, etc. */
    drwav_uint16 channels;

    /* The bits per sample. Will be set to something like 16, 24, etc. */
    drwav_uint16 bitsPerSample;

    /* Equal to fmt.formatTag, or the value specified by fmt.subFormat if fmt.formatTag is equal to 65534 (WAVE_FORMAT_EXTENSIBLE). */
    drwav_uint16 translatedFormatTag;

    /* The total number of PCM frames making up the audio data. */
    drwav_uint64 totalPCMFrameCount;


    /* The size in bytes of the data chunk. */
    drwav_uint64 dataChunkDataSize;
    
    /* The position in the stream of the first byte of the data chunk. This is used for seeking. */
    drwav_uint64 dataChunkDataPos;

    /* The number of bytes remaining in the data chunk. */
    drwav_uint64 bytesRemaining;


    /*
    Only used in sequential write mode. Keeps track of the desired size of the "data" chunk at the point of initialization time. Always
    set to 0 for non-sequential writes and when the drwav object is opened in read mode. Used for validation.
    */
    drwav_uint64 dataChunkDataSizeTargetWrite;

    /* Keeps track of whether or not the wav writer was initialized in sequential mode. */
    drwav_bool32 isSequentialWrite;


    /* smpl chunk. */
    drwav_smpl smpl;


    /* A hack to avoid a DRWAV_MALLOC() when opening a decoder with drwav_init_memory(). */
    drwav__memory_stream memoryStream;
    drwav__memory_stream_write memoryStreamWrite;

    /* Generic data for compressed formats. This data is shared across all block-compressed formats. */
    struct
    {
        drwav_uint64 iCurrentPCMFrame;  /* The index of the next PCM frame that will be read by drwav_read_*(). This is used with "totalPCMFrameCount" to ensure we don't read excess samples at the end of the last block. */
    } compressed;
    
    /* Microsoft ADPCM specific data. */
    struct
    {
        drwav_uint32 bytesRemainingInBlock;
        drwav_uint16 predictor[2];
        drwav_int32  delta[2];
        drwav_int32  cachedFrames[4];  /* Samples are stored in this cache during decoding. */
        drwav_uint32 cachedFrameCount;
        drwav_int32  prevFrames[2][2]; /* The previous 2 samples for each channel (2 channels at most). */
    } msadpcm;

    /* IMA ADPCM specific data. */
    struct
    {
        drwav_uint32 bytesRemainingInBlock;
        drwav_int32  predictor[2];
        drwav_int32  stepIndex[2];
        drwav_int32  cachedFrames[16]; /* Samples are stored in this cache during decoding. */
        drwav_uint32 cachedFrameCount;
    } ima;
} drwav;


/*
Initializes a pre-allocated drwav object for reading.

pWav                         [out]          A pointer to the drwav object being initialized.
onRead                       [in]           The function to call when data needs to be read from the client.
onSeek                       [in]           The function to call when the read position of the client data needs to move.
onChunk                      [in, optional] The function to call when a chunk is enumerated at initialized time.
pUserData, pReadSeekUserData [in, optional] A pointer to application defined data that will be passed to onRead and onSeek.
pChunkUserData               [in, optional] A pointer to application defined data that will be passed to onChunk.
flags                        [in, optional] A set of flags for controlling how things are loaded.

Returns true if successful; false otherwise.

Close the loader with drwav_uninit().

This is the lowest level function for initializing a WAV file. You can also use drwav_init_file() and drwav_init_memory()
to open the stream from a file or from a block of memory respectively.

Possible values for flags:
  DRWAV_SEQUENTIAL: Never perform a backwards seek while loading. This disables the chunk callback and will cause this function
                    to return as soon as the data chunk is found. Any chunks after the data chunk will be ignored.

drwav_init() is equivalent to "drwav_init_ex(pWav, onRead, onSeek, NULL, pUserData, NULL, 0);".

The onChunk callback is not called for the WAVE or FMT chunks. The contents of the FMT chunk can be read from pWav->fmt
after the function returns.

See also: drwav_init_file(), drwav_init_memory(), drwav_uninit()
*/
DRWAV_API drwav_bool32 drwav_init(drwav* pWav, drwav_read_proc onRead, drwav_seek_proc onSeek, void* pUserData, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API drwav_bool32 drwav_init_ex(drwav* pWav, drwav_read_proc onRead, drwav_seek_proc onSeek, drwav_chunk_proc onChunk, void* pReadSeekUserData, void* pChunkUserData, drwav_uint32 flags, const drwav_allocation_callbacks* pAllocationCallbacks);

/*
Initializes a pre-allocated drwav object for writing.

onWrite   [in]           The function to call when data needs to be written.
onSeek    [in]           The function to call when the write position needs to move.
pUserData [in, optional] A pointer to application defined data that will be passed to onWrite and onSeek.

Returns true if successful; false otherwise.

Close the writer with drwav_uninit().

This is the lowest level function for initializing a WAV file. You can also use drwav_init_file_write() and drwav_init_memory_write()
to open the stream from a file or from a block of memory respectively.

If the total sample count is known, you can use drwav_init_write_sequential(). This avoids the need for dr_wav to perform
a post-processing step for storing the total sample count and the size of the data chunk which requires a backwards seek.

See also: drwav_init_file_write(), drwav_init_memory_write(), drwav_uninit()
*/
DRWAV_API drwav_bool32 drwav_init_write(drwav* pWav, const drwav_data_format* pFormat, drwav_write_proc onWrite, drwav_seek_proc onSeek, void* pUserData, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API drwav_bool32 drwav_init_write_sequential(drwav* pWav, const drwav_data_format* pFormat, drwav_uint64 totalSampleCount, drwav_write_proc onWrite, void* pUserData, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API drwav_bool32 drwav_init_write_sequential_pcm_frames(drwav* pWav, const drwav_data_format* pFormat, drwav_uint64 totalPCMFrameCount, drwav_write_proc onWrite, void* pUserData, const drwav_allocation_callbacks* pAllocationCallbacks);

/*
Utility function to determine the target size of the entire data to be written (including all headers and chunks).

Returns the target size in bytes.

Useful if the application needs to know the size to allocate.

Only writing to the RIFF chunk and one data chunk is currently supported.

See also: drwav_init_write(), drwav_init_file_write(), drwav_init_memory_write()
*/
DRWAV_API drwav_uint64 drwav_target_write_size_bytes(const drwav_data_format* pFormat, drwav_uint64 totalSampleCount);

/*
Uninitializes the given drwav object.

Use this only for objects initialized with drwav_init*() functions (drwav_init(), drwav_init_ex(), drwav_init_write(), drwav_init_write_sequential()).
*/
DRWAV_API drwav_result drwav_uninit(drwav* pWav);


/*
Reads raw audio data.

This is the lowest level function for reading audio data. It simply reads the given number of
bytes of the raw internal sample data.

Consider using drwav_read_pcm_frames_s16(), drwav_read_pcm_frames_s32() or drwav_read_pcm_frames_f32() for
reading sample data in a consistent format.

pBufferOut can be NULL in which case a seek will be performed.

Returns the number of bytes actually read.
*/
DRWAV_API size_t drwav_read_raw(drwav* pWav, size_t bytesToRead, void* pBufferOut);

/*
Reads up to the specified number of PCM frames from the WAV file.

The output data will be in the file's internal format, converted to native-endian byte order. Use
drwav_read_pcm_frames_s16/f32/s32() to read data in a specific format.

If the return value is less than <framesToRead> it means the end of the file has been reached or
you have requested more PCM frames than can possibly fit in the output buffer.

This function will only work when sample data is of a fixed size and uncompressed. If you are
using a compressed format consider using drwav_read_raw() or drwav_read_pcm_frames_s16/s32/f32().

pBufferOut can be NULL in which case a seek will be performed.
*/
DRWAV_API drwav_uint64 drwav_read_pcm_frames(drwav* pWav, drwav_uint64 framesToRead, void* pBufferOut);
DRWAV_API drwav_uint64 drwav_read_pcm_frames_le(drwav* pWav, drwav_uint64 framesToRead, void* pBufferOut);
DRWAV_API drwav_uint64 drwav_read_pcm_frames_be(drwav* pWav, drwav_uint64 framesToRead, void* pBufferOut);

/*
Seeks to the given PCM frame.

Returns true if successful; false otherwise.
*/
DRWAV_API drwav_bool32 drwav_seek_to_pcm_frame(drwav* pWav, drwav_uint64 targetFrameIndex);


/*
Writes raw audio data.

Returns the number of bytes actually written. If this differs from bytesToWrite, it indicates an error.
*/
DRWAV_API size_t drwav_write_raw(drwav* pWav, size_t bytesToWrite, const void* pData);

/*
Writes PCM frames.

Returns the number of PCM frames written.

Input samples need to be in native-endian byte order. On big-endian architectures the input data will be converted to
little-endian. Use drwav_write_raw() to write raw audio data without performing any conversion.
*/
DRWAV_API drwav_uint64 drwav_write_pcm_frames(drwav* pWav, drwav_uint64 framesToWrite, const void* pData);
DRWAV_API drwav_uint64 drwav_write_pcm_frames_le(drwav* pWav, drwav_uint64 framesToWrite, const void* pData);
DRWAV_API drwav_uint64 drwav_write_pcm_frames_be(drwav* pWav, drwav_uint64 framesToWrite, const void* pData);


/* Conversion Utilities */
#ifndef DR_WAV_NO_CONVERSION_API

/*
Reads a chunk of audio data and converts it to signed 16-bit PCM samples.

pBufferOut can be NULL in which case a seek will be performed.

Returns the number of PCM frames actually read.

If the return value is less than <framesToRead> it means the end of the file has been reached.
*/
DRWAV_API drwav_uint64 drwav_read_pcm_frames_s16(drwav* pWav, drwav_uint64 framesToRead, drwav_int16* pBufferOut);
DRWAV_API drwav_uint64 drwav_read_pcm_frames_s16le(drwav* pWav, drwav_uint64 framesToRead, drwav_int16* pBufferOut);
DRWAV_API drwav_uint64 drwav_read_pcm_frames_s16be(drwav* pWav, drwav_uint64 framesToRead, drwav_int16* pBufferOut);

/* Low-level function for converting unsigned 8-bit PCM samples to signed 16-bit PCM samples. */
DRWAV_API void drwav_u8_to_s16(drwav_int16* pOut, const drwav_uint8* pIn, size_t sampleCount);

/* Low-level function for converting signed 24-bit PCM samples to signed 16-bit PCM samples. */
DRWAV_API void drwav_s24_to_s16(drwav_int16* pOut, const drwav_uint8* pIn, size_t sampleCount);

/* Low-level function for converting signed 32-bit PCM samples to signed 16-bit PCM samples. */
DRWAV_API void drwav_s32_to_s16(drwav_int16* pOut, const drwav_int32* pIn, size_t sampleCount);

/* Low-level function for converting IEEE 32-bit floating point samples to signed 16-bit PCM samples. */
DRWAV_API void drwav_f32_to_s16(drwav_int16* pOut, const float* pIn, size_t sampleCount);

/* Low-level function for converting IEEE 64-bit floating point samples to signed 16-bit PCM samples. */
DRWAV_API void drwav_f64_to_s16(drwav_int16* pOut, const double* pIn, size_t sampleCount);

/* Low-level function for converting A-law samples to signed 16-bit PCM samples. */
DRWAV_API void drwav_alaw_to_s16(drwav_int16* pOut, const drwav_uint8* pIn, size_t sampleCount);

/* Low-level function for converting u-law samples to signed 16-bit PCM samples. */
DRWAV_API void drwav_mulaw_to_s16(drwav_int16* pOut, const drwav_uint8* pIn, size_t sampleCount);


/*
Reads a chunk of audio data and converts it to IEEE 32-bit floating point samples.

pBufferOut can be NULL in which case a seek will be performed.

Returns the number of PCM frames actually read.

If the return value is less than <framesToRead> it means the end of the file has been reached.
*/
DRWAV_API drwav_uint64 drwav_read_pcm_frames_f32(drwav* pWav, drwav_uint64 framesToRead, float* pBufferOut);
DRWAV_API drwav_uint64 drwav_read_pcm_frames_f32le(drwav* pWav, drwav_uint64 framesToRead, float* pBufferOut);
DRWAV_API drwav_uint64 drwav_read_pcm_frames_f32be(drwav* pWav, drwav_uint64 framesToRead, float* pBufferOut);

/* Low-level function for converting unsigned 8-bit PCM samples to IEEE 32-bit floating point samples. */
DRWAV_API void drwav_u8_to_f32(float* pOut, const drwav_uint8* pIn, size_t sampleCount);

/* Low-level function for converting signed 16-bit PCM samples to IEEE 32-bit floating point samples. */
DRWAV_API void drwav_s16_to_f32(float* pOut, const drwav_int16* pIn, size_t sampleCount);

/* Low-level function for converting signed 24-bit PCM samples to IEEE 32-bit floating point samples. */
DRWAV_API void drwav_s24_to_f32(float* pOut, const drwav_uint8* pIn, size_t sampleCount);

/* Low-level function for converting signed 32-bit PCM samples to IEEE 32-bit floating point samples. */
DRWAV_API void drwav_s32_to_f32(float* pOut, const drwav_int32* pIn, size_t sampleCount);

/* Low-level function for converting IEEE 64-bit floating point samples to IEEE 32-bit floating point samples. */
DRWAV_API void drwav_f64_to_f32(float* pOut, const double* pIn, size_t sampleCount);

/* Low-level function for converting A-law samples to IEEE 32-bit floating point samples. */
DRWAV_API void drwav_alaw_to_f32(float* pOut, const drwav_uint8* pIn, size_t sampleCount);

/* Low-level function for converting u-law samples to IEEE 32-bit floating point samples. */
DRWAV_API void drwav_mulaw_to_f32(float* pOut, const drwav_uint8* pIn, size_t sampleCount);


/*
Reads a chunk of audio data and converts it to signed 32-bit PCM samples.

pBufferOut can be NULL in which case a seek will be performed.

Returns the number of PCM frames actually read.

If the return value is less than <framesToRead> it means the end of the file has been reached.
*/
DRWAV_API drwav_uint64 drwav_read_pcm_frames_s32(drwav* pWav, drwav_uint64 framesToRead, drwav_int32* pBufferOut);
DRWAV_API drwav_uint64 drwav_read_pcm_frames_s32le(drwav* pWav, drwav_uint64 framesToRead, drwav_int32* pBufferOut);
DRWAV_API drwav_uint64 drwav_read_pcm_frames_s32be(drwav* pWav, drwav_uint64 framesToRead, drwav_int32* pBufferOut);

/* Low-level function for converting unsigned 8-bit PCM samples to signed 32-bit PCM samples. */
DRWAV_API void drwav_u8_to_s32(drwav_int32* pOut, const drwav_uint8* pIn, size_t sampleCount);

/* Low-level function for converting signed 16-bit PCM samples to signed 32-bit PCM samples. */
DRWAV_API void drwav_s16_to_s32(drwav_int32* pOut, const drwav_int16* pIn, size_t sampleCount);

/* Low-level function for converting signed 24-bit PCM samples to signed 32-bit PCM samples. */
DRWAV_API void drwav_s24_to_s32(drwav_int32* pOut, const drwav_uint8* pIn, size_t sampleCount);

/* Low-level function for converting IEEE 32-bit floating point samples to signed 32-bit PCM samples. */
DRWAV_API void drwav_f32_to_s32(drwav_int32* pOut, const float* pIn, size_t sampleCount);

/* Low-level function for converting IEEE 64-bit floating point samples to signed 32-bit PCM samples. */
DRWAV_API void drwav_f64_to_s32(drwav_int32* pOut, const double* pIn, size_t sampleCount);

/* Low-level function for converting A-law samples to signed 32-bit PCM samples. */
DRWAV_API void drwav_alaw_to_s32(drwav_int32* pOut, const drwav_uint8* pIn, size_t sampleCount);

/* Low-level function for converting u-law samples to signed 32-bit PCM samples. */
DRWAV_API void drwav_mulaw_to_s32(drwav_int32* pOut, const drwav_uint8* pIn, size_t sampleCount);

#endif  /* DR_WAV_NO_CONVERSION_API */


/* High-Level Convenience Helpers */

#ifndef DR_WAV_NO_STDIO
/*
Helper for initializing a wave file for reading using stdio.

This holds the internal FILE object until drwav_uninit() is called. Keep this in mind if you're caching drwav
objects because the operating system may restrict the number of file handles an application can have open at
any given time.
*/
DRWAV_API drwav_bool32 drwav_init_file(drwav* pWav, const char* filename, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API drwav_bool32 drwav_init_file_ex(drwav* pWav, const char* filename, drwav_chunk_proc onChunk, void* pChunkUserData, drwav_uint32 flags, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API drwav_bool32 drwav_init_file_w(drwav* pWav, const wchar_t* filename, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API drwav_bool32 drwav_init_file_ex_w(drwav* pWav, const wchar_t* filename, drwav_chunk_proc onChunk, void* pChunkUserData, drwav_uint32 flags, const drwav_allocation_callbacks* pAllocationCallbacks);

/*
Helper for initializing a wave file for writing using stdio.

This holds the internal FILE object until drwav_uninit() is called. Keep this in mind if you're caching drwav
objects because the operating system may restrict the number of file handles an application can have open at
any given time.
*/
DRWAV_API drwav_bool32 drwav_init_file_write(drwav* pWav, const char* filename, const drwav_data_format* pFormat, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API drwav_bool32 drwav_init_file_write_sequential(drwav* pWav, const char* filename, const drwav_data_format* pFormat, drwav_uint64 totalSampleCount, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API drwav_bool32 drwav_init_file_write_sequential_pcm_frames(drwav* pWav, const char* filename, const drwav_data_format* pFormat, drwav_uint64 totalPCMFrameCount, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API drwav_bool32 drwav_init_file_write_w(drwav* pWav, const wchar_t* filename, const drwav_data_format* pFormat, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API drwav_bool32 drwav_init_file_write_sequential_w(drwav* pWav, const wchar_t* filename, const drwav_data_format* pFormat, drwav_uint64 totalSampleCount, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API drwav_bool32 drwav_init_file_write_sequential_pcm_frames_w(drwav* pWav, const wchar_t* filename, const drwav_data_format* pFormat, drwav_uint64 totalPCMFrameCount, const drwav_allocation_callbacks* pAllocationCallbacks);
#endif  /* DR_WAV_NO_STDIO */

/*
Helper for initializing a loader from a pre-allocated memory buffer.

This does not create a copy of the data. It is up to the application to ensure the buffer remains valid for
the lifetime of the drwav object.

The buffer should contain the contents of the entire wave file, not just the sample data.
*/
DRWAV_API drwav_bool32 drwav_init_memory(drwav* pWav, const void* data, size_t dataSize, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API drwav_bool32 drwav_init_memory_ex(drwav* pWav, const void* data, size_t dataSize, drwav_chunk_proc onChunk, void* pChunkUserData, drwav_uint32 flags, const drwav_allocation_callbacks* pAllocationCallbacks);

/*
Helper for initializing a writer which outputs data to a memory buffer.

dr_wav will manage the memory allocations, however it is up to the caller to free the data with drwav_free().

The buffer will remain allocated even after drwav_uninit() is called. Indeed, the buffer should not be
considered valid until after drwav_uninit() has been called anyway.
*/
DRWAV_API drwav_bool32 drwav_init_memory_write(drwav* pWav, void** ppData, size_t* pDataSize, const drwav_data_format* pFormat, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API drwav_bool32 drwav_init_memory_write_sequential(drwav* pWav, void** ppData, size_t* pDataSize, const drwav_data_format* pFormat, drwav_uint64 totalSampleCount, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API drwav_bool32 drwav_init_memory_write_sequential_pcm_frames(drwav* pWav, void** ppData, size_t* pDataSize, const drwav_data_format* pFormat, drwav_uint64 totalPCMFrameCount, const drwav_allocation_callbacks* pAllocationCallbacks);


#ifndef DR_WAV_NO_CONVERSION_API
/*
Opens and reads an entire wav file in a single operation.

The return value is a heap-allocated buffer containing the audio data. Use drwav_free() to free the buffer.
*/
DRWAV_API drwav_int16* drwav_open_and_read_pcm_frames_s16(drwav_read_proc onRead, drwav_seek_proc onSeek, void* pUserData, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API float* drwav_open_and_read_pcm_frames_f32(drwav_read_proc onRead, drwav_seek_proc onSeek, void* pUserData, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API drwav_int32* drwav_open_and_read_pcm_frames_s32(drwav_read_proc onRead, drwav_seek_proc onSeek, void* pUserData, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks);
#ifndef DR_WAV_NO_STDIO
/*
Opens and decodes an entire wav file in a single operation.

The return value is a heap-allocated buffer containing the audio data. Use drwav_free() to free the buffer.
*/
DRWAV_API drwav_int16* drwav_open_file_and_read_pcm_frames_s16(const char* filename, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API float* drwav_open_file_and_read_pcm_frames_f32(const char* filename, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API drwav_int32* drwav_open_file_and_read_pcm_frames_s32(const char* filename, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API drwav_int16* drwav_open_file_and_read_pcm_frames_s16_w(const wchar_t* filename, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API float* drwav_open_file_and_read_pcm_frames_f32_w(const wchar_t* filename, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API drwav_int32* drwav_open_file_and_read_pcm_frames_s32_w(const wchar_t* filename, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks);
#endif
/*
Opens and decodes an entire wav file from a block of memory in a single operation.

The return value is a heap-allocated buffer containing the audio data. Use drwav_free() to free the buffer.
*/
DRWAV_API drwav_int16* drwav_open_memory_and_read_pcm_frames_s16(const void* data, size_t dataSize, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API float* drwav_open_memory_and_read_pcm_frames_f32(const void* data, size_t dataSize, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks);
DRWAV_API drwav_int32* drwav_open_memory_and_read_pcm_frames_s32(const void* data, size_t dataSize, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks);
#endif

/* Frees data that was allocated internally by dr_wav. */
DRWAV_API void drwav_free(void* p, const drwav_allocation_callbacks* pAllocationCallbacks);

/* Converts bytes from a wav stream to a sized type of native endian. */
DRWAV_API drwav_uint16 drwav_bytes_to_u16(const drwav_uint8* data);
DRWAV_API drwav_int16 drwav_bytes_to_s16(const drwav_uint8* data);
DRWAV_API drwav_uint32 drwav_bytes_to_u32(const drwav_uint8* data);
DRWAV_API drwav_int32 drwav_bytes_to_s32(const drwav_uint8* data);
DRWAV_API drwav_uint64 drwav_bytes_to_u64(const drwav_uint8* data);
DRWAV_API drwav_int64 drwav_bytes_to_s64(const drwav_uint8* data);

/* Compares a GUID for the purpose of checking the type of a Wave64 chunk. */
DRWAV_API drwav_bool32 drwav_guid_equal(const drwav_uint8 a[16], const drwav_uint8 b[16]);

/* Compares a four-character-code for the purpose of checking the type of a RIFF chunk. */
DRWAV_API drwav_bool32 drwav_fourcc_equal(const drwav_uint8* a, const char* b);

#ifdef __cplusplus
}
#endif


/************************************************************************************************************************************************************
 ************************************************************************************************************************************************************

 IMPLEMENTATION

 ************************************************************************************************************************************************************
 ************************************************************************************************************************************************************/
#if defined(DR_WAV_IMPLEMENTATION) || defined(DRWAV_IMPLEMENTATION)

#include <stdlib.h>
#include <string.h> /* For memcpy(), memset() */
#include <limits.h> /* For INT_MAX */

#ifndef DR_WAV_NO_STDIO
#include <stdio.h>
#include <wchar.h>
#endif

/* Standard library stuff. */
#ifndef DRWAV_ASSERT
#include <assert.h>
#define DRWAV_ASSERT(expression)           assert(expression)
#endif
#ifndef DRWAV_MALLOC
#define DRWAV_MALLOC(sz)                   malloc((sz))
#endif
#ifndef DRWAV_REALLOC
#define DRWAV_REALLOC(p, sz)               realloc((p), (sz))
#endif
#ifndef DRWAV_FREE
#define DRWAV_FREE(p)                      free((p))
#endif
#ifndef DRWAV_COPY_MEMORY
#define DRWAV_COPY_MEMORY(dst, src, sz)    memcpy((dst), (src), (sz))
#endif
#ifndef DRWAV_ZERO_MEMORY
#define DRWAV_ZERO_MEMORY(p, sz)           memset((p), 0, (sz))
#endif
#ifndef DRWAV_ZERO_OBJECT
#define DRWAV_ZERO_OBJECT(p)               DRWAV_ZERO_MEMORY((p), sizeof(*p))
#endif

#define drwav_countof(x)                   (sizeof(x) / sizeof(x[0]))
#define drwav_align(x, a)                  ((((x) + (a) - 1) / (a)) * (a))
#define drwav_min(a, b)                    (((a) < (b)) ? (a) : (b))
#define drwav_max(a, b)                    (((a) > (b)) ? (a) : (b))
#define drwav_clamp(x, lo, hi)             (drwav_max((lo), drwav_min((hi), (x))))

#define DRWAV_MAX_SIMD_VECTOR_SIZE         64  /* 64 for AVX-512 in the future. */

/* CPU architecture. */
#if defined(__x86_64__) || defined(_M_X64)
    #define DRWAV_X64
#elif defined(__i386) || defined(_M_IX86)
    #define DRWAV_X86
#elif defined(__arm__) || defined(_M_ARM)
    #define DRWAV_ARM
#endif

#ifdef _MSC_VER
    #define DRWAV_INLINE __forceinline
#elif defined(__GNUC__)
    /*
    I've had a bug report where GCC is emitting warnings about functions possibly not being inlineable. This warning happens when
    the __attribute__((always_inline)) attribute is defined without an "inline" statement. I think therefore there must be some
    case where "__inline__" is not always defined, thus the compiler emitting these warnings. When using -std=c89 or -ansi on the
    command line, we cannot use the "inline" keyword and instead need to use "__inline__". In an attempt to work around this issue
    I am using "__inline__" only when we're compiling in strict ANSI mode.
    */
    #if defined(__STRICT_ANSI__)
        #define DRWAV_INLINE __inline__ __attribute__((always_inline))
    #else
        #define DRWAV_INLINE inline __attribute__((always_inline))
    #endif
#else
    #define DRWAV_INLINE
#endif

#if defined(SIZE_MAX)
    #define DRWAV_SIZE_MAX  SIZE_MAX
#else
    #if defined(_WIN64) || defined(_LP64) || defined(__LP64__)
        #define DRWAV_SIZE_MAX  ((drwav_uint64)0xFFFFFFFFFFFFFFFF)
    #else
        #define DRWAV_SIZE_MAX  0xFFFFFFFF
    #endif
#endif

#if defined(_MSC_VER) && _MSC_VER >= 1400
    #define DRWAV_HAS_BYTESWAP16_INTRINSIC
    #define DRWAV_HAS_BYTESWAP32_INTRINSIC
    #define DRWAV_HAS_BYTESWAP64_INTRINSIC
#elif defined(__clang__)
    #if defined(__has_builtin)
        #if __has_builtin(__builtin_bswap16)
            #define DRWAV_HAS_BYTESWAP16_INTRINSIC
        #endif
        #if __has_builtin(__builtin_bswap32)
            #define DRWAV_HAS_BYTESWAP32_INTRINSIC
        #endif
        #if __has_builtin(__builtin_bswap64)
            #define DRWAV_HAS_BYTESWAP64_INTRINSIC
        #endif
    #endif
#elif defined(__GNUC__)
    #if ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))
        #define DRWAV_HAS_BYTESWAP32_INTRINSIC
        #define DRWAV_HAS_BYTESWAP64_INTRINSIC
    #endif
    #if ((__GNUC__ > 4) || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8))
        #define DRWAV_HAS_BYTESWAP16_INTRINSIC
    #endif
#endif

DRWAV_API void drwav_version(drwav_uint32* pMajor, drwav_uint32* pMinor, drwav_uint32* pRevision)
{
    if (pMajor) {
        *pMajor = DRWAV_VERSION_MAJOR;
    }

    if (pMinor) {
        *pMinor = DRWAV_VERSION_MINOR;
    }

    if (pRevision) {
        *pRevision = DRWAV_VERSION_REVISION;
    }
}

DRWAV_API const char* drwav_version_string(void)
{
    return DRWAV_VERSION_STRING;
}

/*
These limits are used for basic validation when initializing the decoder. If you exceed these limits, first of all: what on Earth are
you doing?! (Let me know, I'd be curious!) Second, you can adjust these by #define-ing them before the dr_wav implementation.
*/
#ifndef DRWAV_MAX_SAMPLE_RATE
#define DRWAV_MAX_SAMPLE_RATE       384000
#endif
#ifndef DRWAV_MAX_CHANNELS
#define DRWAV_MAX_CHANNELS          256
#endif
#ifndef DRWAV_MAX_BITS_PER_SAMPLE
#define DRWAV_MAX_BITS_PER_SAMPLE   64
#endif

static const drwav_uint8 drwavGUID_W64_RIFF[16] = {0x72,0x69,0x66,0x66, 0x2E,0x91, 0xCF,0x11, 0xA5,0xD6, 0x28,0xDB,0x04,0xC1,0x00,0x00};    /* 66666972-912E-11CF-A5D6-28DB04C10000 */
static const drwav_uint8 drwavGUID_W64_WAVE[16] = {0x77,0x61,0x76,0x65, 0xF3,0xAC, 0xD3,0x11, 0x8C,0xD1, 0x00,0xC0,0x4F,0x8E,0xDB,0x8A};    /* 65766177-ACF3-11D3-8CD1-00C04F8EDB8A */
static const drwav_uint8 drwavGUID_W64_JUNK[16] = {0x6A,0x75,0x6E,0x6B, 0xF3,0xAC, 0xD3,0x11, 0x8C,0xD1, 0x00,0xC0,0x4F,0x8E,0xDB,0x8A};    /* 6B6E756A-ACF3-11D3-8CD1-00C04F8EDB8A */
static const drwav_uint8 drwavGUID_W64_FMT [16] = {0x66,0x6D,0x74,0x20, 0xF3,0xAC, 0xD3,0x11, 0x8C,0xD1, 0x00,0xC0,0x4F,0x8E,0xDB,0x8A};    /* 20746D66-ACF3-11D3-8CD1-00C04F8EDB8A */
static const drwav_uint8 drwavGUID_W64_FACT[16] = {0x66,0x61,0x63,0x74, 0xF3,0xAC, 0xD3,0x11, 0x8C,0xD1, 0x00,0xC0,0x4F,0x8E,0xDB,0x8A};    /* 74636166-ACF3-11D3-8CD1-00C04F8EDB8A */
static const drwav_uint8 drwavGUID_W64_DATA[16] = {0x64,0x61,0x74,0x61, 0xF3,0xAC, 0xD3,0x11, 0x8C,0xD1, 0x00,0xC0,0x4F,0x8E,0xDB,0x8A};    /* 61746164-ACF3-11D3-8CD1-00C04F8EDB8A */
static const drwav_uint8 drwavGUID_W64_SMPL[16] = {0x73,0x6D,0x70,0x6C, 0xF3,0xAC, 0xD3,0x11, 0x8C,0xD1, 0x00,0xC0,0x4F,0x8E,0xDB,0x8A};    /* 6C706D73-ACF3-11D3-8CD1-00C04F8EDB8A */

static DRWAV_INLINE drwav_bool32 drwav__guid_equal(const drwav_uint8 a[16], const drwav_uint8 b[16])
{
    int i;
    for (i = 0; i < 16; i += 1) {
        if (a[i] != b[i]) {
            return DRWAV_FALSE;
        }
    }

    return DRWAV_TRUE;
}

static DRWAV_INLINE drwav_bool32 drwav__fourcc_equal(const drwav_uint8* a, const char* b)
{
    return
        a[0] == b[0] &&
        a[1] == b[1] &&
        a[2] == b[2] &&
        a[3] == b[3];
}



static DRWAV_INLINE int drwav__is_little_endian(void)
{
#if defined(DRWAV_X86) || defined(DRWAV_X64)
    return DRWAV_TRUE;
#elif defined(__BYTE_ORDER) && defined(__LITTLE_ENDIAN) && __BYTE_ORDER == __LITTLE_ENDIAN
    return DRWAV_TRUE;
#else
    int n = 1;
    return (*(char*)&n) == 1;
#endif
}

static DRWAV_INLINE drwav_uint16 drwav__bytes_to_u16(const drwav_uint8* data)
{
    return (data[0] << 0) | (data[1] << 8);
}

static DRWAV_INLINE drwav_int16 drwav__bytes_to_s16(const drwav_uint8* data)
{
    return (short)drwav__bytes_to_u16(data);
}

static DRWAV_INLINE drwav_uint32 drwav__bytes_to_u32(const drwav_uint8* data)
{
    return (data[0] << 0) | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
}

static DRWAV_INLINE drwav_int32 drwav__bytes_to_s32(const drwav_uint8* data)
{
    return (drwav_int32)drwav__bytes_to_u32(data);
}

static DRWAV_INLINE drwav_uint64 drwav__bytes_to_u64(const drwav_uint8* data)
{
    return
        ((drwav_uint64)data[0] <<  0) | ((drwav_uint64)data[1] <<  8) | ((drwav_uint64)data[2] << 16) | ((drwav_uint64)data[3] << 24) |
        ((drwav_uint64)data[4] << 32) | ((drwav_uint64)data[5] << 40) | ((drwav_uint64)data[6] << 48) | ((drwav_uint64)data[7] << 56);
}

static DRWAV_INLINE drwav_int64 drwav__bytes_to_s64(const drwav_uint8* data)
{
    return (drwav_int64)drwav__bytes_to_u64(data);
}

static DRWAV_INLINE void drwav__bytes_to_guid(const drwav_uint8* data, drwav_uint8* guid)
{
    int i;
    for (i = 0; i < 16; ++i) {
        guid[i] = data[i];
    }
}


static DRWAV_INLINE drwav_uint16 drwav__bswap16(drwav_uint16 n)
{
#ifdef DRWAV_HAS_BYTESWAP16_INTRINSIC
    #if defined(_MSC_VER)
        return _byteswap_ushort(n);
    #elif defined(__GNUC__) || defined(__clang__)
        return __builtin_bswap16(n);
    #else
        #error "This compiler does not support the byte swap intrinsic."
    #endif
#else
    return ((n & 0xFF00) >> 8) |
           ((n & 0x00FF) << 8);
#endif
}

static DRWAV_INLINE drwav_uint32 drwav__bswap32(drwav_uint32 n)
{
#ifdef DRWAV_HAS_BYTESWAP32_INTRINSIC
    #if defined(_MSC_VER)
        return _byteswap_ulong(n);
    #elif defined(__GNUC__) || defined(__clang__)
        #if defined(DRWAV_ARM) && (defined(__ARM_ARCH) && __ARM_ARCH >= 6) && !defined(DRWAV_64BIT)   /* <-- 64-bit inline assembly has not been tested, so disabling for now. */
            /* Inline assembly optimized implementation for ARM. In my testing, GCC does not generate optimized code with __builtin_bswap32(). */
            drwav_uint32 r;
            __asm__ __volatile__ (
            #if defined(DRWAV_64BIT)
                "rev %w[out], %w[in]" : [out]"=r"(r) : [in]"r"(n)   /* <-- This is untested. If someone in the community could test this, that would be appreciated! */
            #else
                "rev %[out], %[in]" : [out]"=r"(r) : [in]"r"(n)
            #endif
            );
            return r;
        #else
            return __builtin_bswap32(n);
        #endif
    #else
        #error "This compiler does not support the byte swap intrinsic."
    #endif
#else
    return ((n & 0xFF000000) >> 24) |
           ((n & 0x00FF0000) >>  8) |
           ((n & 0x0000FF00) <<  8) |
           ((n & 0x000000FF) << 24);
#endif
}

static DRWAV_INLINE drwav_uint64 drwav__bswap64(drwav_uint64 n)
{
#ifdef DRWAV_HAS_BYTESWAP64_INTRINSIC
    #if defined(_MSC_VER)
        return _byteswap_uint64(n);
    #elif defined(__GNUC__) || defined(__clang__)
        return __builtin_bswap64(n);
    #else
        #error "This compiler does not support the byte swap intrinsic."
    #endif
#else
    return ((n & (drwav_uint64)0xFF00000000000000) >> 56) |
           ((n & (drwav_uint64)0x00FF000000000000) >> 40) |
           ((n & (drwav_uint64)0x0000FF0000000000) >> 24) |
           ((n & (drwav_uint64)0x000000FF00000000) >>  8) |
           ((n & (drwav_uint64)0x00000000FF000000) <<  8) |
           ((n & (drwav_uint64)0x0000000000FF0000) << 24) |
           ((n & (drwav_uint64)0x000000000000FF00) << 40) |
           ((n & (drwav_uint64)0x00000000000000FF) << 56);
#endif
}


static DRWAV_INLINE drwav_int16 drwav__bswap_s16(drwav_int16 n)
{
    return (drwav_int16)drwav__bswap16((drwav_uint16)n);
}

static DRWAV_INLINE void drwav__bswap_samples_s16(drwav_int16* pSamples, drwav_uint64 sampleCount)
{
    drwav_uint64 iSample;
    for (iSample = 0; iSample < sampleCount; iSample += 1) {
        pSamples[iSample] = drwav__bswap_s16(pSamples[iSample]);
    }
}


static DRWAV_INLINE void drwav__bswap_s24(drwav_uint8* p)
{
    drwav_uint8 t;
    t = p[0];
    p[0] = p[2];
    p[2] = t;
}

static DRWAV_INLINE void drwav__bswap_samples_s24(drwav_uint8* pSamples, drwav_uint64 sampleCount)
{
    drwav_uint64 iSample;
    for (iSample = 0; iSample < sampleCount; iSample += 1) {
        drwav_uint8* pSample = pSamples + (iSample*3);
        drwav__bswap_s24(pSample);
    }
}


static DRWAV_INLINE drwav_int32 drwav__bswap_s32(drwav_int32 n)
{
    return (drwav_int32)drwav__bswap32((drwav_uint32)n);
}

static DRWAV_INLINE void drwav__bswap_samples_s32(drwav_int32* pSamples, drwav_uint64 sampleCount)
{
    drwav_uint64 iSample;
    for (iSample = 0; iSample < sampleCount; iSample += 1) {
        pSamples[iSample] = drwav__bswap_s32(pSamples[iSample]);
    }
}


static DRWAV_INLINE float drwav__bswap_f32(float n)
{
    union {
        drwav_uint32 i;
        float f;
    } x;
    x.f = n;
    x.i = drwav__bswap32(x.i);

    return x.f;
}

static DRWAV_INLINE void drwav__bswap_samples_f32(float* pSamples, drwav_uint64 sampleCount)
{
    drwav_uint64 iSample;
    for (iSample = 0; iSample < sampleCount; iSample += 1) {
        pSamples[iSample] = drwav__bswap_f32(pSamples[iSample]);
    }
}


static DRWAV_INLINE double drwav__bswap_f64(double n)
{
    union {
        drwav_uint64 i;
        double f;
    } x;
    x.f = n;
    x.i = drwav__bswap64(x.i);

    return x.f;
}

static DRWAV_INLINE void drwav__bswap_samples_f64(double* pSamples, drwav_uint64 sampleCount)
{
    drwav_uint64 iSample;
    for (iSample = 0; iSample < sampleCount; iSample += 1) {
        pSamples[iSample] = drwav__bswap_f64(pSamples[iSample]);
    }
}


static DRWAV_INLINE void drwav__bswap_samples_pcm(void* pSamples, drwav_uint64 sampleCount, drwav_uint32 bytesPerSample)
{
    /* Assumes integer PCM. Floating point PCM is done in drwav__bswap_samples_ieee(). */
    switch (bytesPerSample)
    {
        case 2: /* s16, s12 (loosely packed) */
        {
            drwav__bswap_samples_s16((drwav_int16*)pSamples, sampleCount);
        } break;
        case 3: /* s24 */
        {
            drwav__bswap_samples_s24((drwav_uint8*)pSamples, sampleCount);
        } break;
        case 4: /* s32 */
        {
            drwav__bswap_samples_s32((drwav_int32*)pSamples, sampleCount);
        } break;
        default:
        {
            /* Unsupported format. */
            DRWAV_ASSERT(DRWAV_FALSE);
        } break;
    }
}

static DRWAV_INLINE void drwav__bswap_samples_ieee(void* pSamples, drwav_uint64 sampleCount, drwav_uint32 bytesPerSample)
{
    switch (bytesPerSample)
    {
    #if 0   /* Contributions welcome for f16 support. */
        case 2: /* f16 */
        {
            drwav__bswap_samples_f16((drwav_float16*)pSamples, sampleCount);
        } break;
    #endif
        case 4: /* f32 */
        {
            drwav__bswap_samples_f32((float*)pSamples, sampleCount);
        } break;
        case 8: /* f64 */
        {
            drwav__bswap_samples_f64((double*)pSamples, sampleCount);
        } break;
        default:
        {
            /* Unsupported format. */
            DRWAV_ASSERT(DRWAV_FALSE);
        } break;
    }
}

static DRWAV_INLINE void drwav__bswap_samples(void* pSamples, drwav_uint64 sampleCount, drwav_uint32 bytesPerSample, drwav_uint16 format)
{
    switch (format)
    {
        case DR_WAVE_FORMAT_PCM:
        {
            drwav__bswap_samples_pcm(pSamples, sampleCount, bytesPerSample);
        } break;

        case DR_WAVE_FORMAT_IEEE_FLOAT:
        {
            drwav__bswap_samples_ieee(pSamples, sampleCount, bytesPerSample);
        } break;

        case DR_WAVE_FORMAT_ALAW:
        case DR_WAVE_FORMAT_MULAW:
        {
            drwav__bswap_samples_s16((drwav_int16*)pSamples, sampleCount);
        } break;

        case DR_WAVE_FORMAT_ADPCM:
        case DR_WAVE_FORMAT_DVI_ADPCM:
        default:
        {
            /* Unsupported format. */
            DRWAV_ASSERT(DRWAV_FALSE);
        } break;
    }
}


static void* drwav__malloc_default(size_t sz, void* pUserData)
{
    (void)pUserData;
    return DRWAV_MALLOC(sz);
}

static void* drwav__realloc_default(void* p, size_t sz, void* pUserData)
{
    (void)pUserData;
    return DRWAV_REALLOC(p, sz);
}

static void drwav__free_default(void* p, void* pUserData)
{
    (void)pUserData;
    DRWAV_FREE(p);
}


static void* drwav__malloc_from_callbacks(size_t sz, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    if (pAllocationCallbacks == NULL) {
        return NULL;
    }

    if (pAllocationCallbacks->onMalloc != NULL) {
        return pAllocationCallbacks->onMalloc(sz, pAllocationCallbacks->pUserData);
    }

    /* Try using realloc(). */
    if (pAllocationCallbacks->onRealloc != NULL) {
        return pAllocationCallbacks->onRealloc(NULL, sz, pAllocationCallbacks->pUserData);
    }

    return NULL;
}

static void* drwav__realloc_from_callbacks(void* p, size_t szNew, size_t szOld, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    if (pAllocationCallbacks == NULL) {
        return NULL;
    }

    if (pAllocationCallbacks->onRealloc != NULL) {
        return pAllocationCallbacks->onRealloc(p, szNew, pAllocationCallbacks->pUserData);
    }

    /* Try emulating realloc() in terms of malloc()/free(). */
    if (pAllocationCallbacks->onMalloc != NULL && pAllocationCallbacks->onFree != NULL) {
        void* p2;

        p2 = pAllocationCallbacks->onMalloc(szNew, pAllocationCallbacks->pUserData);
        if (p2 == NULL) {
            return NULL;
        }

        if (p != NULL) {
            DRWAV_COPY_MEMORY(p2, p, szOld);
            pAllocationCallbacks->onFree(p, pAllocationCallbacks->pUserData);
        }

        return p2;
    }

    return NULL;
}

static void drwav__free_from_callbacks(void* p, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    if (p == NULL || pAllocationCallbacks == NULL) {
        return;
    }

    if (pAllocationCallbacks->onFree != NULL) {
        pAllocationCallbacks->onFree(p, pAllocationCallbacks->pUserData);
    }
}


static drwav_allocation_callbacks drwav_copy_allocation_callbacks_or_defaults(const drwav_allocation_callbacks* pAllocationCallbacks)
{
    if (pAllocationCallbacks != NULL) {
        /* Copy. */
        return *pAllocationCallbacks;
    } else {
        /* Defaults. */
        drwav_allocation_callbacks allocationCallbacks;
        allocationCallbacks.pUserData = NULL;
        allocationCallbacks.onMalloc  = drwav__malloc_default;
        allocationCallbacks.onRealloc = drwav__realloc_default;
        allocationCallbacks.onFree    = drwav__free_default;
        return allocationCallbacks;
    }
}


static DRWAV_INLINE drwav_bool32 drwav__is_compressed_format_tag(drwav_uint16 formatTag)
{
    return
        formatTag == DR_WAVE_FORMAT_ADPCM ||
        formatTag == DR_WAVE_FORMAT_DVI_ADPCM;
}

static unsigned int drwav__chunk_padding_size_riff(drwav_uint64 chunkSize)
{
    return (unsigned int)(chunkSize % 2);
}

static unsigned int drwav__chunk_padding_size_w64(drwav_uint64 chunkSize)
{
    return (unsigned int)(chunkSize % 8);
}

static drwav_uint64 drwav_read_pcm_frames_s16__msadpcm(drwav* pWav, drwav_uint64 samplesToRead, drwav_int16* pBufferOut);
static drwav_uint64 drwav_read_pcm_frames_s16__ima(drwav* pWav, drwav_uint64 samplesToRead, drwav_int16* pBufferOut);
static drwav_bool32 drwav_init_write__internal(drwav* pWav, const drwav_data_format* pFormat, drwav_uint64 totalSampleCount);

static drwav_result drwav__read_chunk_header(drwav_read_proc onRead, void* pUserData, drwav_container container, drwav_uint64* pRunningBytesReadOut, drwav_chunk_header* pHeaderOut)
{
    if (container == drwav_container_riff) {
        drwav_uint8 sizeInBytes[4];

        if (onRead(pUserData, pHeaderOut->id.fourcc, 4) != 4) {
            return DRWAV_AT_END;
        }

        if (onRead(pUserData, sizeInBytes, 4) != 4) {
            return DRWAV_INVALID_FILE;
        }

        pHeaderOut->sizeInBytes = drwav__bytes_to_u32(sizeInBytes);
        pHeaderOut->paddingSize = drwav__chunk_padding_size_riff(pHeaderOut->sizeInBytes);
        *pRunningBytesReadOut += 8;
    } else {
        drwav_uint8 sizeInBytes[8];

        if (onRead(pUserData, pHeaderOut->id.guid, 16) != 16) {
            return DRWAV_AT_END;
        }

        if (onRead(pUserData, sizeInBytes, 8) != 8) {
            return DRWAV_INVALID_FILE;
        }

        pHeaderOut->sizeInBytes = drwav__bytes_to_u64(sizeInBytes) - 24;    /* <-- Subtract 24 because w64 includes the size of the header. */
        pHeaderOut->paddingSize = drwav__chunk_padding_size_w64(pHeaderOut->sizeInBytes);
        *pRunningBytesReadOut += 24;
    }

    return DRWAV_SUCCESS;
}

static drwav_bool32 drwav__seek_forward(drwav_seek_proc onSeek, drwav_uint64 offset, void* pUserData)
{
    drwav_uint64 bytesRemainingToSeek = offset;
    while (bytesRemainingToSeek > 0) {
        if (bytesRemainingToSeek > 0x7FFFFFFF) {
            if (!onSeek(pUserData, 0x7FFFFFFF, drwav_seek_origin_current)) {
                return DRWAV_FALSE;
            }
            bytesRemainingToSeek -= 0x7FFFFFFF;
        } else {
            if (!onSeek(pUserData, (int)bytesRemainingToSeek, drwav_seek_origin_current)) {
                return DRWAV_FALSE;
            }
            bytesRemainingToSeek = 0;
        }
    }

    return DRWAV_TRUE;
}

static drwav_bool32 drwav__seek_from_start(drwav_seek_proc onSeek, drwav_uint64 offset, void* pUserData)
{
    if (offset <= 0x7FFFFFFF) {
        return onSeek(pUserData, (int)offset, drwav_seek_origin_start);
    }

    /* Larger than 32-bit seek. */
    if (!onSeek(pUserData, 0x7FFFFFFF, drwav_seek_origin_start)) {
        return DRWAV_FALSE;
    }
    offset -= 0x7FFFFFFF;

    for (;;) {
        if (offset <= 0x7FFFFFFF) {
            return onSeek(pUserData, (int)offset, drwav_seek_origin_current);
        }

        if (!onSeek(pUserData, 0x7FFFFFFF, drwav_seek_origin_current)) {
            return DRWAV_FALSE;
        }
        offset -= 0x7FFFFFFF;
    }

    /* Should never get here. */
    /*return DRWAV_TRUE; */
}


static drwav_bool32 drwav__read_fmt(drwav_read_proc onRead, drwav_seek_proc onSeek, void* pUserData, drwav_container container, drwav_uint64* pRunningBytesReadOut, drwav_fmt* fmtOut)
{
    drwav_chunk_header header;
    drwav_uint8 fmt[16];

    if (drwav__read_chunk_header(onRead, pUserData, container, pRunningBytesReadOut, &header) != DRWAV_SUCCESS) {
        return DRWAV_FALSE;
    }


    /* Skip non-fmt chunks. */
    while ((container == drwav_container_riff && !drwav__fourcc_equal(header.id.fourcc, "fmt ")) || (container == drwav_container_w64 && !drwav__guid_equal(header.id.guid, drwavGUID_W64_FMT))) {
        if (!drwav__seek_forward(onSeek, header.sizeInBytes + header.paddingSize, pUserData)) {
            return DRWAV_FALSE;
        }
        *pRunningBytesReadOut += header.sizeInBytes + header.paddingSize;

        /* Try the next header. */
        if (drwav__read_chunk_header(onRead, pUserData, container, pRunningBytesReadOut, &header) != DRWAV_SUCCESS) {
            return DRWAV_FALSE;
        }
    }


    /* Validation. */
    if (container == drwav_container_riff) {
        if (!drwav__fourcc_equal(header.id.fourcc, "fmt ")) {
            return DRWAV_FALSE;
        }
    } else {
        if (!drwav__guid_equal(header.id.guid, drwavGUID_W64_FMT)) {
            return DRWAV_FALSE;
        }
    }


    if (onRead(pUserData, fmt, sizeof(fmt)) != sizeof(fmt)) {
        return DRWAV_FALSE;
    }
    *pRunningBytesReadOut += sizeof(fmt);

    fmtOut->formatTag      = drwav__bytes_to_u16(fmt + 0);
    fmtOut->channels       = drwav__bytes_to_u16(fmt + 2);
    fmtOut->sampleRate     = drwav__bytes_to_u32(fmt + 4);
    fmtOut->avgBytesPerSec = drwav__bytes_to_u32(fmt + 8);
    fmtOut->blockAlign     = drwav__bytes_to_u16(fmt + 12);
    fmtOut->bitsPerSample  = drwav__bytes_to_u16(fmt + 14);

    fmtOut->extendedSize       = 0;
    fmtOut->validBitsPerSample = 0;
    fmtOut->channelMask        = 0;
    memset(fmtOut->subFormat, 0, sizeof(fmtOut->subFormat));

    if (header.sizeInBytes > 16) {
        drwav_uint8 fmt_cbSize[2];
        int bytesReadSoFar = 0;

        if (onRead(pUserData, fmt_cbSize, sizeof(fmt_cbSize)) != sizeof(fmt_cbSize)) {
            return DRWAV_FALSE;    /* Expecting more data. */
        }
        *pRunningBytesReadOut += sizeof(fmt_cbSize);

        bytesReadSoFar = 18;

        fmtOut->extendedSize = drwav__bytes_to_u16(fmt_cbSize);
        if (fmtOut->extendedSize > 0) {
            /* Simple validation. */
            if (fmtOut->formatTag == DR_WAVE_FORMAT_EXTENSIBLE) {
                if (fmtOut->extendedSize != 22) {
                    return DRWAV_FALSE;
                }
            }

            if (fmtOut->formatTag == DR_WAVE_FORMAT_EXTENSIBLE) {
                drwav_uint8 fmtext[22];
                if (onRead(pUserData, fmtext, fmtOut->extendedSize) != fmtOut->extendedSize) {
                    return DRWAV_FALSE;    /* Expecting more data. */
                }

                fmtOut->validBitsPerSample = drwav__bytes_to_u16(fmtext + 0);
                fmtOut->channelMask        = drwav__bytes_to_u32(fmtext + 2);
                drwav__bytes_to_guid(fmtext + 6, fmtOut->subFormat);
            } else {
                if (!onSeek(pUserData, fmtOut->extendedSize, drwav_seek_origin_current)) {
                    return DRWAV_FALSE;
                }
            }
            *pRunningBytesReadOut += fmtOut->extendedSize;

            bytesReadSoFar += fmtOut->extendedSize;
        }

        /* Seek past any leftover bytes. For w64 the leftover will be defined based on the chunk size. */
        if (!onSeek(pUserData, (int)(header.sizeInBytes - bytesReadSoFar), drwav_seek_origin_current)) {
            return DRWAV_FALSE;
        }
        *pRunningBytesReadOut += (header.sizeInBytes - bytesReadSoFar);
    }

    if (header.paddingSize > 0) {
        if (!onSeek(pUserData, header.paddingSize, drwav_seek_origin_current)) {
            return DRWAV_FALSE;
        }
        *pRunningBytesReadOut += header.paddingSize;
    }

    return DRWAV_TRUE;
}


static size_t drwav__on_read(drwav_read_proc onRead, void* pUserData, void* pBufferOut, size_t bytesToRead, drwav_uint64* pCursor)
{
    size_t bytesRead;

    DRWAV_ASSERT(onRead != NULL);
    DRWAV_ASSERT(pCursor != NULL);

    bytesRead = onRead(pUserData, pBufferOut, bytesToRead);
    *pCursor += bytesRead;
    return bytesRead;
}

#if 0
static drwav_bool32 drwav__on_seek(drwav_seek_proc onSeek, void* pUserData, int offset, drwav_seek_origin origin, drwav_uint64* pCursor)
{
    DRWAV_ASSERT(onSeek != NULL);
    DRWAV_ASSERT(pCursor != NULL);

    if (!onSeek(pUserData, offset, origin)) {
        return DRWAV_FALSE;
    }

    if (origin == drwav_seek_origin_start) {
        *pCursor = offset;
    } else {
        *pCursor += offset;
    }

    return DRWAV_TRUE;
}
#endif



static drwav_uint32 drwav_get_bytes_per_pcm_frame(drwav* pWav)
{
    /*
    The bytes per frame is a bit ambiguous. It can be either be based on the bits per sample, or the block align. The way I'm doing it here
    is that if the bits per sample is a multiple of 8, use floor(bitsPerSample*channels/8), otherwise fall back to the block align.
    */
    if ((pWav->bitsPerSample & 0x7) == 0) {
        /* Bits per sample is a multiple of 8. */
        return (pWav->bitsPerSample * pWav->fmt.channels) >> 3;
    } else {
        return pWav->fmt.blockAlign;
    }
}

DRWAV_API drwav_uint16 drwav_fmt_get_format(const drwav_fmt* pFMT)
{
    if (pFMT == NULL) {
        return 0;
    }

    if (pFMT->formatTag != DR_WAVE_FORMAT_EXTENSIBLE) {
        return pFMT->formatTag;
    } else {
        return drwav__bytes_to_u16(pFMT->subFormat);    /* Only the first two bytes are required. */
    }
}

static drwav_bool32 drwav_preinit(drwav* pWav, drwav_read_proc onRead, drwav_seek_proc onSeek, void* pReadSeekUserData, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    if (pWav == NULL || onRead == NULL || onSeek == NULL) {
        return DRWAV_FALSE;
    }

    DRWAV_ZERO_MEMORY(pWav, sizeof(*pWav));
    pWav->onRead    = onRead;
    pWav->onSeek    = onSeek;
    pWav->pUserData = pReadSeekUserData;
    pWav->allocationCallbacks = drwav_copy_allocation_callbacks_or_defaults(pAllocationCallbacks);

    if (pWav->allocationCallbacks.onFree == NULL || (pWav->allocationCallbacks.onMalloc == NULL && pWav->allocationCallbacks.onRealloc == NULL)) {
        return DRWAV_FALSE;    /* Invalid allocation callbacks. */
    }

    return DRWAV_TRUE;
}

static drwav_bool32 drwav_init__internal(drwav* pWav, drwav_chunk_proc onChunk, void* pChunkUserData, drwav_uint32 flags)
{
    /* This function assumes drwav_preinit() has been called beforehand. */

    drwav_uint64 cursor;    /* <-- Keeps track of the byte position so we can seek to specific locations. */
    drwav_bool32 sequential;
    drwav_uint8 riff[4];
    drwav_fmt fmt;
    unsigned short translatedFormatTag;
    drwav_uint64 sampleCountFromFactChunk;
    drwav_bool32 foundDataChunk;
    drwav_uint64 dataChunkSize;
    drwav_uint64 chunkSize;

    cursor = 0;
    sequential = (flags & DRWAV_SEQUENTIAL) != 0;

    /* The first 4 bytes should be the RIFF identifier. */
    if (drwav__on_read(pWav->onRead, pWav->pUserData, riff, sizeof(riff), &cursor) != sizeof(riff)) {
        return DRWAV_FALSE;
    }

    /*
    The first 4 bytes can be used to identify the container. For RIFF files it will start with "RIFF" and for
    w64 it will start with "riff".
    */
    if (drwav__fourcc_equal(riff, "RIFF")) {
        pWav->container = drwav_container_riff;
    } else if (drwav__fourcc_equal(riff, "riff")) {
        int i;
        drwav_uint8 riff2[12];

        pWav->container = drwav_container_w64;

        /* Check the rest of the GUID for validity. */
        if (drwav__on_read(pWav->onRead, pWav->pUserData, riff2, sizeof(riff2), &cursor) != sizeof(riff2)) {
            return DRWAV_FALSE;
        }

        for (i = 0; i < 12; ++i) {
            if (riff2[i] != drwavGUID_W64_RIFF[i+4]) {
                return DRWAV_FALSE;
            }
        }
    } else {
        return DRWAV_FALSE;   /* Unknown or unsupported container. */
    }


    if (pWav->container == drwav_container_riff) {
        drwav_uint8 chunkSizeBytes[4];
        drwav_uint8 wave[4];

        /* RIFF/WAVE */
        if (drwav__on_read(pWav->onRead, pWav->pUserData, chunkSizeBytes, sizeof(chunkSizeBytes), &cursor) != sizeof(chunkSizeBytes)) {
            return DRWAV_FALSE;
        }

        if (drwav__bytes_to_u32(chunkSizeBytes) < 36) {
            return DRWAV_FALSE;    /* Chunk size should always be at least 36 bytes. */
        }

        if (drwav__on_read(pWav->onRead, pWav->pUserData, wave, sizeof(wave), &cursor) != sizeof(wave)) {
            return DRWAV_FALSE;
        }

        if (!drwav__fourcc_equal(wave, "WAVE")) {
            return DRWAV_FALSE;    /* Expecting "WAVE". */
        }
    } else {
        drwav_uint8 chunkSizeBytes[8];
        drwav_uint8 wave[16];

        /* W64 */
        if (drwav__on_read(pWav->onRead, pWav->pUserData, chunkSizeBytes, sizeof(chunkSizeBytes), &cursor) != sizeof(chunkSizeBytes)) {
            return DRWAV_FALSE;
        }

        if (drwav__bytes_to_u64(chunkSizeBytes) < 80) {
            return DRWAV_FALSE;
        }

        if (drwav__on_read(pWav->onRead, pWav->pUserData, wave, sizeof(wave), &cursor) != sizeof(wave)) {
            return DRWAV_FALSE;
        }

        if (!drwav__guid_equal(wave, drwavGUID_W64_WAVE)) {
            return DRWAV_FALSE;
        }
    }


    /* The next bytes should be the "fmt " chunk. */
    if (!drwav__read_fmt(pWav->onRead, pWav->onSeek, pWav->pUserData, pWav->container, &cursor, &fmt)) {
        return DRWAV_FALSE;    /* Failed to read the "fmt " chunk. */
    }

    /* Basic validation. */
    if ((fmt.sampleRate    == 0 || fmt.sampleRate    > DRWAV_MAX_SAMPLE_RATE)     ||
        (fmt.channels      == 0 || fmt.channels      > DRWAV_MAX_CHANNELS)        ||
        (fmt.bitsPerSample == 0 || fmt.bitsPerSample > DRWAV_MAX_BITS_PER_SAMPLE) ||
        fmt.blockAlign == 0) {
        return DRWAV_FALSE; /* Probably an invalid WAV file. */
    }


    /* Translate the internal format. */
    translatedFormatTag = fmt.formatTag;
    if (translatedFormatTag == DR_WAVE_FORMAT_EXTENSIBLE) {
        translatedFormatTag = drwav__bytes_to_u16(fmt.subFormat + 0);
    }



    sampleCountFromFactChunk = 0;

    /*
    We need to enumerate over each chunk for two reasons:
      1) The "data" chunk may not be the next one
      2) We may want to report each chunk back to the client
    
    In order to correctly report each chunk back to the client we will need to keep looping until the end of the file.
    */
    foundDataChunk = DRWAV_FALSE;
    dataChunkSize = 0;

    /* The next chunk we care about is the "data" chunk. This is not necessarily the next chunk so we'll need to loop. */
    for (;;)
    {
        drwav_chunk_header header;
        drwav_result result = drwav__read_chunk_header(pWav->onRead, pWav->pUserData, pWav->container, &cursor, &header);
        if (result != DRWAV_SUCCESS) {
            if (!foundDataChunk) {
                return DRWAV_FALSE;
            } else {
                break;  /* Probably at the end of the file. Get out of the loop. */
            }
        }

        /* Tell the client about this chunk. */
        if (!sequential && onChunk != NULL) {
            drwav_uint64 callbackBytesRead = onChunk(pChunkUserData, pWav->onRead, pWav->onSeek, pWav->pUserData, &header, pWav->container, &fmt);

            /*
            dr_wav may need to read the contents of the chunk, so we now need to seek back to the position before
            we called the callback.
            */
            if (callbackBytesRead > 0) {
                if (!drwav__seek_from_start(pWav->onSeek, cursor, pWav->pUserData)) {
                    return DRWAV_FALSE;
                }
            }
        }
        

        if (!foundDataChunk) {
            pWav->dataChunkDataPos = cursor;
        }

        chunkSize = header.sizeInBytes;
        if (pWav->container == drwav_container_riff) {
            if (drwav__fourcc_equal(header.id.fourcc, "data")) {
                foundDataChunk = DRWAV_TRUE;
                dataChunkSize = chunkSize;
            }
        } else {
            if (drwav__guid_equal(header.id.guid, drwavGUID_W64_DATA)) {
                foundDataChunk = DRWAV_TRUE;
                dataChunkSize = chunkSize;
            }
        }

        /*
        If at this point we have found the data chunk and we're running in sequential mode, we need to break out of this loop. The reason for
        this is that we would otherwise require a backwards seek which sequential mode forbids.
        */
        if (foundDataChunk && sequential) {
            break;
        }

        /* Optional. Get the total sample count from the FACT chunk. This is useful for compressed formats. */
        if (pWav->container == drwav_container_riff) {
            if (drwav__fourcc_equal(header.id.fourcc, "fact")) {
                drwav_uint32 sampleCount;
                if (drwav__on_read(pWav->onRead, pWav->pUserData, &sampleCount, 4, &cursor) != 4) {
                    return DRWAV_FALSE;
                }
                chunkSize -= 4;

                if (!foundDataChunk) {
                    pWav->dataChunkDataPos = cursor;
                }

                /*
                The sample count in the "fact" chunk is either unreliable, or I'm not understanding it properly. For now I am only enabling this
                for Microsoft ADPCM formats.
                */
                if (pWav->translatedFormatTag == DR_WAVE_FORMAT_ADPCM) {
                    sampleCountFromFactChunk = sampleCount;
                } else {
                    sampleCountFromFactChunk = 0;
                }
            }
        } else {
            if (drwav__guid_equal(header.id.guid, drwavGUID_W64_FACT)) {
                if (drwav__on_read(pWav->onRead, pWav->pUserData, &sampleCountFromFactChunk, 8, &cursor) != 8) {
                    return DRWAV_FALSE;
                }
                chunkSize -= 8;

                if (!foundDataChunk) {
                    pWav->dataChunkDataPos = cursor;
                }
            }
        }

        /* "smpl" chunk. */
        if (pWav->container == drwav_container_riff) {
            if (drwav__fourcc_equal(header.id.fourcc, "smpl")) {
                drwav_uint8 smplHeaderData[36];    /* 36 = size of the smpl header section, not including the loop data. */
                if (chunkSize >= sizeof(smplHeaderData)) {
                    drwav_uint64 bytesJustRead = drwav__on_read(pWav->onRead, pWav->pUserData, smplHeaderData, sizeof(smplHeaderData), &cursor);
                    chunkSize -= bytesJustRead;

                    if (bytesJustRead == sizeof(smplHeaderData)) {
                        drwav_uint32 iLoop;

                        pWav->smpl.manufacturer      = drwav__bytes_to_u32(smplHeaderData+0);
                        pWav->smpl.product           = drwav__bytes_to_u32(smplHeaderData+4);
                        pWav->smpl.samplePeriod      = drwav__bytes_to_u32(smplHeaderData+8);
                        pWav->smpl.midiUnityNotes    = drwav__bytes_to_u32(smplHeaderData+12);
                        pWav->smpl.midiPitchFraction = drwav__bytes_to_u32(smplHeaderData+16);
                        pWav->smpl.smpteFormat       = drwav__bytes_to_u32(smplHeaderData+20);
                        pWav->smpl.smpteOffset       = drwav__bytes_to_u32(smplHeaderData+24);
                        pWav->smpl.numSampleLoops    = drwav__bytes_to_u32(smplHeaderData+28);
                        pWav->smpl.samplerData       = drwav__bytes_to_u32(smplHeaderData+32);

                        for (iLoop = 0; iLoop < pWav->smpl.numSampleLoops && iLoop < drwav_countof(pWav->smpl.loops); ++iLoop) {
                            drwav_uint8 smplLoopData[24];  /* 24 = size of a loop section in the smpl chunk. */
                            bytesJustRead = drwav__on_read(pWav->onRead, pWav->pUserData, smplLoopData, sizeof(smplLoopData), &cursor);
                            chunkSize -= bytesJustRead;

                            if (bytesJustRead == sizeof(smplLoopData)) {
                                pWav->smpl.loops[iLoop].cuePointId = drwav__bytes_to_u32(smplLoopData+0);
                                pWav->smpl.loops[iLoop].type       = drwav__bytes_to_u32(smplLoopData+4);
                                pWav->smpl.loops[iLoop].start      = drwav__bytes_to_u32(smplLoopData+8);
                                pWav->smpl.loops[iLoop].end        = drwav__bytes_to_u32(smplLoopData+12);
                                pWav->smpl.loops[iLoop].fraction   = drwav__bytes_to_u32(smplLoopData+16);
                                pWav->smpl.loops[iLoop].playCount  = drwav__bytes_to_u32(smplLoopData+20);
                            } else {
                                break;  /* Break from the smpl loop for loop. */
                            }
                        }
                    }
                } else {
                    /* Looks like invalid data. Ignore the chunk. */
                }
            }
        } else {
            if (drwav__guid_equal(header.id.guid, drwavGUID_W64_SMPL)) {
                /*
                This path will be hit when a W64 WAV file contains a smpl chunk. I don't have a sample file to test this path, so a contribution
                is welcome to add support for this.
                */
            }
        }

        /* Make sure we seek past the padding. */
        chunkSize += header.paddingSize;
        if (!drwav__seek_forward(pWav->onSeek, chunkSize, pWav->pUserData)) {
            break;
        }
        cursor += chunkSize;

        if (!foundDataChunk) {
            pWav->dataChunkDataPos = cursor;
        }
    }

    /* If we haven't found a data chunk, return an error. */
    if (!foundDataChunk) {
        return DRWAV_FALSE;
    }

    /* We may have moved passed the data chunk. If so we need to move back. If running in sequential mode we can assume we are already sitting on the data chunk. */
    if (!sequential) {
        if (!drwav__seek_from_start(pWav->onSeek, pWav->dataChunkDataPos, pWav->pUserData)) {
            return DRWAV_FALSE;
        }
        cursor = pWav->dataChunkDataPos;
    }
    

    /* At this point we should be sitting on the first byte of the raw audio data. */

    pWav->fmt                 = fmt;
    pWav->sampleRate          = fmt.sampleRate;
    pWav->channels            = fmt.channels;
    pWav->bitsPerSample       = fmt.bitsPerSample;
    pWav->bytesRemaining      = dataChunkSize;
    pWav->translatedFormatTag = translatedFormatTag;
    pWav->dataChunkDataSize   = dataChunkSize;

    if (sampleCountFromFactChunk != 0) {
        pWav->totalPCMFrameCount = sampleCountFromFactChunk;
    } else {
        pWav->totalPCMFrameCount = dataChunkSize / drwav_get_bytes_per_pcm_frame(pWav);

        if (pWav->translatedFormatTag == DR_WAVE_FORMAT_ADPCM) {
            drwav_uint64 totalBlockHeaderSizeInBytes;
            drwav_uint64 blockCount = dataChunkSize / fmt.blockAlign;

            /* Make sure any trailing partial block is accounted for. */
            if ((blockCount * fmt.blockAlign) < dataChunkSize) {
                blockCount += 1;
            }

            /* We decode two samples per byte. There will be blockCount headers in the data chunk. This is enough to know how to calculate the total PCM frame count. */
            totalBlockHeaderSizeInBytes = blockCount * (6*fmt.channels);
            pWav->totalPCMFrameCount = ((dataChunkSize - totalBlockHeaderSizeInBytes) * 2) / fmt.channels;
        }
        if (pWav->translatedFormatTag == DR_WAVE_FORMAT_DVI_ADPCM) {
            drwav_uint64 totalBlockHeaderSizeInBytes;
            drwav_uint64 blockCount = dataChunkSize / fmt.blockAlign;

            /* Make sure any trailing partial block is accounted for. */
            if ((blockCount * fmt.blockAlign) < dataChunkSize) {
                blockCount += 1;
            }

            /* We decode two samples per byte. There will be blockCount headers in the data chunk. This is enough to know how to calculate the total PCM frame count. */
            totalBlockHeaderSizeInBytes = blockCount * (4*fmt.channels);
            pWav->totalPCMFrameCount = ((dataChunkSize - totalBlockHeaderSizeInBytes) * 2) / fmt.channels;

            /* The header includes a decoded sample for each channel which acts as the initial predictor sample. */
            pWav->totalPCMFrameCount += blockCount;
        }
    }

    /* Some formats only support a certain number of channels. */
    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_ADPCM || pWav->translatedFormatTag == DR_WAVE_FORMAT_DVI_ADPCM) {
        if (pWav->channels > 2) {
            return DRWAV_FALSE;
        }
    }

#ifdef DR_WAV_LIBSNDFILE_COMPAT
    /*
    I use libsndfile as a benchmark for testing, however in the version I'm using (from the Windows installer on the libsndfile website),
    it appears the total sample count libsndfile uses for MS-ADPCM is incorrect. It would seem they are computing the total sample count
    from the number of blocks, however this results in the inclusion of extra silent samples at the end of the last block. The correct
    way to know the total sample count is to inspect the "fact" chunk, which should always be present for compressed formats, and should
    always include the sample count. This little block of code below is only used to emulate the libsndfile logic so I can properly run my
    correctness tests against libsndfile, and is disabled by default.
    */
    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_ADPCM) {
        drwav_uint64 blockCount = dataChunkSize / fmt.blockAlign;
        pWav->totalPCMFrameCount = (((blockCount * (fmt.blockAlign - (6*pWav->channels))) * 2)) / fmt.channels;  /* x2 because two samples per byte. */
    }
    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_DVI_ADPCM) {
        drwav_uint64 blockCount = dataChunkSize / fmt.blockAlign;
        pWav->totalPCMFrameCount = (((blockCount * (fmt.blockAlign - (4*pWav->channels))) * 2) + (blockCount * pWav->channels)) / fmt.channels;
    }
#endif

    return DRWAV_TRUE;
}

DRWAV_API drwav_bool32 drwav_init(drwav* pWav, drwav_read_proc onRead, drwav_seek_proc onSeek, void* pUserData, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    return drwav_init_ex(pWav, onRead, onSeek, NULL, pUserData, NULL, 0, pAllocationCallbacks);
}

DRWAV_API drwav_bool32 drwav_init_ex(drwav* pWav, drwav_read_proc onRead, drwav_seek_proc onSeek, drwav_chunk_proc onChunk, void* pReadSeekUserData, void* pChunkUserData, drwav_uint32 flags, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    if (!drwav_preinit(pWav, onRead, onSeek, pReadSeekUserData, pAllocationCallbacks)) {
        return DRWAV_FALSE;
    }

    return drwav_init__internal(pWav, onChunk, pChunkUserData, flags);
}


static drwav_uint32 drwav__riff_chunk_size_riff(drwav_uint64 dataChunkSize)
{
    drwav_uint32 dataSubchunkPaddingSize = drwav__chunk_padding_size_riff(dataChunkSize);

    if (dataChunkSize <= (0xFFFFFFFFUL - 36 - dataSubchunkPaddingSize)) {
        return 36 + (drwav_uint32)(dataChunkSize + dataSubchunkPaddingSize);
    } else {
        return 0xFFFFFFFF;
    }
}

static drwav_uint32 drwav__data_chunk_size_riff(drwav_uint64 dataChunkSize)
{
    if (dataChunkSize <= 0xFFFFFFFFUL) {
        return (drwav_uint32)dataChunkSize;
    } else {
        return 0xFFFFFFFFUL;
    }
}

static drwav_uint64 drwav__riff_chunk_size_w64(drwav_uint64 dataChunkSize)
{
    drwav_uint64 dataSubchunkPaddingSize = drwav__chunk_padding_size_w64(dataChunkSize);

    return 80 + 24 + dataChunkSize + dataSubchunkPaddingSize;   /* +24 because W64 includes the size of the GUID and size fields. */
}

static drwav_uint64 drwav__data_chunk_size_w64(drwav_uint64 dataChunkSize)
{
    return 24 + dataChunkSize;        /* +24 because W64 includes the size of the GUID and size fields. */
}


static size_t drwav__write(drwav* pWav, const void* pData, size_t dataSize)
{
    DRWAV_ASSERT(pWav          != NULL);
    DRWAV_ASSERT(pWav->onWrite != NULL);

    /* Generic write. Assumes no byte reordering required. */
    return pWav->onWrite(pWav->pUserData, pData, dataSize);
}

static size_t drwav__write_u16ne_to_le(drwav* pWav, drwav_uint16 value)
{
    DRWAV_ASSERT(pWav          != NULL);
    DRWAV_ASSERT(pWav->onWrite != NULL);

    if (!drwav__is_little_endian()) {
        value = drwav__bswap16(value);
    }

    return drwav__write(pWav, &value, 2);
}

static size_t drwav__write_u32ne_to_le(drwav* pWav, drwav_uint32 value)
{
    DRWAV_ASSERT(pWav          != NULL);
    DRWAV_ASSERT(pWav->onWrite != NULL);

    if (!drwav__is_little_endian()) {
        value = drwav__bswap32(value);
    }

    return drwav__write(pWav, &value, 4);
}

static size_t drwav__write_u64ne_to_le(drwav* pWav, drwav_uint64 value)
{
    DRWAV_ASSERT(pWav          != NULL);
    DRWAV_ASSERT(pWav->onWrite != NULL);

    if (!drwav__is_little_endian()) {
        value = drwav__bswap64(value);
    }

    return drwav__write(pWav, &value, 8);
}


static drwav_bool32 drwav_preinit_write(drwav* pWav, const drwav_data_format* pFormat, drwav_bool32 isSequential, drwav_write_proc onWrite, drwav_seek_proc onSeek, void* pUserData, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    if (pWav == NULL || onWrite == NULL) {
        return DRWAV_FALSE;
    }

    if (!isSequential && onSeek == NULL) {
        return DRWAV_FALSE; /* <-- onSeek is required when in non-sequential mode. */
    }

    /* Not currently supporting compressed formats. Will need to add support for the "fact" chunk before we enable this. */
    if (pFormat->format == DR_WAVE_FORMAT_EXTENSIBLE) {
        return DRWAV_FALSE;
    }
    if (pFormat->format == DR_WAVE_FORMAT_ADPCM || pFormat->format == DR_WAVE_FORMAT_DVI_ADPCM) {
        return DRWAV_FALSE;
    }

    DRWAV_ZERO_MEMORY(pWav, sizeof(*pWav));
    pWav->onWrite   = onWrite;
    pWav->onSeek    = onSeek;
    pWav->pUserData = pUserData;
    pWav->allocationCallbacks = drwav_copy_allocation_callbacks_or_defaults(pAllocationCallbacks);

    if (pWav->allocationCallbacks.onFree == NULL || (pWav->allocationCallbacks.onMalloc == NULL && pWav->allocationCallbacks.onRealloc == NULL)) {
        return DRWAV_FALSE;    /* Invalid allocation callbacks. */
    }

    pWav->fmt.formatTag = (drwav_uint16)pFormat->format;
    pWav->fmt.channels = (drwav_uint16)pFormat->channels;
    pWav->fmt.sampleRate = pFormat->sampleRate;
    pWav->fmt.avgBytesPerSec = (drwav_uint32)((pFormat->bitsPerSample * pFormat->sampleRate * pFormat->channels) / 8);
    pWav->fmt.blockAlign = (drwav_uint16)((pFormat->channels * pFormat->bitsPerSample) / 8);
    pWav->fmt.bitsPerSample = (drwav_uint16)pFormat->bitsPerSample;
    pWav->fmt.extendedSize = 0;
    pWav->isSequentialWrite = isSequential;

    return DRWAV_TRUE;
}

static drwav_bool32 drwav_init_write__internal(drwav* pWav, const drwav_data_format* pFormat, drwav_uint64 totalSampleCount)
{
    /* The function assumes drwav_preinit_write() was called beforehand. */

    size_t runningPos = 0;
    drwav_uint64 initialDataChunkSize = 0;
    drwav_uint64 chunkSizeFMT;

    /*
    The initial values for the "RIFF" and "data" chunks depends on whether or not we are initializing in sequential mode or not. In
    sequential mode we set this to its final values straight away since they can be calculated from the total sample count. In non-
    sequential mode we initialize it all to zero and fill it out in drwav_uninit() using a backwards seek.
    */
    if (pWav->isSequentialWrite) {
        initialDataChunkSize = (totalSampleCount * pWav->fmt.bitsPerSample) / 8;

        /*
        The RIFF container has a limit on the number of samples. drwav is not allowing this. There's no practical limits for Wave64
        so for the sake of simplicity I'm not doing any validation for that.
        */
        if (pFormat->container == drwav_container_riff) {
            if (initialDataChunkSize > (0xFFFFFFFFUL - 36)) {
                return DRWAV_FALSE; /* Not enough room to store every sample. */
            }
        }
    }

    pWav->dataChunkDataSizeTargetWrite = initialDataChunkSize;


    /* "RIFF" chunk. */
    if (pFormat->container == drwav_container_riff) {
        drwav_uint32 chunkSizeRIFF = 36 + (drwav_uint32)initialDataChunkSize;   /* +36 = "RIFF"+[RIFF Chunk Size]+"WAVE" + [sizeof "fmt " chunk] */
        runningPos += drwav__write(pWav, "RIFF", 4);
        runningPos += drwav__write_u32ne_to_le(pWav, chunkSizeRIFF);
        runningPos += drwav__write(pWav, "WAVE", 4);
    } else {
        drwav_uint64 chunkSizeRIFF = 80 + 24 + initialDataChunkSize;   /* +24 because W64 includes the size of the GUID and size fields. */
        runningPos += drwav__write(pWav, drwavGUID_W64_RIFF, 16);
        runningPos += drwav__write_u64ne_to_le(pWav, chunkSizeRIFF);
        runningPos += drwav__write(pWav, drwavGUID_W64_WAVE, 16);
    }

    /* "fmt " chunk. */
    if (pFormat->container == drwav_container_riff) {
        chunkSizeFMT = 16;
        runningPos += drwav__write(pWav, "fmt ", 4);
        runningPos += drwav__write_u32ne_to_le(pWav, (drwav_uint32)chunkSizeFMT);
    } else {
        chunkSizeFMT = 40;
        runningPos += drwav__write(pWav, drwavGUID_W64_FMT, 16);
        runningPos += drwav__write_u64ne_to_le(pWav, chunkSizeFMT);
    }

    runningPos += drwav__write_u16ne_to_le(pWav, pWav->fmt.formatTag);
    runningPos += drwav__write_u16ne_to_le(pWav, pWav->fmt.channels);
    runningPos += drwav__write_u32ne_to_le(pWav, pWav->fmt.sampleRate);
    runningPos += drwav__write_u32ne_to_le(pWav, pWav->fmt.avgBytesPerSec);
    runningPos += drwav__write_u16ne_to_le(pWav, pWav->fmt.blockAlign);
    runningPos += drwav__write_u16ne_to_le(pWav, pWav->fmt.bitsPerSample);

    pWav->dataChunkDataPos = runningPos;

    /* "data" chunk. */
    if (pFormat->container == drwav_container_riff) {
        drwav_uint32 chunkSizeDATA = (drwav_uint32)initialDataChunkSize;
        runningPos += drwav__write(pWav, "data", 4);
        runningPos += drwav__write_u32ne_to_le(pWav, chunkSizeDATA);
    } else {
        drwav_uint64 chunkSizeDATA = 24 + initialDataChunkSize; /* +24 because W64 includes the size of the GUID and size fields. */
        runningPos += drwav__write(pWav, drwavGUID_W64_DATA, 16);
        runningPos += drwav__write_u64ne_to_le(pWav, chunkSizeDATA);
    }


    /* Simple validation. */
    if (pFormat->container == drwav_container_riff) {
        if (runningPos != 20 + chunkSizeFMT + 8) {
            return DRWAV_FALSE;
        }
    } else {
        if (runningPos != 40 + chunkSizeFMT + 24) {
            return DRWAV_FALSE;
        }
    }
    

    /* Set some properties for the client's convenience. */
    pWav->container = pFormat->container;
    pWav->channels = (drwav_uint16)pFormat->channels;
    pWav->sampleRate = pFormat->sampleRate;
    pWav->bitsPerSample = (drwav_uint16)pFormat->bitsPerSample;
    pWav->translatedFormatTag = (drwav_uint16)pFormat->format;

    return DRWAV_TRUE;
}


DRWAV_API drwav_bool32 drwav_init_write(drwav* pWav, const drwav_data_format* pFormat, drwav_write_proc onWrite, drwav_seek_proc onSeek, void* pUserData, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    if (!drwav_preinit_write(pWav, pFormat, DRWAV_FALSE, onWrite, onSeek, pUserData, pAllocationCallbacks)) {
        return DRWAV_FALSE;
    }

    return drwav_init_write__internal(pWav, pFormat, 0);               /* DRWAV_FALSE = Not Sequential */
}

DRWAV_API drwav_bool32 drwav_init_write_sequential(drwav* pWav, const drwav_data_format* pFormat, drwav_uint64 totalSampleCount, drwav_write_proc onWrite, void* pUserData, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    if (!drwav_preinit_write(pWav, pFormat, DRWAV_TRUE, onWrite, NULL, pUserData, pAllocationCallbacks)) {
        return DRWAV_FALSE;
    }

    return drwav_init_write__internal(pWav, pFormat, totalSampleCount); /* DRWAV_TRUE = Sequential */
}

DRWAV_API drwav_bool32 drwav_init_write_sequential_pcm_frames(drwav* pWav, const drwav_data_format* pFormat, drwav_uint64 totalPCMFrameCount, drwav_write_proc onWrite, void* pUserData, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    if (pFormat == NULL) {
        return DRWAV_FALSE;
    }

    return drwav_init_write_sequential(pWav, pFormat, totalPCMFrameCount*pFormat->channels, onWrite, pUserData, pAllocationCallbacks);
}

DRWAV_API drwav_uint64 drwav_target_write_size_bytes(const drwav_data_format* pFormat, drwav_uint64 totalSampleCount)
{
    /* Casting totalSampleCount to drwav_int64 for VC6 compatibility. No issues in practice because nobody is going to exhaust the whole 63 bits. */
    drwav_uint64 targetDataSizeBytes = (drwav_uint64)((drwav_int64)totalSampleCount * pFormat->channels * pFormat->bitsPerSample/8.0);
    drwav_uint64 riffChunkSizeBytes;
    drwav_uint64 fileSizeBytes;

    if (pFormat->container == drwav_container_riff) {
        riffChunkSizeBytes = drwav__riff_chunk_size_riff(targetDataSizeBytes);
        fileSizeBytes = (8 + riffChunkSizeBytes); /* +8 because WAV doesn't include the size of the ChunkID and ChunkSize fields. */
    } else {
        riffChunkSizeBytes = drwav__riff_chunk_size_w64(targetDataSizeBytes);
        fileSizeBytes = riffChunkSizeBytes;
    }

    return fileSizeBytes;
}


#ifndef DR_WAV_NO_STDIO

/* drwav_result_from_errno() is only used for fopen() and wfopen() so putting it inside DR_WAV_NO_STDIO for now. If something else needs this later we can move it out. */
#include <errno.h>
static drwav_result drwav_result_from_errno(int e)
{
    switch (e)
    {
        case 0: return DRWAV_SUCCESS;
    #ifdef EPERM
        case EPERM: return DRWAV_INVALID_OPERATION;
    #endif
    #ifdef ENOENT
        case ENOENT: return DRWAV_DOES_NOT_EXIST;
    #endif
    #ifdef ESRCH
        case ESRCH: return DRWAV_DOES_NOT_EXIST;
    #endif
    #ifdef EINTR
        case EINTR: return DRWAV_INTERRUPT;
    #endif
    #ifdef EIO
        case EIO: return DRWAV_IO_ERROR;
    #endif
    #ifdef ENXIO
        case ENXIO: return DRWAV_DOES_NOT_EXIST;
    #endif
    #ifdef E2BIG
        case E2BIG: return DRWAV_INVALID_ARGS;
    #endif
    #ifdef ENOEXEC
        case ENOEXEC: return DRWAV_INVALID_FILE;
    #endif
    #ifdef EBADF
        case EBADF: return DRWAV_INVALID_FILE;
    #endif
    #ifdef ECHILD
        case ECHILD: return DRWAV_ERROR;
    #endif
    #ifdef EAGAIN
        case EAGAIN: return DRWAV_UNAVAILABLE;
    #endif
    #ifdef ENOMEM
        case ENOMEM: return DRWAV_OUT_OF_MEMORY;
    #endif
    #ifdef EACCES
        case EACCES: return DRWAV_ACCESS_DENIED;
    #endif
    #ifdef EFAULT
        case EFAULT: return DRWAV_BAD_ADDRESS;
    #endif
    #ifdef ENOTBLK
        case ENOTBLK: return DRWAV_ERROR;
    #endif
    #ifdef EBUSY
        case EBUSY: return DRWAV_BUSY;
    #endif
    #ifdef EEXIST
        case EEXIST: return DRWAV_ALREADY_EXISTS;
    #endif
    #ifdef EXDEV
        case EXDEV: return DRWAV_ERROR;
    #endif
    #ifdef ENODEV
        case ENODEV: return DRWAV_DOES_NOT_EXIST;
    #endif
    #ifdef ENOTDIR
        case ENOTDIR: return DRWAV_NOT_DIRECTORY;
    #endif
    #ifdef EISDIR
        case EISDIR: return DRWAV_IS_DIRECTORY;
    #endif
    #ifdef EINVAL
        case EINVAL: return DRWAV_INVALID_ARGS;
    #endif
    #ifdef ENFILE
        case ENFILE: return DRWAV_TOO_MANY_OPEN_FILES;
    #endif
    #ifdef EMFILE
        case EMFILE: return DRWAV_TOO_MANY_OPEN_FILES;
    #endif
    #ifdef ENOTTY
        case ENOTTY: return DRWAV_INVALID_OPERATION;
    #endif
    #ifdef ETXTBSY
        case ETXTBSY: return DRWAV_BUSY;
    #endif
    #ifdef EFBIG
        case EFBIG: return DRWAV_TOO_BIG;
    #endif
    #ifdef ENOSPC
        case ENOSPC: return DRWAV_NO_SPACE;
    #endif
    #ifdef ESPIPE
        case ESPIPE: return DRWAV_BAD_SEEK;
    #endif
    #ifdef EROFS
        case EROFS: return DRWAV_ACCESS_DENIED;
    #endif
    #ifdef EMLINK
        case EMLINK: return DRWAV_TOO_MANY_LINKS;
    #endif
    #ifdef EPIPE
        case EPIPE: return DRWAV_BAD_PIPE;
    #endif
    #ifdef EDOM
        case EDOM: return DRWAV_OUT_OF_RANGE;
    #endif
    #ifdef ERANGE
        case ERANGE: return DRWAV_OUT_OF_RANGE;
    #endif
    #ifdef EDEADLK
        case EDEADLK: return DRWAV_DEADLOCK;
    #endif
    #ifdef ENAMETOOLONG
        case ENAMETOOLONG: return DRWAV_PATH_TOO_LONG;
    #endif
    #ifdef ENOLCK
        case ENOLCK: return DRWAV_ERROR;
    #endif
    #ifdef ENOSYS
        case ENOSYS: return DRWAV_NOT_IMPLEMENTED;
    #endif
    #ifdef ENOTEMPTY
        case ENOTEMPTY: return DRWAV_DIRECTORY_NOT_EMPTY;
    #endif
    #ifdef ELOOP
        case ELOOP: return DRWAV_TOO_MANY_LINKS;
    #endif
    #ifdef ENOMSG
        case ENOMSG: return DRWAV_NO_MESSAGE;
    #endif
    #ifdef EIDRM
        case EIDRM: return DRWAV_ERROR;
    #endif
    #ifdef ECHRNG
        case ECHRNG: return DRWAV_ERROR;
    #endif
    #ifdef EL2NSYNC
        case EL2NSYNC: return DRWAV_ERROR;
    #endif
    #ifdef EL3HLT
        case EL3HLT: return DRWAV_ERROR;
    #endif
    #ifdef EL3RST
        case EL3RST: return DRWAV_ERROR;
    #endif
    #ifdef ELNRNG
        case ELNRNG: return DRWAV_OUT_OF_RANGE;
    #endif
    #ifdef EUNATCH
        case EUNATCH: return DRWAV_ERROR;
    #endif
    #ifdef ENOCSI
        case ENOCSI: return DRWAV_ERROR;
    #endif
    #ifdef EL2HLT
        case EL2HLT: return DRWAV_ERROR;
    #endif
    #ifdef EBADE
        case EBADE: return DRWAV_ERROR;
    #endif
    #ifdef EBADR
        case EBADR: return DRWAV_ERROR;
    #endif
    #ifdef EXFULL
        case EXFULL: return DRWAV_ERROR;
    #endif
    #ifdef ENOANO
        case ENOANO: return DRWAV_ERROR;
    #endif
    #ifdef EBADRQC
        case EBADRQC: return DRWAV_ERROR;
    #endif
    #ifdef EBADSLT
        case EBADSLT: return DRWAV_ERROR;
    #endif
    #ifdef EBFONT
        case EBFONT: return DRWAV_INVALID_FILE;
    #endif
    #ifdef ENOSTR
        case ENOSTR: return DRWAV_ERROR;
    #endif
    #ifdef ENODATA
        case ENODATA: return DRWAV_NO_DATA_AVAILABLE;
    #endif
    #ifdef ETIME
        case ETIME: return DRWAV_TIMEOUT;
    #endif
    #ifdef ENOSR
        case ENOSR: return DRWAV_NO_DATA_AVAILABLE;
    #endif
    #ifdef ENONET
        case ENONET: return DRWAV_NO_NETWORK;
    #endif
    #ifdef ENOPKG
        case ENOPKG: return DRWAV_ERROR;
    #endif
    #ifdef EREMOTE
        case EREMOTE: return DRWAV_ERROR;
    #endif
    #ifdef ENOLINK
        case ENOLINK: return DRWAV_ERROR;
    #endif
    #ifdef EADV
        case EADV: return DRWAV_ERROR;
    #endif
    #ifdef ESRMNT
        case ESRMNT: return DRWAV_ERROR;
    #endif
    #ifdef ECOMM
        case ECOMM: return DRWAV_ERROR;
    #endif
    #ifdef EPROTO
        case EPROTO: return DRWAV_ERROR;
    #endif
    #ifdef EMULTIHOP
        case EMULTIHOP: return DRWAV_ERROR;
    #endif
    #ifdef EDOTDOT
        case EDOTDOT: return DRWAV_ERROR;
    #endif
    #ifdef EBADMSG
        case EBADMSG: return DRWAV_BAD_MESSAGE;
    #endif
    #ifdef EOVERFLOW
        case EOVERFLOW: return DRWAV_TOO_BIG;
    #endif
    #ifdef ENOTUNIQ
        case ENOTUNIQ: return DRWAV_NOT_UNIQUE;
    #endif
    #ifdef EBADFD
        case EBADFD: return DRWAV_ERROR;
    #endif
    #ifdef EREMCHG
        case EREMCHG: return DRWAV_ERROR;
    #endif
    #ifdef ELIBACC
        case ELIBACC: return DRWAV_ACCESS_DENIED;
    #endif
    #ifdef ELIBBAD
        case ELIBBAD: return DRWAV_INVALID_FILE;
    #endif
    #ifdef ELIBSCN
        case ELIBSCN: return DRWAV_INVALID_FILE;
    #endif
    #ifdef ELIBMAX
        case ELIBMAX: return DRWAV_ERROR;
    #endif
    #ifdef ELIBEXEC
        case ELIBEXEC: return DRWAV_ERROR;
    #endif
    #ifdef EILSEQ
        case EILSEQ: return DRWAV_INVALID_DATA;
    #endif
    #ifdef ERESTART
        case ERESTART: return DRWAV_ERROR;
    #endif
    #ifdef ESTRPIPE
        case ESTRPIPE: return DRWAV_ERROR;
    #endif
    #ifdef EUSERS
        case EUSERS: return DRWAV_ERROR;
    #endif
    #ifdef ENOTSOCK
        case ENOTSOCK: return DRWAV_NOT_SOCKET;
    #endif
    #ifdef EDESTADDRREQ
        case EDESTADDRREQ: return DRWAV_NO_ADDRESS;
    #endif
    #ifdef EMSGSIZE
        case EMSGSIZE: return DRWAV_TOO_BIG;
    #endif
    #ifdef EPROTOTYPE
        case EPROTOTYPE: return DRWAV_BAD_PROTOCOL;
    #endif
    #ifdef ENOPROTOOPT
        case ENOPROTOOPT: return DRWAV_PROTOCOL_UNAVAILABLE;
    #endif
    #ifdef EPROTONOSUPPORT
        case EPROTONOSUPPORT: return DRWAV_PROTOCOL_NOT_SUPPORTED;
    #endif
    #ifdef ESOCKTNOSUPPORT
        case ESOCKTNOSUPPORT: return DRWAV_SOCKET_NOT_SUPPORTED;
    #endif
    #ifdef EOPNOTSUPP
        case EOPNOTSUPP: return DRWAV_INVALID_OPERATION;
    #endif
    #ifdef EPFNOSUPPORT
        case EPFNOSUPPORT: return DRWAV_PROTOCOL_FAMILY_NOT_SUPPORTED;
    #endif
    #ifdef EAFNOSUPPORT
        case EAFNOSUPPORT: return DRWAV_ADDRESS_FAMILY_NOT_SUPPORTED;
    #endif
    #ifdef EADDRINUSE
        case EADDRINUSE: return DRWAV_ALREADY_IN_USE;
    #endif
    #ifdef EADDRNOTAVAIL
        case EADDRNOTAVAIL: return DRWAV_ERROR;
    #endif
    #ifdef ENETDOWN
        case ENETDOWN: return DRWAV_NO_NETWORK;
    #endif
    #ifdef ENETUNREACH
        case ENETUNREACH: return DRWAV_NO_NETWORK;
    #endif
    #ifdef ENETRESET
        case ENETRESET: return DRWAV_NO_NETWORK;
    #endif
    #ifdef ECONNABORTED
        case ECONNABORTED: return DRWAV_NO_NETWORK;
    #endif
    #ifdef ECONNRESET
        case ECONNRESET: return DRWAV_CONNECTION_RESET;
    #endif
    #ifdef ENOBUFS
        case ENOBUFS: return DRWAV_NO_SPACE;
    #endif
    #ifdef EISCONN
        case EISCONN: return DRWAV_ALREADY_CONNECTED;
    #endif
    #ifdef ENOTCONN
        case ENOTCONN: return DRWAV_NOT_CONNECTED;
    #endif
    #ifdef ESHUTDOWN
        case ESHUTDOWN: return DRWAV_ERROR;
    #endif
    #ifdef ETOOMANYREFS
        case ETOOMANYREFS: return DRWAV_ERROR;
    #endif
    #ifdef ETIMEDOUT
        case ETIMEDOUT: return DRWAV_TIMEOUT;
    #endif
    #ifdef ECONNREFUSED
        case ECONNREFUSED: return DRWAV_CONNECTION_REFUSED;
    #endif
    #ifdef EHOSTDOWN
        case EHOSTDOWN: return DRWAV_NO_HOST;
    #endif
    #ifdef EHOSTUNREACH
        case EHOSTUNREACH: return DRWAV_NO_HOST;
    #endif
    #ifdef EALREADY
        case EALREADY: return DRWAV_IN_PROGRESS;
    #endif
    #ifdef EINPROGRESS
        case EINPROGRESS: return DRWAV_IN_PROGRESS;
    #endif
    #ifdef ESTALE
        case ESTALE: return DRWAV_INVALID_FILE;
    #endif
    #ifdef EUCLEAN
        case EUCLEAN: return DRWAV_ERROR;
    #endif
    #ifdef ENOTNAM
        case ENOTNAM: return DRWAV_ERROR;
    #endif
    #ifdef ENAVAIL
        case ENAVAIL: return DRWAV_ERROR;
    #endif
    #ifdef EISNAM
        case EISNAM: return DRWAV_ERROR;
    #endif
    #ifdef EREMOTEIO
        case EREMOTEIO: return DRWAV_IO_ERROR;
    #endif
    #ifdef EDQUOT
        case EDQUOT: return DRWAV_NO_SPACE;
    #endif
    #ifdef ENOMEDIUM
        case ENOMEDIUM: return DRWAV_DOES_NOT_EXIST;
    #endif
    #ifdef EMEDIUMTYPE
        case EMEDIUMTYPE: return DRWAV_ERROR;
    #endif
    #ifdef ECANCELED
        case ECANCELED: return DRWAV_CANCELLED;
    #endif
    #ifdef ENOKEY
        case ENOKEY: return DRWAV_ERROR;
    #endif
    #ifdef EKEYEXPIRED
        case EKEYEXPIRED: return DRWAV_ERROR;
    #endif
    #ifdef EKEYREVOKED
        case EKEYREVOKED: return DRWAV_ERROR;
    #endif
    #ifdef EKEYREJECTED
        case EKEYREJECTED: return DRWAV_ERROR;
    #endif
    #ifdef EOWNERDEAD
        case EOWNERDEAD: return DRWAV_ERROR;
    #endif
    #ifdef ENOTRECOVERABLE
        case ENOTRECOVERABLE: return DRWAV_ERROR;
    #endif
    #ifdef ERFKILL
        case ERFKILL: return DRWAV_ERROR;
    #endif
    #ifdef EHWPOISON
        case EHWPOISON: return DRWAV_ERROR;
    #endif
        default: return DRWAV_ERROR;
    }
}

static drwav_result drwav_fopen(FILE** ppFile, const char* pFilePath, const char* pOpenMode)
{
#if _MSC_VER && _MSC_VER >= 1400
    errno_t err;
#endif

    if (ppFile != NULL) {
        *ppFile = NULL;  /* Safety. */
    }

    if (pFilePath == NULL || pOpenMode == NULL || ppFile == NULL) {
        return DRWAV_INVALID_ARGS;
    }

#if _MSC_VER && _MSC_VER >= 1400
    err = fopen_s(ppFile, pFilePath, pOpenMode);
    if (err != 0) {
        return drwav_result_from_errno(err);
    }
#else
#if defined(_WIN32) || defined(__APPLE__)
    *ppFile = fopen(pFilePath, pOpenMode);
#else
    #if defined(_FILE_OFFSET_BITS) && _FILE_OFFSET_BITS == 64 && defined(_LARGEFILE64_SOURCE)
        *ppFile = fopen64(pFilePath, pOpenMode);
    #else
        *ppFile = fopen(pFilePath, pOpenMode);
    #endif
#endif
    if (*ppFile == NULL) {
        drwav_result result = drwav_result_from_errno(errno);
        if (result == DRWAV_SUCCESS) {
            result = DRWAV_ERROR;   /* Just a safety check to make sure we never ever return success when pFile == NULL. */
        }

        return result;
    }
#endif

    return DRWAV_SUCCESS;
}

/*
_wfopen() isn't always available in all compilation environments.

    * Windows only.
    * MSVC seems to support it universally as far back as VC6 from what I can tell (haven't checked further back).
    * MinGW-64 (both 32- and 64-bit) seems to support it.
    * MinGW wraps it in !defined(__STRICT_ANSI__).

This can be reviewed as compatibility issues arise. The preference is to use _wfopen_s() and _wfopen() as opposed to the wcsrtombs()
fallback, so if you notice your compiler not detecting this properly I'm happy to look at adding support.
*/
#if defined(_WIN32)
    #if defined(_MSC_VER) || defined(__MINGW64__) || !defined(__STRICT_ANSI__)
        #define DRWAV_HAS_WFOPEN
    #endif
#endif

static drwav_result drwav_wfopen(FILE** ppFile, const wchar_t* pFilePath, const wchar_t* pOpenMode, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    if (ppFile != NULL) {
        *ppFile = NULL;  /* Safety. */
    }

    if (pFilePath == NULL || pOpenMode == NULL || ppFile == NULL) {
        return DRWAV_INVALID_ARGS;
    }

#if defined(DRWAV_HAS_WFOPEN)
    {
        /* Use _wfopen() on Windows. */
    #if defined(_MSC_VER) && _MSC_VER >= 1400
        errno_t err = _wfopen_s(ppFile, pFilePath, pOpenMode);
        if (err != 0) {
            return drwav_result_from_errno(err);
        }
    #else
        *ppFile = _wfopen(pFilePath, pOpenMode);
        if (*ppFile == NULL) {
            return drwav_result_from_errno(errno);
        }
    #endif
        (void)pAllocationCallbacks;
    }
#else
    /*
    Use fopen() on anything other than Windows. Requires a conversion. This is annoying because fopen() is locale specific. The only real way I can
    think of to do this is with wcsrtombs(). Note that wcstombs() is apparently not thread-safe because it uses a static global mbstate_t object for
    maintaining state. I've checked this with -std=c89 and it works, but if somebody get's a compiler error I'll look into improving compatibility.
    */
    {
        mbstate_t mbs;
        size_t lenMB;
        const wchar_t* pFilePathTemp = pFilePath;
        char* pFilePathMB = NULL;
        char pOpenModeMB[32] = {0};

        /* Get the length first. */
        DRWAV_ZERO_OBJECT(&mbs);
        lenMB = wcsrtombs(NULL, &pFilePathTemp, 0, &mbs);
        if (lenMB == (size_t)-1) {
            return drwav_result_from_errno(errno);
        }

        pFilePathMB = (char*)drwav__malloc_from_callbacks(lenMB + 1, pAllocationCallbacks);
        if (pFilePathMB == NULL) {
            return DRWAV_OUT_OF_MEMORY;
        }

        pFilePathTemp = pFilePath;
        DRWAV_ZERO_OBJECT(&mbs);
        wcsrtombs(pFilePathMB, &pFilePathTemp, lenMB + 1, &mbs);

        /* The open mode should always consist of ASCII characters so we should be able to do a trivial conversion. */
        {
            size_t i = 0;
            for (;;) {
                if (pOpenMode[i] == 0) {
                    pOpenModeMB[i] = '\0';
                    break;
                }

                pOpenModeMB[i] = (char)pOpenMode[i];
                i += 1;
            }
        }

        *ppFile = fopen(pFilePathMB, pOpenModeMB);

        drwav__free_from_callbacks(pFilePathMB, pAllocationCallbacks);
    }

    if (*ppFile == NULL) {
        return DRWAV_ERROR;
    }
#endif

    return DRWAV_SUCCESS;
}


static size_t drwav__on_read_stdio(void* pUserData, void* pBufferOut, size_t bytesToRead)
{
    return fread(pBufferOut, 1, bytesToRead, (FILE*)pUserData);
}

static size_t drwav__on_write_stdio(void* pUserData, const void* pData, size_t bytesToWrite)
{
    return fwrite(pData, 1, bytesToWrite, (FILE*)pUserData);
}

static drwav_bool32 drwav__on_seek_stdio(void* pUserData, int offset, drwav_seek_origin origin)
{
    return fseek((FILE*)pUserData, offset, (origin == drwav_seek_origin_current) ? SEEK_CUR : SEEK_SET) == 0;
}

DRWAV_API drwav_bool32 drwav_init_file(drwav* pWav, const char* filename, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    return drwav_init_file_ex(pWav, filename, NULL, NULL, 0, pAllocationCallbacks);
}


static drwav_bool32 drwav_init_file__internal_FILE(drwav* pWav, FILE* pFile, drwav_chunk_proc onChunk, void* pChunkUserData, drwav_uint32 flags, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    drwav_bool32 result;

    result = drwav_preinit(pWav, drwav__on_read_stdio, drwav__on_seek_stdio, (void*)pFile, pAllocationCallbacks);
    if (result != DRWAV_TRUE) {
        fclose(pFile);
        return result;
    }

    result = drwav_init__internal(pWav, onChunk, pChunkUserData, flags);
    if (result != DRWAV_TRUE) {
        fclose(pFile);
        return result;
    }

    return DRWAV_TRUE;
}

DRWAV_API drwav_bool32 drwav_init_file_ex(drwav* pWav, const char* filename, drwav_chunk_proc onChunk, void* pChunkUserData, drwav_uint32 flags, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    FILE* pFile;
    if (drwav_fopen(&pFile, filename, "rb") != DRWAV_SUCCESS) {
        return DRWAV_FALSE;
    }

    /* This takes ownership of the FILE* object. */
    return drwav_init_file__internal_FILE(pWav, pFile, onChunk, pChunkUserData, flags, pAllocationCallbacks);
}

DRWAV_API drwav_bool32 drwav_init_file_w(drwav* pWav, const wchar_t* filename, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    return drwav_init_file_ex_w(pWav, filename, NULL, NULL, 0, pAllocationCallbacks);
}

DRWAV_API drwav_bool32 drwav_init_file_ex_w(drwav* pWav, const wchar_t* filename, drwav_chunk_proc onChunk, void* pChunkUserData, drwav_uint32 flags, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    FILE* pFile;
    if (drwav_wfopen(&pFile, filename, L"rb", pAllocationCallbacks) != DRWAV_SUCCESS) {
        return DRWAV_FALSE;
    }

    /* This takes ownership of the FILE* object. */
    return drwav_init_file__internal_FILE(pWav, pFile, onChunk, pChunkUserData, flags, pAllocationCallbacks);
}


static drwav_bool32 drwav_init_file_write__internal_FILE(drwav* pWav, FILE* pFile, const drwav_data_format* pFormat, drwav_uint64 totalSampleCount, drwav_bool32 isSequential, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    drwav_bool32 result;

    result = drwav_preinit_write(pWav, pFormat, isSequential, drwav__on_write_stdio, drwav__on_seek_stdio, (void*)pFile, pAllocationCallbacks);
    if (result != DRWAV_TRUE) {
        fclose(pFile);
        return result;
    }

    result = drwav_init_write__internal(pWav, pFormat, totalSampleCount);
    if (result != DRWAV_TRUE) {
        fclose(pFile);
        return result;
    }

    return DRWAV_TRUE;
}

static drwav_bool32 drwav_init_file_write__internal(drwav* pWav, const char* filename, const drwav_data_format* pFormat, drwav_uint64 totalSampleCount, drwav_bool32 isSequential, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    FILE* pFile;
    if (drwav_fopen(&pFile, filename, "wb") != DRWAV_SUCCESS) {
        return DRWAV_FALSE;
    }

    /* This takes ownership of the FILE* object. */
    return drwav_init_file_write__internal_FILE(pWav, pFile, pFormat, totalSampleCount, isSequential, pAllocationCallbacks);
}

static drwav_bool32 drwav_init_file_write_w__internal(drwav* pWav, const wchar_t* filename, const drwav_data_format* pFormat, drwav_uint64 totalSampleCount, drwav_bool32 isSequential, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    FILE* pFile;
    if (drwav_wfopen(&pFile, filename, L"wb", pAllocationCallbacks) != DRWAV_SUCCESS) {
        return DRWAV_FALSE;
    }

    /* This takes ownership of the FILE* object. */
    return drwav_init_file_write__internal_FILE(pWav, pFile, pFormat, totalSampleCount, isSequential, pAllocationCallbacks);
}

DRWAV_API drwav_bool32 drwav_init_file_write(drwav* pWav, const char* filename, const drwav_data_format* pFormat, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    return drwav_init_file_write__internal(pWav, filename, pFormat, 0, DRWAV_FALSE, pAllocationCallbacks);
}

DRWAV_API drwav_bool32 drwav_init_file_write_sequential(drwav* pWav, const char* filename, const drwav_data_format* pFormat, drwav_uint64 totalSampleCount, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    return drwav_init_file_write__internal(pWav, filename, pFormat, totalSampleCount, DRWAV_TRUE, pAllocationCallbacks);
}

DRWAV_API drwav_bool32 drwav_init_file_write_sequential_pcm_frames(drwav* pWav, const char* filename, const drwav_data_format* pFormat, drwav_uint64 totalPCMFrameCount, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    if (pFormat == NULL) {
        return DRWAV_FALSE;
    }

    return drwav_init_file_write_sequential(pWav, filename, pFormat, totalPCMFrameCount*pFormat->channels, pAllocationCallbacks);
}

DRWAV_API drwav_bool32 drwav_init_file_write_w(drwav* pWav, const wchar_t* filename, const drwav_data_format* pFormat, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    return drwav_init_file_write_w__internal(pWav, filename, pFormat, 0, DRWAV_FALSE, pAllocationCallbacks);
}

DRWAV_API drwav_bool32 drwav_init_file_write_sequential_w(drwav* pWav, const wchar_t* filename, const drwav_data_format* pFormat, drwav_uint64 totalSampleCount, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    return drwav_init_file_write_w__internal(pWav, filename, pFormat, totalSampleCount, DRWAV_TRUE, pAllocationCallbacks);
}

DRWAV_API drwav_bool32 drwav_init_file_write_sequential_pcm_frames_w(drwav* pWav, const wchar_t* filename, const drwav_data_format* pFormat, drwav_uint64 totalPCMFrameCount, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    if (pFormat == NULL) {
        return DRWAV_FALSE;
    }

    return drwav_init_file_write_sequential_w(pWav, filename, pFormat, totalPCMFrameCount*pFormat->channels, pAllocationCallbacks);
}
#endif  /* DR_WAV_NO_STDIO */


static size_t drwav__on_read_memory(void* pUserData, void* pBufferOut, size_t bytesToRead)
{
    drwav* pWav = (drwav*)pUserData;
    size_t bytesRemaining;

    DRWAV_ASSERT(pWav != NULL);
    DRWAV_ASSERT(pWav->memoryStream.dataSize >= pWav->memoryStream.currentReadPos);

    bytesRemaining = pWav->memoryStream.dataSize - pWav->memoryStream.currentReadPos;
    if (bytesToRead > bytesRemaining) {
        bytesToRead = bytesRemaining;
    }

    if (bytesToRead > 0) {
        DRWAV_COPY_MEMORY(pBufferOut, pWav->memoryStream.data + pWav->memoryStream.currentReadPos, bytesToRead);
        pWav->memoryStream.currentReadPos += bytesToRead;
    }

    return bytesToRead;
}

static drwav_bool32 drwav__on_seek_memory(void* pUserData, int offset, drwav_seek_origin origin)
{
    drwav* pWav = (drwav*)pUserData;
    DRWAV_ASSERT(pWav != NULL);

    if (origin == drwav_seek_origin_current) {
        if (offset > 0) {
            if (pWav->memoryStream.currentReadPos + offset > pWav->memoryStream.dataSize) {
                return DRWAV_FALSE; /* Trying to seek too far forward. */
            }
        } else {
            if (pWav->memoryStream.currentReadPos < (size_t)-offset) {
                return DRWAV_FALSE; /* Trying to seek too far backwards. */
            }
        }

        /* This will never underflow thanks to the clamps above. */
        pWav->memoryStream.currentReadPos += offset;
    } else {
        if ((drwav_uint32)offset <= pWav->memoryStream.dataSize) {
            pWav->memoryStream.currentReadPos = offset;
        } else {
            return DRWAV_FALSE; /* Trying to seek too far forward. */
        }
    }
    
    return DRWAV_TRUE;
}

static size_t drwav__on_write_memory(void* pUserData, const void* pDataIn, size_t bytesToWrite)
{
    drwav* pWav = (drwav*)pUserData;
    size_t bytesRemaining;

    DRWAV_ASSERT(pWav != NULL);
    DRWAV_ASSERT(pWav->memoryStreamWrite.dataCapacity >= pWav->memoryStreamWrite.currentWritePos);

    bytesRemaining = pWav->memoryStreamWrite.dataCapacity - pWav->memoryStreamWrite.currentWritePos;
    if (bytesRemaining < bytesToWrite) {
        /* Need to reallocate. */
        void* pNewData;
        size_t newDataCapacity = (pWav->memoryStreamWrite.dataCapacity == 0) ? 256 : pWav->memoryStreamWrite.dataCapacity * 2;

        /* If doubling wasn't enough, just make it the minimum required size to write the data. */
        if ((newDataCapacity - pWav->memoryStreamWrite.currentWritePos) < bytesToWrite) {
            newDataCapacity = pWav->memoryStreamWrite.currentWritePos + bytesToWrite;
        }

        pNewData = drwav__realloc_from_callbacks(*pWav->memoryStreamWrite.ppData, newDataCapacity, pWav->memoryStreamWrite.dataCapacity, &pWav->allocationCallbacks);
        if (pNewData == NULL) {
            return 0;
        }

        *pWav->memoryStreamWrite.ppData = pNewData;
        pWav->memoryStreamWrite.dataCapacity = newDataCapacity;
    }

    DRWAV_COPY_MEMORY(((drwav_uint8*)(*pWav->memoryStreamWrite.ppData)) + pWav->memoryStreamWrite.currentWritePos, pDataIn, bytesToWrite);

    pWav->memoryStreamWrite.currentWritePos += bytesToWrite;
    if (pWav->memoryStreamWrite.dataSize < pWav->memoryStreamWrite.currentWritePos) {
        pWav->memoryStreamWrite.dataSize = pWav->memoryStreamWrite.currentWritePos;
    }

    *pWav->memoryStreamWrite.pDataSize = pWav->memoryStreamWrite.dataSize;

    return bytesToWrite;
}

static drwav_bool32 drwav__on_seek_memory_write(void* pUserData, int offset, drwav_seek_origin origin)
{
    drwav* pWav = (drwav*)pUserData;
    DRWAV_ASSERT(pWav != NULL);

    if (origin == drwav_seek_origin_current) {
        if (offset > 0) {
            if (pWav->memoryStreamWrite.currentWritePos + offset > pWav->memoryStreamWrite.dataSize) {
                offset = (int)(pWav->memoryStreamWrite.dataSize - pWav->memoryStreamWrite.currentWritePos);  /* Trying to seek too far forward. */
            }
        } else {
            if (pWav->memoryStreamWrite.currentWritePos < (size_t)-offset) {
                offset = -(int)pWav->memoryStreamWrite.currentWritePos;  /* Trying to seek too far backwards. */
            }
        }

        /* This will never underflow thanks to the clamps above. */
        pWav->memoryStreamWrite.currentWritePos += offset;
    } else {
        if ((drwav_uint32)offset <= pWav->memoryStreamWrite.dataSize) {
            pWav->memoryStreamWrite.currentWritePos = offset;
        } else {
            pWav->memoryStreamWrite.currentWritePos = pWav->memoryStreamWrite.dataSize;  /* Trying to seek too far forward. */
        }
    }
    
    return DRWAV_TRUE;
}

DRWAV_API drwav_bool32 drwav_init_memory(drwav* pWav, const void* data, size_t dataSize, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    return drwav_init_memory_ex(pWav, data, dataSize, NULL, NULL, 0, pAllocationCallbacks);
}

DRWAV_API drwav_bool32 drwav_init_memory_ex(drwav* pWav, const void* data, size_t dataSize, drwav_chunk_proc onChunk, void* pChunkUserData, drwav_uint32 flags, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    if (data == NULL || dataSize == 0) {
        return DRWAV_FALSE;
    }

    if (!drwav_preinit(pWav, drwav__on_read_memory, drwav__on_seek_memory, pWav, pAllocationCallbacks)) {
        return DRWAV_FALSE;
    }

    pWav->memoryStream.data = (const drwav_uint8*)data;
    pWav->memoryStream.dataSize = dataSize;
    pWav->memoryStream.currentReadPos = 0;

    return drwav_init__internal(pWav, onChunk, pChunkUserData, flags);
}


static drwav_bool32 drwav_init_memory_write__internal(drwav* pWav, void** ppData, size_t* pDataSize, const drwav_data_format* pFormat, drwav_uint64 totalSampleCount, drwav_bool32 isSequential, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    if (ppData == NULL || pDataSize == NULL) {
        return DRWAV_FALSE;
    }

    *ppData = NULL; /* Important because we're using realloc()! */
    *pDataSize = 0;

    if (!drwav_preinit_write(pWav, pFormat, isSequential, drwav__on_write_memory, drwav__on_seek_memory_write, pWav, pAllocationCallbacks)) {
        return DRWAV_FALSE;
    }

    pWav->memoryStreamWrite.ppData = ppData;
    pWav->memoryStreamWrite.pDataSize = pDataSize;
    pWav->memoryStreamWrite.dataSize = 0;
    pWav->memoryStreamWrite.dataCapacity = 0;
    pWav->memoryStreamWrite.currentWritePos = 0;

    return drwav_init_write__internal(pWav, pFormat, totalSampleCount);
}

DRWAV_API drwav_bool32 drwav_init_memory_write(drwav* pWav, void** ppData, size_t* pDataSize, const drwav_data_format* pFormat, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    return drwav_init_memory_write__internal(pWav, ppData, pDataSize, pFormat, 0, DRWAV_FALSE, pAllocationCallbacks);
}

DRWAV_API drwav_bool32 drwav_init_memory_write_sequential(drwav* pWav, void** ppData, size_t* pDataSize, const drwav_data_format* pFormat, drwav_uint64 totalSampleCount, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    return drwav_init_memory_write__internal(pWav, ppData, pDataSize, pFormat, totalSampleCount, DRWAV_TRUE, pAllocationCallbacks);
}

DRWAV_API drwav_bool32 drwav_init_memory_write_sequential_pcm_frames(drwav* pWav, void** ppData, size_t* pDataSize, const drwav_data_format* pFormat, drwav_uint64 totalPCMFrameCount, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    if (pFormat == NULL) {
        return DRWAV_FALSE;
    }

    return drwav_init_memory_write_sequential(pWav, ppData, pDataSize, pFormat, totalPCMFrameCount*pFormat->channels, pAllocationCallbacks);
}



DRWAV_API drwav_result drwav_uninit(drwav* pWav)
{
    drwav_result result = DRWAV_SUCCESS;

    if (pWav == NULL) {
        return DRWAV_INVALID_ARGS;
    }

    /*
    If the drwav object was opened in write mode we'll need to finalize a few things:
      - Make sure the "data" chunk is aligned to 16-bits for RIFF containers, or 64 bits for W64 containers.
      - Set the size of the "data" chunk.
    */
    if (pWav->onWrite != NULL) {
        drwav_uint32 paddingSize = 0;

        /* Padding. Do not adjust pWav->dataChunkDataSize - this should not include the padding. */
        if (pWav->container == drwav_container_riff) {
            paddingSize = drwav__chunk_padding_size_riff(pWav->dataChunkDataSize);
        } else {
            paddingSize = drwav__chunk_padding_size_w64(pWav->dataChunkDataSize);
        }
        
        if (paddingSize > 0) {
            drwav_uint64 paddingData = 0;
            drwav__write(pWav, &paddingData, paddingSize);  /* Byte order does not matter for this. */
        }

        /*
        Chunk sizes. When using sequential mode, these will have been filled in at initialization time. We only need
        to do this when using non-sequential mode.
        */
        if (pWav->onSeek && !pWav->isSequentialWrite) {
            if (pWav->container == drwav_container_riff) {
                /* The "RIFF" chunk size. */
                if (pWav->onSeek(pWav->pUserData, 4, drwav_seek_origin_start)) {
                    drwav_uint32 riffChunkSize = drwav__riff_chunk_size_riff(pWav->dataChunkDataSize);
                    drwav__write_u32ne_to_le(pWav, riffChunkSize);
                }

                /* the "data" chunk size. */
                if (pWav->onSeek(pWav->pUserData, (int)pWav->dataChunkDataPos + 4, drwav_seek_origin_start)) {
                    drwav_uint32 dataChunkSize = drwav__data_chunk_size_riff(pWav->dataChunkDataSize);
                    drwav__write_u32ne_to_le(pWav, dataChunkSize);
                }
            } else {
                /* The "RIFF" chunk size. */
                if (pWav->onSeek(pWav->pUserData, 16, drwav_seek_origin_start)) {
                    drwav_uint64 riffChunkSize = drwav__riff_chunk_size_w64(pWav->dataChunkDataSize);
                    drwav__write_u64ne_to_le(pWav, riffChunkSize);
                }

                /* The "data" chunk size. */
                if (pWav->onSeek(pWav->pUserData, (int)pWav->dataChunkDataPos + 16, drwav_seek_origin_start)) {
                    drwav_uint64 dataChunkSize = drwav__data_chunk_size_w64(pWav->dataChunkDataSize);
                    drwav__write_u64ne_to_le(pWav, dataChunkSize);
                }
            }
        }

        /* Validation for sequential mode. */
        if (pWav->isSequentialWrite) {
            if (pWav->dataChunkDataSize != pWav->dataChunkDataSizeTargetWrite) {
                result = DRWAV_INVALID_FILE;
            }
        }
    }

#ifndef DR_WAV_NO_STDIO
    /*
    If we opened the file with drwav_open_file() we will want to close the file handle. We can know whether or not drwav_open_file()
    was used by looking at the onRead and onSeek callbacks.
    */
    if (pWav->onRead == drwav__on_read_stdio || pWav->onWrite == drwav__on_write_stdio) {
        fclose((FILE*)pWav->pUserData);
    }
#endif

    return result;
}



DRWAV_API size_t drwav_read_raw(drwav* pWav, size_t bytesToRead, void* pBufferOut)
{
    size_t bytesRead;

    if (pWav == NULL || bytesToRead == 0) {
        return 0;
    }

    if (bytesToRead > pWav->bytesRemaining) {
        bytesToRead = (size_t)pWav->bytesRemaining;
    }

    if (pBufferOut != NULL) {
        bytesRead = pWav->onRead(pWav->pUserData, pBufferOut, bytesToRead);
    } else {
        /* We need to seek. If we fail, we need to read-and-discard to make sure we get a good byte count. */
        bytesRead = 0;
        while (bytesRead < bytesToRead) {
            size_t bytesToSeek = (bytesToRead - bytesRead);
            if (bytesToSeek > 0x7FFFFFFF) {
                bytesToSeek = 0x7FFFFFFF;
            }

            if (pWav->onSeek(pWav->pUserData, (int)bytesToSeek, drwav_seek_origin_current) == DRWAV_FALSE) {
                break;
            }

            bytesRead += bytesToSeek;
        }

        /* When we get here we may need to read-and-discard some data. */
        while (bytesRead < bytesToRead) {
            drwav_uint8 buffer[4096];
            size_t bytesSeeked;
            size_t bytesToSeek = (bytesToRead - bytesRead);
            if (bytesToSeek > sizeof(buffer)) {
                bytesToSeek = sizeof(buffer);
            }

            bytesSeeked = pWav->onRead(pWav->pUserData, buffer, bytesToSeek);
            bytesRead += bytesSeeked;

            if (bytesSeeked < bytesToSeek) {
                break;  /* Reached the end. */
            }
        }
    }

    pWav->bytesRemaining -= bytesRead;
    return bytesRead;
}



DRWAV_API drwav_uint64 drwav_read_pcm_frames_le(drwav* pWav, drwav_uint64 framesToRead, void* pBufferOut)
{
    drwav_uint32 bytesPerFrame;

    if (pWav == NULL || framesToRead == 0) {
        return 0;
    }

    /* Cannot use this function for compressed formats. */
    if (drwav__is_compressed_format_tag(pWav->translatedFormatTag)) {
        return 0;
    }

    bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav);
    if (bytesPerFrame == 0) {
        return 0;
    }

    /* Don't try to read more samples than can potentially fit in the output buffer. */
    if (framesToRead * bytesPerFrame > DRWAV_SIZE_MAX) {
        framesToRead = DRWAV_SIZE_MAX / bytesPerFrame;
    }

    return drwav_read_raw(pWav, (size_t)(framesToRead * bytesPerFrame), pBufferOut) / bytesPerFrame;
}

DRWAV_API drwav_uint64 drwav_read_pcm_frames_be(drwav* pWav, drwav_uint64 framesToRead, void* pBufferOut)
{
    drwav_uint64 framesRead = drwav_read_pcm_frames_le(pWav, framesToRead, pBufferOut);

    if (pBufferOut != NULL) {
        drwav__bswap_samples(pBufferOut, framesRead*pWav->channels, drwav_get_bytes_per_pcm_frame(pWav)/pWav->channels, pWav->translatedFormatTag);
    }

    return framesRead;
}

DRWAV_API drwav_uint64 drwav_read_pcm_frames(drwav* pWav, drwav_uint64 framesToRead, void* pBufferOut)
{
    if (drwav__is_little_endian()) {
        return drwav_read_pcm_frames_le(pWav, framesToRead, pBufferOut);
    } else {
        return drwav_read_pcm_frames_be(pWav, framesToRead, pBufferOut);
    }
}



DRWAV_API drwav_bool32 drwav_seek_to_first_pcm_frame(drwav* pWav)
{
    if (pWav->onWrite != NULL) {
        return DRWAV_FALSE; /* No seeking in write mode. */
    }

    if (!pWav->onSeek(pWav->pUserData, (int)pWav->dataChunkDataPos, drwav_seek_origin_start)) {
        return DRWAV_FALSE;
    }

    if (drwav__is_compressed_format_tag(pWav->translatedFormatTag)) {
        pWav->compressed.iCurrentPCMFrame = 0;
    }
    
    pWav->bytesRemaining = pWav->dataChunkDataSize;
    return DRWAV_TRUE;
}

DRWAV_API drwav_bool32 drwav_seek_to_pcm_frame(drwav* pWav, drwav_uint64 targetFrameIndex)
{
    /* Seeking should be compatible with wave files > 2GB. */

    if (pWav == NULL || pWav->onSeek == NULL) {
        return DRWAV_FALSE;
    }

    /* No seeking in write mode. */
    if (pWav->onWrite != NULL) {
        return DRWAV_FALSE;
    }

    /* If there are no samples, just return DRWAV_TRUE without doing anything. */
    if (pWav->totalPCMFrameCount == 0) {
        return DRWAV_TRUE;
    }

    /* Make sure the sample is clamped. */
    if (targetFrameIndex >= pWav->totalPCMFrameCount) {
        targetFrameIndex  = pWav->totalPCMFrameCount - 1;
    }

    /*
    For compressed formats we just use a slow generic seek. If we are seeking forward we just seek forward. If we are going backwards we need
    to seek back to the start.
    */
    if (drwav__is_compressed_format_tag(pWav->translatedFormatTag)) {
        /* TODO: This can be optimized. */
        
        /*
        If we're seeking forward it's simple - just keep reading samples until we hit the sample we're requesting. If we're seeking backwards,
        we first need to seek back to the start and then just do the same thing as a forward seek.
        */
        if (targetFrameIndex < pWav->compressed.iCurrentPCMFrame) {
            if (!drwav_seek_to_first_pcm_frame(pWav)) {
                return DRWAV_FALSE;
            }
        }

        if (targetFrameIndex > pWav->compressed.iCurrentPCMFrame) {
            drwav_uint64 offsetInFrames = targetFrameIndex - pWav->compressed.iCurrentPCMFrame;

            drwav_int16 devnull[2048];
            while (offsetInFrames > 0) {
                drwav_uint64 framesRead = 0;
                drwav_uint64 framesToRead = offsetInFrames;
                if (framesToRead > drwav_countof(devnull)/pWav->channels) {
                    framesToRead = drwav_countof(devnull)/pWav->channels;
                }

                if (pWav->translatedFormatTag == DR_WAVE_FORMAT_ADPCM) {
                    framesRead = drwav_read_pcm_frames_s16__msadpcm(pWav, framesToRead, devnull);
                } else if (pWav->translatedFormatTag == DR_WAVE_FORMAT_DVI_ADPCM) {
                    framesRead = drwav_read_pcm_frames_s16__ima(pWav, framesToRead, devnull);
                } else {
                    DRWAV_ASSERT(DRWAV_FALSE);  /* If this assertion is triggered it means I've implemented a new compressed format but forgot to add a branch for it here. */
                }

                if (framesRead != framesToRead) {
                    return DRWAV_FALSE;
                }

                offsetInFrames -= framesRead;
            }
        }
    } else {
        drwav_uint64 totalSizeInBytes;
        drwav_uint64 currentBytePos;
        drwav_uint64 targetBytePos;
        drwav_uint64 offset;

        totalSizeInBytes = pWav->totalPCMFrameCount * drwav_get_bytes_per_pcm_frame(pWav);
        DRWAV_ASSERT(totalSizeInBytes >= pWav->bytesRemaining);

        currentBytePos = totalSizeInBytes - pWav->bytesRemaining;
        targetBytePos  = targetFrameIndex * drwav_get_bytes_per_pcm_frame(pWav);

        if (currentBytePos < targetBytePos) {
            /* Offset forwards. */
            offset = (targetBytePos - currentBytePos);
        } else {
            /* Offset backwards. */
            if (!drwav_seek_to_first_pcm_frame(pWav)) {
                return DRWAV_FALSE;
            }
            offset = targetBytePos;
        }

        while (offset > 0) {
            int offset32 = ((offset > INT_MAX) ? INT_MAX : (int)offset);
            if (!pWav->onSeek(pWav->pUserData, offset32, drwav_seek_origin_current)) {
                return DRWAV_FALSE;
            }

            pWav->bytesRemaining -= offset32;
            offset -= offset32;
        }
    }

    return DRWAV_TRUE;
}


DRWAV_API size_t drwav_write_raw(drwav* pWav, size_t bytesToWrite, const void* pData)
{
    size_t bytesWritten;

    if (pWav == NULL || bytesToWrite == 0 || pData == NULL) {
        return 0;
    }

    bytesWritten = pWav->onWrite(pWav->pUserData, pData, bytesToWrite);
    pWav->dataChunkDataSize += bytesWritten;

    return bytesWritten;
}


DRWAV_API drwav_uint64 drwav_write_pcm_frames_le(drwav* pWav, drwav_uint64 framesToWrite, const void* pData)
{
    drwav_uint64 bytesToWrite;
    drwav_uint64 bytesWritten;
    const drwav_uint8* pRunningData;

    if (pWav == NULL || framesToWrite == 0 || pData == NULL) {
        return 0;
    }

    bytesToWrite = ((framesToWrite * pWav->channels * pWav->bitsPerSample) / 8);
    if (bytesToWrite > DRWAV_SIZE_MAX) {
        return 0;
    }

    bytesWritten = 0;
    pRunningData = (const drwav_uint8*)pData;

    while (bytesToWrite > 0) {
        size_t bytesJustWritten;
        drwav_uint64 bytesToWriteThisIteration;

        bytesToWriteThisIteration = bytesToWrite;
        DRWAV_ASSERT(bytesToWriteThisIteration <= DRWAV_SIZE_MAX);  /* <-- This is checked above. */

        bytesJustWritten = drwav_write_raw(pWav, (size_t)bytesToWriteThisIteration, pRunningData);
        if (bytesJustWritten == 0) {
            break;
        }

        bytesToWrite -= bytesJustWritten;
        bytesWritten += bytesJustWritten;
        pRunningData += bytesJustWritten;
    }

    return (bytesWritten * 8) / pWav->bitsPerSample / pWav->channels;
}

DRWAV_API drwav_uint64 drwav_write_pcm_frames_be(drwav* pWav, drwav_uint64 framesToWrite, const void* pData)
{
    drwav_uint64 bytesToWrite;
    drwav_uint64 bytesWritten;
    drwav_uint32 bytesPerSample;
    const drwav_uint8* pRunningData;

    if (pWav == NULL || framesToWrite == 0 || pData == NULL) {
        return 0;
    }

    bytesToWrite = ((framesToWrite * pWav->channels * pWav->bitsPerSample) / 8);
    if (bytesToWrite > DRWAV_SIZE_MAX) {
        return 0;
    }

    bytesWritten = 0;
    pRunningData = (const drwav_uint8*)pData;

    bytesPerSample = drwav_get_bytes_per_pcm_frame(pWav) / pWav->channels;
    
    while (bytesToWrite > 0) {
        drwav_uint8 temp[4096];
        drwav_uint32 sampleCount;
        size_t bytesJustWritten;
        drwav_uint64 bytesToWriteThisIteration;

        bytesToWriteThisIteration = bytesToWrite;
        DRWAV_ASSERT(bytesToWriteThisIteration <= DRWAV_SIZE_MAX);  /* <-- This is checked above. */

        /*
        WAV files are always little-endian. We need to byte swap on big-endian architectures. Since our input buffer is read-only we need
        to use an intermediary buffer for the conversion.
        */
        sampleCount = sizeof(temp)/bytesPerSample;

        if (bytesToWriteThisIteration > ((drwav_uint64)sampleCount)*bytesPerSample) {
            bytesToWriteThisIteration = ((drwav_uint64)sampleCount)*bytesPerSample;
        }

        DRWAV_COPY_MEMORY(temp, pRunningData, (size_t)bytesToWriteThisIteration);
        drwav__bswap_samples(temp, sampleCount, bytesPerSample, pWav->translatedFormatTag);

        bytesJustWritten = drwav_write_raw(pWav, (size_t)bytesToWriteThisIteration, temp);
        if (bytesJustWritten == 0) {
            break;
        }

        bytesToWrite -= bytesJustWritten;
        bytesWritten += bytesJustWritten;
        pRunningData += bytesJustWritten;
    }

    return (bytesWritten * 8) / pWav->bitsPerSample / pWav->channels;
}

DRWAV_API drwav_uint64 drwav_write_pcm_frames(drwav* pWav, drwav_uint64 framesToWrite, const void* pData)
{
    if (drwav__is_little_endian()) {
        return drwav_write_pcm_frames_le(pWav, framesToWrite, pData);
    } else {
        return drwav_write_pcm_frames_be(pWav, framesToWrite, pData);
    }
}


static drwav_uint64 drwav_read_pcm_frames_s16__msadpcm(drwav* pWav, drwav_uint64 framesToRead, drwav_int16* pBufferOut)
{
    drwav_uint64 totalFramesRead = 0;

    DRWAV_ASSERT(pWav != NULL);
    DRWAV_ASSERT(framesToRead > 0);

    /* TODO: Lots of room for optimization here. */

    while (framesToRead > 0 && pWav->compressed.iCurrentPCMFrame < pWav->totalPCMFrameCount) {
        /* If there are no cached frames we need to load a new block. */
        if (pWav->msadpcm.cachedFrameCount == 0 && pWav->msadpcm.bytesRemainingInBlock == 0) {
            if (pWav->channels == 1) {
                /* Mono. */
                drwav_uint8 header[7];
                if (pWav->onRead(pWav->pUserData, header, sizeof(header)) != sizeof(header)) {
                    return totalFramesRead;
                }
                pWav->msadpcm.bytesRemainingInBlock = pWav->fmt.blockAlign - sizeof(header);

                pWav->msadpcm.predictor[0]     = header[0];
                pWav->msadpcm.delta[0]         = drwav__bytes_to_s16(header + 1);
                pWav->msadpcm.prevFrames[0][1] = (drwav_int32)drwav__bytes_to_s16(header + 3);
                pWav->msadpcm.prevFrames[0][0] = (drwav_int32)drwav__bytes_to_s16(header + 5);
                pWav->msadpcm.cachedFrames[2]  = pWav->msadpcm.prevFrames[0][0];
                pWav->msadpcm.cachedFrames[3]  = pWav->msadpcm.prevFrames[0][1];
                pWav->msadpcm.cachedFrameCount = 2;
            } else {
                /* Stereo. */
                drwav_uint8 header[14];
                if (pWav->onRead(pWav->pUserData, header, sizeof(header)) != sizeof(header)) {
                    return totalFramesRead;
                }
                pWav->msadpcm.bytesRemainingInBlock = pWav->fmt.blockAlign - sizeof(header);

                pWav->msadpcm.predictor[0] = header[0];
                pWav->msadpcm.predictor[1] = header[1];
                pWav->msadpcm.delta[0] = drwav__bytes_to_s16(header + 2);
                pWav->msadpcm.delta[1] = drwav__bytes_to_s16(header + 4);
                pWav->msadpcm.prevFrames[0][1] = (drwav_int32)drwav__bytes_to_s16(header + 6);
                pWav->msadpcm.prevFrames[1][1] = (drwav_int32)drwav__bytes_to_s16(header + 8);
                pWav->msadpcm.prevFrames[0][0] = (drwav_int32)drwav__bytes_to_s16(header + 10);
                pWav->msadpcm.prevFrames[1][0] = (drwav_int32)drwav__bytes_to_s16(header + 12);

                pWav->msadpcm.cachedFrames[0] = pWav->msadpcm.prevFrames[0][0];
                pWav->msadpcm.cachedFrames[1] = pWav->msadpcm.prevFrames[1][0];
                pWav->msadpcm.cachedFrames[2] = pWav->msadpcm.prevFrames[0][1];
                pWav->msadpcm.cachedFrames[3] = pWav->msadpcm.prevFrames[1][1];
                pWav->msadpcm.cachedFrameCount = 2;
            }
        }

        /* Output anything that's cached. */
        while (framesToRead > 0 && pWav->msadpcm.cachedFrameCount > 0 && pWav->compressed.iCurrentPCMFrame < pWav->totalPCMFrameCount) {
            if (pBufferOut != NULL) {
                drwav_uint32 iSample = 0;
                for (iSample = 0; iSample < pWav->channels; iSample += 1) {
                    pBufferOut[iSample] = (drwav_int16)pWav->msadpcm.cachedFrames[(drwav_countof(pWav->msadpcm.cachedFrames) - (pWav->msadpcm.cachedFrameCount*pWav->channels)) + iSample];
                }

                pBufferOut += pWav->channels;
            }

            framesToRead    -= 1;
            totalFramesRead += 1;
            pWav->compressed.iCurrentPCMFrame += 1;
            pWav->msadpcm.cachedFrameCount -= 1;
        }

        if (framesToRead == 0) {
            return totalFramesRead;
        }


        /*
        If there's nothing left in the cache, just go ahead and load more. If there's nothing left to load in the current block we just continue to the next
        loop iteration which will trigger the loading of a new block.
        */
        if (pWav->msadpcm.cachedFrameCount == 0) {
            if (pWav->msadpcm.bytesRemainingInBlock == 0) {
                continue;
            } else {
                static drwav_int32 adaptationTable[] = { 
                    230, 230, 230, 230, 307, 409, 512, 614, 
                    768, 614, 512, 409, 307, 230, 230, 230 
                };
                static drwav_int32 coeff1Table[] = { 256, 512, 0, 192, 240, 460,  392 };
                static drwav_int32 coeff2Table[] = { 0,  -256, 0, 64,  0,  -208, -232 };

                drwav_uint8 nibbles;
                drwav_int32 nibble0;
                drwav_int32 nibble1;

                if (pWav->onRead(pWav->pUserData, &nibbles, 1) != 1) {
                    return totalFramesRead;
                }
                pWav->msadpcm.bytesRemainingInBlock -= 1;

                /* TODO: Optimize away these if statements. */
                nibble0 = ((nibbles & 0xF0) >> 4); if ((nibbles & 0x80)) { nibble0 |= 0xFFFFFFF0UL; }
                nibble1 = ((nibbles & 0x0F) >> 0); if ((nibbles & 0x08)) { nibble1 |= 0xFFFFFFF0UL; }

                if (pWav->channels == 1) {
                    /* Mono. */
                    drwav_int32 newSample0;
                    drwav_int32 newSample1;

                    newSample0  = ((pWav->msadpcm.prevFrames[0][1] * coeff1Table[pWav->msadpcm.predictor[0]]) + (pWav->msadpcm.prevFrames[0][0] * coeff2Table[pWav->msadpcm.predictor[0]])) >> 8;
                    newSample0 += nibble0 * pWav->msadpcm.delta[0];
                    newSample0  = drwav_clamp(newSample0, -32768, 32767);

                    pWav->msadpcm.delta[0] = (adaptationTable[((nibbles & 0xF0) >> 4)] * pWav->msadpcm.delta[0]) >> 8;
                    if (pWav->msadpcm.delta[0] < 16) {
                        pWav->msadpcm.delta[0] = 16;
                    }

                    pWav->msadpcm.prevFrames[0][0] = pWav->msadpcm.prevFrames[0][1];
                    pWav->msadpcm.prevFrames[0][1] = newSample0;


                    newSample1  = ((pWav->msadpcm.prevFrames[0][1] * coeff1Table[pWav->msadpcm.predictor[0]]) + (pWav->msadpcm.prevFrames[0][0] * coeff2Table[pWav->msadpcm.predictor[0]])) >> 8;
                    newSample1 += nibble1 * pWav->msadpcm.delta[0];
                    newSample1  = drwav_clamp(newSample1, -32768, 32767);

                    pWav->msadpcm.delta[0] = (adaptationTable[((nibbles & 0x0F) >> 0)] * pWav->msadpcm.delta[0]) >> 8;
                    if (pWav->msadpcm.delta[0] < 16) {
                        pWav->msadpcm.delta[0] = 16;
                    }

                    pWav->msadpcm.prevFrames[0][0] = pWav->msadpcm.prevFrames[0][1];
                    pWav->msadpcm.prevFrames[0][1] = newSample1;


                    pWav->msadpcm.cachedFrames[2] = newSample0;
                    pWav->msadpcm.cachedFrames[3] = newSample1;
                    pWav->msadpcm.cachedFrameCount = 2;
                } else {
                    /* Stereo. */
                    drwav_int32 newSample0;
                    drwav_int32 newSample1;

                    /* Left. */
                    newSample0  = ((pWav->msadpcm.prevFrames[0][1] * coeff1Table[pWav->msadpcm.predictor[0]]) + (pWav->msadpcm.prevFrames[0][0] * coeff2Table[pWav->msadpcm.predictor[0]])) >> 8;
                    newSample0 += nibble0 * pWav->msadpcm.delta[0];
                    newSample0  = drwav_clamp(newSample0, -32768, 32767);

                    pWav->msadpcm.delta[0] = (adaptationTable[((nibbles & 0xF0) >> 4)] * pWav->msadpcm.delta[0]) >> 8;
                    if (pWav->msadpcm.delta[0] < 16) {
                        pWav->msadpcm.delta[0] = 16;
                    }

                    pWav->msadpcm.prevFrames[0][0] = pWav->msadpcm.prevFrames[0][1];
                    pWav->msadpcm.prevFrames[0][1] = newSample0;


                    /* Right. */
                    newSample1  = ((pWav->msadpcm.prevFrames[1][1] * coeff1Table[pWav->msadpcm.predictor[1]]) + (pWav->msadpcm.prevFrames[1][0] * coeff2Table[pWav->msadpcm.predictor[1]])) >> 8;
                    newSample1 += nibble1 * pWav->msadpcm.delta[1];
                    newSample1  = drwav_clamp(newSample1, -32768, 32767);

                    pWav->msadpcm.delta[1] = (adaptationTable[((nibbles & 0x0F) >> 0)] * pWav->msadpcm.delta[1]) >> 8;
                    if (pWav->msadpcm.delta[1] < 16) {
                        pWav->msadpcm.delta[1] = 16;
                    }

                    pWav->msadpcm.prevFrames[1][0] = pWav->msadpcm.prevFrames[1][1];
                    pWav->msadpcm.prevFrames[1][1] = newSample1;

                    pWav->msadpcm.cachedFrames[2] = newSample0;
                    pWav->msadpcm.cachedFrames[3] = newSample1;
                    pWav->msadpcm.cachedFrameCount = 1;
                }
            }
        }
    }

    return totalFramesRead;
}


static drwav_uint64 drwav_read_pcm_frames_s16__ima(drwav* pWav, drwav_uint64 framesToRead, drwav_int16* pBufferOut)
{
    drwav_uint64 totalFramesRead = 0;
    drwav_uint32 iChannel;

    static drwav_int32 indexTable[16] = {
        -1, -1, -1, -1, 2, 4, 6, 8,
        -1, -1, -1, -1, 2, 4, 6, 8
    };

    static drwav_int32 stepTable[89] = {
        7,     8,     9,     10,    11,    12,    13,    14,    16,    17, 
        19,    21,    23,    25,    28,    31,    34,    37,    41,    45, 
        50,    55,    60,    66,    73,    80,    88,    97,    107,   118, 
        130,   143,   157,   173,   190,   209,   230,   253,   279,   307,
        337,   371,   408,   449,   494,   544,   598,   658,   724,   796,
        876,   963,   1060,  1166,  1282,  1411,  1552,  1707,  1878,  2066, 
        2272,  2499,  2749,  3024,  3327,  3660,  4026,  4428,  4871,  5358,
        5894,  6484,  7132,  7845,  8630,  9493,  10442, 11487, 12635, 13899, 
        15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767 
    };

    DRWAV_ASSERT(pWav != NULL);
    DRWAV_ASSERT(framesToRead > 0);

    /* TODO: Lots of room for optimization here. */

    while (framesToRead > 0 && pWav->compressed.iCurrentPCMFrame < pWav->totalPCMFrameCount) {
        /* If there are no cached samples we need to load a new block. */
        if (pWav->ima.cachedFrameCount == 0 && pWav->ima.bytesRemainingInBlock == 0) {
            if (pWav->channels == 1) {
                /* Mono. */
                drwav_uint8 header[4];
                if (pWav->onRead(pWav->pUserData, header, sizeof(header)) != sizeof(header)) {
                    return totalFramesRead;
                }
                pWav->ima.bytesRemainingInBlock = pWav->fmt.blockAlign - sizeof(header);

                if (header[2] >= drwav_countof(stepTable)) {
                    pWav->onSeek(pWav->pUserData, pWav->ima.bytesRemainingInBlock, drwav_seek_origin_current);
                    pWav->ima.bytesRemainingInBlock = 0;
                    return totalFramesRead; /* Invalid data. */
                }

                pWav->ima.predictor[0] = drwav__bytes_to_s16(header + 0);
                pWav->ima.stepIndex[0] = header[2];
                pWav->ima.cachedFrames[drwav_countof(pWav->ima.cachedFrames) - 1] = pWav->ima.predictor[0];
                pWav->ima.cachedFrameCount = 1;
            } else {
                /* Stereo. */
                drwav_uint8 header[8];
                if (pWav->onRead(pWav->pUserData, header, sizeof(header)) != sizeof(header)) {
                    return totalFramesRead;
                }
                pWav->ima.bytesRemainingInBlock = pWav->fmt.blockAlign - sizeof(header);

                if (header[2] >= drwav_countof(stepTable) || header[6] >= drwav_countof(stepTable)) {
                    pWav->onSeek(pWav->pUserData, pWav->ima.bytesRemainingInBlock, drwav_seek_origin_current);
                    pWav->ima.bytesRemainingInBlock = 0;
                    return totalFramesRead; /* Invalid data. */
                }

                pWav->ima.predictor[0] = drwav__bytes_to_s16(header + 0);
                pWav->ima.stepIndex[0] = header[2];
                pWav->ima.predictor[1] = drwav__bytes_to_s16(header + 4);
                pWav->ima.stepIndex[1] = header[6];

                pWav->ima.cachedFrames[drwav_countof(pWav->ima.cachedFrames) - 2] = pWav->ima.predictor[0];
                pWav->ima.cachedFrames[drwav_countof(pWav->ima.cachedFrames) - 1] = pWav->ima.predictor[1];
                pWav->ima.cachedFrameCount = 1;
            }
        }

        /* Output anything that's cached. */
        while (framesToRead > 0 && pWav->ima.cachedFrameCount > 0 && pWav->compressed.iCurrentPCMFrame < pWav->totalPCMFrameCount) {
            if (pBufferOut != NULL) {
                drwav_uint32 iSample;
                for (iSample = 0; iSample < pWav->channels; iSample += 1) {
                    pBufferOut[iSample] = (drwav_int16)pWav->ima.cachedFrames[(drwav_countof(pWav->ima.cachedFrames) - (pWav->ima.cachedFrameCount*pWav->channels)) + iSample];
                }
                pBufferOut += pWav->channels;
            }

            framesToRead    -= 1;
            totalFramesRead += 1;
            pWav->compressed.iCurrentPCMFrame += 1;
            pWav->ima.cachedFrameCount -= 1;
        }

        if (framesToRead == 0) {
            return totalFramesRead;
        }

        /*
        If there's nothing left in the cache, just go ahead and load more. If there's nothing left to load in the current block we just continue to the next
        loop iteration which will trigger the loading of a new block.
        */
        if (pWav->ima.cachedFrameCount == 0) {
            if (pWav->ima.bytesRemainingInBlock == 0) {
                continue;
            } else {
                /*
                From what I can tell with stereo streams, it looks like every 4 bytes (8 samples) is for one channel. So it goes 4 bytes for the
                left channel, 4 bytes for the right channel.
                */
                pWav->ima.cachedFrameCount = 8;
                for (iChannel = 0; iChannel < pWav->channels; ++iChannel) {
                    drwav_uint32 iByte;
                    drwav_uint8 nibbles[4];
                    if (pWav->onRead(pWav->pUserData, &nibbles, 4) != 4) {
                        pWav->ima.cachedFrameCount = 0;
                        return totalFramesRead;
                    }
                    pWav->ima.bytesRemainingInBlock -= 4;

                    for (iByte = 0; iByte < 4; ++iByte) {
                        drwav_uint8 nibble0 = ((nibbles[iByte] & 0x0F) >> 0);
                        drwav_uint8 nibble1 = ((nibbles[iByte] & 0xF0) >> 4);

                        drwav_int32 step      = stepTable[pWav->ima.stepIndex[iChannel]];
                        drwav_int32 predictor = pWav->ima.predictor[iChannel];

                        drwav_int32      diff  = step >> 3;
                        if (nibble0 & 1) diff += step >> 2;
                        if (nibble0 & 2) diff += step >> 1;
                        if (nibble0 & 4) diff += step;
                        if (nibble0 & 8) diff  = -diff;

                        predictor = drwav_clamp(predictor + diff, -32768, 32767);
                        pWav->ima.predictor[iChannel] = predictor;
                        pWav->ima.stepIndex[iChannel] = drwav_clamp(pWav->ima.stepIndex[iChannel] + indexTable[nibble0], 0, (drwav_int32)drwav_countof(stepTable)-1);
                        pWav->ima.cachedFrames[(drwav_countof(pWav->ima.cachedFrames) - (pWav->ima.cachedFrameCount*pWav->channels)) + (iByte*2+0)*pWav->channels + iChannel] = predictor;


                        step      = stepTable[pWav->ima.stepIndex[iChannel]];
                        predictor = pWav->ima.predictor[iChannel];

                                         diff  = step >> 3;
                        if (nibble1 & 1) diff += step >> 2;
                        if (nibble1 & 2) diff += step >> 1;
                        if (nibble1 & 4) diff += step;
                        if (nibble1 & 8) diff  = -diff;

                        predictor = drwav_clamp(predictor + diff, -32768, 32767);
                        pWav->ima.predictor[iChannel] = predictor;
                        pWav->ima.stepIndex[iChannel] = drwav_clamp(pWav->ima.stepIndex[iChannel] + indexTable[nibble1], 0, (drwav_int32)drwav_countof(stepTable)-1);
                        pWav->ima.cachedFrames[(drwav_countof(pWav->ima.cachedFrames) - (pWav->ima.cachedFrameCount*pWav->channels)) + (iByte*2+1)*pWav->channels + iChannel] = predictor;
                    }
                }
            }
        }
    }

    return totalFramesRead;
}


#ifndef DR_WAV_NO_CONVERSION_API
static unsigned short g_drwavAlawTable[256] = {
    0xEA80, 0xEB80, 0xE880, 0xE980, 0xEE80, 0xEF80, 0xEC80, 0xED80, 0xE280, 0xE380, 0xE080, 0xE180, 0xE680, 0xE780, 0xE480, 0xE580, 
    0xF540, 0xF5C0, 0xF440, 0xF4C0, 0xF740, 0xF7C0, 0xF640, 0xF6C0, 0xF140, 0xF1C0, 0xF040, 0xF0C0, 0xF340, 0xF3C0, 0xF240, 0xF2C0, 
    0xAA00, 0xAE00, 0xA200, 0xA600, 0xBA00, 0xBE00, 0xB200, 0xB600, 0x8A00, 0x8E00, 0x8200, 0x8600, 0x9A00, 0x9E00, 0x9200, 0x9600, 
    0xD500, 0xD700, 0xD100, 0xD300, 0xDD00, 0xDF00, 0xD900, 0xDB00, 0xC500, 0xC700, 0xC100, 0xC300, 0xCD00, 0xCF00, 0xC900, 0xCB00, 
    0xFEA8, 0xFEB8, 0xFE88, 0xFE98, 0xFEE8, 0xFEF8, 0xFEC8, 0xFED8, 0xFE28, 0xFE38, 0xFE08, 0xFE18, 0xFE68, 0xFE78, 0xFE48, 0xFE58, 
    0xFFA8, 0xFFB8, 0xFF88, 0xFF98, 0xFFE8, 0xFFF8, 0xFFC8, 0xFFD8, 0xFF28, 0xFF38, 0xFF08, 0xFF18, 0xFF68, 0xFF78, 0xFF48, 0xFF58, 
    0xFAA0, 0xFAE0, 0xFA20, 0xFA60, 0xFBA0, 0xFBE0, 0xFB20, 0xFB60, 0xF8A0, 0xF8E0, 0xF820, 0xF860, 0xF9A0, 0xF9E0, 0xF920, 0xF960, 
    0xFD50, 0xFD70, 0xFD10, 0xFD30, 0xFDD0, 0xFDF0, 0xFD90, 0xFDB0, 0xFC50, 0xFC70, 0xFC10, 0xFC30, 0xFCD0, 0xFCF0, 0xFC90, 0xFCB0, 
    0x1580, 0x1480, 0x1780, 0x1680, 0x1180, 0x1080, 0x1380, 0x1280, 0x1D80, 0x1C80, 0x1F80, 0x1E80, 0x1980, 0x1880, 0x1B80, 0x1A80, 
    0x0AC0, 0x0A40, 0x0BC0, 0x0B40, 0x08C0, 0x0840, 0x09C0, 0x0940, 0x0EC0, 0x0E40, 0x0FC0, 0x0F40, 0x0CC0, 0x0C40, 0x0DC0, 0x0D40, 
    0x5600, 0x5200, 0x5E00, 0x5A00, 0x4600, 0x4200, 0x4E00, 0x4A00, 0x7600, 0x7200, 0x7E00, 0x7A00, 0x6600, 0x6200, 0x6E00, 0x6A00, 
    0x2B00, 0x2900, 0x2F00, 0x2D00, 0x2300, 0x2100, 0x2700, 0x2500, 0x3B00, 0x3900, 0x3F00, 0x3D00, 0x3300, 0x3100, 0x3700, 0x3500, 
    0x0158, 0x0148, 0x0178, 0x0168, 0x0118, 0x0108, 0x0138, 0x0128, 0x01D8, 0x01C8, 0x01F8, 0x01E8, 0x0198, 0x0188, 0x01B8, 0x01A8, 
    0x0058, 0x0048, 0x0078, 0x0068, 0x0018, 0x0008, 0x0038, 0x0028, 0x00D8, 0x00C8, 0x00F8, 0x00E8, 0x0098, 0x0088, 0x00B8, 0x00A8, 
    0x0560, 0x0520, 0x05E0, 0x05A0, 0x0460, 0x0420, 0x04E0, 0x04A0, 0x0760, 0x0720, 0x07E0, 0x07A0, 0x0660, 0x0620, 0x06E0, 0x06A0, 
    0x02B0, 0x0290, 0x02F0, 0x02D0, 0x0230, 0x0210, 0x0270, 0x0250, 0x03B0, 0x0390, 0x03F0, 0x03D0, 0x0330, 0x0310, 0x0370, 0x0350
};

static unsigned short g_drwavMulawTable[256] = {
    0x8284, 0x8684, 0x8A84, 0x8E84, 0x9284, 0x9684, 0x9A84, 0x9E84, 0xA284, 0xA684, 0xAA84, 0xAE84, 0xB284, 0xB684, 0xBA84, 0xBE84, 
    0xC184, 0xC384, 0xC584, 0xC784, 0xC984, 0xCB84, 0xCD84, 0xCF84, 0xD184, 0xD384, 0xD584, 0xD784, 0xD984, 0xDB84, 0xDD84, 0xDF84, 
    0xE104, 0xE204, 0xE304, 0xE404, 0xE504, 0xE604, 0xE704, 0xE804, 0xE904, 0xEA04, 0xEB04, 0xEC04, 0xED04, 0xEE04, 0xEF04, 0xF004, 
    0xF0C4, 0xF144, 0xF1C4, 0xF244, 0xF2C4, 0xF344, 0xF3C4, 0xF444, 0xF4C4, 0xF544, 0xF5C4, 0xF644, 0xF6C4, 0xF744, 0xF7C4, 0xF844, 
    0xF8A4, 0xF8E4, 0xF924, 0xF964, 0xF9A4, 0xF9E4, 0xFA24, 0xFA64, 0xFAA4, 0xFAE4, 0xFB24, 0xFB64, 0xFBA4, 0xFBE4, 0xFC24, 0xFC64, 
    0xFC94, 0xFCB4, 0xFCD4, 0xFCF4, 0xFD14, 0xFD34, 0xFD54, 0xFD74, 0xFD94, 0xFDB4, 0xFDD4, 0xFDF4, 0xFE14, 0xFE34, 0xFE54, 0xFE74, 
    0xFE8C, 0xFE9C, 0xFEAC, 0xFEBC, 0xFECC, 0xFEDC, 0xFEEC, 0xFEFC, 0xFF0C, 0xFF1C, 0xFF2C, 0xFF3C, 0xFF4C, 0xFF5C, 0xFF6C, 0xFF7C, 
    0xFF88, 0xFF90, 0xFF98, 0xFFA0, 0xFFA8, 0xFFB0, 0xFFB8, 0xFFC0, 0xFFC8, 0xFFD0, 0xFFD8, 0xFFE0, 0xFFE8, 0xFFF0, 0xFFF8, 0x0000, 
    0x7D7C, 0x797C, 0x757C, 0x717C, 0x6D7C, 0x697C, 0x657C, 0x617C, 0x5D7C, 0x597C, 0x557C, 0x517C, 0x4D7C, 0x497C, 0x457C, 0x417C, 
    0x3E7C, 0x3C7C, 0x3A7C, 0x387C, 0x367C, 0x347C, 0x327C, 0x307C, 0x2E7C, 0x2C7C, 0x2A7C, 0x287C, 0x267C, 0x247C, 0x227C, 0x207C, 
    0x1EFC, 0x1DFC, 0x1CFC, 0x1BFC, 0x1AFC, 0x19FC, 0x18FC, 0x17FC, 0x16FC, 0x15FC, 0x14FC, 0x13FC, 0x12FC, 0x11FC, 0x10FC, 0x0FFC, 
    0x0F3C, 0x0EBC, 0x0E3C, 0x0DBC, 0x0D3C, 0x0CBC, 0x0C3C, 0x0BBC, 0x0B3C, 0x0ABC, 0x0A3C, 0x09BC, 0x093C, 0x08BC, 0x083C, 0x07BC, 
    0x075C, 0x071C, 0x06DC, 0x069C, 0x065C, 0x061C, 0x05DC, 0x059C, 0x055C, 0x051C, 0x04DC, 0x049C, 0x045C, 0x041C, 0x03DC, 0x039C, 
    0x036C, 0x034C, 0x032C, 0x030C, 0x02EC, 0x02CC, 0x02AC, 0x028C, 0x026C, 0x024C, 0x022C, 0x020C, 0x01EC, 0x01CC, 0x01AC, 0x018C, 
    0x0174, 0x0164, 0x0154, 0x0144, 0x0134, 0x0124, 0x0114, 0x0104, 0x00F4, 0x00E4, 0x00D4, 0x00C4, 0x00B4, 0x00A4, 0x0094, 0x0084, 
    0x0078, 0x0070, 0x0068, 0x0060, 0x0058, 0x0050, 0x0048, 0x0040, 0x0038, 0x0030, 0x0028, 0x0020, 0x0018, 0x0010, 0x0008, 0x0000
};

static DRWAV_INLINE drwav_int16 drwav__alaw_to_s16(drwav_uint8 sampleIn)
{
    return (short)g_drwavAlawTable[sampleIn];
}

static DRWAV_INLINE drwav_int16 drwav__mulaw_to_s16(drwav_uint8 sampleIn)
{
    return (short)g_drwavMulawTable[sampleIn];
}



static void drwav__pcm_to_s16(drwav_int16* pOut, const drwav_uint8* pIn, size_t totalSampleCount, unsigned int bytesPerSample)
{
    unsigned int i;

    /* Special case for 8-bit sample data because it's treated as unsigned. */
    if (bytesPerSample == 1) {
        drwav_u8_to_s16(pOut, pIn, totalSampleCount);
        return;
    }


    /* Slightly more optimal implementation for common formats. */
    if (bytesPerSample == 2) {
        for (i = 0; i < totalSampleCount; ++i) {
           *pOut++ = ((const drwav_int16*)pIn)[i];
        }
        return;
    }
    if (bytesPerSample == 3) {
        drwav_s24_to_s16(pOut, pIn, totalSampleCount);
        return;
    }
    if (bytesPerSample == 4) {
        drwav_s32_to_s16(pOut, (const drwav_int32*)pIn, totalSampleCount);
        return;
    }


    /* Anything more than 64 bits per sample is not supported. */
    if (bytesPerSample > 8) {
        DRWAV_ZERO_MEMORY(pOut, totalSampleCount * sizeof(*pOut));
        return;
    }


    /* Generic, slow converter. */
    for (i = 0; i < totalSampleCount; ++i) {
        drwav_uint64 sample = 0;
        unsigned int shift  = (8 - bytesPerSample) * 8;

        unsigned int j;
        for (j = 0; j < bytesPerSample; j += 1) {
            DRWAV_ASSERT(j < 8);
            sample |= (drwav_uint64)(pIn[j]) << shift;
            shift  += 8;
        }

        pIn += j;
        *pOut++ = (drwav_int16)((drwav_int64)sample >> 48);
    }
}

static void drwav__ieee_to_s16(drwav_int16* pOut, const drwav_uint8* pIn, size_t totalSampleCount, unsigned int bytesPerSample)
{
    if (bytesPerSample == 4) {
        drwav_f32_to_s16(pOut, (const float*)pIn, totalSampleCount);
        return;
    } else if (bytesPerSample == 8) {
        drwav_f64_to_s16(pOut, (const double*)pIn, totalSampleCount);
        return;
    } else {
        /* Only supporting 32- and 64-bit float. Output silence in all other cases. Contributions welcome for 16-bit float. */
        DRWAV_ZERO_MEMORY(pOut, totalSampleCount * sizeof(*pOut));
        return;
    }
}

static drwav_uint64 drwav_read_pcm_frames_s16__pcm(drwav* pWav, drwav_uint64 framesToRead, drwav_int16* pBufferOut)
{
    drwav_uint32 bytesPerFrame;
    drwav_uint64 totalFramesRead;
    drwav_uint8 sampleData[4096];

    /* Fast path. */
    if ((pWav->translatedFormatTag == DR_WAVE_FORMAT_PCM && pWav->bitsPerSample == 16) || pBufferOut == NULL) {
        return drwav_read_pcm_frames(pWav, framesToRead, pBufferOut);
    }
    
    bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav);
    if (bytesPerFrame == 0) {
        return 0;
    }

    totalFramesRead = 0;
    
    while (framesToRead > 0) {
        drwav_uint64 framesRead = drwav_read_pcm_frames(pWav, drwav_min(framesToRead, sizeof(sampleData)/bytesPerFrame), sampleData);
        if (framesRead == 0) {
            break;
        }

        drwav__pcm_to_s16(pBufferOut, sampleData, (size_t)(framesRead*pWav->channels), bytesPerFrame/pWav->channels);

        pBufferOut      += framesRead*pWav->channels;
        framesToRead    -= framesRead;
        totalFramesRead += framesRead;
    }

    return totalFramesRead;
}

static drwav_uint64 drwav_read_pcm_frames_s16__ieee(drwav* pWav, drwav_uint64 framesToRead, drwav_int16* pBufferOut)
{
    drwav_uint64 totalFramesRead;
    drwav_uint8 sampleData[4096];
    drwav_uint32 bytesPerFrame;

    if (pBufferOut == NULL) {
        return drwav_read_pcm_frames(pWav, framesToRead, NULL);
    }

    bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav);
    if (bytesPerFrame == 0) {
        return 0;
    }

    totalFramesRead = 0;
    
    while (framesToRead > 0) {
        drwav_uint64 framesRead = drwav_read_pcm_frames(pWav, drwav_min(framesToRead, sizeof(sampleData)/bytesPerFrame), sampleData);
        if (framesRead == 0) {
            break;
        }

        drwav__ieee_to_s16(pBufferOut, sampleData, (size_t)(framesRead*pWav->channels), bytesPerFrame/pWav->channels);

        pBufferOut      += framesRead*pWav->channels;
        framesToRead    -= framesRead;
        totalFramesRead += framesRead;
    }

    return totalFramesRead;
}

static drwav_uint64 drwav_read_pcm_frames_s16__alaw(drwav* pWav, drwav_uint64 framesToRead, drwav_int16* pBufferOut)
{
    drwav_uint64 totalFramesRead;
    drwav_uint8 sampleData[4096];
    drwav_uint32 bytesPerFrame;

    if (pBufferOut == NULL) {
        return drwav_read_pcm_frames(pWav, framesToRead, NULL);
    }

    bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav);
    if (bytesPerFrame == 0) {
        return 0;
    }

    totalFramesRead = 0;
    
    while (framesToRead > 0) {
        drwav_uint64 framesRead = drwav_read_pcm_frames(pWav, drwav_min(framesToRead, sizeof(sampleData)/bytesPerFrame), sampleData);
        if (framesRead == 0) {
            break;
        }

        drwav_alaw_to_s16(pBufferOut, sampleData, (size_t)(framesRead*pWav->channels));

        pBufferOut      += framesRead*pWav->channels;
        framesToRead    -= framesRead;
        totalFramesRead += framesRead;
    }

    return totalFramesRead;
}

static drwav_uint64 drwav_read_pcm_frames_s16__mulaw(drwav* pWav, drwav_uint64 framesToRead, drwav_int16* pBufferOut)
{
    drwav_uint64 totalFramesRead;
    drwav_uint8 sampleData[4096];
    drwav_uint32 bytesPerFrame;

    if (pBufferOut == NULL) {
        return drwav_read_pcm_frames(pWav, framesToRead, NULL);
    }

    bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav);
    if (bytesPerFrame == 0) {
        return 0;
    }

    totalFramesRead = 0;

    while (framesToRead > 0) {
        drwav_uint64 framesRead = drwav_read_pcm_frames(pWav, drwav_min(framesToRead, sizeof(sampleData)/bytesPerFrame), sampleData);
        if (framesRead == 0) {
            break;
        }

        drwav_mulaw_to_s16(pBufferOut, sampleData, (size_t)(framesRead*pWav->channels));

        pBufferOut      += framesRead*pWav->channels;
        framesToRead    -= framesRead;
        totalFramesRead += framesRead;
    }

    return totalFramesRead;
}

DRWAV_API drwav_uint64 drwav_read_pcm_frames_s16(drwav* pWav, drwav_uint64 framesToRead, drwav_int16* pBufferOut)
{
    if (pWav == NULL || framesToRead == 0) {
        return 0;
    }

    if (pBufferOut == NULL) {
        return drwav_read_pcm_frames(pWav, framesToRead, NULL);
    }

    /* Don't try to read more samples than can potentially fit in the output buffer. */
    if (framesToRead * pWav->channels * sizeof(drwav_int16) > DRWAV_SIZE_MAX) {
        framesToRead = DRWAV_SIZE_MAX / sizeof(drwav_int16) / pWav->channels;
    }

    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_PCM) {
        return drwav_read_pcm_frames_s16__pcm(pWav, framesToRead, pBufferOut);
    }

    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_IEEE_FLOAT) {
        return drwav_read_pcm_frames_s16__ieee(pWav, framesToRead, pBufferOut);
    }

    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_ALAW) {
        return drwav_read_pcm_frames_s16__alaw(pWav, framesToRead, pBufferOut);
    }

    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_MULAW) {
        return drwav_read_pcm_frames_s16__mulaw(pWav, framesToRead, pBufferOut);
    }

    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_ADPCM) {
        return drwav_read_pcm_frames_s16__msadpcm(pWav, framesToRead, pBufferOut);
    }

    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_DVI_ADPCM) {
        return drwav_read_pcm_frames_s16__ima(pWav, framesToRead, pBufferOut);
    }

    return 0;
}

DRWAV_API drwav_uint64 drwav_read_pcm_frames_s16le(drwav* pWav, drwav_uint64 framesToRead, drwav_int16* pBufferOut)
{
    drwav_uint64 framesRead = drwav_read_pcm_frames_s16(pWav, framesToRead, pBufferOut);
    if (pBufferOut != NULL && drwav__is_little_endian() == DRWAV_FALSE) {
        drwav__bswap_samples_s16(pBufferOut, framesRead*pWav->channels);
    }

    return framesRead;
}

DRWAV_API drwav_uint64 drwav_read_pcm_frames_s16be(drwav* pWav, drwav_uint64 framesToRead, drwav_int16* pBufferOut)
{
    drwav_uint64 framesRead = drwav_read_pcm_frames_s16(pWav, framesToRead, pBufferOut);
    if (pBufferOut != NULL && drwav__is_little_endian() == DRWAV_TRUE) {
        drwav__bswap_samples_s16(pBufferOut, framesRead*pWav->channels);
    }

    return framesRead;
}


DRWAV_API void drwav_u8_to_s16(drwav_int16* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    int r;
    size_t i;
    for (i = 0; i < sampleCount; ++i) {
        int x = pIn[i];
        r = x << 8;
        r = r - 32768;
        pOut[i] = (short)r;
    }
}

DRWAV_API void drwav_s24_to_s16(drwav_int16* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    int r;
    size_t i;
    for (i = 0; i < sampleCount; ++i) {
        int x = ((int)(((unsigned int)(((const drwav_uint8*)pIn)[i*3+0]) << 8) | ((unsigned int)(((const drwav_uint8*)pIn)[i*3+1]) << 16) | ((unsigned int)(((const drwav_uint8*)pIn)[i*3+2])) << 24)) >> 8;
        r = x >> 8;
        pOut[i] = (short)r;
    }
}

DRWAV_API void drwav_s32_to_s16(drwav_int16* pOut, const drwav_int32* pIn, size_t sampleCount)
{
    int r;
    size_t i;
    for (i = 0; i < sampleCount; ++i) {
        int x = pIn[i];
        r = x >> 16;
        pOut[i] = (short)r;
    }
}

DRWAV_API void drwav_f32_to_s16(drwav_int16* pOut, const float* pIn, size_t sampleCount)
{
    int r;
    size_t i;
    for (i = 0; i < sampleCount; ++i) {
        float x = pIn[i];
        float c;
        c = ((x < -1) ? -1 : ((x > 1) ? 1 : x));
        c = c + 1;
        r = (int)(c * 32767.5f);
        r = r - 32768;
        pOut[i] = (short)r;
    }
}

DRWAV_API void drwav_f64_to_s16(drwav_int16* pOut, const double* pIn, size_t sampleCount)
{
    int r;
    size_t i;
    for (i = 0; i < sampleCount; ++i) {
        double x = pIn[i];
        double c;
        c = ((x < -1) ? -1 : ((x > 1) ? 1 : x));
        c = c + 1;
        r = (int)(c * 32767.5);
        r = r - 32768;
        pOut[i] = (short)r;
    }
}

DRWAV_API void drwav_alaw_to_s16(drwav_int16* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    size_t i;
    for (i = 0; i < sampleCount; ++i) {
        pOut[i] = drwav__alaw_to_s16(pIn[i]);
    }
}

DRWAV_API void drwav_mulaw_to_s16(drwav_int16* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    size_t i;
    for (i = 0; i < sampleCount; ++i) {
        pOut[i] = drwav__mulaw_to_s16(pIn[i]);
    }
}



static void drwav__pcm_to_f32(float* pOut, const drwav_uint8* pIn, size_t sampleCount, unsigned int bytesPerSample)
{
    unsigned int i;

    /* Special case for 8-bit sample data because it's treated as unsigned. */
    if (bytesPerSample == 1) {
        drwav_u8_to_f32(pOut, pIn, sampleCount);
        return;
    }

    /* Slightly more optimal implementation for common formats. */
    if (bytesPerSample == 2) {
        drwav_s16_to_f32(pOut, (const drwav_int16*)pIn, sampleCount);
        return;
    }
    if (bytesPerSample == 3) {
        drwav_s24_to_f32(pOut, pIn, sampleCount);
        return;
    }
    if (bytesPerSample == 4) {
        drwav_s32_to_f32(pOut, (const drwav_int32*)pIn, sampleCount);
        return;
    }


    /* Anything more than 64 bits per sample is not supported. */
    if (bytesPerSample > 8) {
        DRWAV_ZERO_MEMORY(pOut, sampleCount * sizeof(*pOut));
        return;
    }


    /* Generic, slow converter. */
    for (i = 0; i < sampleCount; ++i) {
        drwav_uint64 sample = 0;
        unsigned int shift  = (8 - bytesPerSample) * 8;

        unsigned int j;
        for (j = 0; j < bytesPerSample; j += 1) {
            DRWAV_ASSERT(j < 8);
            sample |= (drwav_uint64)(pIn[j]) << shift;
            shift  += 8;
        }

        pIn += j;
        *pOut++ = (float)((drwav_int64)sample / 9223372036854775807.0);
    }
}

static void drwav__ieee_to_f32(float* pOut, const drwav_uint8* pIn, size_t sampleCount, unsigned int bytesPerSample)
{
    if (bytesPerSample == 4) {
        unsigned int i;
        for (i = 0; i < sampleCount; ++i) {
            *pOut++ = ((const float*)pIn)[i];
        }
        return;
    } else if (bytesPerSample == 8) {
        drwav_f64_to_f32(pOut, (const double*)pIn, sampleCount);
        return;
    } else {
        /* Only supporting 32- and 64-bit float. Output silence in all other cases. Contributions welcome for 16-bit float. */
        DRWAV_ZERO_MEMORY(pOut, sampleCount * sizeof(*pOut));
        return;
    }
}


static drwav_uint64 drwav_read_pcm_frames_f32__pcm(drwav* pWav, drwav_uint64 framesToRead, float* pBufferOut)
{
    drwav_uint64 totalFramesRead;
    drwav_uint8 sampleData[4096];

    drwav_uint32 bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav);
    if (bytesPerFrame == 0) {
        return 0;
    }

    totalFramesRead = 0;

    while (framesToRead > 0) {
        drwav_uint64 framesRead = drwav_read_pcm_frames(pWav, drwav_min(framesToRead, sizeof(sampleData)/bytesPerFrame), sampleData);
        if (framesRead == 0) {
            break;
        }

        drwav__pcm_to_f32(pBufferOut, sampleData, (size_t)framesRead*pWav->channels, bytesPerFrame/pWav->channels);

        pBufferOut      += framesRead*pWav->channels;
        framesToRead    -= framesRead;
        totalFramesRead += framesRead;
    }

    return totalFramesRead;
}

static drwav_uint64 drwav_read_pcm_frames_f32__msadpcm(drwav* pWav, drwav_uint64 framesToRead, float* pBufferOut)
{
    /*
    We're just going to borrow the implementation from the drwav_read_s16() since ADPCM is a little bit more complicated than other formats and I don't
    want to duplicate that code.
    */
    drwav_uint64 totalFramesRead = 0;
    drwav_int16 samples16[2048];
    while (framesToRead > 0) {
        drwav_uint64 framesRead = drwav_read_pcm_frames_s16(pWav, drwav_min(framesToRead, drwav_countof(samples16)/pWav->channels), samples16);
        if (framesRead == 0) {
            break;
        }

        drwav_s16_to_f32(pBufferOut, samples16, (size_t)(framesRead*pWav->channels));   /* <-- Safe cast because we're clamping to 2048. */

        pBufferOut      += framesRead*pWav->channels;
        framesToRead    -= framesRead;
        totalFramesRead += framesRead;
    }

    return totalFramesRead;
}

static drwav_uint64 drwav_read_pcm_frames_f32__ima(drwav* pWav, drwav_uint64 framesToRead, float* pBufferOut)
{
    /*
    We're just going to borrow the implementation from the drwav_read_s16() since IMA-ADPCM is a little bit more complicated than other formats and I don't
    want to duplicate that code.
    */
    drwav_uint64 totalFramesRead = 0;
    drwav_int16 samples16[2048];
    while (framesToRead > 0) {
        drwav_uint64 framesRead = drwav_read_pcm_frames_s16(pWav, drwav_min(framesToRead, drwav_countof(samples16)/pWav->channels), samples16);
        if (framesRead == 0) {
            break;
        }

        drwav_s16_to_f32(pBufferOut, samples16, (size_t)(framesRead*pWav->channels));   /* <-- Safe cast because we're clamping to 2048. */

        pBufferOut      += framesRead*pWav->channels;
        framesToRead    -= framesRead;
        totalFramesRead += framesRead;
    }

    return totalFramesRead;
}

static drwav_uint64 drwav_read_pcm_frames_f32__ieee(drwav* pWav, drwav_uint64 framesToRead, float* pBufferOut)
{
    drwav_uint64 totalFramesRead;
    drwav_uint8 sampleData[4096];
    drwav_uint32 bytesPerFrame;

    /* Fast path. */
    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_IEEE_FLOAT && pWav->bitsPerSample == 32) {
        return drwav_read_pcm_frames(pWav, framesToRead, pBufferOut);
    }
    
    bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav);
    if (bytesPerFrame == 0) {
        return 0;
    }

    totalFramesRead = 0;

    while (framesToRead > 0) {
        drwav_uint64 framesRead = drwav_read_pcm_frames(pWav, drwav_min(framesToRead, sizeof(sampleData)/bytesPerFrame), sampleData);
        if (framesRead == 0) {
            break;
        }

        drwav__ieee_to_f32(pBufferOut, sampleData, (size_t)(framesRead*pWav->channels), bytesPerFrame/pWav->channels);

        pBufferOut      += framesRead*pWav->channels;
        framesToRead    -= framesRead;
        totalFramesRead += framesRead;
    }

    return totalFramesRead;
}

static drwav_uint64 drwav_read_pcm_frames_f32__alaw(drwav* pWav, drwav_uint64 framesToRead, float* pBufferOut)
{
    drwav_uint64 totalFramesRead;
    drwav_uint8 sampleData[4096];
    drwav_uint32 bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav);
    if (bytesPerFrame == 0) {
        return 0;
    }

    totalFramesRead = 0;

    while (framesToRead > 0) {
        drwav_uint64 framesRead = drwav_read_pcm_frames(pWav, drwav_min(framesToRead, sizeof(sampleData)/bytesPerFrame), sampleData);
        if (framesRead == 0) {
            break;
        }

        drwav_alaw_to_f32(pBufferOut, sampleData, (size_t)(framesRead*pWav->channels));

        pBufferOut      += framesRead*pWav->channels;
        framesToRead    -= framesRead;
        totalFramesRead += framesRead;
    }

    return totalFramesRead;
}

static drwav_uint64 drwav_read_pcm_frames_f32__mulaw(drwav* pWav, drwav_uint64 framesToRead, float* pBufferOut)
{
    drwav_uint64 totalFramesRead;
    drwav_uint8 sampleData[4096];

    drwav_uint32 bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav);
    if (bytesPerFrame == 0) {
        return 0;
    }

    totalFramesRead = 0;

    while (framesToRead > 0) {
        drwav_uint64 framesRead = drwav_read_pcm_frames(pWav, drwav_min(framesToRead, sizeof(sampleData)/bytesPerFrame), sampleData);
        if (framesRead == 0) {
            break;
        }

        drwav_mulaw_to_f32(pBufferOut, sampleData, (size_t)(framesRead*pWav->channels));

        pBufferOut      += framesRead*pWav->channels;
        framesToRead    -= framesRead;
        totalFramesRead += framesRead;
    }

    return totalFramesRead;
}

DRWAV_API drwav_uint64 drwav_read_pcm_frames_f32(drwav* pWav, drwav_uint64 framesToRead, float* pBufferOut)
{
    if (pWav == NULL || framesToRead == 0) {
        return 0;
    }

    if (pBufferOut == NULL) {
        return drwav_read_pcm_frames(pWav, framesToRead, NULL);
    }

    /* Don't try to read more samples than can potentially fit in the output buffer. */
    if (framesToRead * pWav->channels * sizeof(float) > DRWAV_SIZE_MAX) {
        framesToRead = DRWAV_SIZE_MAX / sizeof(float) / pWav->channels;
    }

    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_PCM) {
        return drwav_read_pcm_frames_f32__pcm(pWav, framesToRead, pBufferOut);
    }

    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_ADPCM) {
        return drwav_read_pcm_frames_f32__msadpcm(pWav, framesToRead, pBufferOut);
    }

    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_IEEE_FLOAT) {
        return drwav_read_pcm_frames_f32__ieee(pWav, framesToRead, pBufferOut);
    }

    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_ALAW) {
        return drwav_read_pcm_frames_f32__alaw(pWav, framesToRead, pBufferOut);
    }

    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_MULAW) {
        return drwav_read_pcm_frames_f32__mulaw(pWav, framesToRead, pBufferOut);
    }

    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_DVI_ADPCM) {
        return drwav_read_pcm_frames_f32__ima(pWav, framesToRead, pBufferOut);
    }

    return 0;
}

DRWAV_API drwav_uint64 drwav_read_pcm_frames_f32le(drwav* pWav, drwav_uint64 framesToRead, float* pBufferOut)
{
    drwav_uint64 framesRead = drwav_read_pcm_frames_f32(pWav, framesToRead, pBufferOut);
    if (pBufferOut != NULL && drwav__is_little_endian() == DRWAV_FALSE) {
        drwav__bswap_samples_f32(pBufferOut, framesRead*pWav->channels);
    }

    return framesRead;
}

DRWAV_API drwav_uint64 drwav_read_pcm_frames_f32be(drwav* pWav, drwav_uint64 framesToRead, float* pBufferOut)
{
    drwav_uint64 framesRead = drwav_read_pcm_frames_f32(pWav, framesToRead, pBufferOut);
    if (pBufferOut != NULL && drwav__is_little_endian() == DRWAV_TRUE) {
        drwav__bswap_samples_f32(pBufferOut, framesRead*pWav->channels);
    }

    return framesRead;
}


DRWAV_API void drwav_u8_to_f32(float* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

#ifdef DR_WAV_LIBSNDFILE_COMPAT
    /*
    It appears libsndfile uses slightly different logic for the u8 -> f32 conversion to dr_wav, which in my opinion is incorrect. It appears
    libsndfile performs the conversion something like "f32 = (u8 / 256) * 2 - 1", however I think it should be "f32 = (u8 / 255) * 2 - 1" (note
    the divisor of 256 vs 255). I use libsndfile as a benchmark for testing, so I'm therefore leaving this block here just for my automated
    correctness testing. This is disabled by default.
    */
    for (i = 0; i < sampleCount; ++i) {
        *pOut++ = (pIn[i] / 256.0f) * 2 - 1;
    }
#else
    for (i = 0; i < sampleCount; ++i) {
        float x = pIn[i];
        x = x * 0.00784313725490196078f;    /* 0..255 to 0..2 */
        x = x - 1;                          /* 0..2 to -1..1 */

        *pOut++ = x;
    }
#endif
}

DRWAV_API void drwav_s16_to_f32(float* pOut, const drwav_int16* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i = 0; i < sampleCount; ++i) {
        *pOut++ = pIn[i] * 0.000030517578125f;
    }
}

DRWAV_API void drwav_s24_to_f32(float* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i = 0; i < sampleCount; ++i) {
        double x;
        drwav_uint32 a = ((drwav_uint32)(pIn[i*3+0]) <<  8);
        drwav_uint32 b = ((drwav_uint32)(pIn[i*3+1]) << 16);
        drwav_uint32 c = ((drwav_uint32)(pIn[i*3+2]) << 24);

        x = (double)((drwav_int32)(a | b | c) >> 8);
        *pOut++ = (float)(x * 0.00000011920928955078125);
    }
}

DRWAV_API void drwav_s32_to_f32(float* pOut, const drwav_int32* pIn, size_t sampleCount)
{
    size_t i;
    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i = 0; i < sampleCount; ++i) {
        *pOut++ = (float)(pIn[i] / 2147483648.0);
    }
}

DRWAV_API void drwav_f64_to_f32(float* pOut, const double* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i = 0; i < sampleCount; ++i) {
        *pOut++ = (float)pIn[i];
    }
}

DRWAV_API void drwav_alaw_to_f32(float* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i = 0; i < sampleCount; ++i) {
        *pOut++ = drwav__alaw_to_s16(pIn[i]) / 32768.0f;
    }
}

DRWAV_API void drwav_mulaw_to_f32(float* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i = 0; i < sampleCount; ++i) {
        *pOut++ = drwav__mulaw_to_s16(pIn[i]) / 32768.0f;
    }
}



static void drwav__pcm_to_s32(drwav_int32* pOut, const drwav_uint8* pIn, size_t totalSampleCount, unsigned int bytesPerSample)
{
    unsigned int i;

    /* Special case for 8-bit sample data because it's treated as unsigned. */
    if (bytesPerSample == 1) {
        drwav_u8_to_s32(pOut, pIn, totalSampleCount);
        return;
    }

    /* Slightly more optimal implementation for common formats. */
    if (bytesPerSample == 2) {
        drwav_s16_to_s32(pOut, (const drwav_int16*)pIn, totalSampleCount);
        return;
    }
    if (bytesPerSample == 3) {
        drwav_s24_to_s32(pOut, pIn, totalSampleCount);
        return;
    }
    if (bytesPerSample == 4) {
        for (i = 0; i < totalSampleCount; ++i) {
           *pOut++ = ((const drwav_int32*)pIn)[i];
        }
        return;
    }


    /* Anything more than 64 bits per sample is not supported. */
    if (bytesPerSample > 8) {
        DRWAV_ZERO_MEMORY(pOut, totalSampleCount * sizeof(*pOut));
        return;
    }


    /* Generic, slow converter. */
    for (i = 0; i < totalSampleCount; ++i) {
        drwav_uint64 sample = 0;
        unsigned int shift  = (8 - bytesPerSample) * 8;

        unsigned int j;
        for (j = 0; j < bytesPerSample; j += 1) {
            DRWAV_ASSERT(j < 8);
            sample |= (drwav_uint64)(pIn[j]) << shift;
            shift  += 8;
        }

        pIn += j;
        *pOut++ = (drwav_int32)((drwav_int64)sample >> 32);
    }
}

static void drwav__ieee_to_s32(drwav_int32* pOut, const drwav_uint8* pIn, size_t totalSampleCount, unsigned int bytesPerSample)
{
    if (bytesPerSample == 4) {
        drwav_f32_to_s32(pOut, (const float*)pIn, totalSampleCount);
        return;
    } else if (bytesPerSample == 8) {
        drwav_f64_to_s32(pOut, (const double*)pIn, totalSampleCount);
        return;
    } else {
        /* Only supporting 32- and 64-bit float. Output silence in all other cases. Contributions welcome for 16-bit float. */
        DRWAV_ZERO_MEMORY(pOut, totalSampleCount * sizeof(*pOut));
        return;
    }
}


static drwav_uint64 drwav_read_pcm_frames_s32__pcm(drwav* pWav, drwav_uint64 framesToRead, drwav_int32* pBufferOut)
{
    drwav_uint64 totalFramesRead;
    drwav_uint8 sampleData[4096];
    drwav_uint32 bytesPerFrame;

    /* Fast path. */
    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_PCM && pWav->bitsPerSample == 32) {
        return drwav_read_pcm_frames(pWav, framesToRead, pBufferOut);
    }
    
    bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav);
    if (bytesPerFrame == 0) {
        return 0;
    }

    totalFramesRead = 0;

    while (framesToRead > 0) {
        drwav_uint64 framesRead = drwav_read_pcm_frames(pWav, drwav_min(framesToRead, sizeof(sampleData)/bytesPerFrame), sampleData);
        if (framesRead == 0) {
            break;
        }

        drwav__pcm_to_s32(pBufferOut, sampleData, (size_t)(framesRead*pWav->channels), bytesPerFrame/pWav->channels);

        pBufferOut      += framesRead*pWav->channels;
        framesToRead    -= framesRead;
        totalFramesRead += framesRead;
    }

    return totalFramesRead;
}

static drwav_uint64 drwav_read_pcm_frames_s32__msadpcm(drwav* pWav, drwav_uint64 framesToRead, drwav_int32* pBufferOut)
{
    /*
    We're just going to borrow the implementation from the drwav_read_s16() since ADPCM is a little bit more complicated than other formats and I don't
    want to duplicate that code.
    */
    drwav_uint64 totalFramesRead = 0;
    drwav_int16 samples16[2048];
    while (framesToRead > 0) {
        drwav_uint64 framesRead = drwav_read_pcm_frames_s16(pWav, drwav_min(framesToRead, drwav_countof(samples16)/pWav->channels), samples16);
        if (framesRead == 0) {
            break;
        }

        drwav_s16_to_s32(pBufferOut, samples16, (size_t)(framesRead*pWav->channels));   /* <-- Safe cast because we're clamping to 2048. */

        pBufferOut      += framesRead*pWav->channels;
        framesToRead    -= framesRead;
        totalFramesRead += framesRead;
    }

    return totalFramesRead;
}

static drwav_uint64 drwav_read_pcm_frames_s32__ima(drwav* pWav, drwav_uint64 framesToRead, drwav_int32* pBufferOut)
{
    /*
    We're just going to borrow the implementation from the drwav_read_s16() since IMA-ADPCM is a little bit more complicated than other formats and I don't
    want to duplicate that code.
    */
    drwav_uint64 totalFramesRead = 0;
    drwav_int16 samples16[2048];
    while (framesToRead > 0) {
        drwav_uint64 framesRead = drwav_read_pcm_frames_s16(pWav, drwav_min(framesToRead, drwav_countof(samples16)/pWav->channels), samples16);
        if (framesRead == 0) {
            break;
        }

        drwav_s16_to_s32(pBufferOut, samples16, (size_t)(framesRead*pWav->channels));   /* <-- Safe cast because we're clamping to 2048. */

        pBufferOut      += framesRead*pWav->channels;
        framesToRead    -= framesRead;
        totalFramesRead += framesRead;
    }

    return totalFramesRead;
}

static drwav_uint64 drwav_read_pcm_frames_s32__ieee(drwav* pWav, drwav_uint64 framesToRead, drwav_int32* pBufferOut)
{
    drwav_uint64 totalFramesRead;
    drwav_uint8 sampleData[4096];

    drwav_uint32 bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav);
    if (bytesPerFrame == 0) {
        return 0;
    }

    totalFramesRead = 0;

    while (framesToRead > 0) {
        drwav_uint64 framesRead = drwav_read_pcm_frames(pWav, drwav_min(framesToRead, sizeof(sampleData)/bytesPerFrame), sampleData);
        if (framesRead == 0) {
            break;
        }

        drwav__ieee_to_s32(pBufferOut, sampleData, (size_t)(framesRead*pWav->channels), bytesPerFrame/pWav->channels);

        pBufferOut      += framesRead*pWav->channels;
        framesToRead    -= framesRead;
        totalFramesRead += framesRead;
    }

    return totalFramesRead;
}

static drwav_uint64 drwav_read_pcm_frames_s32__alaw(drwav* pWav, drwav_uint64 framesToRead, drwav_int32* pBufferOut)
{
    drwav_uint64 totalFramesRead;
    drwav_uint8 sampleData[4096];

    drwav_uint32 bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav);
    if (bytesPerFrame == 0) {
        return 0;
    }

    totalFramesRead = 0;

    while (framesToRead > 0) {
        drwav_uint64 framesRead = drwav_read_pcm_frames(pWav, drwav_min(framesToRead, sizeof(sampleData)/bytesPerFrame), sampleData);
        if (framesRead == 0) {
            break;
        }

        drwav_alaw_to_s32(pBufferOut, sampleData, (size_t)(framesRead*pWav->channels));

        pBufferOut      += framesRead*pWav->channels;
        framesToRead    -= framesRead;
        totalFramesRead += framesRead;
    }

    return totalFramesRead;
}

static drwav_uint64 drwav_read_pcm_frames_s32__mulaw(drwav* pWav, drwav_uint64 framesToRead, drwav_int32* pBufferOut)
{
    drwav_uint64 totalFramesRead;
    drwav_uint8 sampleData[4096];

    drwav_uint32 bytesPerFrame = drwav_get_bytes_per_pcm_frame(pWav);
    if (bytesPerFrame == 0) {
        return 0;
    }

    totalFramesRead = 0;

    while (framesToRead > 0) {
        drwav_uint64 framesRead = drwav_read_pcm_frames(pWav, drwav_min(framesToRead, sizeof(sampleData)/bytesPerFrame), sampleData);
        if (framesRead == 0) {
            break;
        }

        drwav_mulaw_to_s32(pBufferOut, sampleData, (size_t)(framesRead*pWav->channels));

        pBufferOut      += framesRead*pWav->channels;
        framesToRead    -= framesRead;
        totalFramesRead += framesRead;
    }

    return totalFramesRead;
}

DRWAV_API drwav_uint64 drwav_read_pcm_frames_s32(drwav* pWav, drwav_uint64 framesToRead, drwav_int32* pBufferOut)
{
    if (pWav == NULL || framesToRead == 0) {
        return 0;
    }

    if (pBufferOut == NULL) {
        return drwav_read_pcm_frames(pWav, framesToRead, NULL);
    }

    /* Don't try to read more samples than can potentially fit in the output buffer. */
    if (framesToRead * pWav->channels * sizeof(drwav_int32) > DRWAV_SIZE_MAX) {
        framesToRead = DRWAV_SIZE_MAX / sizeof(drwav_int32) / pWav->channels;
    }

    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_PCM) {
        return drwav_read_pcm_frames_s32__pcm(pWav, framesToRead, pBufferOut);
    }

    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_ADPCM) {
        return drwav_read_pcm_frames_s32__msadpcm(pWav, framesToRead, pBufferOut);
    }

    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_IEEE_FLOAT) {
        return drwav_read_pcm_frames_s32__ieee(pWav, framesToRead, pBufferOut);
    }

    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_ALAW) {
        return drwav_read_pcm_frames_s32__alaw(pWav, framesToRead, pBufferOut);
    }

    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_MULAW) {
        return drwav_read_pcm_frames_s32__mulaw(pWav, framesToRead, pBufferOut);
    }

    if (pWav->translatedFormatTag == DR_WAVE_FORMAT_DVI_ADPCM) {
        return drwav_read_pcm_frames_s32__ima(pWav, framesToRead, pBufferOut);
    }

    return 0;
}

DRWAV_API drwav_uint64 drwav_read_pcm_frames_s32le(drwav* pWav, drwav_uint64 framesToRead, drwav_int32* pBufferOut)
{
    drwav_uint64 framesRead = drwav_read_pcm_frames_s32(pWav, framesToRead, pBufferOut);
    if (pBufferOut != NULL && drwav__is_little_endian() == DRWAV_FALSE) {
        drwav__bswap_samples_s32(pBufferOut, framesRead*pWav->channels);
    }

    return framesRead;
}

DRWAV_API drwav_uint64 drwav_read_pcm_frames_s32be(drwav* pWav, drwav_uint64 framesToRead, drwav_int32* pBufferOut)
{
    drwav_uint64 framesRead = drwav_read_pcm_frames_s32(pWav, framesToRead, pBufferOut);
    if (pBufferOut != NULL && drwav__is_little_endian() == DRWAV_TRUE) {
        drwav__bswap_samples_s32(pBufferOut, framesRead*pWav->channels);
    }

    return framesRead;
}


DRWAV_API void drwav_u8_to_s32(drwav_int32* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i = 0; i < sampleCount; ++i) {
        *pOut++ = ((int)pIn[i] - 128) << 24;
    }
}

DRWAV_API void drwav_s16_to_s32(drwav_int32* pOut, const drwav_int16* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i = 0; i < sampleCount; ++i) {
        *pOut++ = pIn[i] << 16;
    }
}

DRWAV_API void drwav_s24_to_s32(drwav_int32* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i = 0; i < sampleCount; ++i) {
        unsigned int s0 = pIn[i*3 + 0];
        unsigned int s1 = pIn[i*3 + 1];
        unsigned int s2 = pIn[i*3 + 2];

        drwav_int32 sample32 = (drwav_int32)((s0 << 8) | (s1 << 16) | (s2 << 24));
        *pOut++ = sample32;
    }
}

DRWAV_API void drwav_f32_to_s32(drwav_int32* pOut, const float* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i = 0; i < sampleCount; ++i) {
        *pOut++ = (drwav_int32)(2147483648.0 * pIn[i]);
    }
}

DRWAV_API void drwav_f64_to_s32(drwav_int32* pOut, const double* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i = 0; i < sampleCount; ++i) {
        *pOut++ = (drwav_int32)(2147483648.0 * pIn[i]);
    }
}

DRWAV_API void drwav_alaw_to_s32(drwav_int32* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i = 0; i < sampleCount; ++i) {
        *pOut++ = ((drwav_int32)drwav__alaw_to_s16(pIn[i])) << 16;
    }
}

DRWAV_API void drwav_mulaw_to_s32(drwav_int32* pOut, const drwav_uint8* pIn, size_t sampleCount)
{
    size_t i;

    if (pOut == NULL || pIn == NULL) {
        return;
    }

    for (i= 0; i < sampleCount; ++i) {
        *pOut++ = ((drwav_int32)drwav__mulaw_to_s16(pIn[i])) << 16;
    }
}



static drwav_int16* drwav__read_pcm_frames_and_close_s16(drwav* pWav, unsigned int* channels, unsigned int* sampleRate, drwav_uint64* totalFrameCount)
{
    drwav_uint64 sampleDataSize;
    drwav_int16* pSampleData;
    drwav_uint64 framesRead;

    DRWAV_ASSERT(pWav != NULL);

    sampleDataSize = pWav->totalPCMFrameCount * pWav->channels * sizeof(drwav_int16);
    if (sampleDataSize > DRWAV_SIZE_MAX) {
        drwav_uninit(pWav);
        return NULL;    /* File's too big. */
    }

    pSampleData = (drwav_int16*)drwav__malloc_from_callbacks((size_t)sampleDataSize, &pWav->allocationCallbacks); /* <-- Safe cast due to the check above. */
    if (pSampleData == NULL) {
        drwav_uninit(pWav);
        return NULL;    /* Failed to allocate memory. */
    }

    framesRead = drwav_read_pcm_frames_s16(pWav, (size_t)pWav->totalPCMFrameCount, pSampleData);
    if (framesRead != pWav->totalPCMFrameCount) {
        drwav__free_from_callbacks(pSampleData, &pWav->allocationCallbacks);
        drwav_uninit(pWav);
        return NULL;    /* There was an error reading the samples. */
    }

    drwav_uninit(pWav);

    if (sampleRate) {
        *sampleRate = pWav->sampleRate;
    }
    if (channels) {
        *channels = pWav->channels;
    }
    if (totalFrameCount) {
        *totalFrameCount = pWav->totalPCMFrameCount;
    }

    return pSampleData;
}

static float* drwav__read_pcm_frames_and_close_f32(drwav* pWav, unsigned int* channels, unsigned int* sampleRate, drwav_uint64* totalFrameCount)
{
    drwav_uint64 sampleDataSize;
    float* pSampleData;
    drwav_uint64 framesRead;

    DRWAV_ASSERT(pWav != NULL);

    sampleDataSize = pWav->totalPCMFrameCount * pWav->channels * sizeof(float);
    if (sampleDataSize > DRWAV_SIZE_MAX) {
        drwav_uninit(pWav);
        return NULL;    /* File's too big. */
    }

    pSampleData = (float*)drwav__malloc_from_callbacks((size_t)sampleDataSize, &pWav->allocationCallbacks); /* <-- Safe cast due to the check above. */
    if (pSampleData == NULL) {
        drwav_uninit(pWav);
        return NULL;    /* Failed to allocate memory. */
    }

    framesRead = drwav_read_pcm_frames_f32(pWav, (size_t)pWav->totalPCMFrameCount, pSampleData);
    if (framesRead != pWav->totalPCMFrameCount) {
        drwav__free_from_callbacks(pSampleData, &pWav->allocationCallbacks);
        drwav_uninit(pWav);
        return NULL;    /* There was an error reading the samples. */
    }

    drwav_uninit(pWav);

    if (sampleRate) {
        *sampleRate = pWav->sampleRate;
    }
    if (channels) {
        *channels = pWav->channels;
    }
    if (totalFrameCount) {
        *totalFrameCount = pWav->totalPCMFrameCount;
    }

    return pSampleData;
}

static drwav_int32* drwav__read_pcm_frames_and_close_s32(drwav* pWav, unsigned int* channels, unsigned int* sampleRate, drwav_uint64* totalFrameCount)
{
    drwav_uint64 sampleDataSize;
    drwav_int32* pSampleData;
    drwav_uint64 framesRead;

    DRWAV_ASSERT(pWav != NULL);

    sampleDataSize = pWav->totalPCMFrameCount * pWav->channels * sizeof(drwav_int32);
    if (sampleDataSize > DRWAV_SIZE_MAX) {
        drwav_uninit(pWav);
        return NULL;    /* File's too big. */
    }

    pSampleData = (drwav_int32*)drwav__malloc_from_callbacks((size_t)sampleDataSize, &pWav->allocationCallbacks); /* <-- Safe cast due to the check above. */
    if (pSampleData == NULL) {
        drwav_uninit(pWav);
        return NULL;    /* Failed to allocate memory. */
    }

    framesRead = drwav_read_pcm_frames_s32(pWav, (size_t)pWav->totalPCMFrameCount, pSampleData);
    if (framesRead != pWav->totalPCMFrameCount) {
        drwav__free_from_callbacks(pSampleData, &pWav->allocationCallbacks);
        drwav_uninit(pWav);
        return NULL;    /* There was an error reading the samples. */
    }

    drwav_uninit(pWav);

    if (sampleRate) {
        *sampleRate = pWav->sampleRate;
    }
    if (channels) {
        *channels = pWav->channels;
    }
    if (totalFrameCount) {
        *totalFrameCount = pWav->totalPCMFrameCount;
    }

    return pSampleData;
}



DRWAV_API drwav_int16* drwav_open_and_read_pcm_frames_s16(drwav_read_proc onRead, drwav_seek_proc onSeek, void* pUserData, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    drwav wav;

    if (channelsOut) {
        *channelsOut = 0;
    }
    if (sampleRateOut) {
        *sampleRateOut = 0;
    }
    if (totalFrameCountOut) {
        *totalFrameCountOut = 0;
    }

    if (!drwav_init(&wav, onRead, onSeek, pUserData, pAllocationCallbacks)) {
        return NULL;
    }

    return drwav__read_pcm_frames_and_close_s16(&wav, channelsOut, sampleRateOut, totalFrameCountOut);
}

DRWAV_API float* drwav_open_and_read_pcm_frames_f32(drwav_read_proc onRead, drwav_seek_proc onSeek, void* pUserData, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    drwav wav;

    if (channelsOut) {
        *channelsOut = 0;
    }
    if (sampleRateOut) {
        *sampleRateOut = 0;
    }
    if (totalFrameCountOut) {
        *totalFrameCountOut = 0;
    }

    if (!drwav_init(&wav, onRead, onSeek, pUserData, pAllocationCallbacks)) {
        return NULL;
    }

    return drwav__read_pcm_frames_and_close_f32(&wav, channelsOut, sampleRateOut, totalFrameCountOut);
}

DRWAV_API drwav_int32* drwav_open_and_read_pcm_frames_s32(drwav_read_proc onRead, drwav_seek_proc onSeek, void* pUserData, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    drwav wav;

    if (channelsOut) {
        *channelsOut = 0;
    }
    if (sampleRateOut) {
        *sampleRateOut = 0;
    }
    if (totalFrameCountOut) {
        *totalFrameCountOut = 0;
    }

    if (!drwav_init(&wav, onRead, onSeek, pUserData, pAllocationCallbacks)) {
        return NULL;
    }

    return drwav__read_pcm_frames_and_close_s32(&wav, channelsOut, sampleRateOut, totalFrameCountOut);
}

#ifndef DR_WAV_NO_STDIO
DRWAV_API drwav_int16* drwav_open_file_and_read_pcm_frames_s16(const char* filename, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    drwav wav;

    if (channelsOut) {
        *channelsOut = 0;
    }
    if (sampleRateOut) {
        *sampleRateOut = 0;
    }
    if (totalFrameCountOut) {
        *totalFrameCountOut = 0;
    }

    if (!drwav_init_file(&wav, filename, pAllocationCallbacks)) {
        return NULL;
    }

    return drwav__read_pcm_frames_and_close_s16(&wav, channelsOut, sampleRateOut, totalFrameCountOut);
}

DRWAV_API float* drwav_open_file_and_read_pcm_frames_f32(const char* filename, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    drwav wav;

    if (channelsOut) {
        *channelsOut = 0;
    }
    if (sampleRateOut) {
        *sampleRateOut = 0;
    }
    if (totalFrameCountOut) {
        *totalFrameCountOut = 0;
    }

    if (!drwav_init_file(&wav, filename, pAllocationCallbacks)) {
        return NULL;
    }

    return drwav__read_pcm_frames_and_close_f32(&wav, channelsOut, sampleRateOut, totalFrameCountOut);
}

DRWAV_API drwav_int32* drwav_open_file_and_read_pcm_frames_s32(const char* filename, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    drwav wav;

    if (channelsOut) {
        *channelsOut = 0;
    }
    if (sampleRateOut) {
        *sampleRateOut = 0;
    }
    if (totalFrameCountOut) {
        *totalFrameCountOut = 0;
    }

    if (!drwav_init_file(&wav, filename, pAllocationCallbacks)) {
        return NULL;
    }

    return drwav__read_pcm_frames_and_close_s32(&wav, channelsOut, sampleRateOut, totalFrameCountOut);
}


DRWAV_API drwav_int16* drwav_open_file_and_read_pcm_frames_s16_w(const wchar_t* filename, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    drwav wav;

    if (sampleRateOut) {
        *sampleRateOut = 0;
    }
    if (channelsOut) {
        *channelsOut = 0;
    }
    if (totalFrameCountOut) {
        *totalFrameCountOut = 0;
    }

    if (!drwav_init_file_w(&wav, filename, pAllocationCallbacks)) {
        return NULL;
    }

    return drwav__read_pcm_frames_and_close_s16(&wav, channelsOut, sampleRateOut, totalFrameCountOut);
}

DRWAV_API float* drwav_open_file_and_read_pcm_frames_f32_w(const wchar_t* filename, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    drwav wav;

    if (sampleRateOut) {
        *sampleRateOut = 0;
    }
    if (channelsOut) {
        *channelsOut = 0;
    }
    if (totalFrameCountOut) {
        *totalFrameCountOut = 0;
    }

    if (!drwav_init_file_w(&wav, filename, pAllocationCallbacks)) {
        return NULL;
    }

    return drwav__read_pcm_frames_and_close_f32(&wav, channelsOut, sampleRateOut, totalFrameCountOut);
}

DRWAV_API drwav_int32* drwav_open_file_and_read_pcm_frames_s32_w(const wchar_t* filename, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    drwav wav;

    if (sampleRateOut) {
        *sampleRateOut = 0;
    }
    if (channelsOut) {
        *channelsOut = 0;
    }
    if (totalFrameCountOut) {
        *totalFrameCountOut = 0;
    }

    if (!drwav_init_file_w(&wav, filename, pAllocationCallbacks)) {
        return NULL;
    }

    return drwav__read_pcm_frames_and_close_s32(&wav, channelsOut, sampleRateOut, totalFrameCountOut);
}
#endif

DRWAV_API drwav_int16* drwav_open_memory_and_read_pcm_frames_s16(const void* data, size_t dataSize, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    drwav wav;

    if (channelsOut) {
        *channelsOut = 0;
    }
    if (sampleRateOut) {
        *sampleRateOut = 0;
    }
    if (totalFrameCountOut) {
        *totalFrameCountOut = 0;
    }

    if (!drwav_init_memory(&wav, data, dataSize, pAllocationCallbacks)) {
        return NULL;
    }

    return drwav__read_pcm_frames_and_close_s16(&wav, channelsOut, sampleRateOut, totalFrameCountOut);
}

DRWAV_API float* drwav_open_memory_and_read_pcm_frames_f32(const void* data, size_t dataSize, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    drwav wav;

    if (channelsOut) {
        *channelsOut = 0;
    }
    if (sampleRateOut) {
        *sampleRateOut = 0;
    }
    if (totalFrameCountOut) {
        *totalFrameCountOut = 0;
    }

    if (!drwav_init_memory(&wav, data, dataSize, pAllocationCallbacks)) {
        return NULL;
    }

    return drwav__read_pcm_frames_and_close_f32(&wav, channelsOut, sampleRateOut, totalFrameCountOut);
}

DRWAV_API drwav_int32* drwav_open_memory_and_read_pcm_frames_s32(const void* data, size_t dataSize, unsigned int* channelsOut, unsigned int* sampleRateOut, drwav_uint64* totalFrameCountOut, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    drwav wav;

    if (channelsOut) {
        *channelsOut = 0;
    }
    if (sampleRateOut) {
        *sampleRateOut = 0;
    }
    if (totalFrameCountOut) {
        *totalFrameCountOut = 0;
    }

    if (!drwav_init_memory(&wav, data, dataSize, pAllocationCallbacks)) {
        return NULL;
    }

    return drwav__read_pcm_frames_and_close_s32(&wav, channelsOut, sampleRateOut, totalFrameCountOut);
}
#endif  /* DR_WAV_NO_CONVERSION_API */


DRWAV_API void drwav_free(void* p, const drwav_allocation_callbacks* pAllocationCallbacks)
{
    if (pAllocationCallbacks != NULL) {
        drwav__free_from_callbacks(p, pAllocationCallbacks);
    } else {
        drwav__free_default(p, NULL);
    }
}

DRWAV_API drwav_uint16 drwav_bytes_to_u16(const drwav_uint8* data)
{
    return drwav__bytes_to_u16(data);
}

DRWAV_API drwav_int16 drwav_bytes_to_s16(const drwav_uint8* data)
{
    return drwav__bytes_to_s16(data);
}

DRWAV_API drwav_uint32 drwav_bytes_to_u32(const drwav_uint8* data)
{
    return drwav__bytes_to_u32(data);
}

DRWAV_API drwav_int32 drwav_bytes_to_s32(const drwav_uint8* data)
{
    return drwav__bytes_to_s32(data);
}

DRWAV_API drwav_uint64 drwav_bytes_to_u64(const drwav_uint8* data)
{
    return drwav__bytes_to_u64(data);
}

DRWAV_API drwav_int64 drwav_bytes_to_s64(const drwav_uint8* data)
{
    return drwav__bytes_to_s64(data);
}


DRWAV_API drwav_bool32 drwav_guid_equal(const drwav_uint8 a[16], const drwav_uint8 b[16])
{
    return drwav__guid_equal(a, b);
}

DRWAV_API drwav_bool32 drwav_fourcc_equal(const drwav_uint8* a, const char* b)
{
    return drwav__fourcc_equal(a, b);
}

#endif  /* DR_WAV_IMPLEMENTATION */


#include <stdint.h>

/* This is the struct used to tell the encoder about the input PCM */
enum channel {
    PCM_MONO = 1,
    PCM_STEREO = 2
};

enum mpeg_versions {
    MPEG_I = 3,
    MPEG_II = 2,
    MPEG_25 = 0
};

/* Only Layer III currently implemented. */
enum mpeg_layers {
    LAYER_III = 1
};

typedef struct {
    enum channel channels;
    int samplerate;
} shine_wave_t;

/* This is the struct the encoder uses to tell the encoder about the output MP3 */

enum modes {
    STEREO = 0,
    JOINT_STEREO = 1,
    DUAL_CHANNEL = 2,
    MONO = 3
};

enum emph {
    NONE = 0,
    MU50_15 = 1,
    CITT = 3
};

typedef struct {
    enum modes mode;      /* Stereo mode */
    int bitr;      /* Must conform to known bitrate */
    enum emph emph;      /* De-emphasis */
    int copyright;
    int original;
} shine_mpeg_t;

typedef struct {
    shine_wave_t wave;
    shine_mpeg_t mpeg;
} shine_config_t;

/* Tables of supported audio parameters & format.
 *
 * Valid samplerates and bitrates.
 * const int samplerates[9] = {
 *   44100, 48000, 32000, // MPEG-I
 *   22050, 24000, 16000, // MPEG-II
 *   11025, 12000, 8000   // MPEG-2.5 
 * };
 *
 * const int bitrates[16][4] = {
 * //  MPEG version:
 * //  2.5, reserved,  II,  I
 *   { -1,  -1,        -1,  -1},
 *   { 8,   -1,         8,  32},
 *   { 16,  -1,        16,  40},
 *   { 24,  -1,        24,  48},
 *   { 32,  -1,        32,  56},
 *   { 40,  -1,        40,  64},
 *   { 48,  -1,        48,  80},
 *   { 56,  -1,        56,  96},
 *   { 64,  -1,        64, 112},
 *   { 80,  -1,        80, 128},
 *   { 96,  -1,        96, 160},
 *   {112,  -1,       112, 192},
 *   {128,  -1,       128, 224},
 *   {144,  -1,       144, 256},
 *   {160,  -1,       160, 320},
 *   { -1,  -1,        -1,  -1}
 *  };
 *
 */

/* Abtract type for the shine encoder handle. */
typedef struct shine_global_flags *shine_t;

/* Fill in a `mpeg_t` structure with default values. */
void shine_set_config_mpeg_defaults(shine_mpeg_t *mpeg);

/* Check if a given bitrate is supported by the encoder (see `bitrates` above for a list
 * of acceptable values. */
int shine_find_bitrate_index(int bitr, int mpeg_version);

/* Check if a given samplerate is supported by the encoder (see `samplerates` above for a list
 * of acceptable values. */
int shine_find_samplerate_index(int freq);

/* Returns the MPEG version used for the given samplerate index. See above
 * `mpeg_versions` for a list of possible values. */
int shine_mpeg_version(int samplerate_index);

/* Check if a given bitrate and samplerate is supported by the encoder (see `samplerates` 
 * and `bitrates` above for a list of acceptable values). 
 *
 * Returns -1 on error, mpeg_version on success. */
int shine_check_config(int freq, int bitr);

/* Pass a pointer to a `config_t` structure and returns an initialized
 * encoder. 
 *
 * Configuration data is copied over to the encoder. It is not possible
 * to change its values after initializing the encoder at the moment.
 *
 * Checking for valid configuration values is left for the application to 
 * implement. You can use the `shine_find_bitrate_index` and 
 * `shine_find_samplerate_index` functions or the `bitrates` and 
 * `samplerates` arrays above to check those parameters. Mone and stereo 
 * mode for wave and mpeg should also be consistent with each other.
 *
 * This function returns NULL if it was not able to allocate memory data for 
 * the encoder. */
shine_t shine_initialise(shine_config_t *config);

/* Maximun possible value for the function below. */
#define SHINE_MAX_SAMPLES 1152

/* Returns audio samples expected in each frame. */
int shine_samples_per_pass(shine_t s);

/* Encode audio data. Source data must have `shine_samples_per_pass(s)` audio samples per
 * channels. Mono encoder only expect one channel. 
 *
 * Returns a pointer to freshly encoded data while `written` contains the size of
 * available data. This pointer's memory is handled by the library and is only valid 
 * until the next call to `shine_encode_buffer` or `shine_close` and may be NULL if no data
 * was written. */
unsigned char *shine_encode_buffer(shine_t s, int16_t **data, int *written);

/* Encode interleaved audio data. Source data must have `shine_samples_per_pass(s)` audio samples per
 * channels. Mono encoder only expect one channel. 
 *
 * Returns a pointer to freshly encoded data while `written` contains the size of
 * available data. This pointer's memory is handled by the library and is only valid 
 * until the next call to `shine_encode_buffer` or `shine_close` and may be NULL if no data
 * was written. */
unsigned char *shine_encode_buffer_interleaved(shine_t s, int16_t *data, int *written);

/* Flush all data currently in the encoding buffer. Should be used before closing
 * the encoder, to make all encoded data has been written. */
unsigned char *shine_flush(shine_t s, int *written);

/* Close an encoder, freeing all associated memory. Encoder handler is not
 * valid after this call. */
void shine_close(shine_t s);

#endif
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define GRANULE_SIZE  576
/* Include arch-specific instructions,
 * when defined. */
#if defined(__mips__) && (__mips == 32)
#include <stdint.h>

#define mul(a,b) \
({ \
    register int32_t res; \
    __asm__ __volatile__("mult %0, %1" : : "r" (a), "r" (b)); \
    __asm__ __volatile__("mfhi %0" : "=r" (res)); \
    res; \
})

#define mul0(hi,lo,a,b) \
    __asm__ __volatile__("mult %0, %1" : : "r" (a), "r" (b))

#define muladd(hi,lo,a,b) \
    __asm__ __volatile__("madd %0, %1" : : "r" (a), "r" (b))

#define mulsub(hi,lo,a,b) \
    __asm__ __volatile__("msub %0, %1" : : "r" (a), "r" (b))

#define mulz(hi,lo) \
do { \
    register int32_t t; \
    __asm__ __volatile__("mfhi %0" : "=r" (t)); \
    (hi) = t; \
} while (0)

#define cmuls(dre, dim, are, aim, bre, bim) \
do { \
    register int32_t t1, t2, tre; \
    __asm__ __volatile__("mult %0, %1" : : "r" (are), "r" (bre)); \
    __asm__ __volatile__("msub %0, %1" : : "r" (aim), "r" (bim)); \
    __asm__ __volatile__("mfhi %0; mflo %1" : "=r" (t1), "=r" (t2)); \
    tre = (t1 << 1) | ((uint32_t)t2 >> 31); \
    __asm__ __volatile__("mult %0, %1" : : "r" (are), "r" (bim)); \
    __asm__ __volatile__("madd %0, %1" : : "r" (bre), "r" (aim)); \
    dre = tre; \
    __asm__ __volatile__("mfhi %0; mflo %1" : "=r" (t1), "=r" (t2)); \
    dim = (t1 << 1) | ((uint32_t)t2 >> 31); \
} while (0)

#if __mips_isa_rev >= 2
static inline uint32_t SWAB32(uint32_t x)
{
    __asm__(
    "	wsbh	%0, %1			\n"
    "	rotr	%0, %0, 16		\n"
    : "=r" (x) : "r" (x));
    return x;
}
#define SWAB32 SWAB32
#endif

#elif defined(__arm__) && !defined(__thumb__)
#include <stdint.h>

/* Fractional multiply */
#if __ARM_ARCH >= 6
#define mul(x,y) \
({ \
    register int32_t result; \
    asm ("smmul %0, %2, %1" : "=r" (result) : "r" (x), "r" (y)); \
    result ;\
})
#else
#define mul(x,y) \
({ \
    register int32_t result; \
    asm ("smull r3, %0, %2, %1" : "=r" (result) : "r" (x), "r" (y) : "r3"); \
    result ; \
})
#endif

/* Fractional multiply with single bit left shift. */
#define muls(x,y) \
({ \
    register int32_t result; \
    asm ( \
        "smull r3, %0, %2, %1\n\t" \
        "movs r3, r3, lsl #1\n\t" \
        "adc %0, %0, %0" \
        : "=r" (result) : "r" (x), "r" (y) : "r3", "cc" \
    ); \
    result; \
})


#if __ARM_ARCH >= 6
#define mulr(x,y) \
({ \
    register int32_t result; \
    asm ( \
        "smmulr %0, %2, %1" : "=r" (result) : "r" (x), "r" (y) \
    ); \
    result; \
})
#else
#define mulr(x,y) \
({ \
    register int32_t result; \
    asm ( \
        "smull r3, %0, %2, %1\n\t" \
        "adds r3, r3, #0x80000000\n\t" \
        "adc %0, %0, #0" \
        : "=r" (result) : "r" (x), "r" (y) : "r3", "cc" \
    ); \
    result; \
})
#endif

#define mulsr(x,y) \
({ \
    register int32_t result; \
    asm ( \
        "smull r3, %0, %1, %2\n\t" \
        "movs r3, r3, lsl #1\n\t" \
        "adc %0, %0, %0\n\t" \
        "adds r3, r3, #0x80000000\n\t" \
        "adc %0, %0, #0" \
        : "=r" (result) : "r" (x), "r" (y) : "r3", "cc" \
    ); \
    result; \
})

#define mul0(hi,lo,a,b) \
    asm ("smull %0, %1, %2, %3" : "=r" (lo), "=r" (hi) : "r" (a), "r" (b))

#define muladd(hi,lo,a,b) \
    asm ("smlal %0, %1, %2, %3" : "+r" (lo), "+r" (hi) : "r" (a), "r" (b))

#define mulsub(hi,lo,a,b) \
    asm ("smlal %0, %1, %2, %3" : "+r" (lo), "+r" (hi) : "r" (a), "r" (-(b)))

#define mulz(hi,lo)

#define cmuls(dre, dim, are, aim, bre, bim) \
do { \
    register int32_t tre, tim; \
    asm ( \
        "smull r3, %0, %2, %4\n\t" \
        "smlal r3, %0, %3, %5\n\t" \
        "movs r3, r3, lsl #1\n\t" \
        "adc %0, %0, %0\n\t" \
        "smull r3, %1, %2, %6\n\t" \
        "smlal r3, %1, %4, %3\n\t" \
        "movs r3, r3, lsl #1\n\t" \
        "adc %1, %1, %1\n\t" \
        : "=&r" (tre), "=&r" (tim) \
        : "r" (are), "r" (aim), "r" (bre), "r" (-(bim)), "r" (bim) \
        : "r3", "cc" \
    ); \
    dre = tre; \
    dim = tim; \
} while (0)

#if __ARM_ARCH >= 6
static inline uint32_t SWAB32(uint32_t x)
{
    asm ("rev %0, %1" : "=r" (x) : "r" (x));
    return x;
}
#define SWAB32 SWAB32
#endif
#endif

/* Include and define generic instructions,
 * when not already defined above. */
#include <stdint.h>

#ifndef mul
#define mul(a, b)   (int32_t)  ( ( ((int64_t) a) * ((int64_t) b) ) >>32 )
#endif

#ifndef muls
#define muls(a, b)  (int32_t)  ( ( ((int64_t) a) * ((int64_t) b) ) >>31 )
#endif

#ifndef mulr
#define mulr(a, b)  (int32_t)  ( ( ( ((int64_t) a) * ((int64_t) b)) + 0x80000000LL ) >>32 )
#endif

#ifndef mulsr
#define mulsr(a, b) (int32_t)  ( ( ( ((int64_t) a) * ((int64_t) b)) + 0x40000000LL ) >>31 )
#endif

#ifndef mul0
#define mul0(hi, lo, a, b)     ((hi)  = mul((a), (b)))
#define muladd(hi, lo, a, b)   ((hi) += mul((a), (b)))
#define mulsub(hi, lo, a, b)   ((hi) -= mul((a), (b)))
#define mulz(hi, lo)
#endif

#ifndef cmuls
#define cmuls(dre, dim, are, aim, bre, bim) \
do { \
    int32_t tre; \
    (tre) = (int32_t) (((int64_t) (are) * (int64_t) (bre) - (int64_t) (aim) * (int64_t) (bim)) >> 31); \
    (dim) = (int32_t) (((int64_t) (are) * (int64_t) (bim) + (int64_t) (aim) * (int64_t) (bre)) >> 31); \
    (dre) = tre; \
} while (0)
#endif


#ifndef SWAB32
#if defined(__GNUC__) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 2))
#define SWAB32(x)    __builtin_bswap32(x)
#else
#define SWAB32(x)	(((unsigned int)(x) >> 24) | (((unsigned int)(x) >> 8) & 0xff00) | (((unsigned int)(x) & 0xff00) << 8) | ((unsigned int)(x) << 24))
#endif

/* #define DEBUG if you want the library to dump info to stdout */

#define PI          3.14159265358979
#define PI4         0.78539816339745
#define PI12        0.26179938779915
#define PI36        0.087266462599717
#define PI64        0.049087385212
#define SQRT2       1.41421356237
#define LN2         0.69314718
#define LN_TO_LOG10 0.2302585093
#define BLKSIZE     1024
#define HAN_SIZE    512 /* for loop unrolling, require that HAN_SIZE%8==0 */
#define SCALE_BLOCK 12
#define SCALE_RANGE 64
#define SCALE       32768
#define SBLIMIT     32

#ifndef MAX_CHANNELS
#define MAX_CHANNELS 2
#endif

#ifndef MAX_GRANULES
#define MAX_GRANULES 2
#endif

typedef struct {
    int channels;
    int samplerate;
} priv_shine_wave_t;

typedef struct {
    int version;
    int layer;
    int granules_per_frame;
    int mode;      /* + */ /* Stereo mode */
    int bitr;      /* + */ /* Must conform to known bitrate - see Main.c */
    int emph;      /* + */ /* De-emphasis */
    int padding;
    int bits_per_frame;
    int bits_per_slot;
    double frac_slots_per_frame;
    double slot_lag;
    int whole_slots_per_frame;
    int bitrate_index;     /* + */ /* See Main.c and Layer3.c */
    int samplerate_index;  /* + */ /* See Main.c and Layer3.c */
    int crc;
    int ext;
    int mode_ext;
    int copyright;  /* + */
    int original;   /* + */
} priv_shine_mpeg_t;

typedef struct {
    int32_t *xr;                    /* magnitudes of the spectral values */
    int32_t xrsq[GRANULE_SIZE];     /* xr squared */
    int32_t xrabs[GRANULE_SIZE];    /* xr absolute */
    int32_t xrmax;                  /* maximum of xrabs array */
    int32_t en_tot[MAX_GRANULES];   /* gr */
    int32_t en[MAX_GRANULES][21];
    int32_t xm[MAX_GRANULES][21];
    int32_t xrmaxl[MAX_GRANULES];
    double steptab[128]; /* 2**(-x/4)  for x = -127..0 */
    int32_t steptabi[128];  /* 2**(-x/4)  for x = -127..0 */
    int int2idx[10000]; /* x**(3/4)   for x = 0..9999 */
} l3loop_t;

typedef struct {
    int32_t cos_l[18][36];
} mdct_t;

typedef struct {
    int off[MAX_CHANNELS];
    int32_t fl[SBLIMIT][64];
    int32_t x[MAX_CHANNELS][HAN_SIZE];
} subband_t;

/* Side information */
typedef struct {
    unsigned part2_3_length;
    unsigned big_values;
    unsigned count1;
    unsigned global_gain;
    unsigned scalefac_compress;
    unsigned table_select[3];
    unsigned region0_count;
    unsigned region1_count;
    unsigned preflag;
    unsigned scalefac_scale;
    unsigned count1table_select;
    unsigned part2_length;
    unsigned sfb_lmax;
    unsigned address1;
    unsigned address2;
    unsigned address3;
    int quantizerStepSize;
    unsigned slen[4];
} gr_info;

typedef struct {
    unsigned private_bits;
    int resvDrain;
    unsigned scfsi[MAX_CHANNELS][4];
    struct {
        struct {
            gr_info tt;
        } ch[MAX_CHANNELS];
    } gr[MAX_GRANULES];
} shine_side_info_t;

typedef struct {
    double l[MAX_GRANULES][MAX_CHANNELS][21];
} shine_psy_ratio_t;

typedef struct {
    double l[MAX_GRANULES][MAX_CHANNELS][21];
} shine_psy_xmin_t;

typedef struct {
    int32_t l[MAX_GRANULES][MAX_CHANNELS][22];            /* [cb] */
    int32_t s[MAX_GRANULES][MAX_CHANNELS][13][3];         /* [window][cb] */
} shine_scalefac_t;

typedef struct bit_stream_struc {
    unsigned char *data;        /* Processed data */
    int data_size;      /* Total data size */
    int data_position;  /* Data position */
    unsigned int cache;            /* bit stream cache */
    int cache_bits;     /* free bits in cache */
} bitstream_t;


#define         MINIMUM         4    /* Minimum size of the buffer in bytes */
#define         MAX_LENGTH      32   /* Maximum length of word written or
                                        read from bit stream */

#define         BUFFER_SIZE     4096

#define         MIN(A, B)       ((A) < (B) ? (A) : (B))
#define         MAX(A, B)       ((A) > (B) ? (A) : (B))

void shine_open_bit_stream(bitstream_t *bs, const int size);

void shine_close_bit_stream(bitstream_t *bs);

void shine_putbits(bitstream_t *bs, unsigned int val, unsigned int N);

int shine_get_bits_count(bitstream_t *bs);


typedef struct shine_global_flags {
    priv_shine_wave_t wave;
    priv_shine_mpeg_t mpeg;
    bitstream_t bs;
    shine_side_info_t side_info;
    int sideinfo_len;
    int mean_bits;
    shine_psy_ratio_t ratio;
    shine_scalefac_t scalefactor;
    int16_t *buffer[MAX_CHANNELS];
    double pe[MAX_CHANNELS][MAX_GRANULES];
    int l3_enc[MAX_CHANNELS][MAX_GRANULES][GRANULE_SIZE];
    int32_t l3_sb_sample[MAX_CHANNELS][MAX_GRANULES + 1][18][SBLIMIT];
    int32_t mdct_freq[MAX_CHANNELS][MAX_GRANULES][GRANULE_SIZE];
    int ResvSize;
    int ResvMax;
    l3loop_t l3loop;
    mdct_t mdct;
    subband_t subband;
} shine_global_config;


void shine_format_bitstream(shine_global_config *config);


/*
 *
 * Here are MPEG1 Table B.8 and MPEG2 Table B.1 -- Layer III scalefactor bands.
 * Index into this using a method such as:
 *    idx  = fr_ps->header->sampling_frequency + (fr_ps->header->version * 3)
 */

const int shine_slen1_tab[16] = {0, 0, 0, 0, 3, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4};
const int shine_slen2_tab[16] = {0, 1, 2, 3, 0, 1, 2, 3, 1, 2, 3, 1, 2, 3, 2, 3};

/* Valid samplerates and bitrates. */
const int samplerates[9] = {
        44100, 48000, 32000, /* MPEG-I */
        22050, 24000, 16000, /* MPEG-II */
        11025, 12000, 8000   /* MPEG-2.5 */
};

const int bitrates[16][4] = {
        /* MPEG version:
         * 2.5, reserved, II, I */
        {-1, -1, -1,  -1},
        {8,  -1, 8,   32},
        {16, -1, 16,  40},
        {24, -1, 24,  48},
        {32, -1, 32,  56},
        {40, -1, 40,  64},
        {48, -1, 48,  80},
        {56, -1, 56,  96},
        {64, -1, 64,  112},
        {-1, -1, 80,  128},
        {-1, -1, 96,  160},
        {-1, -1, 112, 192},
        {-1, -1, 128, 224},
        {-1, -1, 144, 256},
        {-1, -1, 160, 320},
        {-1, -1, -1,  -1}
};

const int shine_scale_fact_band_index[9][23] =
        {
                /* MPEG-I */
                /* Table B.8.b: 44.1 kHz */
                {0, 4,  8,  12, 16, 20, 24, 30, 36,  44,  52,  62,  74,  90,  110, 134, 162, 196, 238, 288, 342, 418, 576},
                /* Table B.8.c: 48 kHz */
                {0, 4,  8,  12, 16, 20, 24, 30, 36,  42,  50,  60,  72,  88,  106, 128, 156, 190, 230, 276, 330, 384, 576},
                /* Table B.8.a: 32 kHz */
                {0, 4,  8,  12, 16, 20, 24, 30, 36,  44,  54,  66,  82,  102, 126, 156, 194, 240, 296, 364, 448, 550, 576},
                /* MPEG-II */
                /* Table B.2.b: 22.05 kHz */
                {0, 6,  12, 18, 24, 30, 36, 44, 54,  66,  80,  96,  116, 140, 168, 200, 238, 284, 336, 396, 464, 522, 576},
                /* Table B.2.c: 24 kHz */
                {0, 6,  12, 18, 24, 30, 36, 44, 54,  66,  80,  96,  114, 136, 162, 194, 232, 278, 330, 394, 464, 540, 576},
                /* Table B.2.a: 16 kHz */
                {0, 6,  12, 18, 24, 30, 36, 44, 45,  66,  80,  96,  116, 140, 168, 200, 238, 248, 336, 396, 464, 522, 576},

                /* MPEG-2.5 */
                /* 11.025 kHz */
                {0, 6,  12, 18, 24, 30, 36, 44, 54,  66,  80,  96,  116, 140, 168, 200, 238, 284, 336, 396, 464, 522, 576},
                /* 12 kHz */
                {0, 6,  12, 18, 24, 30, 36, 44, 54,  66,  80,  96,  116, 140, 168, 200, 238, 284, 336, 396, 464, 522, 576},
                /* MPEG-2.5 8 kHz */
                {0, 12, 24, 36, 48, 60, 72, 88, 108, 132, 160, 192, 232, 280, 336, 400, 476, 566, 568, 570, 572, 574, 576},
        };

/* note. 0.035781 is shine_enwindow maximum value */
/* scale and convert to fixed point before storing */
#define SHINE_EW(x)                    (int32_t)((double)(x) * 0x7fffffff)
#define SHINE_EW2(a, b)                    SHINE_EW(a), SHINE_EW(b)
#define SHINE_EW10(a, b, c, d, e, f, g, h, i, j)    SHINE_EW2(a,b), SHINE_EW2(c,d), SHINE_EW2(e,f), SHINE_EW2(g,h), SHINE_EW2(i,j)

const int32_t shine_enwindow[] = {
        SHINE_EW10(0.000000, -0.000000, -0.000000, -0.000000, -0.000000, -0.000000, -0.000000, -0.000001, -0.000001,
                   -0.000001),
        SHINE_EW10(-0.000001, -0.000001, -0.000001, -0.000002, -0.000002, -0.000002, -0.000002, -0.000003, -0.000003,
                   -0.000003),
        SHINE_EW10(-0.000004, -0.000004, -0.000005, -0.000005, -0.000006, -0.000007, -0.000008, -0.000008, -0.000009,
                   -0.000010),
        SHINE_EW10(-0.000011, -0.000012, -0.000014, -0.000015, -0.000017, -0.000018, -0.000020, -0.000021, -0.000023,
                   -0.000025),
        SHINE_EW10(-0.000028, -0.000030, -0.000032, -0.000035, -0.000038, -0.000041, -0.000043, -0.000046, -0.000050,
                   -0.000053),
        SHINE_EW10(-0.000056, -0.000060, -0.000063, -0.000066, -0.000070, -0.000073, -0.000077, -0.000081, -0.000084,
                   -0.000087),
        SHINE_EW10(-0.000091, -0.000093, -0.000096, -0.000099, 0.000102, 0.000104, 0.000106, 0.000107, 0.000108,
                   0.000109),
        SHINE_EW10(0.000109, 0.000108, 0.000107, 0.000105, 0.000103, 0.000099, 0.000095, 0.000090, 0.000084, 0.000078),
        SHINE_EW10(0.000070, 0.000061, 0.000051, 0.000040, 0.000027, 0.000014, -0.000001, -0.000017, -0.000034,
                   -0.000053),
        SHINE_EW10(-0.000073, -0.000094, -0.000116, -0.000140, -0.000165, -0.000191, -0.000219, -0.000247, -0.000277,
                   -0.000308),
        SHINE_EW10(-0.000339, -0.000371, -0.000404, -0.000438, -0.000473, -0.000507, -0.000542, -0.000577, -0.000612,
                   -0.000647),
        SHINE_EW10(-0.000681, -0.000714, -0.000747, -0.000779, -0.000810, -0.000839, -0.000866, -0.000892, -0.000915,
                   -0.000936),
        SHINE_EW10(-0.000954, -0.000969, -0.000981, -0.000989, -0.000994, -0.000995, -0.000992, -0.000984, 0.000971,
                   0.000954),
        SHINE_EW10(0.000931, 0.000903, 0.000869, 0.000829, 0.000784, 0.000732, 0.000674, 0.000610, 0.000539, 0.000463),
        SHINE_EW10(0.000379, 0.000288, 0.000192, 0.000088, -0.000021, -0.000137, -0.000260, -0.000388, -0.000522,
                   -0.000662),
        SHINE_EW10(-0.000807, -0.000957, -0.001111, -0.001270, -0.001432, -0.001598, -0.001767, -0.001937, -0.002110,
                   -0.002283),
        SHINE_EW10(-0.002457, -0.002631, -0.002803, -0.002974, -0.003142, -0.003307, -0.003467, -0.003623, -0.003772,
                   -0.003914),
        SHINE_EW10(-0.004049, -0.004175, -0.004291, -0.004396, -0.004490, -0.004570, -0.004638, -0.004691, -0.004728,
                   -0.004749),
        SHINE_EW10(-0.004752, -0.004737, -0.004703, -0.004649, -0.004574, -0.004477, -0.004358, -0.004215, -0.004049,
                   -0.003859),
        SHINE_EW10(-0.003643, -0.003402, 0.003135, 0.002841, 0.002522, 0.002175, 0.001801, 0.001400, 0.000971,
                   0.000516),
        SHINE_EW10(0.000033, -0.000476, -0.001012, -0.001574, -0.002162, -0.002774, -0.003411, -0.004072, -0.004756,
                   -0.005462),
        SHINE_EW10(-0.006189, -0.006937, -0.007703, -0.008487, -0.009288, -0.010104, -0.010933, -0.011775, -0.012628,
                   -0.013489),
        SHINE_EW10(-0.014359, -0.015234, -0.016113, -0.016994, -0.017876, -0.018757, -0.019634, -0.020507, -0.021372,
                   -0.022229),
        SHINE_EW10(-0.023074, -0.023907, -0.024725, -0.025527, -0.026311, -0.027074, -0.027815, -0.028533, -0.029225,
                   -0.029890),
        SHINE_EW10(-0.030527, -0.031133, -0.031707, -0.032248, -0.032755, -0.033226, -0.033660, -0.034056, -0.034413,
                   -0.034730),
        SHINE_EW10(-0.035007, -0.035242, -0.035435, -0.035586, -0.035694, -0.035759, 0.035781, 0.035759, 0.035694,
                   0.035586),
        SHINE_EW10(0.035435, 0.035242, 0.035007, 0.034730, 0.034413, 0.034056, 0.033660, 0.033226, 0.032755, 0.032248),
        SHINE_EW10(0.031707, 0.031133, 0.030527, 0.029890, 0.029225, 0.028533, 0.027815, 0.027074, 0.026311, 0.025527),
        SHINE_EW10(0.024725, 0.023907, 0.023074, 0.022229, 0.021372, 0.020507, 0.019634, 0.018757, 0.017876, 0.016994),
        SHINE_EW10(0.016113, 0.015234, 0.014359, 0.013489, 0.012628, 0.011775, 0.010933, 0.010104, 0.009288, 0.008487),
        SHINE_EW10(0.007703, 0.006937, 0.006189, 0.005462, 0.004756, 0.004072, 0.003411, 0.002774, 0.002162, 0.001574),
        SHINE_EW10(0.001012, 0.000476, -0.000033, -0.000516, -0.000971, -0.001400, -0.001801, -0.002175, -0.002522,
                   -0.002841),
        SHINE_EW10(0.003135, 0.003402, 0.003643, 0.003859, 0.004049, 0.004215, 0.004358, 0.004477, 0.004574, 0.004649),
        SHINE_EW10(0.004703, 0.004737, 0.004752, 0.004749, 0.004728, 0.004691, 0.004638, 0.004570, 0.004490, 0.004396),
        SHINE_EW10(0.004291, 0.004175, 0.004049, 0.003914, 0.003772, 0.003623, 0.003467, 0.003307, 0.003142, 0.002974),
        SHINE_EW10(0.002803, 0.002631, 0.002457, 0.002283, 0.002110, 0.001937, 0.001767, 0.001598, 0.001432, 0.001270),
        SHINE_EW10(0.001111, 0.000957, 0.000807, 0.000662, 0.000522, 0.000388, 0.000260, 0.000137, 0.000021, -0.000088),
        SHINE_EW10(-0.000192, -0.000288, -0.000379, -0.000463, -0.000539, -0.000610, -0.000674, -0.000732, -0.000784,
                   -0.000829),
        SHINE_EW10(-0.000869, -0.000903, -0.000931, -0.000954, 0.000971, 0.000984, 0.000992, 0.000995, 0.000994,
                   0.000989),
        SHINE_EW10(0.000981, 0.000969, 0.000954, 0.000936, 0.000915, 0.000892, 0.000866, 0.000839, 0.000810, 0.000779),
        SHINE_EW10(0.000747, 0.000714, 0.000681, 0.000647, 0.000612, 0.000577, 0.000542, 0.000507, 0.000473, 0.000438),
        SHINE_EW10(0.000404, 0.000371, 0.000339, 0.000308, 0.000277, 0.000247, 0.000219, 0.000191, 0.000165, 0.000140),
        SHINE_EW10(0.000116, 0.000094, 0.000073, 0.000053, 0.000034, 0.000017, 0.000001, -0.000014, -0.000027,
                   -0.000040),
        SHINE_EW10(-0.000051, -0.000061, -0.000070, -0.000078, -0.000084, -0.000090, -0.000095, -0.000099, -0.000103,
                   -0.000105),
        SHINE_EW10(-0.000107, -0.000108, -0.000109, -0.000109, -0.000108, -0.000107, -0.000106, -0.000104, 0.000102,
                   0.000099),
        SHINE_EW10(0.000096, 0.000093, 0.000091, 0.000087, 0.000084, 0.000081, 0.000077, 0.000073, 0.000070, 0.000066),
        SHINE_EW10(0.000063, 0.000060, 0.000056, 0.000053, 0.000050, 0.000046, 0.000043, 0.000041, 0.000038, 0.000035),
        SHINE_EW10(0.000032, 0.000030, 0.000028, 0.000025, 0.000023, 0.000021, 0.000020, 0.000018, 0.000017, 0.000015),
        SHINE_EW10(0.000014, 0.000012, 0.000011, 0.000010, 0.000009, 0.000008, 0.000008, 0.000007, 0.000006, 0.000005),
        SHINE_EW10(0.000005, 0.000004, 0.000004, 0.000003, 0.000003, 0.000003, 0.000002, 0.000002, 0.000002, 0.000002),
        SHINE_EW10(0.000001, 0.000001, 0.000001, 0.000001, 0.000001, 0.000001, 0.000000, 0.000000, 0.000000, 0.000000),
        SHINE_EW2 (0.000000, 0.000000)
};

#endif
#define HUFFBITS uint16_t
#define HTN     34
#define MXOFF   250

struct huffcodetab {
    unsigned int xlen;         /*max. x-index+                         */
    unsigned int ylen;         /*max. y-index+                         */
    unsigned int linbits;      /*number of linbits                     */
    unsigned int linmax;       /*max number to be stored in linbits    */
    const HUFFBITS *table;     /*pointer to array[xlen][ylen]          */
    const unsigned char *hlen; /*pointer to array[xlen][ylen]          */
};

extern const struct huffcodetab shine_huffman_table[HTN];/* global memory block                */
/* array of all huffcodtable headers    */
/* 0..31 Huffman code table 0..31       */
/* 32,33 count1-tables                  */

#ifndef RESERVOIR_H
#define RESERVOIR_H

void shine_ResvFrameBegin(int frameLength, shine_global_config *config);

int shine_max_reservoir_bits(double *pe, shine_global_config *config);

void shine_ResvAdjust(gr_info *gi, shine_global_config *config);

void shine_ResvFrameEnd(shine_global_config *config);

#endif


#ifndef L3SUBBAND_H
#define L3SUBBAND_H

#include <stdint.h>

void shine_subband_initialise(shine_global_config *config);

void shine_window_filter_subband(int16_t **buffer, int32_t s[SBLIMIT], int k, shine_global_config *config, int stride);

#endif

#ifndef shine_MDCT_H
#define shine_MDCT_H

void shine_mdct_initialise(shine_global_config *config);

void shine_mdct_sub(shine_global_config *config, int stride);

#endif

#ifndef L3LOOP_H
#define L3LOOP_H

void shine_loop_initialise(shine_global_config *config);

void shine_iteration_loop(shine_global_config *config);

#endif


const HUFFBITS dmask = 1 << (((sizeof(HUFFBITS)) << 3) - 1);
const unsigned int hs = sizeof(HUFFBITS) << 3;

static const HUFFBITS t1HB[] = {1, 1, 1, 0};
static const HUFFBITS t2HB[] = {1, 2, 1, 3, 1, 1, 3, 2, 0};
static const HUFFBITS t3HB[] = {3, 2, 1, 1, 1, 1, 3, 2, 0};
static const HUFFBITS t5HB[] = {1, 2, 6, 5, 3, 1, 4, 4, 7, 5, 7, 1, 6, 1, 1, 0};
static const HUFFBITS t6HB[] = {7, 3, 5, 1, 6, 2, 3, 2, 5, 4, 4, 1, 3, 3, 2, 0};
static const HUFFBITS t7HB[] = {1, 2, 10, 19, 16, 10, 3, 3, 7, 10, 5, 3, 11, 4, 13, 17, 8, 4, 12, 11, 18, 15, 11, 2, 7,
                                6, 9, 14, 3, 1, 6, 4, 5, 3, 2, 0};
static const HUFFBITS t8HB[] = {3, 4, 6, 18, 12, 5, 5, 1, 2, 16, 9, 3, 7, 3, 5, 14, 7, 3, 19, 17, 15, 13, 10, 4, 13, 5,
                                8, 11, 5, 1, 12, 4, 4, 1, 1, 0};
static const HUFFBITS t9HB[] = {7, 5, 9, 14, 15, 7, 6, 4, 5, 5, 6, 7, 7, 6, 8, 8, 8, 5, 15, 6, 9, 10, 5, 1, 11, 7, 9, 6,
                                4, 1, 14, 4, 6, 2, 6, 0};
static const HUFFBITS t10HB[] = {1, 2, 10, 23, 35, 30, 12, 17, 3, 3, 8, 12, 18, 21, 12, 7, 11, 9, 15, 21, 32, 40, 19, 6,
                                 14, 13, 22, 34, 46, 23, 18, 7, 20, 19, 33, 47, 27, 22, 9, 3, 31, 22, 41, 26, 21, 20, 5,
                                 3, 14, 13, 10, 11, 16, 6, 5, 1, 9, 8, 7, 8, 4, 4, 2, 0};
static const HUFFBITS t11HB[] = {3, 4, 10, 24, 34, 33, 21, 15, 5, 3, 4, 10, 32, 17, 11, 10, 11, 7, 13, 18, 30, 31, 20,
                                 5, 25, 11, 19, 59, 27, 18, 12, 5, 35, 33, 31, 58, 30, 16, 7, 5, 28, 26, 32, 19, 17, 15,
                                 8, 14, 14, 12, 9, 13, 14, 9, 4, 1, 11, 4, 6, 6, 6, 3, 2, 0};
static const HUFFBITS t12HB[] = {9, 6, 16, 33, 41, 39, 38, 26, 7, 5, 6, 9, 23, 16, 26, 11, 17, 7, 11, 14, 21, 30, 10, 7,
                                 17, 10, 15, 12, 18, 28, 14, 5, 32, 13, 22, 19, 18, 16, 9, 5, 40, 17, 31, 29, 17, 13, 4,
                                 2, 27, 12, 11, 15, 10, 7, 4, 1, 27, 12, 8, 12, 6, 3, 1, 0};
static const HUFFBITS t13HB[] = {1, 5, 14, 21, 34, 51, 46, 71, 42, 52, 68, 52, 67, 44, 43, 19, 3, 4, 12, 19, 31, 26, 44,
                                 33, 31, 24, 32, 24, 31, 35, 22, 14, 15, 13, 23, 36, 59, 49, 77, 65, 29, 40, 30, 40, 27,
                                 33, 42, 16, 22,
                                 20, 37, 61, 56, 79, 73, 64, 43, 76, 56, 37, 26, 31, 25, 14, 35, 16, 60, 57, 97, 75,
                                 114, 91, 54, 73, 55, 41, 48, 53, 23, 24, 58, 27, 50, 96, 76, 70, 93, 84, 77, 58, 79,
                                 29, 74, 49, 41, 17, 47,
                                 45, 78, 74, 115, 94, 90, 79, 69, 83, 71, 50, 59, 38, 36, 15, 72, 34, 56, 95, 92, 85,
                                 91, 90, 86, 73, 77, 65, 51, 44, 43, 42, 43, 20, 30, 44, 55, 78, 72, 87, 78, 61, 46, 54,
                                 37, 30, 20, 16, 53,
                                 25, 41, 37, 44, 59, 54, 81, 66, 76, 57, 54, 37, 18, 39, 11, 35, 33, 31, 57, 42, 82, 72,
                                 80, 47, 58, 55, 21, 22, 26, 38, 22, 53, 25, 23, 38, 70, 60, 51, 36, 55, 26, 34, 23, 27,
                                 14, 9, 7, 34, 32,
                                 28, 39, 49, 75, 30, 52, 48, 40, 52, 28, 18, 17, 9, 5, 45, 21, 34, 64, 56, 50, 49, 45,
                                 31, 19, 12, 15, 10, 7, 6, 3, 48, 23, 20, 39, 36, 35, 53, 21, 16, 23, 13, 10, 6, 1, 4,
                                 2, 16, 15, 17, 27, 25,
                                 20, 29, 11, 17, 12, 16, 8, 1, 1, 0, 1};
static const HUFFBITS t15HB[] = {7, 12, 18, 53, 47, 76, 124, 108, 89, 123, 108, 119, 107, 81, 122, 63, 13, 5, 16, 27,
                                 46, 36, 61, 51, 42, 70, 52, 83, 65, 41, 59, 36, 19, 17, 15, 24, 41, 34, 59, 48, 40, 64,
                                 50, 78, 62, 80, 56,
                                 33, 29, 28, 25, 43, 39, 63, 55, 93, 76, 59, 93, 72, 54, 75, 50, 29, 52, 22, 42, 40, 67,
                                 57, 95, 79, 72, 57, 89, 69, 49, 66, 46, 27, 77, 37, 35, 66, 58, 52, 91, 74, 62, 48, 79,
                                 63, 90, 62, 40, 38,
                                 125, 32, 60, 56, 50, 92, 78, 65, 55, 87, 71, 51, 73, 51, 70, 30, 109, 53, 49, 94, 88,
                                 75, 66, 122, 91, 73, 56, 42, 64, 44, 21, 25, 90, 43, 41, 77, 73, 63, 56, 92, 77, 66,
                                 47, 67, 48, 53, 36, 20,
                                 71, 34, 67, 60, 58, 49, 88, 76, 67, 106, 71, 54, 38, 39, 23, 15, 109, 53, 51, 47, 90,
                                 82, 58, 57, 48, 72, 57, 41, 23, 27, 62, 9, 86, 42, 40, 37, 70, 64, 52, 43, 70, 55, 42,
                                 25, 29, 18, 11, 11,
                                 118, 68, 30, 55, 50, 46, 74, 65, 49, 39, 24, 16, 22, 13, 14, 7, 91, 44, 39, 38, 34, 63,
                                 52, 45, 31, 52, 28, 19, 14, 8, 9, 3, 123, 60, 58, 53, 47, 43, 32, 22, 37, 24, 17, 12,
                                 15, 10, 2, 1, 71,
                                 37, 34, 30, 28, 20, 17, 26, 21, 16, 10, 6, 8, 6, 2, 0};
static const HUFFBITS t16HB[] = {1, 5, 14, 44, 74, 63, 110, 93, 172, 149, 138, 242, 225, 195, 376, 17, 3, 4, 12, 20, 35,
                                 62, 53, 47, 83, 75, 68, 119, 201, 107, 207, 9, 15, 13, 23, 38, 67, 58, 103, 90, 161,
                                 72, 127, 117,
                                 110, 209, 206, 16, 45, 21, 39, 69, 64, 114, 99, 87, 158, 140, 252, 212, 199, 387, 365,
                                 26, 75, 36, 68, 65, 115, 101, 179, 164, 155, 264, 246, 226, 395, 382, 362, 9, 66, 30,
                                 59, 56, 102,
                                 185, 173, 265, 142, 253, 232, 400, 388, 378, 445, 16, 111, 54, 52, 100, 184, 178, 160,
                                 133, 257, 244, 228, 217, 385, 366, 715, 10, 98, 48, 91, 88, 165, 157, 148, 261, 248,
                                 407, 397, 372,
                                 380, 889, 884, 8, 85, 84, 81, 159, 156, 143, 260, 249, 427, 401, 392, 383, 727, 713,
                                 708, 7, 154, 76, 73, 141, 131, 256, 245, 426, 406, 394, 384, 735, 359, 710, 352, 11,
                                 139, 129, 67, 125,
                                 247, 233, 229, 219, 393, 743, 737, 720, 885, 882, 439, 4, 243, 120, 118, 115, 227, 223,
                                 396, 746, 742, 736, 721, 712, 706, 223, 436, 6, 202, 224, 222, 218, 216, 389, 386, 381,
                                 364, 888,
                                 443, 707, 440, 437, 1728, 4, 747, 211, 210, 208, 370, 379, 734, 723, 714, 1735, 883,
                                 877, 876, 3459, 865, 2, 377, 369, 102, 187, 726, 722, 358, 711, 709, 866, 1734, 871,
                                 3458, 870, 434,
                                 0, 12, 10, 7, 11, 10, 17, 11, 9, 13, 12, 10, 7, 5, 3, 1, 3};
static const HUFFBITS t24HB[] = {15, 13, 46, 80, 146, 262, 248, 434, 426, 669, 653, 649, 621, 517, 1032, 88, 14, 12, 21,
                                 38, 71, 130, 122, 216, 209, 198, 327, 345, 319, 297, 279, 42, 47, 22, 41, 74, 68, 128,
                                 120, 221,
                                 207, 194, 182, 340, 315, 295, 541, 18, 81, 39, 75, 70, 134, 125, 116, 220, 204, 190,
                                 178, 325, 311, 293, 271, 16, 147, 72, 69, 135, 127, 118, 112, 210, 200, 188, 352, 323,
                                 306, 285,
                                 540, 14, 263, 66, 129, 126, 119, 114, 214, 202, 192, 180, 341, 317, 301, 281, 262, 12,
                                 249, 123, 121, 117, 113, 215, 206, 195, 185, 347, 330, 308, 291, 272, 520, 10, 435,
                                 115, 111,
                                 109, 211, 203, 196, 187, 353, 332, 313, 298, 283, 531, 381, 17, 427, 212, 208, 205,
                                 201, 193, 186, 177, 169, 320, 303, 286, 268, 514, 377, 16, 335, 199, 197, 191, 189,
                                 181, 174, 333,
                                 321, 305, 289, 275, 521, 379, 371, 11, 668, 184, 183, 179, 175, 344, 331, 314, 304,
                                 290, 277, 530, 383, 373, 366, 10, 652, 346, 171, 168, 164, 318, 309, 299, 287, 276,
                                 263, 513, 375,
                                 368, 362, 6, 648, 322, 316, 312, 307, 302, 292, 284, 269, 261, 512, 376, 370, 364, 359,
                                 4, 620, 300, 296, 294, 288, 282, 273, 266, 515, 380, 374, 369, 365, 361, 357, 2, 1033,
                                 280, 278,
                                 274, 267, 264, 259, 382, 378, 372, 367, 363, 360, 358, 356, 0, 43, 20, 19, 17, 15, 13,
                                 11, 9, 7, 6, 4, 7, 5, 3, 1, 3};
static const HUFFBITS t32HB[] = {1, 5, 4, 5, 6, 5, 4, 4, 7, 3, 6, 0, 7, 2, 3, 1};
static const HUFFBITS t33HB[] = {15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

static const unsigned char t1l[] = {1, 3, 2, 3};
static const unsigned char t2l[] = {1, 3, 6, 3, 3, 5, 5, 5, 6};
static const unsigned char t3l[] = {2, 2, 6, 3, 2, 5, 5, 5, 6};
static const unsigned char t5l[] = {1, 3, 6, 7, 3, 3, 6, 7, 6, 6, 7, 8, 7, 6, 7, 8};
static const unsigned char t6l[] = {3, 3, 5, 7, 3, 2, 4, 5, 4, 4, 5, 6, 6, 5, 6, 7};
static const unsigned char t7l[] = {1, 3, 6, 8, 8, 9, 3, 4, 6, 7, 7, 8, 6, 5, 7, 8, 8, 9, 7, 7, 8, 9, 9, 9, 7, 7, 8, 9,
                                    9, 10, 8, 8, 9, 10, 10, 10};
static const unsigned char t8l[] = {2, 3, 6, 8, 8, 9, 3, 2, 4, 8, 8, 8, 6, 4, 6, 8, 8, 9, 8, 8, 8, 9, 9, 10, 8, 7, 8, 9,
                                    10, 10, 9, 8, 9, 9, 11, 11};
static const unsigned char t9l[] = {3, 3, 5, 6, 8, 9, 3, 3, 4, 5, 6, 8, 4, 4, 5, 6, 7, 8, 6, 5, 6, 7, 7, 8, 7, 6, 7, 7,
                                    8, 9, 8, 7, 8, 8, 9, 9};
static const unsigned char t10l[] = {1, 3, 6, 8, 9, 9, 9, 10, 3, 4, 6, 7, 8, 9, 8, 8, 6, 6, 7, 8, 9, 10, 9, 9, 7, 7, 8,
                                     9, 10, 10, 9, 10, 8, 8, 9, 10, 10, 10, 10, 10, 9, 9, 10, 10, 11, 11, 10, 11, 8, 8,
                                     9, 10, 10, 10, 11, 11, 9, 8, 9, 10, 10, 11, 11, 11};
static const unsigned char t11l[] = {2, 3, 5, 7, 8, 9, 8, 9, 3, 3, 4, 6, 8, 8, 7, 8, 5, 5, 6, 7, 8, 9, 8, 8, 7, 6, 7, 9,
                                     8, 10, 8, 9, 8, 8, 8, 9, 9, 10, 9, 10, 8, 8, 9, 10, 10, 11, 10, 11, 8, 7, 7, 8, 9,
                                     10, 10, 10, 8, 7, 8, 9, 10, 10, 10, 10};
static const unsigned char t12l[] = {4, 3, 5, 7, 8, 9, 9, 9, 3, 3, 4, 5, 7, 7, 8, 8, 5, 4, 5, 6, 7, 8, 7, 8, 6, 5, 6, 6,
                                     7, 8, 8, 8, 7, 6, 7, 7, 8, 8, 8, 9, 8, 7, 8, 8, 8, 9, 8, 9, 8, 7, 7, 8, 8, 9, 9,
                                     10, 9, 8, 8, 9, 9, 9, 9, 10};
static const unsigned char t13l[] = {1, 4, 6, 7, 8, 9, 9, 10, 9, 10, 11, 11, 12, 12, 13, 13, 3, 4, 6, 7, 8, 8, 9, 9, 9,
                                     9, 10, 10, 11, 12, 12, 12, 6, 6, 7, 8, 9, 9, 10, 10, 9, 10, 10, 11, 11, 12, 13, 13,
                                     7, 7, 8, 9, 9, 10, 10, 10, 10, 11, 11, 11, 11, 12, 13, 13,
                                     8, 7, 9, 9, 10, 10, 11, 11, 10, 11, 11, 12, 12, 13, 13, 14, 9, 8, 9, 10, 10, 10,
                                     11, 11, 11, 11, 12, 11, 13, 13, 14, 14, 9, 9, 10, 10, 11, 11, 11, 11, 11, 12, 12,
                                     12, 13, 13, 14, 14, 10, 9, 10, 11, 11, 11, 12, 12, 12, 12, 13, 13, 13, 14, 16, 16,
                                     9, 8, 9, 10,
                                     10, 11, 11, 12, 12, 12, 12, 13, 13, 14, 15, 15, 10, 9, 10, 10, 11, 11, 11, 13, 12,
                                     13, 13, 14, 14, 14, 16, 15, 10, 10, 10, 11, 11, 12, 12, 13, 12, 13, 14, 13, 14, 15,
                                     16, 17, 11, 10, 10, 11, 12, 12, 12, 12, 13, 13, 13, 14, 15, 15, 15, 16, 11, 11, 11,
                                     12, 12,
                                     13, 12, 13, 14, 14, 15, 15, 15, 16, 16, 16, 12, 11, 12, 13, 13, 13, 14, 14, 14, 14,
                                     14, 15, 16, 15, 16, 16, 13, 12, 12, 13, 13, 13, 15, 14, 14, 17, 15, 15, 15, 17, 16,
                                     16, 12, 12, 13, 14, 14, 14, 15, 14, 15, 15, 16, 16, 19, 18, 19, 16};
static const unsigned char t15l[] = {3, 4, 5, 7, 7, 8, 9, 9, 9, 10, 10, 11, 11, 11, 12, 13, 4, 3, 5, 6, 7, 7, 8, 8, 8,
                                     9, 9, 10, 10, 10, 11, 11, 5, 5, 5, 6, 7, 7, 8, 8, 8, 9, 9, 10, 10, 11, 11, 11, 6,
                                     6, 6, 7, 7, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 11, 7, 6, 7,
                                     7, 8, 8, 9, 9, 9, 9, 10, 10, 10, 11, 11, 11, 8, 7, 7, 8, 8, 8, 9, 9, 9, 9, 10, 10,
                                     11, 11, 11, 12, 9, 7, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 11, 11, 12, 12, 9, 8, 8, 9,
                                     9, 9, 9, 10, 10, 10, 10, 10, 11, 11, 11, 12, 9, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10,
                                     11, 11,
                                     12, 12, 12, 9, 8, 9, 9, 9, 9, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 10, 9, 9, 9,
                                     10, 10, 10, 10, 10, 11, 11, 11, 11, 12, 13, 12, 10, 9, 9, 9, 10, 10, 10, 10, 11,
                                     11, 11, 11, 12, 12, 12, 13, 11, 10, 9, 10, 10, 10, 11, 11, 11, 11, 11, 11, 12, 12,
                                     13, 13,
                                     11, 10, 10, 10, 10, 11, 11, 11, 11, 12, 12, 12, 12, 12, 13, 13, 12, 11, 11, 11, 11,
                                     11, 11, 11, 12, 12, 12, 12, 13, 13, 12, 13, 12, 11, 11, 11, 11, 11, 11, 12, 12, 12,
                                     12, 12, 13, 13, 13, 13};
static const unsigned char t16l[] = {1, 4, 6, 8, 9, 9, 10, 10, 11, 11, 11, 12, 12, 12, 13, 9, 3, 4, 6, 7, 8, 9, 9, 9,
                                     10, 10, 10, 11, 12, 11, 12, 8, 6, 6, 7, 8, 9, 9, 10, 10, 11, 10, 11, 11, 11, 12,
                                     12, 9, 8, 7, 8, 9, 9, 10, 10, 10, 11, 11, 12, 12, 12, 13, 13,
                                     10, 9, 8, 9, 9, 10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 9, 9, 8, 9, 9, 10, 11,
                                     11, 12, 11, 12, 12, 13, 13, 13, 14, 10, 10, 9, 9, 10, 11, 11, 11, 11, 12, 12, 12,
                                     12, 13, 13, 14, 10, 10, 9, 10, 10, 11, 11, 11, 12, 12, 13, 13, 13, 13, 15, 15, 10,
                                     10, 10,
                                     10, 11, 11, 11, 12, 12, 13, 13, 13, 13, 14, 14, 14, 10, 11, 10, 10, 11, 11, 12, 12,
                                     13, 13, 13, 13, 14, 13, 14, 13, 11, 11, 11, 10, 11, 12, 12, 12, 12, 13, 14, 14, 14,
                                     15, 15, 14, 10, 12, 11, 11, 11, 12, 12, 13, 14, 14, 14, 14, 14, 14, 13, 14, 11, 12,
                                     12,
                                     12, 12, 12, 13, 13, 13, 13, 15, 14, 14, 14, 14, 16, 11, 14, 12, 12, 12, 13, 13, 14,
                                     14, 14, 16, 15, 15, 15, 17, 15, 11, 13, 13, 11, 12, 14, 14, 13, 14, 14, 15, 16, 15,
                                     17, 15, 14, 11, 9, 8, 8, 9, 9, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 8};
static const unsigned char t24l[] = {4, 4, 6, 7, 8, 9, 9, 10, 10, 11, 11, 11, 11, 11, 12, 9, 4, 4, 5, 6, 7, 8, 8, 9, 9,
                                     9, 10, 10, 10, 10, 10, 8, 6, 5, 6, 7, 7, 8, 8, 9, 9, 9, 9, 10, 10, 10, 11, 7, 7, 6,
                                     7, 7, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 7, 8, 7, 7, 8,
                                     8, 8, 8, 9, 9, 9, 10, 10, 10, 10, 11, 7, 9, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10,
                                     10, 10, 7, 9, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 10, 11, 7, 10, 8, 8, 8, 9, 9,
                                     9, 9, 10, 10, 10, 10, 10, 11, 11, 8, 10, 9, 9, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10,
                                     11, 11,
                                     8, 10, 9, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10, 11, 11, 11, 8, 11, 9, 9, 9, 9, 10, 10,
                                     10, 10, 10, 10, 11, 11, 11, 11, 8, 11, 10, 9, 9, 9, 10, 10, 10, 10, 10, 10, 11, 11,
                                     11, 11, 8, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 8, 11, 10,
                                     10,
                                     10, 10, 10, 10, 10, 11, 11, 11, 11, 11, 11, 11, 8, 12, 10, 10, 10, 10, 10, 10, 11,
                                     11, 11, 11, 11, 11, 11, 11, 8, 8, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 4};
static const unsigned char t32l[] = {1, 4, 4, 5, 4, 6, 5, 6, 4, 5, 5, 6, 5, 6, 6, 6};
static const unsigned char t33l[] = {4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4};

#define NOREF -1
const struct huffcodetab shine_huffman_table[HTN] =
        {
                {0,  0,  0,  0, NULL, NULL},
                {2,  2,  0,  0,    t1HB,  t1l},
                {3,  3,  0,  0,    t2HB,  t2l},
                {3,  3,  0,  0,    t3HB,  t3l},
                {0,  0,  0,  0, NULL, NULL},/* Apparently not used*/
                {4,  4,  0,  0,    t5HB,  t5l},
                {4,  4,  0,  0,    t6HB,  t6l},
                {6,  6,  0,  0,    t7HB,  t7l},
                {6,  6,  0,  0,    t8HB,  t8l},
                {6,  6,  0,  0,    t9HB,  t9l},
                {8,  8,  0,  0,    t10HB, t10l},
                {8,  8,  0,  0,    t11HB, t11l},
                {8,  8,  0,  0,    t12HB, t12l},
                {16, 16, 0,  0,    t13HB, t13l},
                {0,  0,  0,  0, NULL, NULL},/* Apparently not used*/
                {16, 16, 0,  0,    t15HB, t15l},
                {16, 16, 1,  1,    t16HB, t16l},
                {16, 16, 2,  3,    t16HB, t16l},
                {16, 16, 3,  7,    t16HB, t16l},
                {16, 16, 4,  15,   t16HB, t16l},
                {16, 16, 6,  63,   t16HB, t16l},
                {16, 16, 8,  255,  t16HB, t16l},
                {16, 16, 10, 1023, t16HB, t16l},
                {16, 16, 13, 8191, t16HB, t16l},
                {16, 16, 4,  15,   t24HB, t24l},
                {16, 16, 5,  31,   t24HB, t24l},
                {16, 16, 6,  63,   t24HB, t24l},
                {16, 16, 7,  127,  t24HB, t24l},
                {16, 16, 8,  255,  t24HB, t24l},
                {16, 16, 9,  511,  t24HB, t24l},
                {16, 16, 11, 2047, t24HB, t24l},
                {16, 16, 13, 8191, t24HB, t24l},
                {1,  16, 0,  0,    t32HB, t32l},
                {1,  16, 0,  0,    t33HB, t33l},
        };


static int granules_per_frame[4] = {
        1,  /* MPEG 2.5 */
        -1,  /* Reserved */
        1,  /* MPEG II */
        2  /* MPEG I */
};

/* Set default values for important vars */
void shine_set_config_mpeg_defaults(shine_mpeg_t *mpeg) {
    mpeg->bitr = 192;
    mpeg->emph = NONE;
    mpeg->copyright = 0;
    mpeg->original = 1;
}

int shine_mpeg_version(int samplerate_index) {
    /* Pick mpeg version according to samplerate index. */
    if (samplerate_index < 3)
        /* First 3 samplerates are for MPEG-I */
        return MPEG_I;
    else if (samplerate_index < 6)
        /* Then it's MPEG-II */
        return MPEG_II;
    else
        /* Finally, MPEG-2.5 */
        return MPEG_25;
}

int shine_find_samplerate_index(int freq) {
    int i;

    for (i = 0; i < 9; i++)
        if (freq == samplerates[i]) return i;

    return -1; /* error - not a valid samplerate for encoder */
}

int shine_find_bitrate_index(int bitr, int mpeg_version) {
    int i;

    for (i = 0; i < 16; i++)
        if (bitr == bitrates[i][mpeg_version]) return i;

    return -1; /* error - not a valid samplerate for encoder */
}

int shine_check_config(int freq, int bitr) {
    int samplerate_index, bitrate_index, mpeg_version;

    samplerate_index = shine_find_samplerate_index(freq);
    if (samplerate_index < 0) return -1;

    mpeg_version = shine_mpeg_version(samplerate_index);

    bitrate_index = shine_find_bitrate_index(bitr, mpeg_version);
    if (bitrate_index < 0) return -1;

    return mpeg_version;
}

int shine_samples_per_pass(shine_t s) {
    return s->mpeg.granules_per_frame * GRANULE_SIZE;
}

/* Compute default encoding values. */
shine_global_config *shine_initialise(shine_config_t *pub_config) {
    double avg_slots_per_frame;
    shine_global_config *config;

    if (shine_check_config(pub_config->wave.samplerate, pub_config->mpeg.bitr) < 0)
        return NULL;

    config = (shine_global_config *)calloc(1, sizeof(shine_global_config));
    if (config == NULL)
        return config;

    shine_subband_initialise(config);
    shine_mdct_initialise(config);
    shine_loop_initialise(config);

    /* Copy public config. */
    config->wave.channels = pub_config->wave.channels;
    config->wave.samplerate = pub_config->wave.samplerate;
    config->mpeg.mode = pub_config->mpeg.mode;
    config->mpeg.bitr = pub_config->mpeg.bitr;
    config->mpeg.emph = pub_config->mpeg.emph;
    config->mpeg.copyright = pub_config->mpeg.copyright;
    config->mpeg.original = pub_config->mpeg.original;

    /* Set default values. */
    config->ResvMax = 0;
    config->ResvSize = 0;
    config->mpeg.layer = LAYER_III;
    config->mpeg.crc = 0;
    config->mpeg.ext = 0;
    config->mpeg.mode_ext = 0;
    config->mpeg.bits_per_slot = 8;

    config->mpeg.samplerate_index = shine_find_samplerate_index(config->wave.samplerate);
    config->mpeg.version = shine_mpeg_version(config->mpeg.samplerate_index);
    config->mpeg.bitrate_index = shine_find_bitrate_index(config->mpeg.bitr, config->mpeg.version);
    config->mpeg.granules_per_frame = granules_per_frame[config->mpeg.version];

    /* Figure average number of 'slots' per frame. */
    avg_slots_per_frame = ((double) config->mpeg.granules_per_frame * GRANULE_SIZE /
                           ((double) config->wave.samplerate)) *
                          (1000 * (double) config->mpeg.bitr /
                           (double) config->mpeg.bits_per_slot);

    config->mpeg.whole_slots_per_frame = (int) avg_slots_per_frame;

    config->mpeg.frac_slots_per_frame = avg_slots_per_frame - (double) config->mpeg.whole_slots_per_frame;
    config->mpeg.slot_lag = -config->mpeg.frac_slots_per_frame;

    if (config->mpeg.frac_slots_per_frame == 0)
        config->mpeg.padding = 0;

    shine_open_bit_stream(&config->bs, BUFFER_SIZE);

    memset((char *) &config->side_info, 0, sizeof(shine_side_info_t));

    /* determine the mean bitrate for main data */
    if (config->mpeg.granules_per_frame == 2) /* MPEG 1 */
        config->sideinfo_len = 8 * ((config->wave.channels == 1) ? 4 + 17 : 4 + 32);
    else                /* MPEG 2 */
        config->sideinfo_len = 8 * ((config->wave.channels == 1) ? 4 + 9 : 4 + 17);

    return config;
}

static unsigned char *shine_encode_buffer_internal(shine_global_config *config, int *written, int stride) {
    if (config->mpeg.frac_slots_per_frame) {
        config->mpeg.padding = (config->mpeg.slot_lag <= (config->mpeg.frac_slots_per_frame - 1.0));
        config->mpeg.slot_lag += (config->mpeg.padding - config->mpeg.frac_slots_per_frame);
    }

    config->mpeg.bits_per_frame = 8 * (config->mpeg.whole_slots_per_frame + config->mpeg.padding);
    config->mean_bits = (config->mpeg.bits_per_frame - config->sideinfo_len) / config->mpeg.granules_per_frame;

    /* apply mdct to the polyphase output */
    shine_mdct_sub(config, stride);

    /* bit and noise allocation */
    shine_iteration_loop(config);

    /* write the frame to the bitstream */
    shine_format_bitstream(config);

    /* Return data. */
    *written = config->bs.data_position;
    config->bs.data_position = 0;

    return config->bs.data;
}

unsigned char *shine_encode_buffer(shine_global_config *config, int16_t **data, int *written) {
    config->buffer[0] = data[0];
    if (config->wave.channels == 2)
        config->buffer[1] = data[1];

    return shine_encode_buffer_internal(config, written, 1);
}

unsigned char *shine_encode_buffer_interleaved(shine_global_config *config, int16_t *data, int *written) {
    config->buffer[0] = data;
    if (config->wave.channels == 2)
        config->buffer[1] = data + 1;

    return shine_encode_buffer_internal(config, written, config->wave.channels);
}

unsigned char *shine_flush(shine_global_config *config, int *written) {
    *written = config->bs.data_position;
    config->bs.data_position = 0;

    return config->bs.data;
}


void shine_close(shine_global_config *config) {
    shine_close_bit_stream(&config->bs);
    free(config);
}
/*
 *  bit_stream.c package
 *  Author:  Jean-Georges Fritsch, C-Cube Microsystems
 *
 * This package provides functions to write information to the bit stream.
 *
 * Removed unused functions. Feb 2001 P.Everett
 */



#if !defined(__APPLE__)

#include <malloc.h>

#endif

/* open the device to write the bit stream into it */
void shine_open_bit_stream(bitstream_t *bs, int size) {
    bs->data = (unsigned char *) malloc(size * sizeof(unsigned char));
    bs->data_size = size;
    bs->data_position = 0;
    bs->cache = 0;
    bs->cache_bits = 32;
}

/*close the device containing the bit stream */
void shine_close_bit_stream(bitstream_t *bs) {
    if (bs->data)
        free(bs->data);
}

/*
 * shine_putbits:
 * --------
 * write N bits into the bit stream.
 * bs = bit stream structure
 * val = value to write into the buffer
 * N = number of bits of val
 */
void shine_putbits(bitstream_t *bs, unsigned int val, unsigned int N) {
#ifdef DEBUG
    if (N > 32)
        printf("Cannot write more than 32 bits at a time.\n");
    if (N < 32 && (val >> N) != 0)
        printf("Upper bits (higher than %d) are not all zeros.\n", N);
#endif

    if (bs->cache_bits > N) {
        bs->cache_bits -= N;
        bs->cache |= val << bs->cache_bits;
    } else {
        if (bs->data_position + sizeof(unsigned int) >= bs->data_size) {
            bs->data = (unsigned char *) realloc(bs->data, bs->data_size + (bs->data_size / 2));
            bs->data_size += (bs->data_size / 2);
        }

        N -= bs->cache_bits;
        bs->cache |= val >> N;
#ifdef SHINE_BIG_ENDIAN
        *(unsigned int*)(bs->data + bs->data_position) = bs->cache;
#else
        *(unsigned int *) (bs->data + bs->data_position) = SWAB32(bs->cache);
#endif
        bs->data_position += sizeof(unsigned int);
        bs->cache_bits = 32 - N;
        if (N != 0)
            bs->cache = val << bs->cache_bits;
        else
            bs->cache = 0;
    }
}

int shine_get_bits_count(bitstream_t *bs) {
    return bs->data_position * 8 + 32 - bs->cache_bits;
}


static void shine_HuffmanCode(bitstream_t *bs, int table_select, int x, int y);

static void encodeSideInfo(shine_global_config *config);

static void encodeMainData(shine_global_config *config);

static void Huffmancodebits(shine_global_config *config, int *ix, gr_info *gi);

/*
  shine_format_bitstream()

  This is called after a frame of audio has been quantized and coded.
  It will write the encoded audio to the bitstream. Note that
  from a layer3 encoder's perspective the bit stream is primarily
  a series of main_data() blocks, with header and side information
  inserted at the proper locations to maintain framing. (See Figure A.7
  in the IS).
*/

void
shine_format_bitstream(shine_global_config *config) {
    int gr, ch, i;

    for (ch = 0; ch < config->wave.channels; ch++)
        for (gr = 0; gr < config->mpeg.granules_per_frame; gr++) {
            int *pi = &config->l3_enc[ch][gr][0];
            int32_t *pr = &config->mdct_freq[ch][gr][0];
            for (i = 0; i < GRANULE_SIZE; i++) {
                if ((pr[i] < 0) && (pi[i] > 0))
                    pi[i] *= -1;
            }
        }

    encodeSideInfo(config);
    encodeMainData(config);
}

static void encodeMainData(shine_global_config *config) {
    int gr, ch, sfb;
    shine_side_info_t si = config->side_info;

    for (gr = 0; gr < config->mpeg.granules_per_frame; gr++) {
        for (ch = 0; ch < config->wave.channels; ch++) {
            gr_info *gi = &(si.gr[gr].ch[ch].tt);
            unsigned slen1 = shine_slen1_tab[gi->scalefac_compress];
            unsigned slen2 = shine_slen2_tab[gi->scalefac_compress];
            int *ix = &config->l3_enc[ch][gr][0];

            if (gr == 0 || si.scfsi[ch][0] == 0)
                for (sfb = 0; sfb < 6; sfb++)
                    shine_putbits(&config->bs, config->scalefactor.l[gr][ch][sfb], slen1);
            if (gr == 0 || si.scfsi[ch][1] == 0)
                for (sfb = 6; sfb < 11; sfb++)
                    shine_putbits(&config->bs, config->scalefactor.l[gr][ch][sfb], slen1);
            if (gr == 0 || si.scfsi[ch][2] == 0)
                for (sfb = 11; sfb < 16; sfb++)
                    shine_putbits(&config->bs, config->scalefactor.l[gr][ch][sfb], slen2);
            if (gr == 0 || si.scfsi[ch][3] == 0)
                for (sfb = 16; sfb < 21; sfb++)
                    shine_putbits(&config->bs, config->scalefactor.l[gr][ch][sfb], slen2);

            Huffmancodebits(config, ix, gi);
        }
    }
}
static void shine_huffman_coder_count1(bitstream_t *bs, const struct huffcodetab *h, int v, int w, int x, int y);

static void encodeSideInfo(shine_global_config *config) {
    int gr, ch, scfsi_band, region;
    shine_side_info_t si = config->side_info;

    shine_putbits(&config->bs, 0x7ff, 11);
    shine_putbits(&config->bs, config->mpeg.version, 2);
    shine_putbits(&config->bs, config->mpeg.layer, 2);
    shine_putbits(&config->bs, !config->mpeg.crc, 1);
    shine_putbits(&config->bs, config->mpeg.bitrate_index, 4);
    shine_putbits(&config->bs, config->mpeg.samplerate_index % 3, 2);
    shine_putbits(&config->bs, config->mpeg.padding, 1);
    shine_putbits(&config->bs, config->mpeg.ext, 1);
    shine_putbits(&config->bs, config->mpeg.mode, 2);
    shine_putbits(&config->bs, config->mpeg.mode_ext, 2);
    shine_putbits(&config->bs, config->mpeg.copyright, 1);
    shine_putbits(&config->bs, config->mpeg.original, 1);
    shine_putbits(&config->bs, config->mpeg.emph, 2);

    if (config->mpeg.version == MPEG_I) {
        shine_putbits(&config->bs, 0, 9);
        if (config->wave.channels == 2)
            shine_putbits(&config->bs, si.private_bits, 3);
        else
            shine_putbits(&config->bs, si.private_bits, 5);
    } else {
        shine_putbits(&config->bs, 0, 8);
        if (config->wave.channels == 2)
            shine_putbits(&config->bs, si.private_bits, 2);
        else
            shine_putbits(&config->bs, si.private_bits, 1);
    }

    if (config->mpeg.version == MPEG_I)
        for (ch = 0; ch < config->wave.channels; ch++) {
            for (scfsi_band = 0; scfsi_band < 4; scfsi_band++)
                shine_putbits(&config->bs, si.scfsi[ch][scfsi_band], 1);
        }

    for (gr = 0; gr < config->mpeg.granules_per_frame; gr++)
        for (ch = 0; ch < config->wave.channels; ch++) {
            gr_info *gi = &(si.gr[gr].ch[ch].tt);

            shine_putbits(&config->bs, gi->part2_3_length, 12);
            shine_putbits(&config->bs, gi->big_values, 9);
            shine_putbits(&config->bs, gi->global_gain, 8);
            if (config->mpeg.version == MPEG_I)
                shine_putbits(&config->bs, gi->scalefac_compress, 4);
            else
                shine_putbits(&config->bs, gi->scalefac_compress, 9);
            shine_putbits(&config->bs, 0, 1);

            for (region = 0; region < 3; region++)
                shine_putbits(&config->bs, gi->table_select[region], 5);

            shine_putbits(&config->bs, gi->region0_count, 4);
            shine_putbits(&config->bs, gi->region1_count, 3);

            if (config->mpeg.version == MPEG_I)
                shine_putbits(&config->bs, gi->preflag, 1);
            shine_putbits(&config->bs, gi->scalefac_scale, 1);
            shine_putbits(&config->bs, gi->count1table_select, 1);
        }
}

/* Note the discussion of huffmancodebits() on pages 28 and 29 of the IS, as
  well as the definitions of the side information on pages 26 and 27. */
static void Huffmancodebits(shine_global_config *config, int *ix, gr_info *gi) {
    const int *scalefac = &shine_scale_fact_band_index[config->mpeg.samplerate_index][0];
    unsigned scalefac_index;
    int region1Start, region2Start;
    int i, bigvalues, count1End;
    int v, w, x, y;
    const struct huffcodetab *h;
    int bits;

    bits = shine_get_bits_count(&config->bs);

    /* 1: Write the bigvalues */
    bigvalues = gi->big_values << 1;

    scalefac_index = gi->region0_count + 1;
    region1Start = scalefac[scalefac_index];
    scalefac_index += gi->region1_count + 1;
    region2Start = scalefac[scalefac_index];

    for (i = 0; i < bigvalues; i += 2) {
        /* get table pointer */
        int idx = (i >= region1Start) + (i >= region2Start);
        unsigned tableindex = gi->table_select[idx];
        /* get huffman code */
        if (tableindex) {
            x = ix[i];
            y = ix[i + 1];
            shine_HuffmanCode(&config->bs, tableindex, x, y);
        }
    }

    /* 2: Write count1 area */
    h = &shine_huffman_table[gi->count1table_select + 32];
    count1End = bigvalues + (gi->count1 << 2);
    for (i = bigvalues; i < count1End; i += 4) {
        v = ix[i];
        w = ix[i + 1];
        x = ix[i + 2];
        y = ix[i + 3];
        shine_huffman_coder_count1(&config->bs, h, v, w, x, y);
    }

    bits = shine_get_bits_count(&config->bs) - bits;
    bits = gi->part2_3_length - gi->part2_length - bits;
    if (bits) {
        int stuffingWords = bits / 32;
        int remainingBits = bits % 32;

        /* Due to the nature of the Huffman code tables, we will pad with ones */
        while (stuffingWords--)
            shine_putbits(&config->bs, ~0, 32);
        if (remainingBits)
            shine_putbits(&config->bs, (1UL << remainingBits) - 1, remainingBits);
    }
}

static inline int shine_abs_and_sign(int *x) {
    if (*x > 0) return 0;
    *x *= -1;
    return 1;
}

static void shine_huffman_coder_count1(bitstream_t *bs, const struct huffcodetab *h, int v, int w, int x, int y) {
    unsigned int signv, signw, signx, signy;
    unsigned int code = 0;
    int p, cbits = 0;

    signv = shine_abs_and_sign(&v);
    signw = shine_abs_and_sign(&w);
    signx = shine_abs_and_sign(&x);
    signy = shine_abs_and_sign(&y);

    p = v + (w << 1) + (x << 2) + (y << 3);
    shine_putbits(bs, h->table[p], h->hlen[p]);

    if (v) {
        code = signv;
        cbits = 1;
    }
    if (w) {
        code = (code << 1) | signw;
        cbits++;
    }
    if (x) {
        code = (code << 1) | signx;
        cbits++;
    }
    if (y) {
        code = (code << 1) | signy;
        cbits++;
    }
    shine_putbits(bs, code, cbits);
}

/* Implements the pseudocode of page 98 of the IS */
static void shine_HuffmanCode(bitstream_t *bs, int table_select, int x, int y) {
    int cbits = 0, xbits = 0;
    unsigned int code = 0, ext = 0;
    unsigned signx, signy, ylen, idx;
    const struct huffcodetab *h;

    signx = shine_abs_and_sign(&x);
    signy = shine_abs_and_sign(&y);

    h = &(shine_huffman_table[table_select]);
    ylen = h->ylen;

    if (table_select > 15) { /* ESC-table is used */
        unsigned linbitsx = 0, linbitsy = 0, linbits = h->linbits;

        if (x > 14) {
            linbitsx = x - 15;
            x = 15;
        }
        if (y > 14) {
            linbitsy = y - 15;
            y = 15;
        }

        idx = (x * ylen) + y;
        code = h->table[idx];
        cbits = h->hlen[idx];
        if (x > 14) {
            ext |= linbitsx;
            xbits += linbits;
        }
        if (x != 0) {
            ext <<= 1;
            ext |= signx;
            xbits += 1;
        }
        if (y > 14) {
            ext <<= linbits;
            ext |= linbitsy;
            xbits += linbits;
        }
        if (y != 0) {
            ext <<= 1;
            ext |= signy;
            xbits += 1;
        }

        shine_putbits(bs, code, cbits);
        shine_putbits(bs, ext, xbits);
    } else { /* No ESC-words */
        idx = (x * ylen) + y;
        code = h->table[idx];
        cbits = h->hlen[idx];
        if (x != 0) {
            code <<= 1;
            code |= signx;
            cbits += 1;
        }
        if (y != 0) {
            code <<= 1;
            code |= signy;
            cbits += 1;
        }

        shine_putbits(bs, code, cbits);
    }
}

#define e        2.71828182845
#define CBLIMIT  21
#define SFB_LMAX 22
#define en_tot_krit 10
#define en_dif_krit 100
#define en_scfsi_band_krit 10
#define xm_scfsi_band_krit 10

static void calc_scfsi(shine_psy_xmin_t *l3_xmin, int ch, int gr, shine_global_config *config);

static int part2_length(int gr, int ch, shine_global_config *config);

static int bin_search_StepSize(int desired_rate, int ix[GRANULE_SIZE], gr_info *cod_info, shine_global_config *config);

static int count_bit(int ix[GRANULE_SIZE], unsigned int start, unsigned int end, unsigned int table);

static int bigv_bitcount(int ix[GRANULE_SIZE], gr_info *gi);

static int new_choose_table(int ix[GRANULE_SIZE], unsigned int begin, unsigned int end);

static void bigv_tab_select(int ix[GRANULE_SIZE], gr_info *cod_info);

static void subdivide(gr_info *cod_info, shine_global_config *config);

static int count1_bitcount(int ix[GRANULE_SIZE], gr_info *cod_info);

static void calc_runlen(int ix[GRANULE_SIZE], gr_info *cod_info);

static void calc_xmin(shine_psy_ratio_t *ratio, gr_info *cod_info, shine_psy_xmin_t *l3_xmin, int gr, int ch);

static int quantize(int ix[GRANULE_SIZE], int stepsize, shine_global_config *config);

/*
 * shine_inner_loop:
 * ----------
 * The code selects the best quantizerStepSize for a particular set
 * of scalefacs.
 */
int shine_inner_loop(int ix[GRANULE_SIZE],
                     int max_bits, gr_info *cod_info, int gr, int ch,
                     shine_global_config *config) {
    int bits, c1bits, bvbits;

    if (max_bits < 0)
        cod_info->quantizerStepSize--;
    do {
        while (quantize(ix, ++cod_info->quantizerStepSize, config) > 8192); /* within table range? */

        calc_runlen(ix, cod_info);                        /* rzero,count1,big_values*/
        bits = c1bits = count1_bitcount(ix, cod_info);    /* count1_table selection*/
        subdivide(cod_info, config);                     /* bigvalues sfb division */
        bigv_tab_select(ix, cod_info);                    /* codebook selection*/
        bits += bvbits = bigv_bitcount(ix, cod_info);  /* bit count */
    } while (bits > max_bits);
    return bits;
}

/*
 * shine_outer_loop:
 * -----------
 *  Function: The outer iteration loop controls the masking conditions
 *  of all scalefactorbands. It computes the best scalefac and
 *  global gain. This module calls the inner iteration loop.
 */

int shine_outer_loop(int max_bits,
                     shine_psy_xmin_t *l3_xmin, /* the allowed distortion of the scalefactor */
                     int ix[GRANULE_SIZE], /* vector of quantized values ix(0..575) */
                     int gr, int ch, shine_global_config *config) {
    int bits, huff_bits;
    shine_side_info_t *side_info = &config->side_info;
    gr_info *cod_info = &side_info->gr[gr].ch[ch].tt;

    cod_info->quantizerStepSize = bin_search_StepSize(max_bits, ix, cod_info, config);

    cod_info->part2_length = part2_length(gr, ch, config);
    huff_bits = max_bits - cod_info->part2_length;

    bits = shine_inner_loop(ix, huff_bits, cod_info, gr, ch, config);
    cod_info->part2_3_length = cod_info->part2_length + bits;

    return cod_info->part2_3_length;
}

/*
 * shine_iteration_loop:
 * ------------------
 */
void shine_iteration_loop(shine_global_config *config) {
    shine_psy_xmin_t l3_xmin;
    gr_info *cod_info;
    int max_bits;
    int ch, gr, i;
    int *ix;

    for (ch = config->wave.channels; ch--;) {
        for (gr = 0; gr < config->mpeg.granules_per_frame; gr++) {
            /* setup pointers */
            ix = config->l3_enc[ch][gr];
            config->l3loop.xr = config->mdct_freq[ch][gr];

            /* Precalculate the square, abs,  and maximum,
             * for use later on.
             */
            for (i = GRANULE_SIZE, config->l3loop.xrmax = 0; i--;) {
                config->l3loop.xrsq[i] = mulsr(config->l3loop.xr[i], config->l3loop.xr[i]);
                config->l3loop.xrabs[i] = labs(config->l3loop.xr[i]);
                if (config->l3loop.xrabs[i] > config->l3loop.xrmax)
                    config->l3loop.xrmax = config->l3loop.xrabs[i];
            }

            cod_info = (gr_info *) &(config->side_info.gr[gr].ch[ch]);
            cod_info->sfb_lmax = SFB_LMAX - 1; /* gr_deco */

            calc_xmin(&config->ratio, cod_info, &l3_xmin, gr, ch);

            if (config->mpeg.version == MPEG_I)
                calc_scfsi(&l3_xmin, ch, gr, config);

            /* calculation of number of available bit( per granule ) */
            max_bits = shine_max_reservoir_bits(&config->pe[ch][gr], config);

            /* reset of iteration variables */
            memset(config->scalefactor.l[gr][ch], 0, sizeof(config->scalefactor.l[gr][ch]));
            memset(config->scalefactor.s[gr][ch], 0, sizeof(config->scalefactor.s[gr][ch]));

            for (i = 4; i--;)
                cod_info->slen[i] = 0;

            cod_info->part2_3_length = 0;
            cod_info->big_values = 0;
            cod_info->count1 = 0;
            cod_info->scalefac_compress = 0;
            cod_info->table_select[0] = 0;
            cod_info->table_select[1] = 0;
            cod_info->table_select[2] = 0;
            cod_info->region0_count = 0;
            cod_info->region1_count = 0;
            cod_info->part2_length = 0;
            cod_info->preflag = 0;
            cod_info->scalefac_scale = 0;
            cod_info->count1table_select = 0;

            /* all spectral values zero ? */
            if (config->l3loop.xrmax)
                cod_info->part2_3_length = shine_outer_loop(max_bits, &l3_xmin, ix,
                                                            gr, ch, config);

            shine_ResvAdjust(cod_info, config);
            cod_info->global_gain = cod_info->quantizerStepSize + 210;

        } /* for gr */
    } /* for ch */

    shine_ResvFrameEnd(config);
}

/*
 * calc_scfsi:
 * -----------
 * calculation of the scalefactor select information ( scfsi ).
 */
void calc_scfsi(shine_psy_xmin_t *l3_xmin, int ch, int gr,
                shine_global_config *config) {
    shine_side_info_t *l3_side = &config->side_info;
    /* This is the scfsi_band table from 2.4.2.7 of the IS */
    static const int scfsi_band_long[5] = {0, 6, 11, 16, 21};

    int scfsi_band;
    unsigned scfsi_set;

    int sfb, start, end, i;
    int condition = 0;
    int temp;

    const int *scalefac_band_long = &shine_scale_fact_band_index[config->mpeg.samplerate_index][0];

    /* note. it goes quite a bit faster if you uncomment the next bit and exit
       early from scfsi, but you then loose the advantage of common scale factors.

    for(scfsi_band=0;scfsi_band<4;scfsi_band++)
      l3_side->scfsi[ch][scfsi_band] = 0;
    return;

    */

    config->l3loop.xrmaxl[gr] = config->l3loop.xrmax;
    scfsi_set = 0;

    /* the total energy of the granule */
    for (temp = 0, i = GRANULE_SIZE; i--;)
        temp += config->l3loop.xrsq[i] >> 10; /* a bit of scaling to avoid overflow, (not very good) */
    if (temp)
        config->l3loop.en_tot[gr] = log((double) temp * 4.768371584e-7) / LN2; /* 1024 / 0x7fffffff */
    else
        config->l3loop.en_tot[gr] = 0;

    /* the energy of each scalefactor band, en */
    /* the allowed distortion of each scalefactor band, xm */

    for (sfb = 21; sfb--;) {
        start = scalefac_band_long[sfb];
        end = scalefac_band_long[sfb + 1];

        for (temp = 0, i = start; i < end; i++)
            temp += config->l3loop.xrsq[i] >> 10;
        if (temp)
            config->l3loop.en[gr][sfb] = log((double) temp * 4.768371584e-7) / LN2; /* 1024 / 0x7fffffff */
        else
            config->l3loop.en[gr][sfb] = 0;

        if (l3_xmin->l[gr][ch][sfb])
            config->l3loop.xm[gr][sfb] = log(l3_xmin->l[gr][ch][sfb]) / LN2;
        else
            config->l3loop.xm[gr][sfb] = 0;
    }

    if (gr == 1) {
        int gr2, tp;

        for (gr2 = 2; gr2--;) {
            /* The spectral values are not all zero */
            if (config->l3loop.xrmaxl[gr2])
                condition++;

            condition++;
        }
        if (abs(config->l3loop.en_tot[0] - config->l3loop.en_tot[1]) < en_tot_krit)
            condition++;
        for (tp = 0, sfb = 21; sfb--;)
            tp += abs(config->l3loop.en[0][sfb] - config->l3loop.en[1][sfb]);
        if (tp < en_dif_krit)
            condition++;

        if (condition == 6) {
            for (scfsi_band = 0; scfsi_band < 4; scfsi_band++) {
                int sum0 = 0, sum1 = 0;
                l3_side->scfsi[ch][scfsi_band] = 0;
                start = scfsi_band_long[scfsi_band];
                end = scfsi_band_long[scfsi_band + 1];
                for (sfb = start; sfb < end; sfb++) {
                    sum0 += abs(config->l3loop.en[0][sfb] - config->l3loop.en[1][sfb]);
                    sum1 += abs(config->l3loop.xm[0][sfb] - config->l3loop.xm[1][sfb]);
                }

                if (sum0 < en_scfsi_band_krit && sum1 < xm_scfsi_band_krit) {
                    l3_side->scfsi[ch][scfsi_band] = 1;
                    scfsi_set |= (1 << scfsi_band);
                } else
                    l3_side->scfsi[ch][scfsi_band] = 0;
            } /* for scfsi_band */
        } /* if condition == 6 */
        else
            for (scfsi_band = 0; scfsi_band < 4; scfsi_band++)
                l3_side->scfsi[ch][scfsi_band] = 0;
    } /* if gr == 1 */
}

/*
 * part2_length:
 * -------------
 * calculates the number of bits needed to encode the scalefacs in the
 * main data block.
 */
int part2_length(int gr, int ch, shine_global_config *config) {
    int slen1, slen2, bits;
    gr_info *gi = &config->side_info.gr[gr].ch[ch].tt;

    bits = 0;

    {
        slen1 = shine_slen1_tab[gi->scalefac_compress];
        slen2 = shine_slen2_tab[gi->scalefac_compress];

        if (!gr || !(config->side_info.scfsi[ch][0]))
            bits += (6 * slen1);

        if (!gr || !(config->side_info.scfsi[ch][1]))
            bits += (5 * slen1);

        if (!gr || !(config->side_info.scfsi[ch][2]))
            bits += (5 * slen2);

        if (!gr || !(config->side_info.scfsi[ch][3]))
            bits += (5 * slen2);
    }
    return bits;
}

/*
 * calc_xmin:
 * ----------
 * Calculate the allowed distortion for each scalefactor band,
 * as determined by the psychoacoustic model.
 * xmin(sb) = ratio(sb) * en(sb) / bw(sb)
 */
void calc_xmin(shine_psy_ratio_t *ratio,
               gr_info *cod_info,
               shine_psy_xmin_t *l3_xmin,
               int gr, int ch) {
    int sfb;

    for (sfb = cod_info->sfb_lmax; sfb--;) {
/*  note. xmin will always be zero with no psychoacoustic model

    start = scalefac_band_long[ sfb ];
    end   = scalefac_band_long[ sfb+1 ];
    bw = end - start;

    for ( en = 0, l = start; l < end; l++ )
      en += config->l3loop.xrsq[l];

    l3_xmin->l[gr][ch][sfb] = ratio->l[gr][ch][sfb] * en / bw;
*/
        l3_xmin->l[gr][ch][sfb] = 0;
    }
}

/*
 * shine_loop_initialise:
 * -------------------
 * Calculates the look up tables used by the iteration loop.
 */
void shine_loop_initialise(shine_global_config *config) {
    int i;

    /* quantize: stepsize conversion, fourth root of 2 table.
     * The table is inverted (negative power) from the equation given
     * in the spec because it is quicker to do x*y than x/y.
     * The 0.5 is for rounding.
     */
    for (i = 128; i--;) {
        config->l3loop.steptab[i] = pow(2.0, (double) (127 - i) / 4);
        if ((config->l3loop.steptab[i] * 2) > 0x7fffffff) /* MAXINT = 2**31 = 2**(124/4) */
            config->l3loop.steptabi[i] = 0x7fffffff;
        else
            /* The table is multiplied by 2 to give an extra bit of accuracy.
             * In quantize, the long multiply does not shift it's result left one
             * bit to compensate.
             */
            config->l3loop.steptabi[i] = (int32_t) ((config->l3loop.steptab[i] * 2) + 0.5);
    }

    /* quantize: vector conversion, three quarter power table.
     * The 0.5 is for rounding, the .0946 comes from the spec.
     */
    for (i = 10000; i--;)
        config->l3loop.int2idx[i] = (int) (sqrt(sqrt((double) i) * (double) i) - 0.0946 + 0.5);
}

/*
 * quantize:
 * ---------
 * Function: Quantization of the vector xr ( -> ix).
 * Returns maximum value of ix.
 */
int quantize(int ix[GRANULE_SIZE], int stepsize, shine_global_config *config) {
    int i, max, ln;
    int32_t scalei;
    double scale, dbl;

    scalei = config->l3loop.steptabi[stepsize + 127]; /* 2**(-stepsize/4) */

    /* a quick check to see if ixmax will be less than 8192 */
    /* this speeds up the early calls to bin_search_StepSize */
    if ((mulr(config->l3loop.xrmax, scalei)) > 165140) /* 8192**(4/3) */
        max = 16384; /* no point in continuing, stepsize not big enough */
    else
        for (i = 0, max = 0; i < GRANULE_SIZE; i++) {
            /* This calculation is very sensitive. The multiply must round it's
             * result or bad things happen to the quality.
             */
            ln = mulr(labs(config->l3loop.xr[i]), scalei);

            if (ln < 10000) /* ln < 10000 catches most values */
                ix[i] = config->l3loop.int2idx[ln]; /* quick look up method */
            else {
                /* outside table range so have to do it using floats */
                scale = config->l3loop.steptab[stepsize + 127]; /* 2**(-stepsize/4) */
                dbl = ((double) config->l3loop.xrabs[i]) * scale * 4.656612875e-10; /* 0x7fffffff */
                ix[i] = (int) sqrt(sqrt(dbl) * dbl); /* dbl**(3/4) */
            }

            /* calculate ixmax while we're here */
            /* note. ix cannot be negative */
            if (max < ix[i])
                max = ix[i];
        }

    return max;
}

/*
 * ix_max:
 * -------
 * Function: Calculate the maximum of ix from 0 to 575
 */
static inline int ix_max(int ix[GRANULE_SIZE], unsigned int begin, unsigned int end) {
    register int i;
    register int max = 0;

    for (i = begin; i < end; i++)
        if (max < ix[i])
            max = ix[i];
    return max;
}

/*
 * calc_runlen:
 * ------------
 * Function: Calculation of rzero, count1, big_values
 * (Partitions ix into big values, quadruples and zeros).
 */
void calc_runlen(int ix[GRANULE_SIZE], gr_info *cod_info) {
    int i;
    int rzero = 0;

    for (i = GRANULE_SIZE; i > 1; i -= 2)
        if (!ix[i - 1] && !ix[i - 2])
            rzero++;
        else
            break;

    cod_info->count1 = 0;
    for (; i > 3; i -= 4)
        if (ix[i - 1] <= 1
            && ix[i - 2] <= 1
            && ix[i - 3] <= 1
            && ix[i - 4] <= 1)
            cod_info->count1++;
        else
            break;

    cod_info->big_values = i >> 1;
}

/*
 * count1_bitcount:
 * ----------------
 * Determines the number of bits to encode the quadruples.
 */
int count1_bitcount(int ix[GRANULE_SIZE], gr_info *cod_info) {
    int p, i, k;
    int v, w, x, y, signbits;
    int sum0 = 0,
            sum1 = 0;

    for (i = cod_info->big_values << 1, k = 0; k < cod_info->count1; i += 4, k++) {
        v = ix[i];
        w = ix[i + 1];
        x = ix[i + 2];
        y = ix[i + 3];

        p = v + (w << 1) + (x << 2) + (y << 3);

        signbits = 0;
        if (v != 0) signbits++;
        if (w != 0) signbits++;
        if (x != 0) signbits++;
        if (y != 0) signbits++;

        sum0 += signbits;
        sum1 += signbits;

        sum0 += shine_huffman_table[32].hlen[p];
        sum1 += shine_huffman_table[33].hlen[p];
    }

    if (sum0 < sum1) {
        cod_info->count1table_select = 0;
        return sum0;
    } else {
        cod_info->count1table_select = 1;
        return sum1;
    }
}

/*
 * subdivide:
 * ----------
 * presumable subdivides the bigvalue region which will use separate Huffman tables.
 */
void subdivide(gr_info *cod_info, shine_global_config *config) {
    static const struct {
        unsigned region0_count;
        unsigned region1_count;
    } subdv_table[23] =
            {
                    {0, 0}, /* 0 bands */
                    {0, 0}, /* 1 bands */
                    {0, 0}, /* 2 bands */
                    {0, 0}, /* 3 bands */
                    {0, 0}, /* 4 bands */
                    {0, 1}, /* 5 bands */
                    {1, 1}, /* 6 bands */
                    {1, 1}, /* 7 bands */
                    {1, 2}, /* 8 bands */
                    {2, 2}, /* 9 bands */
                    {2, 3}, /* 10 bands */
                    {2, 3}, /* 11 bands */
                    {3, 4}, /* 12 bands */
                    {3, 4}, /* 13 bands */
                    {3, 4}, /* 14 bands */
                    {4, 5}, /* 15 bands */
                    {4, 5}, /* 16 bands */
                    {4, 6}, /* 17 bands */
                    {5, 6}, /* 18 bands */
                    {5, 6}, /* 19 bands */
                    {5, 7}, /* 20 bands */
                    {6, 7}, /* 21 bands */
                    {6, 7}, /* 22 bands */
            };

    if (!cod_info->big_values) { /* no big_values region */
        cod_info->region0_count = 0;
        cod_info->region1_count = 0;
    } else {
        const int *scalefac_band_long = &shine_scale_fact_band_index[config->mpeg.samplerate_index][0];
        int bigvalues_region, scfb_anz, thiscount;

        bigvalues_region = 2 * cod_info->big_values;

        /* Calculate scfb_anz */
        scfb_anz = 0;
        while (scalefac_band_long[scfb_anz] < bigvalues_region)
            scfb_anz++;

        for (thiscount = subdv_table[scfb_anz].region0_count; thiscount; thiscount--) {
            if (scalefac_band_long[thiscount + 1] <= bigvalues_region)
                break;
        }
        cod_info->region0_count = thiscount;
        cod_info->address1 = scalefac_band_long[thiscount + 1];

        scalefac_band_long += cod_info->region0_count + 1;

        for (thiscount = subdv_table[scfb_anz].region1_count; thiscount; thiscount--) {
            if (scalefac_band_long[thiscount + 1] <= bigvalues_region)
                break;
        }
        cod_info->region1_count = thiscount;
        cod_info->address2 = scalefac_band_long[thiscount + 1];

        cod_info->address3 = bigvalues_region;
    }
}

/*
 * bigv_tab_select:
 * ----------------
 * Function: Select huffman code tables for bigvalues regions
 */
void bigv_tab_select(int ix[GRANULE_SIZE], gr_info *cod_info) {
    cod_info->table_select[0] = 0;
    cod_info->table_select[1] = 0;
    cod_info->table_select[2] = 0;

    {
        if (cod_info->address1 > 0)
            cod_info->table_select[0] = new_choose_table(ix, 0, cod_info->address1);

        if (cod_info->address2 > cod_info->address1)
            cod_info->table_select[1] = new_choose_table(ix, cod_info->address1, cod_info->address2);

        if (cod_info->big_values << 1 > cod_info->address2)
            cod_info->table_select[2] = new_choose_table(ix, cod_info->address2, cod_info->big_values << 1);
    }
}

/*
 * new_choose_table:
 * -----------------
 * Choose the Huffman table that will encode ix[begin..end] with
 * the fewest bits.
 * Note: This code contains knowledge about the sizes and characteristics
 * of the Huffman tables as defined in the IS (Table B.7), and will not work
 * with any arbitrary tables.
 */
int new_choose_table(int ix[GRANULE_SIZE], unsigned int begin, unsigned int end) {
    int i, max;
    int choice[2];
    int sum[2];

    max = ix_max(ix, begin, end);
    if (!max)
        return 0;

    choice[0] = 0;
    choice[1] = 0;

    if (max < 15) {
        /* try tables with no linbits */
        for (i = 14; i--;)
            if (shine_huffman_table[i].xlen > max) {
                choice[0] = i;
                break;
            }

        sum[0] = count_bit(ix, begin, end, choice[0]);

        switch (choice[0]) {
            case 2:
                sum[1] = count_bit(ix, begin, end, 3);
                if (sum[1] <= sum[0])
                    choice[0] = 3;
                break;

            case 5:
                sum[1] = count_bit(ix, begin, end, 6);
                if (sum[1] <= sum[0])
                    choice[0] = 6;
                break;

            case 7:
                sum[1] = count_bit(ix, begin, end, 8);
                if (sum[1] <= sum[0]) {
                    choice[0] = 8;
                    sum[0] = sum[1];
                }
                sum[1] = count_bit(ix, begin, end, 9);
                if (sum[1] <= sum[0])
                    choice[0] = 9;
                break;

            case 10:
                sum[1] = count_bit(ix, begin, end, 11);
                if (sum[1] <= sum[0]) {
                    choice[0] = 11;
                    sum[0] = sum[1];
                }
                sum[1] = count_bit(ix, begin, end, 12);
                if (sum[1] <= sum[0])
                    choice[0] = 12;
                break;

            case 13:
                sum[1] = count_bit(ix, begin, end, 15);
                if (sum[1] <= sum[0])
                    choice[0] = 15;
                break;
        }
    } else {
        /* try tables with linbits */
        max -= 15;

        for (i = 15; i < 24; i++)
            if (shine_huffman_table[i].linmax >= max) {
                choice[0] = i;
                break;
            }

        for (i = 24; i < 32; i++)
            if (shine_huffman_table[i].linmax >= max) {
                choice[1] = i;
                break;
            }

        sum[0] = count_bit(ix, begin, end, choice[0]);
        sum[1] = count_bit(ix, begin, end, choice[1]);
        if (sum[1] < sum[0])
            choice[0] = choice[1];
    }
    return choice[0];
}

/*
 * bigv_bitcount:
 * --------------
 * Function: Count the number of bits necessary to code the bigvalues region.
 */
int bigv_bitcount(int ix[GRANULE_SIZE], gr_info *gi) {
    int bits = 0;
    unsigned int table;

    if ((table = gi->table_select[0]))  /* region0 */
        bits += count_bit(ix, 0, gi->address1, table);
    if ((table = gi->table_select[1]))  /* region1 */
        bits += count_bit(ix, gi->address1, gi->address2, table);
    if ((table = gi->table_select[2]))  /* region2 */
        bits += count_bit(ix, gi->address2, gi->address3, table);
    return bits;
}

/*
 * count_bit:
 * ----------
 * Function: Count the number of bits necessary to code the subregion.
 */
int count_bit(int ix[GRANULE_SIZE],
              unsigned int start,
              unsigned int end,
              unsigned int table) {
    unsigned linbits, ylen;
    register int i, sum;
    register int x, y;
    const struct huffcodetab *h;

    if (!table)
        return 0;

    h = &(shine_huffman_table[table]);
    sum = 0;

    ylen = h->ylen;
    linbits = h->linbits;

    if (table > 15) { /* ESC-table is used */
        for (i = start; i < end; i += 2) {
            x = ix[i];
            y = ix[i + 1];
            if (x > 14) {
                x = 15;
                sum += linbits;
            }
            if (y > 14) {
                y = 15;
                sum += linbits;
            }

            sum += h->hlen[(x * ylen) + y];
            if (x)
                sum++;
            if (y)
                sum++;
        }
    } else { /* No ESC-words */
        for (i = start; i < end; i += 2) {
            x = ix[i];
            y = ix[i + 1];

            sum += h->hlen[(x * ylen) + y];

            if (x != 0)
                sum++;
            if (y != 0)
                sum++;
        }
    }
    return sum;
}

/*
 * bin_search_StepSize:
 * --------------------
 * Succesive approximation approach to obtaining a initial quantizer
 * step size.
 * The following optional code written by Seymour Shlien
 * will speed up the shine_outer_loop code which is called
 * by iteration_loop. When BIN_SEARCH is defined, the
 * shine_outer_loop function precedes the call to the function shine_inner_loop
 * with a call to bin_search gain defined below, which
 * returns a good starting quantizerStepSize.
 */
int bin_search_StepSize(int desired_rate, int ix[GRANULE_SIZE],
                        gr_info *cod_info, shine_global_config *config) {
    int bit, next, count;

    next = -120;
    count = 120;

    do {
        int half = count / 2;

        if (quantize(ix, next + half, config) > 8192)
            bit = 100000;  /* fail */
        else {
            calc_runlen(ix, cod_info);           /* rzero,count1,big_values */
            bit = count1_bitcount(ix, cod_info); /* count1_table selection */
            subdivide(cod_info, config);         /* bigvalues sfb division */
            bigv_tab_select(ix, cod_info);       /* codebook selection */
            bit += bigv_bitcount(ix, cod_info);  /* bit count */
        }

        if (bit < desired_rate)
            count = half;
        else {
            next += half;
            count -= half;
        }
    } while (count > 1);

    return next;
}

/* This is table B.9: coefficients for aliasing reduction */
#define MDCT_CA(coef)    (int32_t)(coef / sqrt(1.0 + (coef * coef)) * 0x7fffffff)
#define MDCT_CS(coef)    (int32_t)(1.0  / sqrt(1.0 + (coef * coef)) * 0x7fffffff)

#define MDCT_CA0    MDCT_CA(-0.6)
#define MDCT_CA1    MDCT_CA(-0.535)
#define MDCT_CA2    MDCT_CA(-0.33)
#define MDCT_CA3    MDCT_CA(-0.185)
#define MDCT_CA4    MDCT_CA(-0.095)
#define MDCT_CA5    MDCT_CA(-0.041)
#define MDCT_CA6    MDCT_CA(-0.0142)
#define MDCT_CA7    MDCT_CA(-0.0037)

#define MDCT_CS0    MDCT_CS(-0.6)
#define MDCT_CS1    MDCT_CS(-0.535)
#define MDCT_CS2    MDCT_CS(-0.33)
#define MDCT_CS3    MDCT_CS(-0.185)
#define MDCT_CS4    MDCT_CS(-0.095)
#define MDCT_CS5    MDCT_CS(-0.041)
#define MDCT_CS6    MDCT_CS(-0.0142)
#define MDCT_CS7    MDCT_CS(-0.0037)

/*
 * shine_mdct_initialise:
 * -------------------
 */
void shine_mdct_initialise(shine_global_config *config) {
    int m, k;

    /* prepare the mdct coefficients */
    for (m = 18; m--;)
        for (k = 36; k--;)
            /* combine window and mdct coefficients into a single table */
            /* scale and convert to fixed point before storing */
            config->mdct.cos_l[m][k] = (int32_t) (sin(PI36 * (k + 0.5))
                                                  * cos((PI / 72) * (2 * k + 19) * (2 * m + 1)) * 0x7fffffff);
}

/*
 * shine_mdct_sub:
 * ------------
 */
void shine_mdct_sub(shine_global_config *config, int stride) {
    /* note. we wish to access the array 'config->mdct_freq[2][2][576]' as
     * [2][2][32][18]. (32*18=576),
     */
    int32_t (*mdct_enc)[18];

    int ch, gr, band, j, k;
    int32_t mdct_in[36];

    for (ch = config->wave.channels; ch--;) {
        for (gr = 0; gr < config->mpeg.granules_per_frame; gr++) {
            /* set up pointer to the part of config->mdct_freq we're using */
            mdct_enc = (int32_t (*)[18]) config->mdct_freq[ch][gr];

            /* polyphase filtering */
            for (k = 0; k < 18; k += 2) {
                shine_window_filter_subband(&config->buffer[ch], &config->l3_sb_sample[ch][gr + 1][k][0], ch, config,
                                            stride);
                shine_window_filter_subband(&config->buffer[ch], &config->l3_sb_sample[ch][gr + 1][k + 1][0], ch,
                                            config, stride);
                /* Compensate for inversion in the analysis filter
                 * (every odd index of band AND k)
                 */
                for (band = 1; band < 32; band += 2)
                    config->l3_sb_sample[ch][gr + 1][k + 1][band] *= -1;
            }

            /* Perform imdct of 18 previous subband samples + 18 current subband samples */
            for (band = 0; band < 32; band++) {
                for (k = 18; k--;) {
                    mdct_in[k] = config->l3_sb_sample[ch][gr][k][band];
                    mdct_in[k + 18] = config->l3_sb_sample[ch][gr + 1][k][band];
                }

                /* Calculation of the MDCT
                 * In the case of long blocks ( block_type 0,1,3 ) there are
                 * 36 coefficients in the time domain and 18 in the frequency
                 * domain.
                 */
                for (k = 18; k--;) {
                    int32_t vm;
                    uint32_t vm_lo __attribute__((unused));

                    mul0(vm, vm_lo, mdct_in[35], config->mdct.cos_l[k][35]);
                    for (j = 35; j; j -= 7) {
                        muladd(vm, vm_lo, mdct_in[j - 1], config->mdct.cos_l[k][j - 1]);
                        muladd(vm, vm_lo, mdct_in[j - 2], config->mdct.cos_l[k][j - 2]);
                        muladd(vm, vm_lo, mdct_in[j - 3], config->mdct.cos_l[k][j - 3]);
                        muladd(vm, vm_lo, mdct_in[j - 4], config->mdct.cos_l[k][j - 4]);
                        muladd(vm, vm_lo, mdct_in[j - 5], config->mdct.cos_l[k][j - 5]);
                        muladd(vm, vm_lo, mdct_in[j - 6], config->mdct.cos_l[k][j - 6]);
                        muladd(vm, vm_lo, mdct_in[j - 7], config->mdct.cos_l[k][j - 7]);
                    }
                    mulz(vm, vm_lo);
                    mdct_enc[band][k] = vm;
                }

                /* Perform aliasing reduction butterfly */
                if (band != 0) {
                    cmuls(mdct_enc[band][0], mdct_enc[band - 1][17 - 0], mdct_enc[band][0], mdct_enc[band - 1][17 - 0],
                          MDCT_CS0, MDCT_CA0);
                    cmuls(mdct_enc[band][1], mdct_enc[band - 1][17 - 1], mdct_enc[band][1], mdct_enc[band - 1][17 - 1],
                          MDCT_CS1, MDCT_CA1);
                    cmuls(mdct_enc[band][2], mdct_enc[band - 1][17 - 2], mdct_enc[band][2], mdct_enc[band - 1][17 - 2],
                          MDCT_CS2, MDCT_CA2);
                    cmuls(mdct_enc[band][3], mdct_enc[band - 1][17 - 3], mdct_enc[band][3], mdct_enc[band - 1][17 - 3],
                          MDCT_CS3, MDCT_CA3);
                    cmuls(mdct_enc[band][4], mdct_enc[band - 1][17 - 4], mdct_enc[band][4], mdct_enc[band - 1][17 - 4],
                          MDCT_CS4, MDCT_CA4);
                    cmuls(mdct_enc[band][5], mdct_enc[band - 1][17 - 5], mdct_enc[band][5], mdct_enc[band - 1][17 - 5],
                          MDCT_CS5, MDCT_CA5);
                    cmuls(mdct_enc[band][6], mdct_enc[band - 1][17 - 6], mdct_enc[band][6], mdct_enc[band - 1][17 - 6],
                          MDCT_CS6, MDCT_CA6);
                    cmuls(mdct_enc[band][7], mdct_enc[band - 1][17 - 7], mdct_enc[band][7], mdct_enc[band - 1][17 - 7],
                          MDCT_CS7, MDCT_CA7);
                }
            }
        }

        /* Save latest granule's subband samples to be used in the next mdct call */
        memcpy(config->l3_sb_sample[ch][0], config->l3_sb_sample[ch][config->mpeg.granules_per_frame],
               sizeof(config->l3_sb_sample[0][0]));
    }
}

/*
 * shine_subband_initialise:
 * ----------------------
 * Calculates the analysis filterbank coefficients and rounds to the
 * 9th decimal place accuracy of the filterbank tables in the ISO
 * document.  The coefficients are stored in #filter#
 */
void shine_subband_initialise(shine_global_config *config) {
    int i, j;
    double filter;

    for (i = MAX_CHANNELS; i--;) {
        config->subband.off[i] = 0;
        memset(config->subband.x[i], 0, sizeof(config->subband.x[i]));
    }

    for (i = SBLIMIT; i--;)
        for (j = 64; j--;) {
            if ((filter = 1e9 * cos((double) ((2 * i + 1) * (16 - j) * PI64))) >= 0)
                modf(filter + 0.5, &filter);
            else
                modf(filter - 0.5, &filter);
            /* scale and convert to fixed point before storing */
            config->subband.fl[i][j] = (int32_t) (filter * (0x7fffffff * 1e-9));
        }
}

/*
 * shine_window_filter_subband:
 * -------------------------
 * Overlapping window on PCM samples
 * 32 16-bit pcm samples are scaled to fractional 2's complement and
 * concatenated to the end of the window buffer #x#. The updated window
 * buffer #x# is then windowed by the analysis window #shine_enwindow# to produce
 * the windowed sample #z#
 * Calculates the analysis filter bank coefficients
 * The windowed samples #z# is filtered by the digital filter matrix #filter#
 * to produce the subband samples #s#. This done by first selectively
 * picking out values from the windowed samples, and then multiplying
 * them by the filter matrix, producing 32 subband samples.
 */
void
shine_window_filter_subband(int16_t **buffer, int32_t s[SBLIMIT], int ch, shine_global_config *config, int stride) {
    int32_t y[64];
    int i, j;
    int16_t *ptr = *buffer;

    /* replace 32 oldest samples with 32 new samples */
    for (i = 32; i--;) {
        config->subband.x[ch][i + config->subband.off[ch]] = ((int32_t) *ptr) << 16;
        ptr += stride;
    }
    *buffer = ptr;

    for (i = 64; i--;) {
        int32_t s_value;
        uint32_t s_value_lo __attribute__((unused));

        mul0  (s_value, s_value_lo, config->subband.x[ch][(config->subband.off[ch] + i + (0 << 6)) & (HAN_SIZE - 1)],
               shine_enwindow[i + (0 << 6)]);
        muladd(s_value, s_value_lo, config->subband.x[ch][(config->subband.off[ch] + i + (1 << 6)) & (HAN_SIZE - 1)],
               shine_enwindow[i + (1 << 6)]);
        muladd(s_value, s_value_lo, config->subband.x[ch][(config->subband.off[ch] + i + (2 << 6)) & (HAN_SIZE - 1)],
               shine_enwindow[i + (2 << 6)]);
        muladd(s_value, s_value_lo, config->subband.x[ch][(config->subband.off[ch] + i + (3 << 6)) & (HAN_SIZE - 1)],
               shine_enwindow[i + (3 << 6)]);
        muladd(s_value, s_value_lo, config->subband.x[ch][(config->subband.off[ch] + i + (4 << 6)) & (HAN_SIZE - 1)],
               shine_enwindow[i + (4 << 6)]);
        muladd(s_value, s_value_lo, config->subband.x[ch][(config->subband.off[ch] + i + (5 << 6)) & (HAN_SIZE - 1)],
               shine_enwindow[i + (5 << 6)]);
        muladd(s_value, s_value_lo, config->subband.x[ch][(config->subband.off[ch] + i + (6 << 6)) & (HAN_SIZE - 1)],
               shine_enwindow[i + (6 << 6)]);
        muladd(s_value, s_value_lo, config->subband.x[ch][(config->subband.off[ch] + i + (7 << 6)) & (HAN_SIZE - 1)],
               shine_enwindow[i + (7 << 6)]);
        mulz  (s_value, s_value_lo);
        y[i] = s_value;
    }

    config->subband.off[ch] = (config->subband.off[ch] + 480) & (HAN_SIZE - 1); /* offset is modulo (HAN_SIZE)*/

    for (i = SBLIMIT; i--;) {
        int32_t s_value;
        uint32_t s_value_lo __attribute__((unused));

        mul0(s_value, s_value_lo, config->subband.fl[i][63], y[63]);
        for (j = 63; j; j -= 7) {
            muladd(s_value, s_value_lo, config->subband.fl[i][j - 1], y[j - 1]);
            muladd(s_value, s_value_lo, config->subband.fl[i][j - 2], y[j - 2]);
            muladd(s_value, s_value_lo, config->subband.fl[i][j - 3], y[j - 3]);
            muladd(s_value, s_value_lo, config->subband.fl[i][j - 4], y[j - 4]);
            muladd(s_value, s_value_lo, config->subband.fl[i][j - 5], y[j - 5]);
            muladd(s_value, s_value_lo, config->subband.fl[i][j - 6], y[j - 6]);
            muladd(s_value, s_value_lo, config->subband.fl[i][j - 7], y[j - 7]);
        }
        mulz(s_value, s_value_lo);
        s[i] = s_value;
    }
}


/*
 * shine_max_reservoir_bits:
 * ------------
 * Called at the beginning of each granule to get the max bit
 * allowance for the current granule based on reservoir size
 * and perceptual entropy.
 */
int shine_max_reservoir_bits(double *pe, shine_global_config *config) {
    int more_bits, max_bits, add_bits, over_bits;
    int mean_bits = config->mean_bits;

    mean_bits /= config->wave.channels;
    max_bits = mean_bits;

    if (max_bits > 4095)
        max_bits = 4095;
    if (!config->ResvMax)
        return max_bits;

    more_bits = *pe * 3.1 - mean_bits;
    add_bits = 0;
    if (more_bits > 100) {
        int frac = (config->ResvSize * 6) / 10;

        if (frac < more_bits)
            add_bits = frac;
        else
            add_bits = more_bits;
    }
    over_bits = config->ResvSize - ((config->ResvMax << 3) / 10) - add_bits;
    if (over_bits > 0)
        add_bits += over_bits;

    max_bits += add_bits;
    if (max_bits > 4095)
        max_bits = 4095;
    return max_bits;
}

/*
 * shine_ResvAdjust:
 * -----------
 * Called after a granule's bit allocation. Readjusts the size of
 * the reservoir to reflect the granule's usage.
 */
void shine_ResvAdjust(gr_info *gi, shine_global_config *config) {
    config->ResvSize += (config->mean_bits / config->wave.channels) - gi->part2_3_length;
}

/*
 * shine_ResvFrameEnd:
 * -------------
 * Called after all granules in a frame have been allocated. Makes sure
 * that the reservoir size is within limits, possibly by adding stuffing
 * bits. Note that stuffing bits are added by increasing a granule's
 * part2_3_length. The bitstream formatter will detect this and write the
 * appropriate stuffing bits to the bitstream.
 */
void shine_ResvFrameEnd(shine_global_config *config) {
    gr_info *gi;
    int gr, ch, ancillary_pad, stuffingBits;
    int over_bits;
    shine_side_info_t *l3_side = &config->side_info;

    ancillary_pad = 0;

    /* just in case mean_bits is odd, this is necessary... */
    if ((config->wave.channels == 2) && (config->mean_bits & 1))
        config->ResvSize += 1;

    over_bits = config->ResvSize - config->ResvMax;
    if (over_bits < 0)
        over_bits = 0;

    config->ResvSize -= over_bits;
    stuffingBits = over_bits + ancillary_pad;

    /* we must be byte aligned */
    if ((over_bits = config->ResvSize % 8)) {
        stuffingBits += over_bits;
        config->ResvSize -= over_bits;
    }

    if (stuffingBits) {
        /*
         * plan a: put all into the first granule
         * This was preferred by someone designing a
         * real-time decoder...
         */
        gi = (gr_info *) &(l3_side->gr[0].ch[0]);

        if (gi->part2_3_length + stuffingBits < 4095)
            gi->part2_3_length += stuffingBits;
        else {
            /* plan b: distribute throughout the granules */
            for (gr = 0; gr < config->mpeg.granules_per_frame; gr++)
                for (ch = 0; ch < config->wave.channels; ch++) {
                    int extraBits, bitsThisGr;
                    gr_info *gi = (gr_info *) &(l3_side->gr[gr].ch[ch]);
                    if (!stuffingBits)
                        break;
                    extraBits = 4095 - gi->part2_3_length;
                    bitsThisGr = extraBits < stuffingBits ? extraBits : stuffingBits;
                    gi->part2_3_length += bitsThisGr;
                    stuffingBits -= bitsThisGr;
                }
            /*
             * If any stuffing bits remain, we elect to spill them
             * into ancillary data. The bitstream formatter will do this if
             * l3side->resvDrain is set
             */
            l3_side->resvDrain = stuffingBits;
        }
    }
}


