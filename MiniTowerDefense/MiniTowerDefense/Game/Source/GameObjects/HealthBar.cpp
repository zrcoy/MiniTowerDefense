#include "GamePCH.h"

#include <string>
#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/HealthBar.h"
#include "SpriteSheet/SpriteSheet.h"
#include "GameObjects/Boss/Boss.h"

HealthBar::HealthBar(GameCore* pGame, Mesh* pMesh, SpriteSheet* pSpriteSheet, Boss* pBoss, Mesh* pCurrentHealthBarMesh)
    : GameObject(pGame, pMesh, pSpriteSheet)

{
    m_pBoss = pBoss;

    m_pCurrentHealthBarMesh = pCurrentHealthBarMesh;
}

HealthBar::~HealthBar()
{

}

void HealthBar::Update(float deltatime)
{
    m_Position = vec2(m_pBoss->GetPosition().x - 1.0f, m_pBoss->GetPosition().y + 1.5f);
    m_HealthPercentage = m_pBoss->GetHealthPercentage();
}



void HealthBar::Draw(vec2 camPos, vec2 projScale)
{
    float fullLength_HealthBar = 2.0f;
    m_pMesh->Draw(m_Position, m_Angle, vec2(fullLength_HealthBar, 0.3f), camPos, projScale, 0, m_UVScale, m_UVOffset);
    m_pCurrentHealthBarMesh->Draw(m_Position, m_Angle, vec2(fullLength_HealthBar*m_HealthPercentage, 0.3f), camPos, projScale, 0, m_UVScale, m_UVOffset);
}

Boss* HealthBar::GetRelativeBoss()
{
    return m_pBoss;
}




