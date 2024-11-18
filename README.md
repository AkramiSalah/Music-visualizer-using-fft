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
