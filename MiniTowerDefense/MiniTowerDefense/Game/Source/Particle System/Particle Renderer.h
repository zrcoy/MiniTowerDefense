#pragma once

#include <vector>

struct VertexFormat;



class Particle_Renderer
{
public:
    const static int NUM_PARTICLES_TOTAL = 50;
    const static int NUM_VERTICES_VBO = NUM_PARTICLES_TOTAL * 4;
    const static int NUM_VERTICES_IBO = NUM_PARTICLES_TOTAL * 6;


    Particle_Renderer(ShaderProgram* shader);
    ~Particle_Renderer();

    void AddParticle();

    void Draw(vec2 objectPos, float objectAngle, vec2 objectScale, vec2 cameraPos, vec2 projectionScale, GLuint textureHandle, vec2 uvScale, vec2 uvOffset);

    void SetUniform1i(GLuint shader, const char* uniformName, int value);

    void SetUniform2f(GLuint shader, const char* uniformName, vec2 value);

    void SetUniform1f(GLuint shader, const char* uniformName, float value);

    int m_NumParticles;

    void SetupParticleProperties(vec2 pos, vec2 size, MyColor color);
private:
    GLuint m_IBO;
    GLuint m_VBO;
    // std::vector<VertexFormat> m_VertexDataVector;
    VertexFormat* m_pVertexData;

    VertexFormat* m_pFourVerts;

    ShaderProgram* m_pShader;

    GLenum m_PrimitiveType;

    unsigned int indices[NUM_VERTICES_IBO];

    vec2 m_Pos_Attribute;
    vec2 m_Size_Attribute;
    MyColor m_Color_Attribute;
};


