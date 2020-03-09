#include "GamePCH.h"

#include "Mesh/Mesh.h"
#include "Mesh.h"

Mesh::Mesh()
{
    m_VBO = 0;
    m_pShader = 0;

    m_PrimitiveType = -1;
    m_NumVerts = 0;

    //m_IBO = 0;
}

Mesh::~Mesh()
{
    glDeleteBuffers(1, &m_VBO);
    // glDeleteBuffers(1, &m_IBO);
}

void SetUniform1f(GLuint shader, const char* uniformName, float value)
{
    GLint loc = glGetUniformLocation(shader, uniformName);
    if (loc != -1)
    {
        glUniform1f(loc, value);
    }
}

void SetUniform2f(GLuint shader, const char* uniformName, vec2 value)
{
    GLint loc = glGetUniformLocation(shader, uniformName);
    if (loc != -1)
    {
        glUniform2f(loc, value.x, value.y);
    }
}

void SetUniform1i(GLuint shader, const char* uniformName, int value)
{
    GLint loc = glGetUniformLocation(shader, uniformName);
    if (loc != -1)
    {
        glUniform1i(loc, value);
    }
}

void Mesh::Draw(vec2 objectPos, float objectAngle, vec2 objectScale, vec2 cameraPos, vec2 projectionScale, GLuint textureHandle, vec2 uvScale, vec2 uvOffset/*,float healthPercent*/)
{

    assert(m_PrimitiveType != -1);
    assert(m_NumVerts != 0);
    assert(m_pShader != 0);
    assert(m_pShader->GetProgram() != 0);
    // Bind buffer and set up attributes.
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);


    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

    //Draw the primitive
    //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (void*)0);



    GLint loc = glGetAttribLocation(m_pShader->GetProgram(), "a_Position");
    if (loc != -1)
    {
        glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, m_Pos_Attribute));
        glEnableVertexAttribArray(loc);
    }

    loc = glGetAttribLocation(m_pShader->GetProgram(), "a_Color");
    if (loc != -1)
    {
        glVertexAttribPointer(loc, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, m_Color_Attribute));
        glEnableVertexAttribArray(loc);
    }

    loc = glGetAttribLocation(m_pShader->GetProgram(), "a_UVCoord");
    if (loc != -1)
    {
        glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)offsetof(VertexFormat, m_UV));
        glEnableVertexAttribArray(loc);
    }

    int textureUnitNumber = 0;
    glActiveTexture(GL_TEXTURE0 + textureUnitNumber);
    glBindTexture(GL_TEXTURE_2D, textureHandle);



    // Set up shader.
    GLuint shader = m_pShader->GetProgram();
    glUseProgram(shader);

    // Set up uniforms.
    SetUniform2f(shader, "u_ObjectScale", objectScale);
    SetUniform1f(shader, "u_ObjectAngleRadians", objectAngle / 180.0f * PI);
    SetUniform2f(shader, "u_ObjectPosition", objectPos);
    SetUniform2f(shader, "u_CameraTranslation", cameraPos * -1);
    SetUniform2f(shader, "u_ProjectionScale", projectionScale);
    SetUniform1i(shader, "u_TextureSampler", textureUnitNumber);
    SetUniform2f(shader, "u_UVScale", uvScale);
    SetUniform2f(shader, "u_UVOffset", uvOffset);
    //SetUniform1f(shader, "u_HealthPercentage", healthPercent);

    CheckForGLErrors();

    // Draw.
    glDrawArrays(m_PrimitiveType, 0, m_NumVerts);

    CheckForGLErrors();
}

//void Mesh::GenerateParticle()
//{
//    VertexFormat vertexAttributes[] = {
//        VertexFormat(vec2(0.0f,  1.0f), MyColor(255, 255, 255, 255),vec2(0.5f,1.0f)),
//        VertexFormat(vec2(-0.5f, -1.0f), MyColor(255, 255, 255, 255) ,vec2(0.0f,0.0f)),
//        VertexFormat(vec2(0.5f, -1.0f), MyColor(255, 255, 255, 255),vec2(1.0f,0.0f)),
//    };
//
//    glGenBuffers(1, &m_IBO);
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
//    unsigned char indices[] = { 0, 1, 2, 1, 2, 3 };
//
//    //indices[0] = VertexFormat(vec2(0.0f, 1.0f), MyColor(255, 255, 255, 255), vec2(0.5f, 1.0f));
//
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned char) * 6, indices, GL_STATIC_DRAW);
//
//
//}

void Mesh::GenerateRect()
{
    // ATM this can only be called once, so we assert if it's called again with a VBO already allocated.
    assert(m_VBO == 0);


    // Vertex info for a diamond.
    VertexFormat vertexAttributes[] = {
        VertexFormat(vec2(-0.5f,  0.0f), MyColor(255, 255, 255, 255),vec2(0.0f,0.0f)),
        VertexFormat(vec2(-0.5f, 1.5f), MyColor(255, 255, 255, 255) ,vec2(0.0f,1.0f)),
        VertexFormat(vec2(0.5f, 0.0f), MyColor(255, 255, 255, 255),vec2(1.0f,0.0f)),
        VertexFormat(vec2(0.5f, 1.5f), MyColor(255, 255, 255, 255),vec2(1.0f,1.0f))
    };

    // Gen and fill buffer with our attributes.
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertexAttributes, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_PrimitiveType = GL_TRIANGLE_STRIP;
    m_NumVerts = 4;

    // Check for errors.
    CheckForGLErrors();
}

void Mesh::GenerateHealthBar()
{
    // ATM this can only be called once, so we assert if it's called again with a VBO already allocated.
    assert(m_VBO == 0);


    // Vertex info for a diamond.
    VertexFormat vertexAttributes[] = {
        VertexFormat(vec2(0.0f,0.0f), MyColor(155, 155, 155, 255),vec2(0.0f,0.0f)),
        VertexFormat(vec2(0.0f,1.0f), MyColor(155, 155, 155, 255) ,vec2(0.0f,1.0f)),
        VertexFormat(vec2(1.0f,0.0f), MyColor(155, 155, 155, 255),vec2(1.0f,0.0f)),
        VertexFormat(vec2(1.0f,1.0f), MyColor(155, 155, 155, 255),vec2(1.0f,1.0f))
    };

    // Gen and fill buffer with our attributes.
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertexAttributes, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_PrimitiveType = GL_TRIANGLE_STRIP;
    m_NumVerts = 4;

    // Check for errors.
    CheckForGLErrors();
}

void Mesh::GenerateCurrentHealthBar()
{
    // ATM this can only be called once, so we assert if it's called again with a VBO already allocated.
    assert(m_VBO == 0);


    // Vertex info for a diamond.
    VertexFormat vertexAttributes[] = {
        VertexFormat(vec2(0.0f,0.0f), MyColor(255, 0, 0, 255),vec2(0.0f,0.0f)),
        VertexFormat(vec2(0.0f,1.0f), MyColor(255, 0, 0, 255) ,vec2(0.0f,1.0f)),
        VertexFormat(vec2(1.0f,0.0f), MyColor(255, 0, 0, 255),vec2(1.0f,0.0f)),
        VertexFormat(vec2(1.0f,1.0f), MyColor(255, 0, 0, 255),vec2(1.0f,1.0f))
    };

    // Gen and fill buffer with our attributes.
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertexAttributes, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_PrimitiveType = GL_TRIANGLE_STRIP;
    m_NumVerts = 4;

    // Check for errors.
    CheckForGLErrors();
}

void Mesh::GenerateTileRect()
{
    // ATM this can only be called once, so we assert if it's called again with a VBO already allocated.
    assert(m_VBO == 0);


    // Vertex info for a diamond.
    VertexFormat vertexAttributes[] = {
        VertexFormat(vec2(0.0f,0.0f), MyColor(0, 255, 0, 255),vec2(0.0f,0.0f)),
        VertexFormat(vec2(0.0f,1.0f), MyColor(0, 255, 0, 255) ,vec2(0.0f,1.0f)),
        VertexFormat(vec2(1.0f,0.0f), MyColor(0, 255, 0, 255),vec2(1.0f,0.0f)),
        VertexFormat(vec2(1.0f,1.0f), MyColor(0, 255, 0, 255),vec2(1.0f,1.0f))
    };

    // Gen and fill buffer with our attributes.
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertexAttributes, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_PrimitiveType = GL_TRIANGLE_STRIP;
    m_NumVerts = 4;

    // Check for errors.
    CheckForGLErrors();
}



void Mesh::GenerateTriangle()
{
    // ATM this can only be called once, so we assert if it's called again with a VBO already allocated.
    assert(m_VBO == 0);


    // Vertex info for a diamond.
    VertexFormat vertexAttributes[] = {
        VertexFormat(vec2(0.0f,  1.0f), MyColor(255, 255, 255, 255),vec2(0.5f,1.0f)),
        VertexFormat(vec2(-0.5f, -1.0f), MyColor(255, 255, 255, 255) ,vec2(0.0f,0.0f)),
        VertexFormat(vec2(0.5f, -1.0f), MyColor(255, 255, 255, 255),vec2(1.0f,0.0f)),
    };

    // Gen and fill buffer with our attributes.
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 3, vertexAttributes, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_PrimitiveType = GL_TRIANGLES;
    m_NumVerts = 3;

    // Check for errors.
    CheckForGLErrors();
}

void Mesh::GenerateDiamond()
{
    // ATM this can only be called once, so we assert if it's called again with a VBO already allocated.
    assert(m_VBO == 0);



    // Vertex position info for a diamond.
    VertexFormat vertexAttributes[] = {
        VertexFormat(vec2(0.0f,  1.0f), MyColor(0, 255,   0, 255) ,vec2(0.5f,1.0f)),
        VertexFormat(vec2(-1.0f,  0.0f), MyColor(0, 255,   0, 255), vec2(0.0f,0.5f)),
        VertexFormat(vec2(1.0f,  0.0f), MyColor(0, 255,   0, 255) ,vec2(1.0f,0.5f)),
        VertexFormat(vec2(0.0f, -1.0f), MyColor(0, 255,   0, 255), vec2(0.5f,0.0f)),
    };

    // Gen and fill buffer with our attributes.
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertexAttributes, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_PrimitiveType = GL_TRIANGLE_STRIP;
    m_NumVerts = 4;

    // Check for errors.
    CheckForGLErrors();
}

void Mesh::GenerateTexture(float texWidth, float texHeight)
{
    assert(m_VBO == 0);


    vec2 bot_left_objPos((-0.5f)*texWidth, 0.0f);
    vec2 bot_right_objPos((0.5f)*texWidth, 0.0f);
    vec2 top_left_objPos((-0.5f)*texWidth, texHeight);
    vec2 top_right_objPos((0.5f)*texWidth, texHeight);

    MyColor color(255, 255, 255, 255);

    vec2 bot_left_uvPos(0.0f, 0.0f);
    vec2 bot_right_uvPos(1.0f, 0.0f);
    vec2 top_left_uvPos(0.0f, 1.0f);
    vec2 top_right_uvPos(1.0f, 1.0f);

    VertexFormat vertsAttributes[] = {
        VertexFormat(bot_left_objPos, color, bot_left_uvPos),
        VertexFormat(bot_right_objPos, color, bot_right_uvPos),
        VertexFormat(top_left_objPos, color, top_left_uvPos),
        VertexFormat(top_right_objPos, color, top_right_uvPos)
    };

    // Generate and fill buffer with our attributes.
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 4, vertsAttributes, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    m_PrimitiveType = GL_TRIANGLE_STRIP;
    m_NumVerts = 4;

    // Check for errors.
    CheckForGLErrors();
}

