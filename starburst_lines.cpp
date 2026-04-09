#include "raylib.h"
#include <iostream>
#include <random>
#include <vector>

using namespace std;

// Random number generator
mt19937 gen(random_device{}());
float randomFloat(float min, float max) {
    uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

// Random color generator
Color randomColor() {
    return Color{ (unsigned char)randomFloat(0, 255),
                  (unsigned char)randomFloat(0, 255),
                  (unsigned char)randomFloat(0, 255),
                  255 };
}

struct Line {
    float theta;
    Color color;
};

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Starburst Lines");
    SetTargetFPS(60);

    const int cx = screenWidth / 2;
    const int cy = screenHeight / 2;
    const int circleRadius = 150;

    vector<Line> lines; // store all lines

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

        // Add a new line on SPACE
        if (IsKeyPressed(KEY_SPACE)) {
            Line newLine;
            newLine.theta = randomFloat(0.0f, 2.0f * PI);
            newLine.color = randomColor();
            lines.push_back(newLine);
        }

        // Draw all lines
        for (const auto &line : lines) {
            float x = cx + cos(line.theta) * circleRadius;
            float y = cy + sin(line.theta) * circleRadius;
            DrawLine(cx, cy, x, y, line.color);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
