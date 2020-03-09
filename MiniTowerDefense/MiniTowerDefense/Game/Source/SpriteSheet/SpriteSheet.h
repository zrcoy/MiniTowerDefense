#pragma once
#include <vector>
#include <string>

struct SpriteInfo
{
    float m_Width, m_Height;
    vec2 m_Pos;
    std::string m_Filename;

    SpriteInfo(float width, float height, vec2 pos, std::string filename) :
        m_Width(width)
        , m_Height(height)
        , m_Pos(pos)
        , m_Filename(filename)
    {}
};

class SpriteSheet
{
    //GLuint m_TextureHandle;
    float m_SpriteSheet_Width;
    float m_SpriteSheet_Height;
    char* m_JSON_str;


public:
    std::vector<SpriteInfo> m_SpriteInfoVector;

    SpriteSheet();
    ~SpriteSheet();
    //void CreateJSON_Info();
    void LoadJSON_Info();

    //void Fill_JSON_Data(cJSON* objName, float w, float h, float x, float y, const char* filename);
    void Get_JSON_Data(cJSON* objName, float &w, float &h, float &x, float &y, std::string& filename);

    std::vector<SpriteInfo>* GetSpriteInfoVector() { return &m_SpriteInfoVector; }

    float GetSpriteSheetTotalWidth() { return m_SpriteSheet_Width; }

    float GetSpriteSheetTotalHeight() { return m_SpriteSheet_Height; }

    void SaveBinaryData();

    SpriteInfo* GetSpriteInfo(std::string filename);
};