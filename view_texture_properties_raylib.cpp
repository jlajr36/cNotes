#include "raylib.h"
#include <iostream>

int main() {
    // Initialize window and OpenGL context
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [textures] - Property Access");

    // Load texture into GPU memory (VRAM)
    // Ensure the file path is correct relative to the working directory
    Texture2D texture = LoadTexture("assets/bot.png");

    // Validate texture loading
    if (texture.id == 0) {
        std::cerr << "Log: Failed to load texture." << std::endl;
    } else {
        // Output properties to console
        std::cout << "--- Texture Data ---" << std::endl;
        std::cout << "OpenGL ID: " << texture.id      << std::endl;
        std::cout << "Width:     " << texture.width   << "px" << std::endl;
        std::cout << "Height:    " << texture.height  << "px" << std::endl;
        std::cout << "Mipmaps:   " << texture.mipmaps << std::endl;
        std::cout << "Format:    " << texture.format  << std::endl;
        std::cout << "--------------------" << std::endl;
    }

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
            ClearBackground(RAYWHITE);

            if (texture.id > 0) {
                DrawTexture(texture, 10, 10, WHITE);
            }

            DrawText("Check terminal for texture metadata", 250, 210, 20, GRAY);
        EndDrawing();
    }

    // Free VRAM before closing
    UnloadTexture(texture);
    CloseWindow();

    return 0;
}
