#pragma once

#include <vector>

struct VertexFormat;
class Particle_Renderer;
class Boss;

struct Particle
{
    vec2 m_Pos;
    vec2 m_Size;
    MyColor m_Color;
    float m_TimeAlive;
    vec2 m_Velocity;
public:
    Particle() :m_Pos(0, 0), m_Size(1, 1), m_Color(0, 0, 0, 255), m_TimeAlive(5.0f), m_Velocity(0, 0) {}
    Particle(vec2 pos, vec2 size, float timeAlive, MyColor color) :m_Pos(pos), m_Size(size), m_TimeAlive(timeAlive), m_Color(color)
    {
        m_Velocity = vec2((float)(rand() % 4 + 1),(float)( rand() % 4 + 1));
        //m_Velocity = vec2(0, 1.0f);
        //m_Color = MyColor(rand() % 256, rand() % 256, rand() % 256, 255);

    }
    void Update(float DeltaTime)
    {
        m_Pos += m_Velocity * DeltaTime;
    }
};

class Particle_Emitter
{
public:
    Particle_Emitter(ShaderProgram* shader);
    ~Particle_Emitter();

    void Update(float DeltaTime);

    void Draw(vec2 camPos, vec2 projScale);

    void SetDrawFlag(bool flag);

    bool GetDrawFlag();

private:
    std::vector<Particle*> m_VertexInActiveList;
    std::vector<Particle*> m_VertexActiveList;

    float m_Timer;

    Particle* m_Particle;

    Particle_Renderer* m_PR;

    int m_Num_InitInActiveParticle = 40;

    ShaderProgram* m_pShader;

    bool m_drawFlag;



    //vec2 m_Pos;
    //vec2 m_Size;
    //MyColor m_Color;
    //float m_TimeAlive;
    //vec2 m_Velocity;
};


