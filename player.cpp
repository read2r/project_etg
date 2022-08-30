#include "player.h"
#include "raymath.h"

Player::Player(int windowWidth, int windowHeight) :
    windowWidth(windowWidth),
    windowHeight(windowHeight)
{
    // init textures
    textureIdle = LoadTexture("./assets/topdown_shooter_assets/sPlayerIdle_strip4.png");
    textureRun = LoadTexture("./assets/topdown_shooter_assets/sPlayerRun_strip7.png");
    texture = textureIdle;

    // init vars about animation
    frameMaxIdle = 4;
    frameMaxRun = 7;
    frameMax = frameMaxIdle;

    // init texture size
    textureWidthIdle = textureIdle.width / frameMaxIdle;
    textureWidthRun = textureRun.width / frameMaxRun;
    textureWidth = textureWidthIdle;
    textureHeight = textureIdle.height;

    // init position
    position = {
        (windowWidth - textureWidth) / 2.0f,
        (windowHeight - textureHeight) / 2.0f
    };
}

Player::~Player()
{
    // free textures
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

        // X bound check
        if (position.x < 0.0f)
        {
            position.x = 0.0f;
        }
        else if (position.x > windowWidth - textureWidth * scale)
        {
            position.x = windowWidth - textureWidth * scale;
        }

        // Y bound check
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

        // set run texture
        texture = textureRun;
        frameMax = frameMaxRun;
        textureWidth = textureWidthRun;
    }
    else
    {
        // set idle texture
        texture = textureIdle;
        frameMax = frameMaxIdle;
        textureWidth = textureWidthIdle;
    }

    // update player animation frame
    frameRuningTime += deltaTime;
    if (frameRuningTime >= frameUpdateTime)
    {
        frame = (frame + 1) % frameMax;
        frameRuningTime = 0.0f;
    }

    // draw player
    // rec in texture, it represent position on texture.
    Rectangle sourceRec {
        static_cast<float>(textureWidth) * frame,
        0.0f,
        static_cast<float>(textureWidth) * forward,
        static_cast<float>(textureHeight),
    };

    // rec in screen, it represent position on screen.
    Rectangle destRec {
        position.x,
        position.y,
        textureWidth * scale,
        textureHeight * scale
    };

    // draw texture
    DrawTexturePro(texture, sourceRec, destRec, Vector2{}, 0.0f, WHITE);

    // for debug
    DrawRectangleLines(
        position.x,
        position.y,
        textureWidth * scale,
        textureHeight * scale,
        RED
    );
}