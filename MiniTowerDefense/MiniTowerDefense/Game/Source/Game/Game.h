#ifndef __Game_H__
#define __Game_H__

#include <vector>

class Ball;
class Mesh;
class GameObject;
class Player;
class PlayerController;
class Boss;
class SpriteSheet;
class Cursor;
class Tower;
class Tilemap;
class Score;
class Particle_Emitter;
class HealthBar;
//class TestingTexture;

class Game : public GameCore
{
private:
    bool m_DrawTowerOrNot;
    //bool m_DrawProjectileOrNot;

    float m_Timer_RespawnProjectile;

    float m_FireRate;

    bool m_RespawnTimerFlag;

    bool m_WinFlag;

    int m_Score;

    int m_TotalHealthForEnemy;
public:
    static const int Game_WORLD_SIZE_X = 50;
    static const int Game_WORLD_SIZE_Y = 50;
    static const int Game_Screen_Width = 600;
    static const int Game_Screen_Height = 600;
    const int ENEMY_AMOUNT = 10;
    const int NumOfParticleEmitter = 10;

protected:
    ShaderProgram* m_pShader;
    ShaderProgram* m_pColorShader;
    Mesh* m_pMeshTriangle;
    Mesh* m_pMeshDiamond;
    Mesh* m_pMeshRect;
    Mesh* m_pMeshTileRect;
    Mesh* m_pMeshHealthBar;
    Mesh* m_pMeshCurrentHealthBar;
    // Mesh* m_pMeshTestingTexture;
    SpriteSheet* m_pSpriteSheet;
    Tilemap* m_pTilemap;

    Player* m_pPlayer;
    Ball* m_pBall;
    Boss* m_pBoss;
    Cursor* m_pCursor;
    Tower* m_pTower;
    Score* m_pScore;
    HealthBar* m_pHealthBar;
    // TestingTexture* m_pTestingTexture;

    PlayerController* m_pPlayerController;

    std::vector<Tower*> m_pTowersVector;
    //std::vector<Score*> m_pScoreVector;
    std::vector<Ball*> m_pBallVector;
    std::vector<Boss*> m_pBossVector;
    std::vector<HealthBar*> m_HealthBarVector;
    std::vector<Particle_Emitter*> m_ParticleEmitVector;

    GLuint m_TextureHandle;

    Particle_Emitter* m_pParticle_Emitter;

public:
    Game(Framework* pFramework);
    virtual ~Game();

    virtual void OnSurfaceChanged(unsigned int width, unsigned int height);
    virtual void LoadContent();

    virtual void OnEvent(Event* pEvent);
    virtual void Update(float deltatime);
    virtual void Draw();

    void CheckForCollisions(float DeltaTime);
};

#endif //__Game_H__
