#pragma once

class PlayerController;
class Player;
struct SpriteInfo;

class Cursor :public GameObject
{
    const float HALF_SCREEN_WIDTH = Game::Game_Screen_Width / 2.0f;
    const float HALF_SCREEN_HEIGHT = Game::Game_Screen_Height / 2.0f;
protected:
    PlayerController* m_pPlayerController;
    Player* m_pPlayer;
    vec2 m_ProjectionScale;

public:
    Cursor(GameCore*pGame, Mesh* pMesh, SpriteSheet* pSpriteSheet);
    virtual ~Cursor();
    virtual void Update(float deltatime);
    virtual void Draw(vec2 camPos, vec2 projScale);

    virtual void OnCollision(GameObject* pOtherGameObject);

    void SetPlayerController(PlayerController* controller) { m_pPlayerController = controller; }

    void SetPlayer(Player* player) { m_pPlayer = player; }

    void HandleMouseMove();

};
