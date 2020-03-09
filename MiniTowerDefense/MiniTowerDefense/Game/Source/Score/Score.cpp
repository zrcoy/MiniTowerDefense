#include "GamePCH.h"

#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "Score/Score.h"
#include "SpriteSheet/SpriteSheet.h"


Score::Score(GameCore* pGame, Mesh* pMesh, SpriteSheet* pSpriteSheet, int score, GLuint texture)
    : GameObject(pGame, pMesh, pSpriteSheet)
    , m_pSpriteForScore(0)
    , m_IndexOfContainer(0)
    , m_FixedScreenCamPos_Score(0, 0)
    , m_Score(score)

{
    SetTexture(texture);

}

Score::~Score()
{
}

void Score::Update(float deltatime)
{

}

//void Score::Draw(vec2 camPos, vec2 projScale)
//{
//    
//    m_pMesh->Draw(m_Position, m_Angle, vec2(2, 2), m_FixedScreenCamPos_Score, projScale, m_TextureHandle, m_UVScale, m_UVOffset);
//
//    int bp = 0;
//}



bool Score::IsColliding()
{
    return false;
}

void Score::OnCollision(GameObject* pOtherGameObject)
{

}

void Score::Draw(vec2 camPos, vec2 projScale)
{
    int score_ref = m_Score;
    int digit = 0;

    // make sure if score is zero still has 1 digit
    if (score_ref == 0)
    {
        digit = 1;
    }

    //Get how many digit
    while (score_ref != 0)
    {
        score_ref /= 10;
        digit++;

    }


    for (int i = 1; i <= digit; i++)
    {
        // Get relative value from the last digit to the left most digit, store it to number
        int number = m_Score % 10;
        m_Score /= 10;
        // Get the current digit and current number
        SetupSprite(number, i);
        ExtractInfoFromSprite(m_Sprite);
        m_pMesh->Draw(m_Position, m_Angle, vec2(2, 2), m_FixedScreenCamPos_Score, projScale, m_TextureHandle, m_UVScale, m_UVOffset);
    }





}

void Score::SetupSprite(int number, int digitNum)
{
    //which number sprite is drawing now
    if (number == 0)
    {
        m_Sprite = m_pSpriteSheet->GetSpriteInfo("Number0.png");
    }
    else if (number == 1)
    {
        m_Sprite = m_pSpriteSheet->GetSpriteInfo("Number1.png");
    }
    else if (number == 2)
    {
        m_Sprite = m_pSpriteSheet->GetSpriteInfo("Number2.png");
    }
    else if (number == 3)
    {
        m_Sprite = m_pSpriteSheet->GetSpriteInfo("Number3.png");
    }
    else if (number == 4)
    {
        m_Sprite = m_pSpriteSheet->GetSpriteInfo("Number4.png");
    }
    else if (number == 5)
    {
        m_Sprite = m_pSpriteSheet->GetSpriteInfo("Number5.png");
    }
    else if (number == 6)
    {
        m_Sprite = m_pSpriteSheet->GetSpriteInfo("Number6.png");
    }
    else if (number == 7)
    {
        m_Sprite = m_pSpriteSheet->GetSpriteInfo("Number7.png");
    }
    else if (number == 8)
    {
        m_Sprite = m_pSpriteSheet->GetSpriteInfo("Number8.png");
    }
    else if (number == 9)
    {
        m_Sprite = m_pSpriteSheet->GetSpriteInfo("Number9.png");
    }

    // Set up the screen pos for the score
    if (digitNum == 1)
    {
        m_FixedScreenCamPos_Score = vec2(10.0f, -15.0f);
    }
    else if (digitNum == 2)
    {
        m_FixedScreenCamPos_Score = vec2(12.0f, -15.0f);
    }
    else if (digitNum == 3)
    {
        m_FixedScreenCamPos_Score = vec2(14.0f, -15.0f);
    }
    else if (digitNum == 4)
    {
        m_FixedScreenCamPos_Score = vec2(16.0f, -15.0f);
    }
    else if (digitNum == 5)
    {
        m_FixedScreenCamPos_Score = vec2(18.0f, -15.0f);
    }
    else if (digitNum == 6)
    {
        m_FixedScreenCamPos_Score = vec2(20.0f, -15.0f);
    }
}

void Score::SetScore(int score)
{
    m_Score = score;
}

