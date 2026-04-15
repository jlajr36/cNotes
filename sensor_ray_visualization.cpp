#include "raylib.h"
#include <vector>
#include <cmath>

struct SensorRay {
    Vector2 start;
    Vector2 end;
    bool hitObstacle;
};

int main() {
    const int SCREEN_W = 1200;
    const int SCREEN_H = 600;

    InitWindow(SCREEN_W, SCREEN_H, "Sensor Ray Visualization");
    SetTargetFPS(60);

    // 1. Load Resources (Load Image first, then Texture)
    Image mapImg = LoadImage("assets/background.png"); 
    if (mapImg.data == NULL) {
        TraceLog(LOG_ERROR, "Failed to load background image!");
        CloseWindow();
        return 1;
    }
    
    Texture2D mapTex = LoadTextureFromImage(mapImg);
    Texture2D botTex = LoadTexture("assets/bot.png");
    Color* pixels = LoadImageColors(mapImg);

    // Initial bot state
    Vector2 botPos = { 400, 300 };
    float botHeading = 0.0f; 

    while (!WindowShouldClose()) {
        // --- Update Logic ---
        if (IsKeyDown(KEY_LEFT))  botHeading += 0.05f;
        if (IsKeyDown(KEY_RIGHT)) botHeading -= 0.05f;
        
        float speed = 2.0f;
        if (IsKeyDown(KEY_UP)) {
            botPos.x += cosf(botHeading) * speed;
            botPos.y -= sinf(botHeading) * speed;
        }
        if (IsKeyDown(KEY_DOWN)) {
            botPos.x -= cosf(botHeading) * speed;
            botPos.y += sinf(botHeading) * speed;
        }

        // --- Sensor Array Logic ---
        std::vector<SensorRay> rays;
        float fov = 40.0f * DEG2RAD; 
        float range = 200.0f;
        int rayCount = 15;

        for (int r = 0; r < rayCount; r++) {
            float t = (rayCount == 1) ? 0.5f : (float)r / (rayCount - 1);
            // Calculate actual angle for this specific ray
            float angle = (botHeading - fov) + (t * fov * 2.0f);
            
            // Direction vector for the ray
            Vector2 dir = { cosf(angle), -sinf(angle) };
            
            SensorRay ray = { botPos, { botPos.x + dir.x * range, botPos.y + dir.y * range }, false };

            // Precise Ray Casting: Step by 1.0 pixel units
            for (float dist = 0; dist < range; dist += 1.0f) {
                int checkX = (int)(botPos.x + dir.x * dist);
                int checkY = (int)(botPos.y + dir.y * dist);

                // Map Boundary Check
                if (checkX >= 0 && checkX < mapImg.width && checkY >= 0 && checkY < mapImg.height) {
                    Color c = pixels[checkY * mapImg.width + checkX];
                    
                    // Hit detection: Pure black (0,0,0) and not transparent
                    if (c.r == 0 && c.g == 0 && c.b == 0 && c.a > 0) { 
                        ray.end = {(float)checkX, (float)checkY};
                        ray.hitObstacle = true;
                        break;
                    }
                } else {
                    // Ray went out of bounds
                    ray.end = {(float)checkX, (float)checkY};
                    break;
                }
            }
            rays.push_back(ray);
        }

        // --- Rendering ---
        BeginDrawing();
        ClearBackground(WHITE);
        
        DrawTexture(mapTex, 0, 0, WHITE);

        for (const auto& ray : rays) {
            Color rayColor = ray.hitObstacle ? RED : (Color){ 0, 0, 255, 100 };
            DrawLineV(ray.start, ray.end, rayColor);
            if (ray.hitObstacle) DrawCircleV(ray.end, 3, MAROON);
        }

        DrawTexturePro(botTex, 
            {0, 0, (float)botTex.width, (float)botTex.height},
            {botPos.x, botPos.y, (float)botTex.width, (float)botTex.height},
            {botTex.width / 2.0f, botTex.height / 2.0f},
            -botHeading * RAD2DEG, WHITE);

        EndDrawing();
    }

    // --- Cleanup ---
    UnloadImageColors(pixels);
    UnloadImage(mapImg);
    UnloadTexture(mapTex);
    UnloadTexture(botTex);
    CloseWindow();

    return 0;
}
