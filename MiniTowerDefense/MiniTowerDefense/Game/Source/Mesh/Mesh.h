#ifndef __Mesh_H__
#define __Mesh_H__

struct VertexFormat
{
    vec2 m_Pos_Attribute;
    MyColor m_Color_Attribute;
    vec2 m_UV;

    VertexFormat() {}
    VertexFormat(vec2 pos, MyColor color, vec2 uv) :m_Pos_Attribute(pos), m_Color_Attribute(color), m_UV(uv) {}
};



class Mesh
{
protected:
    GLuint m_VBO;
    ShaderProgram* m_pShader;

    GLenum m_PrimitiveType;
    unsigned int m_NumVerts;

    //GLuint m_IBO;
public:
    Mesh();
    virtual ~Mesh();

    void SetShader(ShaderProgram* pShader) { m_pShader = pShader; }

    void Draw(vec2 objectPos, float objectAngle, vec2 objectScale, vec2 camPos, vec2 projScale, GLuint textureHandle, vec2 uvScale, vec2 uvOffset/*,float healthPercent*/);

    void GenerateTriangle();
    void GenerateDiamond();
    void GenerateRect();
    void GenerateTileRect();
    void GenerateCurrentHealthBar();

    void GenerateTexture(float texWidth, float texHeight);

    void GenerateHealthBar();

};

#endif //__Mesh_H__
