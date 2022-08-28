#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <string>

int main()
{
    // window
    const int windowWidth = 800;
    const int windowHeight = 600;
    const char* windowTitle = "Project_ETG";
    InitWindow(windowWidth, windowHeight, windowTitle);

    // player
    Texture2D playerTexIdle = LoadTexture("./assets/topdown_shooter_assets/sPlayerIdle_strip4.png");
    Texture2D playerTexRun = LoadTexture("./assets/topdown_shooter_assets/sPlayerRun_strip7.png");
    Texture2D playerTex = playerTexIdle;

    const int playerFrameMaxRun = 7;
    const int playerFrameMaxIdle = 4;

    const int playerTexWidthRun = playerTexRun.width / playerFrameMaxRun;
    const int playerTexWidthIdle = playerTexIdle.width / playerFrameMaxIdle;

    float playerMoveSpeed = 3.0f;
    float playerTexScale = 1.5;

    int playerFrameNum = 0;
    int playerFrameMax = playerFrameMaxIdle;

    float playerFrameRunningTime = 0.0f;
    float playerFrameUpateTime = 1.0f / 12.0f;
    
    int playerTexWidth = playerTexWidthRun;
    int playerTexHeight = playerTex.height;

    Vector2 playerPosition {
        windowWidth / 2 - playerTexWidth / 2,
        windowHeight / 2 - playerTexHeight / 2,
    };

    float playerRightLeft = 1.0f;

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(WHITE);

        // process input
        Vector2 velocity = {};
        if (IsKeyDown(KEY_W)) { velocity.y -= deltaTime; }
        if (IsKeyDown(KEY_S)) { velocity.y += deltaTime; }
        if (IsKeyDown(KEY_A)) { velocity.x -= deltaTime; }
        if (IsKeyDown(KEY_D)) { velocity.x += deltaTime; }

        // update position
        if (Vector2Length(velocity) > 0.0f)
        {
            // normalize velocity and aplly move speed
            velocity = Vector2Normalize(velocity);
            velocity = Vector2Scale(velocity, playerMoveSpeed);

            // move coordinate
            playerPosition = Vector2Add(playerPosition, velocity);

            // bound check
            if (playerPosition.x < 0.0f)
            {
                playerPosition.x = 0.0f;
            }
            else if (playerPosition.x > windowWidth - playerTexWidth * playerTexScale)
            {
                playerPosition.x = windowWidth - playerTexWidth * playerTexScale;
            }

            if (playerPosition.y < 0.0f)
            {
                playerPosition.y = 0.0f;
            }
            else if (playerPosition.y > windowHeight - playerTexHeight * playerTexScale)
            {
                playerPosition.y = windowHeight - playerTexHeight * playerTexScale;
            }

            // set playerRightLeft
            if (velocity.x < -0.001f) { playerRightLeft = -1.0f; }
            else if (velocity.x > 0.001f) { playerRightLeft = 1.0f; }

            // select idle texture
            playerTex = playerTexRun;
            playerFrameMax = playerFrameMaxRun;
            playerTexWidth = playerTexWidthRun;
        }
        else
        {
            // select run texture
            playerTex = playerTexIdle;
            playerFrameMax = playerFrameMaxIdle;
            playerTexWidth = playerTexWidthIdle;
        }

        // update player animation frame
        playerFrameRunningTime += deltaTime;
        if (playerFrameRunningTime >= playerFrameUpateTime)
        {
            playerFrameNum = (playerFrameNum + 1) % playerFrameMax;
            playerFrameRunningTime = 0.0f;
        }

        // draw player
        Rectangle playerTexSourceRec {
            static_cast<float>(playerTexWidth) * playerFrameNum,
            0.0f,
            static_cast<float>(playerTexWidth) * playerRightLeft,
            static_cast<float>(playerTexHeight),
        };

        Rectangle playerTexDestRec {
            playerPosition.x,
            playerPosition.y,
            playerTexWidth * playerTexScale,
            playerTexHeight * playerTexScale
        };

        DrawTexturePro(playerTex, playerTexSourceRec, playerTexDestRec, Vector2{}, 0.0f, WHITE);
        DrawRectangleLines(
            playerPosition.x,
            playerPosition.y,
            playerTexWidth * playerTexScale,
            playerTexHeight * playerTexScale,
            RED
        );

        EndDrawing();
    }

    UnloadTexture(playerTexIdle);
    UnloadTexture(playerTexRun);
    CloseWindow();
    return 0;
}