#pragma once

class GameObject;
class Mesh;
class PlayerController;
struct SpriteInfo;
class Ball;

class Tower : public GameObject
{
    PlayerController* m_pPlayerController;

    Ball* m_pBall;
public:
    Tower(GameCore* pGame, Mesh* pMesh, SpriteSheet* pSpriteSheet);
    virtual ~Tower();

    virtual void Update(float deltatime);
    virtual void Draw(vec2 camPos, vec2 projScale);

    void SetPlayerController(PlayerController* controller) { m_pPlayerController = controller; }

    void Destroy();

};



