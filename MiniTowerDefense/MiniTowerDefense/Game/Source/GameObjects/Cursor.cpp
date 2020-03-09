#include "GamePCH.h"
#include <string>
#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "Cursor.h"
#include "SpriteSheet/SpriteSheet.h"
#include "GameObjects/PlayerController.h"
#include "GameObjects/Player.h"

using namespace std;

Cursor::Cursor(GameCore * pGame, Mesh * pMesh, SpriteSheet* pSpriteSheet)
    : GameObject(pGame, pMesh, pSpriteSheet)
    , m_pPlayerController(0)

{

    m_ProjectionScale = vec2(0, 0);
    // Get the world width and height.
    //float worldWidth = Game::Game_WORLD_SIZE_X;
    //float worldHeight = Game::Game_WORLD_SIZE_Y;


    m_Sprite = m_pSpriteSheet->GetSpriteInfo("TD_Tower_1.png");

    ExtractInfoFromSprite(m_Sprite);

}

Cursor::~Cursor()
{

}

void Cursor::Update(float deltatime)
{
    HandleMouseMove();
    if (m_pPlayerController->IsNum1Pressed())
    {
        m_Sprite = m_pSpriteSheet->GetSpriteInfo("TD_Tower_1.png");
    }
    else if (m_pPlayerController->IsNum2Pressed())
    {
        m_Sprite = m_pSpriteSheet->GetSpriteInfo("TD_Tower_2.png");
    }
    else if (m_pPlayerController->IsNum3Pressed())
    {
        m_Sprite = m_pSpriteSheet->GetSpriteInfo("TD_Tower_3.png");
    }
    else if (m_pPlayerController->IsNum4Pressed())
    {
        m_Sprite = m_pSpriteSheet->GetSpriteInfo("TD_Tower_4.png");
    }
    ExtractInfoFromSprite(m_Sprite);
}

void Cursor::Draw(vec2 camPos, vec2 projScale)
{
    m_ProjectionScale = projScale;
    m_pMesh->Draw(m_Position, m_Angle, m_Scale, camPos, projScale, m_TextureHandle, m_UVScale, m_UVOffset);
    int bp = 0;
}

void Cursor::OnCollision(GameObject * pOtherGameObject)
{

}

void Cursor::HandleMouseMove()
{
    float nx, ny;
    float ratio = 1.0f / HALF_SCREEN_WIDTH;
    m_ProjectionScale = 1.0f / m_ProjectionScale;
    nx = (m_pPlayerController->GetMousePos().x*ratio - 1.0f) * m_ProjectionScale.x + m_pPlayer->GetPosition().x;
    ny = ((600.0f - m_pPlayerController->GetMousePos().y) * ratio - 1.0f) * m_ProjectionScale.y + m_pPlayer->GetPosition().y;
    /*OutputMessage("mouse: %f,%f  world: %f,%f  player: %f,%f\n", m_pPlayerController->GetMousePos().x,
                  m_pPlayerController->GetMousePos().y, nx, ny, m_pPlayer->GetPosition().x, m_pPlayer->GetPosition().y);*/
    m_Position.Set(nx, ny);
}


