#pragma once

class Pathfinder;
class Tilemap;


class Boss :public GameObject
{
    Tilemap* m_pTilemap;
    int m_CurrentIndexOfPath;

    int m_Path[255];

    float m_MaxHealth, m_CurrentHealth;

    bool m_Drawable;
public:
    Boss(GameCore*pGame, Mesh* pMesh, SpriteSheet* pSpriteSheet);
    virtual ~Boss();
    virtual void Update(float deltatime);
    virtual void Draw(vec2 camPos, vec2 projScale);
    bool IsItColliding(int arrPath[]);
    virtual void OnCollision(GameObject* pOtherGameObject);

    void SetTilemap(Tilemap* tilemap) { m_pTilemap = tilemap; }

    vec2 GetWorldPosFromTilePos(int x, int y);

    void SetupPath();

    void DecreaseHealth();

    float GetHealthPercentage();

    float GetCurrentHealth() { return m_CurrentHealth; }

    float GetMaxHealth() { return m_MaxHealth; }

    void Destroy();

    bool GetDrawable();


};
