#pragma once

struct SpriteInfo;
class GameObject;
class Mesh;
class PlayerController;
class Tilemap;

//struct SingleDigitInfo
//{
//public:
//    Mesh* m_pMesh_Digit;
//    SpriteInfo* m_pSprite_Digit;
//    vec2 m_Pos_Digit;
//    float m_Angle_Digit;
//    vec2 m_Scale_Digit;
//    GLuint m_TextureHandle_Digit;
//    vec2 m_UVScale_Digit;
//    vec2 m_UVOffset_Digit;
//public:
//    SingleDigitInfo(){}
//    SingleDigitInfo(Mesh* mesh, SpriteInfo* sprite, vec2 pos, float angle, vec2 scale, GLuint texture, vec2 uvScale, vec2 uvOffset) 
//        : m_pMesh_Digit(mesh)
//        , m_pSprite_Digit(sprite)
//        , m_Pos_Digit(pos)
//        , m_Angle_Digit(angle)
//        , m_Scale_Digit(scale)
//        , m_TextureHandle_Digit(texture)
//        , m_UVScale_Digit(uvScale)
//        , m_UVOffset_Digit(uvOffset)
//    {}
//    ~SingleDigitInfo(){}
//};


class Score : public GameObject
{
    const static int DIGIT_SCORE = 6;

    SpriteInfo* m_pSpriteForScore;

    //int m_Number;
   // int m_Digit;

    int m_Score;

    int m_IndexOfContainer;

    vec2 m_FixedScreenCamPos_Score;
public:

    // SingleDigitInfo m_NumbersContainer[DIGIT_SCORE];


    Score(GameCore* pGame, Mesh* pMesh, SpriteSheet* pSpriteSheetint, int score, GLuint texture);
    virtual ~Score();

    virtual void Update(float deltatime);
    virtual void Draw(vec2 camPos, vec2 projScale);

    virtual bool IsColliding() override;
    virtual void OnCollision(GameObject* pOtherGameObject) override;


    //void InitNumbersContainer(int score);

    void SetupSprite(int number, int digitNum);

    void SetScore(int score);
};
