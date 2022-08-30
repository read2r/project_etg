#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "raylib.h"

class Player
{
public:
    Player(int windowWidth, int windowHeight);
    ~Player();

    // update player on every frame
    void tick(float deltaTime);
private:
    // window infomation
    int windowWidth;
    int windowHeight;

    // texture
    Texture2D textureIdle;
    Texture2D textureRun;
    Texture2D texture;

    // texture rec size
    int textureWidthIdle;
    int textureWidthRun;
    int textureWidth;
    int textureHeight;

    // animation
    int frameMaxIdle;
    int frameMaxRun;
    int frameMax;
    int frame {0};
    float frameRuningTime {0.0f};
    float frameUpdateTime {1.0f / 12.0f};

    // transform
    // position on screen
    Vector2 position {};
    // scale
    float scale {1.0f};
    // left forward = -1.0f
    // right forward = 1.0f 
    float forward {1.0f};
    // movement
    float moveSpeed {3.0f};

    Vector2 GetCenter();
};

#endif //__PLAYER_H__