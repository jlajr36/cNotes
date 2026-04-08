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
    InitWindow(screenWidth, screenHeight, "Orbiting Points");
    SetTargetFPS(60);

    // Center and radius of orbit
    const int cx = screenWidth / 2;
    const int cy = screenHeight / 2;
    const int circleRadius = 100;

    vector<OrbitalPoint> points;

    while (!WindowShouldClose()) {
        // Input: spawn a new point on SPACE press
        if (IsKeyPressed(KEY_SPACE)) {
            float theta = randomFloat(0.0f, 2.0f * PI);
            float rho = sqrt(randomFloat(0.0f, 1.0f)) * circleRadius;
            float speed = randomFloat(0.0f, 0.05f);
            points.push_back({rho, theta, speed});
        }

        // Drawing
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw center point
        DrawCircle(cx, cy, 2, WHITE);

        // Draw all orbital points
        for (auto &point : points) {
            point.theta += point.speed;
            float x = cx + point.rho * cos(point.theta);
            float y = cy + point.rho * sin(point.theta);
            DrawCircleV({x, y}, 2, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}