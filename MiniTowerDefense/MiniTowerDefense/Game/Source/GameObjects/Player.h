#ifndef __Player_H__
#define __Player_H__

struct SpriteInfo;
class GameObject;
class Mesh;
class PlayerController;
class Tilemap;

enum PlayerState
{
    PS_WALK_DOWN,
    PS_WALK_UP,
    PS_WALK_LEFT,
    PS_WALK_RIGHT
};

class Player : public GameObject
{
    const float PLAYER_START_X_POSITION_PCT = 0.5f;
    const float PLAYER_START_Y_POSITION_PCT = 0.3f;
    const float PLAYER_SPEED_MOVE = 5.0f;
    const float ANIMATION_TIME_PER_FRAME = 0.2f;
    PlayerState m_CurrentPS;
    Tilemap* m_TilemapRef;
    bool m_LockX_Left, m_LockX_Right, m_LockY_Up, m_LockY_Down;
protected:
    PlayerController* m_pPlayerController;

    float m_Speed;
    float m_TimerForAnimationChange = 0.0f;

    //SpriteInfo* m_Sprite;

public:
    Player(GameCore* pGame, Mesh* pMesh, SpriteSheet* pSpriteSheet);
    virtual ~Player();

    virtual void Update(float deltatime);
    virtual void Draw(vec2 camPos, vec2 projScale);

    void SetPlayerController(PlayerController* controller) { m_pPlayerController = controller; }
    void SetSpeed(float speed) { m_Speed = speed; }
    
    vec2 GetPlayerPosition(){ return m_Position; }
    void SetCurrentPlayerState(PlayerState ps) { m_CurrentPS = ps; }
    //void ExtractInfoFromSprite(SpriteInfo* Sprite);
    void ChangeSprite(PlayerState ps);
    void HandleMoving(float deltatime, PlayerState ps);

    virtual bool IsColliding() override;
    virtual void OnCollision(GameObject* pOtherGameObject) override;

    void setTilemap(Tilemap* tilemap) { m_TilemapRef = tilemap; }

    void ResetLockBools();
};

#endif //__Player_H__
