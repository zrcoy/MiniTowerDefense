#include "GamePCH.h"

#include <string>
#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Tower.h"
#include "GameObjects/PlayerController.h"
#include "SpriteSheet/SpriteSheet.h"


Tower::Tower(GameCore* pGame, Mesh* pMesh, SpriteSheet* pSpriteSheet)
    : GameObject(pGame, pMesh, pSpriteSheet)
    , m_pBall(0)
{
    m_Sprite = m_pSpriteSheet->GetSpriteInfo("TD_Tower_1.png");
    ExtractInfoFromSprite(m_Sprite);

    m_Scale = vec2(5, 5);
    //m_pBall = new Ball( pGame, m_pMeshDiamond , m_pSpriteSheet);
}

Tower::~Tower()
{

}

void Tower::Update(float deltatime)
{

}

void Tower::Draw(vec2 camPos, vec2 projScale)
{
    m_pMesh->Draw(m_Position, m_Angle, m_Scale, camPos, projScale, m_TextureHandle, m_UVScale, m_UVOffset);
}

void Tower::Destroy()
{
    m_Sprite = m_pSpriteSheet->GetSpriteInfo("Ruin.png");
    ExtractInfoFromSprite(m_Sprite);
    m_Scale = vec2(2, 1.5);
}




