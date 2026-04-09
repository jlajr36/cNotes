#include "raylib.h"
#include <iostream>
#include <random>

using namespace std;

// Random number generator
mt19937 gen(random_device{}());
float randomFloat(float min, float max) {
    uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Line Angle");
    SetTargetFPS(60);

    const int cx = screenWidth / 2;
    const int cy = screenHeight / 2;
    const int circleRadius = 100;

    float theta = 0.0f;

    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        if (IsKeyPressed(KEY_SPACE)) {
            theta = randomFloat(0.0f, 2.0f * PI); // Update theta
        }

        float x = cx + cos(theta) * circleRadius;
        float y = cy + sin(theta) * circleRadius;

        DrawLine(cx, cy, x, y, RED); // Draw from center to endpoint

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
