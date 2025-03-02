#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <sndfile.h> // For audio file output

#define SAMPLE_RATE 44100 // Sample rate in Hz
#define DURATION 5        // Duration of the signal in seconds
#define FREQ_0 1000      // Frequency for binary '0'
#define FREQ_1 2000      // Frequency for binary '1'
#define AMPLITUDE 0.5    // Amplitude of the signal

// Function to generate FSK signal samples
void generate_fsk_signal(const char *data, int length, int16_t *samples) {
    for (int i = 0; i < SAMPLE_RATE * DURATION; i++) {
        double t = (double)i / SAMPLE_RATE; // Time in seconds
        double sample = 0.0;

        // Determine frequency based on input data
        if (i < length * SAMPLE_RATE) {
            if (data[i / SAMPLE_RATE] == '0') {
                sample = AMPLITUDE * sin(2 * M_PI * FREQ_0 * t);
            } else if (data[i / SAMPLE_RATE] == '1') {
                sample = AMPLITUDE * sin(2 * M_PI * FREQ_1 * t);
            }
        }

        // Convert to 16-bit PCM
        samples[i] = (int16_t)(sample * 32767);
    }
}

// Function to write samples to a WAV file
void write_to_wav(const char *filename, int16_t *samples, int num_samples) {
    SNDFILE *outfile;
    SF_INFO sfinfo;
    sfinfo.frames = num_samples;
    sfinfo.samplerate = SAMPLE_RATE;
    sfinfo.channels = 1; // Mono
    sfinfo.format = SF_FORMAT_WAV | SF_FORMAT_PCM_16;

    // Open the output file
    outfile = sf_open(filename, SFM_WRITE, &sfinfo);
    if (!outfile) {
        printf("Error opening output file.\n");
        return;
    }

    // Write the samples to the output file
    sf_write_short(outfile, samples, num_samples);

    // Close the output file
    sf_close(outfile);
}

int main() {
    const char *data = "0101010101"; // Example binary data
    int length = strlen(data);
    int num_samples = SAMPLE_RATE * DURATION;
    int16_t *samples = (int16_t *)malloc(num_samples * sizeof(int16_t));

    if (samples == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Generate the FSK signal
    generate_fsk_signal(data, length, samples);

    // Write the generated samples to a WAV file
    write_to_wav("fsk_signal.wav", samples, num_samples);

    // Free allocated memory
    free(samples);

    printf("FSK signal generated and saved to fsk_signal.wav\n");
    return 0;
}
