#include "raylib.h"
#include <math.h>
#include <complex>
#include <vector>
#include <algorithm>
#include <limits>

#define FFT_SIZE 1024
#define SAMPLE_RATE 48000

typedef struct
{
    float left;
    float right;
} Frame;

std::vector<Frame> global_frames(FFT_SIZE);
size_t global_frames_count = 0;

std::vector<std::complex<float>> FFT(const std::vector<std::complex<float>> &frames)
{
    size_t N = frames.size();
    if (N == 1)
        return frames;

    size_t N2 = N / 2;
    std::vector<std::complex<float>> even(N2), odd(N2);
    for (size_t k = 0; k < N2; k++)
    {
        even[k] = frames[k * 2];
        odd[k] = frames[k * 2 + 1];
    }

    auto Ye = FFT(even);
    auto Yo = FFT(odd);

    float angle = -2.0f * PI / static_cast<float>(N);

    std::complex<float> wk(1.0f, 0.0f);
    std::complex<float> wn(cos(angle), sin(angle));

    std::vector<std::complex<float>> Y(N);
    for (size_t j = 0; j < N2; j++)
    {
        std::complex<float> odd_term = wk * Yo[j];
        Y[j] = Ye[j] + odd_term;
        Y[j + N2] = Ye[j] - odd_term;
        wk *= wn;
    }

    return Y;
}

void callback(void *bufferData, unsigned int frames)
{
    size_t capacity = global_frames.size();
    size_t available = capacity - global_frames_count;

    if (frames <= available)
    {
        memcpy(global_frames.data() + global_frames_count, bufferData, sizeof(Frame) * frames);
        global_frames_count += frames;
    }
    else if (frames <= capacity)
    {
        std::rotate(global_frames.begin(), global_frames.begin() + frames, global_frames.end());
        memcpy(global_frames.data() + (capacity - frames), bufferData, sizeof(Frame) * frames);
        global_frames_count = capacity;
    }
    else
    {
        memcpy(global_frames.data(), bufferData, sizeof(Frame) * capacity);
        global_frames_count = capacity;
    }
}

inline float Clamp(float value, float min, float max)
{
    if (std::isnan(value))
        return min;
    return (value < min)   ? min
           : (value > max) ? max
                           : value;
}

Color GetFrequencyColor(size_t index, size_t total_bins)
{
    float hue = (float)index / (total_bins / 2) * 360.0f;
    return ColorFromHSV(hue, 0.8f, 0.8f);
}

inline float CalculateBarHeight(float magnitude, float max_magnitude, float height)
{
    float normalized = magnitude / max_magnitude;
    normalized *= height;
    return Clamp(normalized, 1.0f, height);
}

int main(void)
{
    const char *audioFilePath = "./res/arub.ogg"; // Path to the target audio file

    InitWindow(1280, 800, "Music Visualizer with FFT");
    SetTargetFPS(165);

    InitAudioDevice();
    Music music = LoadMusicStream(audioFilePath);
    if (!music.stream.sampleSize)
    {
        printf("Failed to load audio stream\n");
        return -1;
    }

    PlayMusicStream(music);
    SetMusicVolume(music, 1.0f);
    AttachAudioStreamProcessor(music.stream, callback);

    float max_magnitude = 1.0f; // Start with 1.0f, will dynamically adjust

    while (!WindowShouldClose())
    {
        UpdateMusicStream(music);
        float height = GetScreenHeight();
        BeginDrawing();
        ClearBackground(DARKGRAY);

        if (global_frames_count == FFT_SIZE)
        {
            std::vector<std::complex<float>> input(FFT_SIZE);
            for (size_t i = 0; i < FFT_SIZE; i++)
            {
                input[i] = std::complex<float>((global_frames[i].left + global_frames[i].right) / 2.0f, 0.0f);
            }

            auto fft_result = FFT(input);

            size_t half_size = FFT_SIZE / 2;
            // float bar_width = static_cast<float>(GetScreenWidth()) / half_size;
            float bar_width = static_cast<float>(GetScreenWidth()) / half_size; // Add a gap

            float local_max_magnitude = 0.0f;
            for (size_t i = 0; i < half_size; i++)
            {
                float magnitude = std::abs(fft_result[i]);
                local_max_magnitude = std::max(local_max_magnitude, magnitude);
            }

            // changing the global maximum magnitude to ensure scaling is consistent
            max_magnitude = std::max(max_magnitude, local_max_magnitude);

            for (size_t i = 0; i < half_size; i++)
            {
                float magnitude = std::abs(fft_result[i]);
                float bar_height = CalculateBarHeight(magnitude, max_magnitude, height);
                Color bar_color = GetFrequencyColor(i, FFT_SIZE);

                DrawRectangle(i * bar_width, GetScreenHeight() - bar_height, bar_width, bar_height, bar_color);
            }
        }

        EndDrawing();
    }

    UnloadMusicStream(music);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
