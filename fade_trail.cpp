#include "raylib.h"
#include <iostream>
#include <random>
#include <vector>
#include <cmath>

using namespace std;

// Random number generator
mt19937 gen(random_device{}());
float randomFloat(float min, float max) {
    uniform_real_distribution<float> dist(min, max);
    return dist(gen);
}

// Structure to store orbital point data
struct OrbitalPoint {
    float rho;    // distance from center
    float theta;  // angle
    float speed;  // angular speed
};

int main() {
    // Window setup
    const int screenWidth = 800;
    const int screenHeight = 450;
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Orbiting Points with Trails");
    SetTargetFPS(60);

    // Center and radius of orbit
    const int cx = screenWidth / 2;
    const int cy = screenHeight / 2;
    const int circleRadius = 100;

    vector<OrbitalPoint> points;

    while (!WindowShouldClose()) {
        // Spawn a new point on SPACE press
        if (IsKeyPressed(KEY_SPACE)) {
            float theta = randomFloat(0.0f, 2.0f * PI);
            float rho = sqrt(randomFloat(0.0f, 1.0f)) * circleRadius;

            // ✅ Fixed speed (no near-zero values)
            float speed = randomFloat(0.01f, 0.05f);
            if (randomFloat(0.0f, 1.0f) < 0.5f) speed *= -1.0f;

            points.push_back({rho, theta, speed});
        }

        BeginDrawing();

        // ✅ Fading trail (instead of ClearBackground)
        DrawRectangle(0, 0, screenWidth, screenHeight, Fade(BLACK, 0.1f));

        // Draw center
        DrawCircle(cx, cy, 2, WHITE);

        // Optional orbit boundary
        DrawCircleLines(cx, cy, circleRadius, DARKGRAY);

        // Update & draw points
        float dt = GetFrameTime(); // frame-independent motion

        for (auto &point : points) {
            point.theta += point.speed * dt * 60.0f;

            float x = cx + point.rho * cos(point.theta);
            float y = cy + point.rho * sin(point.theta);

            // Optional color for nicer trails
            Color color = ColorFromHSV(point.theta * RAD2DEG, 1.0f, 1.0f);

            DrawCircleV({x, y}, 2, color);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
