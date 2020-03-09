#pragma once

class GameObject;
class Mesh;
class PlayerController;
struct SpriteInfo;
class Ball;
class Boss;

class HealthBar : public GameObject
{
    Boss* m_pBoss;
    Mesh* m_pCurrentHealthBarMesh;
    float m_HealthPercentage;
public:
    HealthBar(GameCore* pGame, Mesh* pMesh, SpriteSheet* pSpriteSheet, Boss* pBoss, Mesh* pCurrentHealthBarMesh);
    virtual ~HealthBar();

    virtual void Update(float deltatime);
    virtual void Draw(vec2 camPos, vec2 projScale);

    Boss* GetRelativeBoss();

};



