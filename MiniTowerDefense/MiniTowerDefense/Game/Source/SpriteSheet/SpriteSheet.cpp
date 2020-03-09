#include "GamePCH.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "SpriteSheet.h"

using namespace std;

SpriteSheet::SpriteSheet() :
    m_SpriteSheet_Height(2048),
    m_SpriteSheet_Width(2048),
    m_JSON_str(0)
{
    //m_TextureHandle = LoadTexture("Data/TowerDefense.png");
    //CreateJSON_Info();
    LoadJSON_Info();
}

SpriteSheet::~SpriteSheet()
{

}



void SpriteSheet::LoadJSON_Info()
{
    float width, height, xPos, yPos;
    string filename;
    m_JSON_str = LoadCompleteFile("Data/TowerDefense.json", 0);
    cJSON* root = cJSON_Parse(m_JSON_str);


    cJSON* FilesArray = cJSON_GetObjectItem(root, "Files");
    int numOfFiles = cJSON_GetArraySize(FilesArray);
    for (int i = 0; i < numOfFiles; i++)
    {
        cJSON* SingleFile = cJSON_GetArrayItem(FilesArray, i);
        //cJSON* GameObject = cJSON_GetObjectItem(SingleFile, "filename");
        //GameObject->valuestring
        Get_JSON_Data(SingleFile, width, height, xPos, yPos, filename);
        SpriteInfo sprite_GameObject(width, height, vec2(xPos, yPos), filename);
        m_SpriteInfoVector.push_back(sprite_GameObject);
    }
    // Save Binary data
    //SaveBinaryData(str);

    delete[](m_JSON_str);
    cJSON_Delete(root);
}



void SpriteSheet::Get_JSON_Data(cJSON* objName, float &w, float &h, float &x, float &y, string& filename)
{
    w = (float)cJSON_GetObjectItem(objName, "origw")->valuedouble;
    h = (float)cJSON_GetObjectItem(objName, "origh")->valuedouble;
    x = (float)cJSON_GetObjectItem(objName, "posx")->valuedouble;
    y = (float)cJSON_GetObjectItem(objName, "posy")->valuedouble;
    filename = cJSON_GetObjectItem(objName, "filename")->valuestring;
}

void SpriteSheet::SaveBinaryData()
{
    ofstream outputstream;
    outputstream.open("TowerDefense.txt", ofstream::out | ofstream::binary);

    if (outputstream.is_open() == true)
    {
        outputstream.write((const char*)m_JSON_str, strlen(m_JSON_str));
        outputstream.close();
    }
}

SpriteInfo* SpriteSheet::GetSpriteInfo(string filename)
{

    for (auto& value : m_SpriteInfoVector)
    {
        if (value.m_Filename == filename)
        {
            return &value;
        }

    }
    return nullptr;
}