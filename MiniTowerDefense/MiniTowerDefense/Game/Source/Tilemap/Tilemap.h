#pragma once
struct SpriteInfo;
class SpriteSheet;
class Mesh;

enum TILE_TYPE
{
    WALL_SW = 0,
    WALL_SE = 1,
    WALL_E = 2,
    WALL_W = 3,
    WALL_NW = 4,
    WALL_NE = 5,
    WALL_S = 6,
    WALL_N = 7,
    BOX = 8,
    WALL = 9,
    FLOOR = 10
};

struct TileInfo
{
public:
    Mesh* m_pMesh;
    SpriteInfo* m_pSprite;
    bool m_Walkable;

public:
    TileInfo() :m_pSprite(0), m_Walkable(0), m_pMesh(0) {};
    ~TileInfo() {}
    TileInfo(Mesh* mesh, SpriteInfo* sprite, bool walkable) :m_pSprite(sprite), m_Walkable(walkable), m_pMesh(mesh) {}
};

class Tilemap
{
private:
    const static int NUM_TILE_TYPES = 11;
    const static int TILE_MAP_WIDTH = 10;
    const static int TILE_MAP_HEIGHT = 10;
    SpriteSheet* m_pSpriteSheet;
    Mesh* m_pMesh;

    float m_Tilesize_X, m_Tilesize_Y;

    int m_TileX, m_TileY;
    float m_WorldPosX, m_WorldPosY;

    TILE_TYPE m_Tiles[TILE_MAP_HEIGHT * TILE_MAP_WIDTH] =
    {
        WALL_SW,WALL_S,WALL_S,WALL_S,WALL_S,WALL_S,WALL_S,WALL_S,WALL_S,WALL_SE,
        WALL_W,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,WALL_E,
        WALL_W,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,WALL_E,
        WALL_W,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,WALL_E,
        WALL_W,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,WALL_E,
        WALL_W,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,WALL_E,
        WALL_W,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,WALL_E,
        WALL_W,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,BOX,WALL_E,
        WALL_W,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,FLOOR,WALL_E,
        WALL_NW,WALL_N,WALL_N,WALL_N,WALL_N,WALL_N,WALL_N,WALL_N,WALL_N,WALL_NE
    };

    TileInfo* m_pTileInfo;
    //TileInfo m_pTileInfo[NUM_TILE_TYPES];

    GLuint m_TextureHandle;

    vec2 m_UVScale;
    vec2 m_UVOffset;

public:
    Tilemap();
    ~Tilemap();

    void Create();
    void Draw(vec2 camPos, vec2 projScale);

    bool IsTileWalkableAtTilePos(int x, int y);

    void SetSpriteSheet(SpriteSheet* spriteSheet);

    void SetMesh(Mesh* mesh);

    TILE_TYPE GetTileAtWorldPos(int x, int y);

    TILE_TYPE GetTileAtTileLocation(int x, int y);

    ivec2 GetTilePosFromWorldPos(float x, float y);

    vec2 GetWorldSpacePosForTilePos(int x, int y);

    vec2 GetWorldPosFromTilemapIndex(int index);

    vec2 GetTilePosFromTilemapIndex(int index);

    void SetTexture(GLuint textureHandle);

    void ExtractInfoFromSprite(SpriteInfo* Sprite);

    TileInfo* GetTileInfo() { return m_pTileInfo; }
};