#ifndef __Ball_H__
#define __Ball_H__

class Tower;

class Ball : public GameObject
{
    /* const float Ball_START_X_POSITION_PCT = 0.5f;
     const float Ball_START_Y_POSITION_PCT = 0.5f;*/
    const float Ball_SPEED_WHEN_HIT = 30.0f; // Units per second

    bool m_DrawBall;

    float m_DetectRangeForShoot;

    Tower* m_pTower;

protected:
    float m_Speed;

public:
    Ball(GameCore* pGame, Mesh* pMesh, SpriteSheet* pSpriteSheet, Tower* pTower, int kind);
    virtual ~Ball();

    virtual void Update(float deltatime);
    virtual void Draw(vec2 camPos, vec2 projScale);

    virtual bool IsInRangeOfShooting(GameObject* pOtherGameObject);

    virtual void OnCollision(GameObject* pOtherGameObject);

    void SetBallDrawBool(bool drawBall) { m_DrawBall = drawBall; }

    bool GetBallDrawBool() { return m_DrawBall; }

    virtual bool IsColliding(GameObject* pOtherGameObject);

    void LaunchProjectile(GameObject* pOtherGameObject);

    void Destroy();

    void Respawn();

    Tower* GetRelativeTower() { return m_pTower; }
};

#endif //__Ball_H__
