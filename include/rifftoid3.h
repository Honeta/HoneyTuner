

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DR_WAV_IMPLEMENTATION
#define DR_MP3_IMPLEMENTATION
#include "id3encoder.h"
#include "id3decoder.h"

void error(char *s);


int16_t *wavRead_int16(char *filename, uint32_t *sampleRate, uint32_t *channels, uint64_t *totalSampleCount) {
    int16_t *buffer = drwav_open_file_and_read_pcm_frames_s16(filename, channels, sampleRate, totalSampleCount, NULL);
    if (buffer == NULL) {
        drmp3_config pConfig;
        buffer = drmp3_open_file_and_read_pcm_frames_s16(filename, &pConfig, totalSampleCount, NULL);
        if (buffer != NULL) {
            *channels = pConfig.channels;
            *sampleRate = pConfig.sampleRate;
            *totalSampleCount *= *channels;
        } else {
            printf("read file [%s] error.\n", filename);
        }
    } else {
        *totalSampleCount *= *channels;
    }
    return buffer;
}


/* Some global vars. */
char *infname, *outfname;
FILE *outfile;
int quiet = 0;
int stereo = STEREO;
int force_mono = 0;

/* Write out the MP3 file */
int write_mp3(long bytes, void *buffer, void *config) {
    return fwrite(buffer, sizeof(unsigned char), bytes, outfile) / sizeof(unsigned char);
}

/* Output error message and exit */
void error(char *s) {
    fprintf(stderr, "Error: %s\n", s);
    exit(1);
}

/* Use these default settings, can be overridden */
static void set_defaults(shine_config_t *config) {
    shine_set_config_mpeg_defaults(&config->mpeg);
}

/* Parse command line arguments */
static int parse_command(int argc, char **argv, shine_config_t *config) {
    int i = 0;

    if (argc < 3) return 0;

    while (argv[++i][0] == '-' && argv[i][1] != '\000' && argv[i][1] != ' ')
        switch (argv[i][1]) {
            case 'b':
                config->mpeg.bitr = atoi(argv[++i]);
                break;

            case 'm':
                force_mono = 1;
                break;

            case 'j':
                stereo = JOINT_STEREO;
                break;

            case 'd':
                stereo = DUAL_CHANNEL;
                break;

            case 'c':
                config->mpeg.copyright = 1;
                break;

            case 'q':
                quiet = 1;
                break;

            case 'v':
                quiet = 0;
                break;

            case 'h':
            default :
                return 0;
        }

    if (argc - i != 2) return 0;
    infname = argv[i++];
    outfname = argv[i];
    return 1;
}

bool transformer() {

    infname="audio\\output.wav";
    outfname="audio\\output.mp3";
    stereo = DUAL_CHANNEL;
    shine_config_t config;
    shine_t s;
    int written;
    unsigned char *data;
    /* Set the default MPEG encoding paramters - basically init the struct */
    set_defaults(&config);


    quiet = quiet || !strcmp(outfname, "-");

    uint32_t sampleRate = 0;
    uint64_t totalSampleCount = 0;
    uint32_t channels = 0;
    int16_t *data_in = wavRead_int16(infname, &sampleRate, &channels, &totalSampleCount);
    if (data_in == NULL)
        return 0;
    config.wave.samplerate = sampleRate;
    config.wave.channels = (channel) channels;

    if (force_mono)
        config.wave.channels = (channel) 1;

    /* See if samplerate and bitrate are valid */
    //if (shine_check_config(config.wave.samplerate, config.mpeg.bitr) < 0)
        //error("Unsupported samplerate/bitrate configuration.");

    /* open the output file */
    if (!strcmp(outfname, "-"))
        outfile = stdout;
    else
        outfile = fopen(outfname, "wb");
    if (!outfile) return 0;
    /* Set to stereo mode if wave data is stereo, mono otherwise. */
    if (config.wave.channels > 1)
        config.mpeg.mode = (modes)stereo;
    else
        config.mpeg.mode = MONO;

    /* Initiate encoder */
    s = shine_initialise(&config);

    // assert(s != NULL);
    /* Print some info about the file about to be created (optional) */

    int samples_per_pass = shine_samples_per_pass(s) * channels;

    /* All the magic happens here */
    size_t count = totalSampleCount / samples_per_pass;
    int16_t *buffer = data_in;
    for (int i = 0; i < count; i++) {
        data = shine_encode_buffer_interleaved(s, buffer, &written);
        if (write_mp3(written, data, &config) != written) return 0;
        buffer += samples_per_pass;
    }
    size_t last = totalSampleCount % samples_per_pass;
    if (last != 0) {
        int16_t *cache = (int16_t *) calloc(samples_per_pass, sizeof(int16_t));
        if (cache != NULL) {
            memcpy(cache, buffer, last * sizeof(int16_t));
            data = shine_encode_buffer_interleaved(s, cache, &written);
            free(cache);
            if (write_mp3(written, data, &config) != written) return 0;
        }
    }
    /* Flush and write remaining data. */
    data = shine_flush(s, &written);
    write_mp3(written, data, &config);
    /* Close encoder. */
    shine_close(s);
    /* Close the MP3 file */
    fclose(outfile);
    free(data_in);
    return 1;
}
