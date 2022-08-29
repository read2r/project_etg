#include "player.h"
#include "raymath.h"

Player::Player(int windowWidth, int windowHeight) :
    windowWidth(windowWidth),
    windowHeight(windowHeight)
{
    textureIdle = LoadTexture("./assets/topdown_shooter_assets/sPlayerIdle_strip4.png");
    textureRun = LoadTexture("./assets/topdown_shooter_assets/sPlayerRun_strip7.png");
    texture = textureIdle;

    frameMaxIdle = 4;
    frameMaxRun = 7;
    frameMax = frameMaxIdle;

    textureWidth = textureIdle.width / frameMax;
    textureHeight = textureIdle.height;
}

Player::~Player()
{
    UnloadTexture(textureIdle);
    UnloadTexture(textureRun);
}

void Player::tick(float deltaTime)
{
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
        velocity = Vector2Scale(velocity, moveSpeed);

        // move coordinate
        position = Vector2Add(position, velocity);

        // bound check
        if (position.x < 0.0f)
        {
            position.x = 0.0f;
        }
        else if (position.x > windowWidth - textureWidth * scale)
        {
            position.x = windowWidth - textureWidth * scale;
        }

        if (position.y < 0.0f)
        {
            position.y = 0.0f;
        }
        else if (position.y > windowHeight - textureHeight * scale)
        {
            position.y = windowHeight - textureHeight * scale;
        }

        // set playerRightLeft
        if (velocity.x < -0.001f) { forward = -1.0f; }
        else if (velocity.x > 0.001f) { forward = 1.0f; }

        // select idle texture
        texture = textureRun;
        frameMax = frameMaxRun;
        textureWidth = textureWidthRun;
    }
    else
    {
        // select run texture
        texture = textureIdle;
        frameMax = frameMaxIdle;
        textureWidth = textureWidthRun;
    }

    // update player animation frame
    frameRuningTime += deltaTime;
    if (frameRuningTime >= frameUpdateTime)
    {
        frame = (frame + 1) % frameMax;
        frameRuningTime = 0.0f;
    }

    // draw player
    Rectangle sourceRec {
        static_cast<float>(textureWidth) * frame,
        0.0f,
        static_cast<float>(textureWidth) * forward,
        static_cast<float>(textureHeight),
    };

    Rectangle destRec {
        position.x,
        position.y,
        textureWidth * scale,
        textureHeight * scale
    };

    DrawTexturePro(texture, sourceRec, destRec, Vector2{}, 0.0f, WHITE);
    DrawRectangleLines(
        position.x,
        position.y,
        textureWidth * scale,
        textureHeight * scale,
        RED
    );
}