#include "raylib.h"
#include <cmath>

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Angle Line");
    SetTargetFPS(60);

    int cx = screenWidth / 2;
    int cy = screenHeight / 2;

    float degrees = 0.0f;
    float radius = 100.0f;

    float x = 0.0f;
    float y = 0.0f;

    while (!WindowShouldClose())
    {
        degrees += 60.0f * GetFrameTime();
        if (degrees >= 360.0f) degrees -= 360.0f;

        x = cx + cosf(DEG2RAD * degrees) * radius;
        y = cy + sinf(DEG2RAD * degrees) * radius;

        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircle(cx, cy, 2, RED);
            DrawCircleLines(cx, cy, radius, DARKGRAY);
            DrawLine(cx, cy, x, y, RED);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
