#include "GamePCH.h"
#include <string>
#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/Ball.h"
#include "GameObjects/PlayerController.h"
#include "SpriteSheet/SpriteSheet.h"
#include "Tilemap/Tilemap.h"

using namespace std;

Player::Player(GameCore* pGame, Mesh* pMesh, SpriteSheet* pSpriteSheet)
    : GameObject(pGame, pMesh, pSpriteSheet)
    , m_pPlayerController(0)
    , m_Speed(0)
    , m_CurrentPS(PS_WALK_DOWN)
    , m_TilemapRef(0)
    , m_LockX_Left(false)
    , m_LockX_Right(false)
    , m_LockY_Up(false)
    , m_LockY_Down(false)
{
    // Get the world width and height.
    unsigned int worldWidth = Game::Game_WORLD_SIZE_X;
    unsigned int worldHeight = Game::Game_WORLD_SIZE_Y;

    // Set the Player's initial position.
    m_Position.Set(worldWidth * PLAYER_START_X_POSITION_PCT, worldHeight * PLAYER_START_Y_POSITION_PCT);
    m_Sprite = m_pSpriteSheet->GetSpriteInfo("BM_WalkDown1.png");
    ExtractInfoFromSprite(m_Sprite);
}

Player::~Player()
{
}

void Player::Update(float deltatime)
{
    //GameObject::Update( deltatime );

    SetSpeed(0);

    if (m_pPlayerController)
    {
        //Handle Key Pressed
        // Moving Up
        if (m_pPlayerController->IsMoveUpHeld())
        {
            HandleMoving(deltatime, PlayerState::PS_WALK_UP);
        }
        // Moving Down
        else if (m_pPlayerController->IsMoveDownHeld())
        {
            HandleMoving(deltatime, PlayerState::PS_WALK_DOWN);
        }
        // Moving Left
        else if (m_pPlayerController->IsMoveLeftHeld())
        {
            HandleMoving(deltatime, PlayerState::PS_WALK_LEFT);
        }
        // Moving Right
        else if (m_pPlayerController->IsMoveRightHeld())
        {
            HandleMoving(deltatime, PlayerState::PS_WALK_RIGHT);
        }
        else
        {
            ResetLockBools();
        }

        // Handle Key Release
        // Set it back to WalkDown1 sprite
        if (!m_pPlayerController->IsMoveDownHeld() && m_CurrentPS == PlayerState::PS_WALK_DOWN)
        {
            ExtractInfoFromSprite(m_pSpriteSheet->GetSpriteInfo("BM_WalkDown1.png"));
            //ResetLockBools();
        }
        // Set it back to WalkUp1 sprite
        if (!m_pPlayerController->IsMoveUpHeld() && m_CurrentPS == PlayerState::PS_WALK_UP)
        {
            ExtractInfoFromSprite(m_pSpriteSheet->GetSpriteInfo("BM_WalkUp1.png"));
            //ResetLockBools();
        }
        // Set it back to WalkLeft1 sprite
        if (!m_pPlayerController->IsMoveLeftHeld() && m_CurrentPS == PlayerState::PS_WALK_LEFT)
        {
            ExtractInfoFromSprite(m_pSpriteSheet->GetSpriteInfo("BM_WalkLeft1.png"));
            //ResetLockBools();
        }
        // Set it back to WalkUp1 sprite
        if (!m_pPlayerController->IsMoveRightHeld() && m_CurrentPS == PlayerState::PS_WALK_RIGHT)
        {
            ExtractInfoFromSprite(m_pSpriteSheet->GetSpriteInfo("BM_WalkRight1.png"));
            //ResetLockBools();
        }
    }


    /*MyClamp(m_Position.x, 0.0f, (float)Game::Game_WORLD_SIZE_X);
    MyClamp(m_Position.y, 0.0f, (float)Game::Game_WORLD_SIZE_Y);*/

    //m_UVOffset.x += (0.0005f*GetSystemTimeSinceGameStart());
}

void Player::Draw(vec2 camPos, vec2 projScale)
{
    m_pMesh->Draw(m_Position, m_Angle, vec2(1, 1), camPos, projScale, m_TextureHandle, m_UVScale, m_UVOffset);
}

//void Player::ExtractInfoFromSprite(SpriteInfo* Sprite)
//{
//    float sprite_w = Sprite->m_Width;
//    float sprite_h = Sprite->m_Height;
//    vec2 sprite_Pos = Sprite->m_Pos;
//    string sprite_file = Sprite->m_Filename;
//
//    m_UVScale = vec2(sprite_w / m_SpriteSheet_TotalWidth, sprite_h / m_SpriteSheet_TotalHeight);
//    m_UVOffset = vec2(sprite_Pos.x / m_SpriteSheet_TotalWidth, sprite_Pos.y / m_SpriteSheet_TotalHeight);
//}

void Player::ChangeSprite(PlayerState ps)
{
    // Walk Down Animation Handle
    if (ps == PlayerState::PS_WALK_DOWN)
    {
        // No matter what sprite currently is, if it's not walk down kind, set it to walk_down1 sprite
        if (
            m_Sprite != m_pSpriteSheet->GetSpriteInfo("BM_WalkDown1.png")
            && m_Sprite != m_pSpriteSheet->GetSpriteInfo("BM_WalkDown2.png")
            && m_Sprite != m_pSpriteSheet->GetSpriteInfo("BM_WalkDown3.png")
            )
        {
            m_Sprite = m_pSpriteSheet->GetSpriteInfo("BM_WalkDown1.png");
        }

        //if it's 1, change to 2 
        else if (m_Sprite == m_pSpriteSheet->GetSpriteInfo("BM_WalkDown1.png"))
        {
            m_Sprite = m_pSpriteSheet->GetSpriteInfo("BM_WalkDown2.png");
        }
        //if it's 2, change to 3
        else if (m_Sprite == m_pSpriteSheet->GetSpriteInfo("BM_WalkDown2.png"))
        {
            m_Sprite = m_pSpriteSheet->GetSpriteInfo("BM_WalkDown3.png");
        }
        //if it's 3, change to 2
        else if (m_Sprite == m_pSpriteSheet->GetSpriteInfo("BM_WalkDown3.png"))
        {
            m_Sprite = m_pSpriteSheet->GetSpriteInfo("BM_WalkDown2.png");
        }
    }

    // Walk up Animation Handle
    else if (ps == PlayerState::PS_WALK_UP)
    {
        // No matter what sprite currently is, if it's not walk up kind, set it to walk_up1 sprite
        if (
            m_Sprite != m_pSpriteSheet->GetSpriteInfo("BM_WalkUp1.png")
            && m_Sprite != m_pSpriteSheet->GetSpriteInfo("BM_WalkUp2.png")
            && m_Sprite != m_pSpriteSheet->GetSpriteInfo("BM_WalkUp3.png")
            )
        {
            m_Sprite = m_pSpriteSheet->GetSpriteInfo("BM_WalkUp1.png");
        }
        //if it's 1, change to 2 
        else if (m_Sprite == m_pSpriteSheet->GetSpriteInfo("BM_WalkUp1.png"))
        {
            m_Sprite = m_pSpriteSheet->GetSpriteInfo("BM_WalkUp2.png");
        }
        //if it's 2, change to 3 
        else if (m_Sprite == m_pSpriteSheet->GetSpriteInfo("BM_WalkUp2.png"))
        {
            m_Sprite = m_pSpriteSheet->GetSpriteInfo("BM_WalkUp3.png");
        }
        //if it's 3, change to 2 
        else if (m_Sprite == m_pSpriteSheet->GetSpriteInfo("BM_WalkUp3.png"))
        {
            m_Sprite = m_pSpriteSheet->GetSpriteInfo("BM_WalkUp2.png");
        }
    }

    // Walk Left Animation Handle
    else if (ps == PlayerState::PS_WALK_LEFT)
    {
        // No matter what sprite currently is, if it's not walk left kind, set it to walk_left1 sprite
        if (
            m_Sprite != m_pSpriteSheet->GetSpriteInfo("BM_WalkLeft1.png")
            && m_Sprite != m_pSpriteSheet->GetSpriteInfo("BM_WalkLeft2.png")
            && m_Sprite != m_pSpriteSheet->GetSpriteInfo("BM_WalkLeft3.png")
            )
        {
            m_Sprite = m_pSpriteSheet->GetSpriteInfo("BM_WalkLeft1.png");
        }
        //if it's 1, change to 2 
        else if (m_Sprite == m_pSpriteSheet->GetSpriteInfo("BM_WalkLeft1.png"))
        {
            m_Sprite = m_pSpriteSheet->GetSpriteInfo("BM_WalkLeft2.png");
        }
        //if it's 2, change to 3 
        else if (m_Sprite == m_pSpriteSheet->GetSpriteInfo("BM_WalkLeft2.png"))
        {
            m_Sprite = m_pSpriteSheet->GetSpriteInfo("BM_WalkLeft3.png");
        }
        //if it's 3, change to 2 
        else if (m_Sprite == m_pSpriteSheet->GetSpriteInfo("BM_WalkLeft3.png"))
        {
            m_Sprite = m_pSpriteSheet->GetSpriteInfo("BM_WalkLeft1.png");
        }
    }

    // Walk Right Animation Handle
    else if (ps == PlayerState::PS_WALK_RIGHT)
    {
        // No matter what sprite currently is, if it's not walkRight kind, set it to walk_right1 sprite
        if (
            m_Sprite != m_pSpriteSheet->GetSpriteInfo("BM_WalkRight1.png")
            && m_Sprite != m_pSpriteSheet->GetSpriteInfo("BM_WalkRight2.png")
            && m_Sprite != m_pSpriteSheet->GetSpriteInfo("BM_WalkRight3.png")
            )
        {
            m_Sprite = m_pSpriteSheet->GetSpriteInfo("BM_WalkRight1.png");
        }
        //if it's 1, change to 2 
        else if (m_Sprite == m_pSpriteSheet->GetSpriteInfo("BM_WalkRight1.png"))
        {
            m_Sprite = m_pSpriteSheet->GetSpriteInfo("BM_WalkRight2.png");
        }
        //if it's 2, change to 3 
        else if (m_Sprite == m_pSpriteSheet->GetSpriteInfo("BM_WalkRight2.png"))
        {
            m_Sprite = m_pSpriteSheet->GetSpriteInfo("BM_WalkRight3.png");
        }
        //if it's 3, change to 2 
        else if (m_Sprite == m_pSpriteSheet->GetSpriteInfo("BM_WalkRight3.png"))
        {
            m_Sprite = m_pSpriteSheet->GetSpriteInfo("BM_WalkRight1.png");
        }
    }
}

void Player::HandleMoving(float deltatime, PlayerState ps)
{
    SetSpeed(PLAYER_SPEED_MOVE);
    SetCurrentPlayerState(ps);
    if (ps == PlayerState::PS_WALK_UP && !m_LockY_Up)
    {
        m_Position.y += deltatime * m_Speed;
    }
    else if (ps == PlayerState::PS_WALK_DOWN && !m_LockY_Down)
    {
        m_Position.y -= deltatime * m_Speed;
    }
    else if (ps == PlayerState::PS_WALK_LEFT && !m_LockX_Left)
    {
        m_Position.x -= deltatime * m_Speed;
    }
    else if (ps == PlayerState::PS_WALK_RIGHT && !m_LockX_Right)
    {
        m_Position.x += deltatime * m_Speed;
    }

    m_TimerForAnimationChange += deltatime;
    if (m_TimerForAnimationChange >= ANIMATION_TIME_PER_FRAME)
    {
        ChangeSprite(ps);
        ExtractInfoFromSprite(m_Sprite);
        m_TimerForAnimationChange = 0;
    }
}

bool Player::IsColliding()
{
    return false;
}

void Player::OnCollision(GameObject* pOtherGameObject)
{
    float offset = 0.5f;
    ivec2 tilePos_LeftTop = m_TilemapRef->GetTilePosFromWorldPos(m_Position.x - offset, m_Position.y + 3 * offset);

    ivec2 tilePos_RightTop = m_TilemapRef->GetTilePosFromWorldPos(m_Position.x + offset, m_Position.y + 3 * offset);

    ivec2 tilePos_LeftBot = m_TilemapRef->GetTilePosFromWorldPos(m_Position.x - offset, m_Position.y);

    ivec2 tilePos_RightBot = m_TilemapRef->GetTilePosFromWorldPos(m_Position.x + offset, m_Position.y);

    // Handle left top corner of the player sprite collision
    if (!m_TilemapRef->IsTileWalkableAtTilePos(tilePos_LeftTop.x, tilePos_LeftTop.y))
    {
        TILE_TYPE tileType_LeftTop = m_TilemapRef->GetTileAtTileLocation(tilePos_LeftTop.x, tilePos_LeftTop.y);
        if (tileType_LeftTop == TILE_TYPE::BOX)
        {
            //trigger win flag
            int bp = 0;
        }
        // Only two cases when collision happens in left top corner, one is in walk up Player State, which is set when press 'w'
        if (m_CurrentPS == PlayerState::PS_WALK_UP)
        {
            m_LockY_Up = true;
            //Set player's position back a bit offset
            m_Position.y -= 0.5f;
        }
        // Another one case is the case when press 'A'
        else if (m_CurrentPS == PlayerState::PS_WALK_LEFT)
        {
            m_LockX_Left = true;

            m_Position.x += 0.5f;
        }
        //return true;

    }

    // Handle right top corner of the player sprite collision
    else if (!m_TilemapRef->IsTileWalkableAtTilePos(tilePos_RightTop.x, tilePos_RightTop.y))
    {
        TILE_TYPE tileType_RightTop = m_TilemapRef->GetTileAtTileLocation(tilePos_RightTop.x, tilePos_RightTop.y);
        if (tileType_RightTop == TILE_TYPE::BOX)
        {
            //trigger win flag
            int bp = 0;
        }

        // Only two cases when collision happens in right top corner, one is in walk up Player State, which is set when press 'w'
        if (m_CurrentPS == PlayerState::PS_WALK_UP)
        {
            m_LockY_Up = true;
            m_Position.y -= 0.5f;
        }
        // Another one case is the case when press 'D'
        else if (m_CurrentPS == PlayerState::PS_WALK_RIGHT)
        {
            m_LockX_Right = true;
            m_Position.x -= 0.5f;
        }
        //return true;
    }

    // Handle left bottom corner of the player sprite collision
    else if (!m_TilemapRef->IsTileWalkableAtTilePos(tilePos_LeftBot.x, tilePos_LeftBot.y))
    {
        TILE_TYPE tileType_LeftBot = m_TilemapRef->GetTileAtTileLocation(tilePos_LeftBot.x, tilePos_LeftBot.y);
        if (tileType_LeftBot == TILE_TYPE::BOX)
        {
            //trigger win flag
            int bp = 0;
        }

        // Only two cases when collision happens in left bottom corner, one is in walk down Player State, which is set when press 'S'
        if (m_CurrentPS == PlayerState::PS_WALK_DOWN)
        {
            m_LockY_Down = true;
            m_Position.y += 0.5f;
        }
        // Another one case is the case when press 'A'
        else if (m_CurrentPS == PlayerState::PS_WALK_LEFT)
        {
            m_LockX_Left = true;
            m_Position.x += 0.5f;
        }
        //return true;
    }
    // Handle right bottom corner of the player sprite collision
    else if (!m_TilemapRef->IsTileWalkableAtTilePos(tilePos_RightBot.x, tilePos_RightBot.y))
    {
        TILE_TYPE tileType_RightBot = m_TilemapRef->GetTileAtTileLocation(tilePos_RightBot.x, tilePos_RightBot.y);
        if (tileType_RightBot == TILE_TYPE::BOX)
        {
            //trigger win flag
            int bp = 0;
        }

        // Only two cases when collision happens in right bottom corner, one is in walk down Player State, which is set when press 'S'
        if (m_CurrentPS == PlayerState::PS_WALK_DOWN)
        {
            m_LockY_Down = true;
            m_Position.y += 0.5f;
        }
        // Another one case is the case when press 'D'
        else if (m_CurrentPS == PlayerState::PS_WALK_RIGHT)
        {
            m_LockX_Right = true;
            m_Position.x -= 0.5f;
        }
        //return true;
    }
    else
    {
        //return false;
    }

}

//void Player::OnCollision(GameObject* pOtherGameObject)
//{
//    if (IsColliding())
//    {
//        if (m_CurrentPS == PlayerState::PS_WALK_DOWN)
//        {
//            m_LockY_Down = true;
//        }
//        else if (m_CurrentPS == PlayerState::PS_WALK_UP)
//        {
//            m_LockY_Up = true;
//        }
//        else if (m_CurrentPS == PlayerState::PS_WALK_LEFT)
//        {
//            m_LockX = true;
//        }
//        else if (m_CurrentPS == PlayerState::PS_WALK_RIGHT)
//        {
//            m_LockX = true;
//        }
//    }
//}

void Player::ResetLockBools()
{
    m_LockY_Down = false;
    m_LockY_Up = false;
    m_LockX_Left = false;
    m_LockX_Right = false;

}