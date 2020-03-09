
#include "GamePCH.h"
#include <vector>
#include "Particle System/Particle Renderer.h"
#include "Mesh/Mesh.h"
#include "Particle Renderer.h"

Particle_Renderer::Particle_Renderer(ShaderProgram* shader)
    : m_IBO(0)
    , m_VBO(0)
    , m_pVertexData(0)
    , m_pFourVerts(0)
    , m_NumParticles(0)
    , m_pShader(shader)
    , m_Pos_Attribute(0, 0)
    , m_Size_Attribute(1, 1)
    , m_Color_Attribute(255, 255, 255, 255)
{
    //Generate a IBO and fill it
    glGenBuffers(1, &m_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

    //loop every line
    for (int i = 0; i < NUM_PARTICLES_TOTAL; i++)
    {
        // loop every column
        for (int j = 0; j < 6; j++)
        {
            if (j < 3)
            {
                // first three indices 
                indices[i * 6 + j] = j + i * 4;
            }
            else
            {
                // last three indices
                indices[i * 6 + j] = (j - 2) + i * 4;
            }
        }
    }
    /*unsigned int indices[] =
    {
        0 , 1 , 2 , 1 , 2 , 3 ,
        4 , 5 , 6 , 5 , 6 , 7 ,
        8 , 9 , 10, 9 , 10 ,11 ,


    };*/
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 6, indices, GL_STATIC_DRAW);




    m_pVertexData = new VertexFormat[NUM_VERTICES_VBO];

    //Generate a VBO
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
}

Particle_Renderer::~Particle_Renderer()
{
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_IBO);
    delete[] m_pVertexData;
    delete[] m_pFourVerts;
}

void Particle_Renderer::AddParticle()
{
    vec2 newPos_LeftBot = vec2((m_Pos_Attribute.x - 1.0f)*m_Size_Attribute.x, (m_Pos_Attribute.y - 1.0f)*m_Size_Attribute.y);
    vec2 newPos_LeftTop = vec2((m_Pos_Attribute.x - 1.0f)*m_Size_Attribute.x, (m_Pos_Attribute.y + 1.0f)*m_Size_Attribute.y);
    vec2 newPos_RightBot = vec2((m_Pos_Attribute.x + 1.0f)*m_Size_Attribute.x, (m_Pos_Attribute.y - 1.0f)*m_Size_Attribute.y);
    vec2 newPos_RightTop = vec2((m_Pos_Attribute.x + 1.0f)*m_Size_Attribute.x, (m_Pos_Attribute.y + 1.0f)*m_Size_Attribute.y);

    //fill 4 vertices on the heap
    m_pVertexData[m_NumParticles * 4 + 0] = VertexFormat(newPos_LeftBot, m_Color_Attribute, vec2(0.0f, 0.0f));
    m_pVertexData[m_NumParticles * 4 + 1] = VertexFormat(newPos_LeftTop, m_Color_Attribute, vec2(0.0f, 1.0f));
    m_pVertexData[m_NumParticles * 4 + 2] = VertexFormat(newPos_RightBot, m_Color_Attribute, vec2(1.0f, 0.0f));
    m_pVertexData[m_NumParticles * 4 + 3] = VertexFormat(newPos_RightTop, m_Color_Attribute, vec2(1.0f, 1.0f));

    // increase the count of particles in the list
    m_NumParticles++;
}


void Particle_Renderer::SetUniform1f(GLuint shader, const char* uniformName, float value)
{
    GLint loc = glGetUniformLocation(shader, uniformName);
    if (loc != -1)
    {
        glUniform1f(loc, value);
    }
}



void Particle_Renderer::SetUniform2f(GLuint shader, const char* uniformName, vec2 value)
{
    GLint loc = glGetUniformLocation(shader, uniformName);
    if (loc != -1)
    {
        glUniform2f(loc, value.x, value.y);
    }
}

void Particle_Renderer::SetUniform1i(GLuint shader, const char* uniformName, int value)
{
    GLint loc = glGetUniformLocation(shader, uniformName);
    if (loc != -1)
    {
        glUniform1i(loc, value);
    }
}


void Particle_Renderer::Draw(vec2 objectPos, float objectAngle, vec2 objectScale_World, vec2 cameraPos, vec2 projectionScale, GLuint textureHandle, vec2 uvScale, vec2 uvOffset)
{



    //Draw the primitive

    // draw VBO
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * m_NumParticles * 4, m_pVertexData, GL_STREAM_DRAW);
    // fill VBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

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
    SetUniform2f(shader, "u_ObjectScale", objectScale_World);
    SetUniform1f(shader, "u_ObjectAngleRadians", objectAngle / 180.0f * PI);
    SetUniform2f(shader, "u_ObjectPosition", objectPos);
    SetUniform2f(shader, "u_CameraTranslation", cameraPos * -1);
    SetUniform2f(shader, "u_ProjectionScale", projectionScale);
    SetUniform1i(shader, "u_TextureSampler", textureUnitNumber);
    SetUniform2f(shader, "u_UVScale", uvScale);
    SetUniform2f(shader, "u_UVOffset", uvOffset);

    CheckForGLErrors();

    // Draw.
    glDrawElements(GL_TRIANGLES, m_NumParticles * 6, GL_UNSIGNED_INT, (void*)0);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    CheckForGLErrors();
}


// Get the pos and size for calculate the world pos for each vertex
void Particle_Renderer::SetupParticleProperties(vec2 pos, vec2 size, MyColor color)
{
    m_Pos_Attribute = pos;
    m_Size_Attribute = size;
    m_Color_Attribute = color;
}
