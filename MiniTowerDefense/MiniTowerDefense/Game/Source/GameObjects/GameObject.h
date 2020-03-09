#ifndef __GameObject_H__
#define __GameObject_H__

class Mesh;
class SpriteSheet;
struct SpriteInfo;

class GameObject
{
protected:
    GameCore* m_pGame;
    Mesh* m_pMesh;
    SpriteSheet* m_pSpriteSheet;

    vec2 m_Position;
    float m_Angle;
    vec2 m_Scale;
    float m_Radius;
    GLuint m_TextureHandle;
    vec2 m_UVScale;
    vec2 m_UVOffset;
    float m_SpriteSheet_TotalWidth;
    float m_SpriteSheet_TotalHeight;

    SpriteInfo* m_Sprite;
public:
    GameObject(GameCore* pGame, Mesh* pMesh, SpriteSheet* pSpriteSheet);
    virtual ~GameObject();

    virtual void OnEvent(Event* pEvent) {}
    virtual void Update(float deltatime) {}
    virtual void Draw(vec2 camPos, vec2 projScale);

    virtual bool IsColliding();
    //virtual bool IsColliding(GameObject* pOtherGameObject);
    virtual void OnCollision(GameObject* pOtherGameObject);
    virtual void ExtractInfoFromSprite(SpriteInfo* Sprite);


    // Getters.
    vec2 GetPosition() { return m_Position; }
    float GetAngle() { return m_Angle; }
    float GetRadius() { return m_Radius; }
    SpriteInfo* GetSprite() { return m_Sprite; }

    // Setters.
    void SetPosition(vec2 pos) { m_Position = pos; }
    void SetAngle(float angle) { m_Angle = angle; }
    void SetRadius(float radius) { m_Radius = radius; }
    void SetSprite(SpriteInfo* sprite) { m_Sprite = sprite; }
    void SetTexture(GLuint textureHandle);
};

#endif //__GameObject_H__
