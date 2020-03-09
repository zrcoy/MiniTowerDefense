#include "GamePCH.h"
#include <string>
#include "Tilemap.h"
#include "SpriteSheet/SpriteSheet.h"
#include "Game/Game.h"
#include "Mesh/Mesh.h"

using namespace std;

Tilemap::Tilemap() :
    m_pSpriteSheet(0)
    , m_pMesh(0)
    , m_TileX(0)
    , m_TileY(0)
    , m_WorldPosX(0)
    , m_WorldPosY(0)
    , m_TextureHandle(0)
    , m_UVScale(0, 0)
    , m_UVOffset(0, 0)
{

    m_pTileInfo = new TileInfo[NUM_TILE_TYPES];

    float worldWidth = Game::Game_WORLD_SIZE_X;
    float worldHeight = Game::Game_WORLD_SIZE_Y;

    m_Tilesize_X = Game::Game_WORLD_SIZE_X / TILE_MAP_WIDTH;
    m_Tilesize_Y = Game::Game_WORLD_SIZE_X / TILE_MAP_WIDTH;
}

Tilemap::~Tilemap()
{
    //delete m_Tiles;
    delete[] m_pTileInfo;
}

void Tilemap::Create()
{

    m_pTileInfo[WALL_SW] = TileInfo(m_pMesh, m_pSpriteSheet->GetSpriteInfo("Wall-SW.png"), false);
    m_pTileInfo[WALL_SE] = TileInfo(m_pMesh, m_pSpriteSheet->GetSpriteInfo("Wall-SE.png"), false);
    m_pTileInfo[WALL_E] = TileInfo(m_pMesh, m_pSpriteSheet->GetSpriteInfo("Wall-E.png"), false);
    m_pTileInfo[WALL_W] = TileInfo(m_pMesh, m_pSpriteSheet->GetSpriteInfo("Wall-W.png"), false);
    m_pTileInfo[WALL_NW] = TileInfo(m_pMesh, m_pSpriteSheet->GetSpriteInfo("Wall-NW.png"), false);
    m_pTileInfo[WALL_NE] = TileInfo(m_pMesh, m_pSpriteSheet->GetSpriteInfo("Wall-NE.png"), false);
    m_pTileInfo[WALL_S] = TileInfo(m_pMesh, m_pSpriteSheet->GetSpriteInfo("Wall-S.png"), false);
    m_pTileInfo[WALL_N] = TileInfo(m_pMesh, m_pSpriteSheet->GetSpriteInfo("Wall-N.png"), false);
    m_pTileInfo[BOX] = TileInfo(m_pMesh, m_pSpriteSheet->GetSpriteInfo("Box.png"), false);
    m_pTileInfo[WALL] = TileInfo(m_pMesh, m_pSpriteSheet->GetSpriteInfo("Wall.png"), false);
    m_pTileInfo[FLOOR] = TileInfo(m_pMesh, m_pSpriteSheet->GetSpriteInfo("Floor.png"), true);

}

void Tilemap::SetSpriteSheet(SpriteSheet* spriteSheet)
{
    m_pSpriteSheet = spriteSheet;
}

void Tilemap::SetMesh(Mesh* mesh)
{
    m_pMesh = mesh;
}

void Tilemap::Draw(vec2 camPos, vec2 projScale)
{

    //int tileSize = 5;
    float angle = 0.0f;
    vec2 scale = vec2(5, 5);



    for (int y = TILE_MAP_HEIGHT - 1; y >= 0; y--)
    {
        for (int x = 0; x < TILE_MAP_WIDTH; x++)
        {
            //Get tileType in this x ,y tile position
            TILE_TYPE tileType = GetTileAtTileLocation(x, y);

            // Get the respective m_UVScale and m_UVOffset
            ExtractInfoFromSprite(m_pTileInfo[tileType].m_pSprite);

            // Draw that tile with relative info
            m_pTileInfo[tileType].m_pMesh->Draw(GetWorldSpacePosForTilePos(x, y), 0, scale, camPos, projScale, m_TextureHandle, m_UVScale, m_UVOffset);
            int bp = 0;
        }
    }
}

bool Tilemap::IsTileWalkableAtTilePos(int x, int y)
{
    int tileIndex = y * TILE_MAP_WIDTH + x;
    TILE_TYPE tileType = m_Tiles[tileIndex];
    if (m_pTileInfo[tileType].m_Walkable)
    {
        return true;
    }
    else return false;
}

TILE_TYPE Tilemap::GetTileAtWorldPos(int x, int y)
{
    int tileIndex = y * TILE_MAP_WIDTH + x;
    TILE_TYPE tileType = m_Tiles[tileIndex];
    return tileType;
}

TILE_TYPE Tilemap::GetTileAtTileLocation(int x, int y)
{
    /* int nx = index % TILE_MAP_WIDTH;
     int ny = index / TILE_MAP_WIDTH;

     return ivec2(nx, ny);*/
    int tileIndex = y * TILE_MAP_WIDTH + x;
    TILE_TYPE tileType = m_Tiles[tileIndex];
    return tileType;
}

ivec2 Tilemap::GetTilePosFromWorldPos(float x, float y)
{

    return ivec2(int(x / m_Tilesize_X), int(y / m_Tilesize_Y));
}

vec2 Tilemap::GetWorldSpacePosForTilePos(int x, int y)
{
    return vec2((float)(x * m_Tilesize_X),(float)( y * m_Tilesize_Y));
}

vec2 Tilemap::GetWorldPosFromTilemapIndex(int index)
{
    vec2 tilePos = GetTilePosFromTilemapIndex(index);
    return GetWorldSpacePosForTilePos((int)tilePos.x, (int)tilePos.y);
}

vec2 Tilemap::GetTilePosFromTilemapIndex(int index)
{
    int x = index % TILE_MAP_WIDTH;
    int y = index / TILE_MAP_WIDTH;
    return vec2((float)x,(float) y);
}

void Tilemap::SetTexture(GLuint textureHandle)
{
    m_TextureHandle = textureHandle;
}

void Tilemap::ExtractInfoFromSprite(SpriteInfo* Sprite)
{
    float sprite_w = Sprite->m_Width;
    float sprite_h = Sprite->m_Height;
    vec2 sprite_Pos = Sprite->m_Pos;
    string sprite_file = Sprite->m_Filename;

    float SpriteSheet_TotalHeight = m_pSpriteSheet->GetSpriteSheetTotalHeight();
    float SpriteSheet_TotalWidth = m_pSpriteSheet->GetSpriteSheetTotalWidth();

    m_UVScale = vec2(sprite_w / SpriteSheet_TotalWidth, sprite_h / SpriteSheet_TotalHeight);
    m_UVOffset = vec2(sprite_Pos.x / SpriteSheet_TotalWidth, sprite_Pos.y / SpriteSheet_TotalHeight);
}