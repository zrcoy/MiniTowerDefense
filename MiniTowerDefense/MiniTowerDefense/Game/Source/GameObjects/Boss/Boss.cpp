#include "GamePCH.h"
#include <string>
#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Boss/Boss.h"
#include "SpriteSheet/SpriteSheet.h"
#include "Pathfinder/Pathfinder.h"
#include "Tilemap/Tilemap.h"

using namespace std;

Boss::Boss(GameCore * pGame, Mesh * pMesh, SpriteSheet* pSpriteSheet)
    : GameObject(pGame, pMesh, pSpriteSheet)
{
    // Get the world width and height.
    float worldWidth = Game::Game_WORLD_SIZE_X;
    float worldHeight = Game::Game_WORLD_SIZE_Y;


    SpriteInfo* Sprite = m_pSpriteSheet->GetSpriteInfo("Boss_1.png");

    float sprite_w = Sprite->m_Width;
    float sprite_h = Sprite->m_Height;
    vec2 sprite_Pos = Sprite->m_Pos;
    string sprite_file = Sprite->m_Filename;

    //m_Position.Set(worldWidth*0.2f, worldHeight*0.3f);
    // random x y ratio of the height and width, I make it a bit far from the chest goal tile which is the right top corner 
    int randxRatio = rand() % 600 + 100;
    int randyRatio = rand() % 600 + 100;
    m_Position.Set(worldWidth*(100.0f / randxRatio), worldHeight*(100.0f / randyRatio));
    //m_Position=GetWorldPosFromTilePos(m_Startx, m_Starty);

    m_UVScale = vec2(sprite_w / m_SpriteSheet_TotalWidth, sprite_h / m_SpriteSheet_TotalHeight);
    m_UVOffset = vec2(sprite_Pos.x / m_SpriteSheet_TotalWidth, sprite_Pos.y / m_SpriteSheet_TotalHeight);

    m_pTilemap = 0;
    m_CurrentIndexOfPath = 0;

    m_MaxHealth = 100.0f;
    m_CurrentHealth = 100.0f;

    m_Drawable = true;
}

Boss::~Boss()
{

}

void Boss::Update(float deltatime)
{

    if (m_CurrentIndexOfPath >= 0 && m_Drawable)
    {

        vec2 targetPos = m_pTilemap->GetWorldPosFromTilemapIndex(m_Path[m_CurrentIndexOfPath]);
        //float anglerad = m_Angle * PI / 180;

        //vec2 dir = m_Position - targetPos;
        vec2 dir = targetPos - m_Position;
        dir.Normalize();
        float angle = atan2(dir.y, dir.x);

        vec2 velocity = /*m_Speed, 3.0 for now*/3.0f * vec2(cosf(angle), sinf(angle));

        // If arrive at current target, set next target
        //if (m_Position == targetPos)
        if (IsItColliding(m_Path))
        {
            //if(m_flag)
            m_CurrentIndexOfPath--;
        }
        // if not arrived yet, keep moving

        m_Position += velocity * deltatime;

    }


}

void Boss::Draw(vec2 camPos, vec2 projScale)
{
    m_pMesh->Draw(m_Position, m_Angle, m_Scale, camPos, projScale, m_TextureHandle, m_UVScale, m_UVOffset);
}

bool Boss::IsItColliding(int arrPath[])
{

    vec2 targetPos = m_pTilemap->GetWorldPosFromTilemapIndex(arrPath[m_CurrentIndexOfPath]);
    vec2 pos1 = m_Position;
    vec2 pos2 = targetPos;

    vec2 diff = pos2 - pos1;
    if (diff.Length() < 1.0f/*m_Radius + 3.5f*/)
        return true;

    return false;
}


void Boss::OnCollision(GameObject * pOtherGameObject)
{

}

vec2 Boss::GetWorldPosFromTilePos(int x, int y)
{
    return vec2((float)(x * 5),(float)( y * 5));
}

void Boss::SetupPath()
{
    Pathfinder pathfinder(m_pTilemap, 10, 10);

    // Fixed end box point
    int endx = 8;
    int endy = 8;


    int randStartx = rand() % 10;
    int randStarty = rand() % 10;
    while (!m_pTilemap->IsTileWalkableAtTilePos(randStartx, randStarty))
    {
        randStartx = rand() % 10;
        randStarty = rand() % 10;
    }

    pathfinder.FindPath(randStartx, randStarty, endx, endy);


    int len = pathfinder.GetPath(m_Path, 255, endx, endy);
    m_CurrentIndexOfPath = len - 2;
}

void Boss::DecreaseHealth()
{
    m_CurrentHealth -= 50.0f;
}

float Boss::GetHealthPercentage()
{
    return m_CurrentHealth / m_MaxHealth;
}

void Boss::Destroy()
{
    m_Drawable = false;
    m_Position = vec2(-10.0f, -10.0f);
}

bool Boss::GetDrawable()
{
    return m_Drawable;
}

