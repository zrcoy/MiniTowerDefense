#include "GamePCH.h"

#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Ball.h"
#include "Ball.h"
#include "SpriteSheet/SpriteSheet.h"
#include "Tower.h"

Ball::Ball(GameCore* pGame, Mesh* pMesh, SpriteSheet* pSpriteSheet, Tower* pTower, int kind)
    : GameObject(pGame, pMesh, pSpriteSheet)
    , m_Speed(0)
    , m_DrawBall(false)
    , m_DetectRangeForShoot(10.0f)
    , m_pTower(pTower)
{
    // Get the world width and height.
    float worldWidth = Game::Game_WORLD_SIZE_X;
    float worldHeight = Game::Game_WORLD_SIZE_Y;

    // Set the Ball's initial position.
    //m_Position.Set( worldWidth * Ball_START_X_POSITION_PCT, worldHeight * Ball_START_Y_POSITION_PCT );
    m_Position = pTower->GetPosition();

    if (kind == 0)
    {
        m_Sprite = m_pSpriteSheet->GetSpriteInfo("Projectile_1.png");
    }
    else if (kind == 1)
    {
        m_Sprite = m_pSpriteSheet->GetSpriteInfo("Projectile_2.png");
    }
    else if (kind == 2)
    {
        m_Sprite = m_pSpriteSheet->GetSpriteInfo("Projectile_3.png");
    }
    else if (kind == 3)
    {
        m_Sprite = m_pSpriteSheet->GetSpriteInfo("Projectile_5.png");
    }
    ExtractInfoFromSprite(m_Sprite);

    //m_TextureHandle = LoadTexture("Data/TowerDefense.png");

    /*m_UVScale = vec2(16.0f / 256.0f, 32.0f / 128.0f);
    m_UVOffset = vec2(0.0f / 256.0f, 96.0f / 128.0f);*/
}

Ball::~Ball()
{
}

void Ball::Update(float deltatime)
{
    //GameObject::Update( deltatime );

    // Calculate the Ball's velocity based on the speed and the angle.
    float anglerad = m_Angle * PI / 180;
    vec2 velocity = m_Speed * vec2(cosf(anglerad), sinf(anglerad));

    // Apply the velocity to the Ball's position.
    m_Position += velocity * deltatime;


}

void Ball::Draw(vec2 camPos, vec2 projScale)
{
    m_pMesh->Draw(m_Position, 0, vec2(1, 1), camPos, projScale, m_TextureHandle, m_UVScale, m_UVOffset);
}

void Ball::OnCollision(GameObject* pOtherGameObject)
{
    // Is it in the range of shooting
    if (IsInRangeOfShooting(pOtherGameObject))
    {
        // launch the projectile
        LaunchProjectile(pOtherGameObject);

    }

    // Is it hit the target
    if (IsColliding(pOtherGameObject))
    {
        m_DrawBall = false;
    }
}

bool Ball::IsInRangeOfShooting(GameObject* pOtherGameObject)
{
    vec2 dist = m_pTower->GetPosition() - pOtherGameObject->GetPosition();
    float DistanceSquare = dist.x * dist.x + dist.y * dist.y;
    // if enemy step into the range of shoot, return true
    if (DistanceSquare <= (m_DetectRangeForShoot * m_DetectRangeForShoot))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Ball::IsColliding(GameObject* pOtherGameObject)
{
    vec2 dist = m_Position - pOtherGameObject->GetPosition();
    float DistanceSquare = dist.x * dist.x + dist.y * dist.y;
    if (DistanceSquare <= (m_Radius + pOtherGameObject->GetRadius() * m_Radius + pOtherGameObject->GetRadius()))
    {
        return true;
    }
    else return false;
}

void Ball::LaunchProjectile(GameObject* pOtherGameObject)
{
    vec2 dir = pOtherGameObject->GetPosition() - m_Position;
    dir.Normalize();

    m_Angle = atan2(dir.y, dir.x) / PI * 180;
    m_Speed = Ball_SPEED_WHEN_HIT;
}

void Ball::Destroy()
{

    m_Position = vec2(0, 0);
}

void Ball::Respawn()
{
    m_Position = m_pTower->GetPosition();
}


