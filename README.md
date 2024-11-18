## Description

This project implements a recursive Fast Fourier Transform (FFT) algorithm, which processes audio data to extract frequency components and visualize them in real-time. The program captures audio from an input file, applies the FFT to analyze the signal's frequency domain, and then displays a graphical representation of the audio's frequency components.

You can use this program to load audio files (only .ogg right now), apply the FFT algorithm to decompose the signal into its frequency components, and see a visualization of how the frequency content evolves over time. This is useful for tasks like audio analysis, music visualization, and exploring signal processing techniques.

The FFT algorithm used is based on the recursive divide-and-conquer approach described in the Introduction to Algorithms (CLRS) book, which helps in understanding the underlying mechanics of the FFT algorithm. This implementation focuses on both accuracy and educational value, allowing users to gain insight into how FFT works in practice.

![Alt Text](https://i.makeagif.com/media/11-18-2024/knE5RM.gif)

## How to Use This

Open the main.code-workspace file by double-clicking on it. This will open the project in Visual Studio Code.
In the Explorer panel of VS Code, navigate to the src folder and double-click on the main.cpp file to open it.
Use the terminal to navigate to the project directory, then run make to build the project by pressing F5.

## Dependencies

Raylib: Used for audio processing and visualization. You can download Raylib from here. Make sure to link Raylib correctly in the Makefile.
MinGW: If you're on Windows, MinGW is required for compiling. Ensure MinGW is installed and properly configured.
CMake: Used for project configuration and building. You can use CMake to generate the Makefile.
Make: A tool for building projects using a Makefile. If you're on Windows, ensure you have a working version of make installed (e.g., via MSYS2 or MinGW).

## Inspiration

I was inspired by tsoding's video, where I noticed that his understanding of FFT wasn't complete. So, I turned to the famous Introduction to Algorithms (CLRS) book and after researching, reading, and watching various resources, I came up with a recursive FFT algorithm as described in CLRS.

## License

This project has no specific license. You can use it however you like, though it would be appreciated if you gave me credit :)
