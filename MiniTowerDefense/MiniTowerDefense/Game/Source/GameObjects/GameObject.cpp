#include "GamePCH.h"
#include <string>
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "SpriteSheet/SpriteSheet.h"

using namespace std;

GameObject::GameObject(GameCore* pGame, Mesh* pMesh, SpriteSheet* pSpriteSheet)
    : m_pGame(pGame)
    , m_pMesh(pMesh)
    , m_pSpriteSheet(pSpriteSheet)
    , m_Position(0, 0)
    , m_Angle(0)
    , m_Radius(1)
    , m_Scale(1, 1)
    , m_UVScale(1, 1)
    , m_UVOffset(0, 0)
    , m_Sprite(0)

{

    m_SpriteSheet_TotalHeight = m_pSpriteSheet->GetSpriteSheetTotalHeight();
    m_SpriteSheet_TotalWidth = m_pSpriteSheet->GetSpriteSheetTotalWidth();
    m_TextureHandle = 0;
    /*m_TextureHandle = LoadTexture("Data/Bomberman.png");*/
}

GameObject::~GameObject()
{


}

void GameObject::SetTexture(GLuint textureHandle)
{
    m_TextureHandle = textureHandle;
}

void GameObject::Draw(vec2 camPos, vec2 projScale)
{
    if (m_pMesh != 0)
        m_pMesh->Draw(m_Position, m_Angle, m_Scale, camPos, projScale, m_TextureHandle, m_UVScale, m_UVOffset);
}

//bool GameObject::IsColliding(GameObject* pOtherGameObject)
//{
//    vec2 pos1 = m_Position;
//    vec2 pos2 = pOtherGameObject->GetPosition();
//
//    vec2 diff = pos2 - pos1;
//    if (diff.Length() < m_Radius + pOtherGameObject->m_Radius)
//        return true;
//
//    return false;
//}

bool GameObject::IsColliding()
{
    return false;
}

void GameObject::OnCollision(GameObject* pOtherGameObject)
{
}

void GameObject::ExtractInfoFromSprite(SpriteInfo* Sprite)
{
    float sprite_w = Sprite->m_Width;
    float sprite_h = Sprite->m_Height;
    vec2 sprite_Pos = Sprite->m_Pos;
    string sprite_file = Sprite->m_Filename;

    m_UVScale = vec2(sprite_w / m_SpriteSheet_TotalWidth, sprite_h / m_SpriteSheet_TotalHeight);
    m_UVOffset = vec2(sprite_Pos.x / m_SpriteSheet_TotalWidth, sprite_Pos.y / m_SpriteSheet_TotalHeight);
}