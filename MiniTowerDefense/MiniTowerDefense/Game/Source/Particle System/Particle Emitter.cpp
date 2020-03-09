
#include "GamePCH.h"

#include <vector>
#include "Particle Renderer.h"
#include "Particle Emitter.h"
#include "Game/Game.h"


Particle_Emitter::Particle_Emitter(ShaderProgram* shader) :
    m_pShader(shader)
    , m_Particle(0)
    //, m_Velocity(0, 0)
    //, m_Pos(0, 0)
    //, m_Size(1, 1)
    //, m_Color(255, 255, 255, 255)
    //, m_TimeAlive(3.0f)
    , m_PR(0)
    , m_Timer(0)

    , m_drawFlag(false)
{
    //m_VertexInActiveList.push_back()

     // Get the world width and height.
    float worldWidth = Game::Game_WORLD_SIZE_X;
    float worldHeight = Game::Game_WORLD_SIZE_Y;

    // Initialize particle renderer
    m_PR = new Particle_Renderer(shader);

    // Allocate a lot of particle objects
    for (int i = 0; i < m_Num_InitInActiveParticle; i++)
    {
        float randX_Ratio = (rand() % 101) / 100.0f;
        float randY_Ratio = (rand() % 101) / 100.0f;
        vec2 randPos = vec2(worldWidth * randX_Ratio, worldHeight * randY_Ratio);
        vec2 randSize = vec2((rand() % 3 + 1) / 5.0f, (rand() % 3 + 1) / 5.0f);
        MyColor randColor = MyColor(rand() % 256, rand() % 256, rand() % 256, 255);
        vec2 pos = vec2(10, 10);
        vec2 size = vec2(0.5, 0.5);
        float timeAlive = 3.0f;

        m_Particle = new Particle(randPos, randSize, timeAlive, randColor);
        m_VertexInActiveList.push_back(m_Particle);
    }

    // Active last particle
    m_VertexActiveList.push_back(m_VertexInActiveList.back());
    // Deactivate the last particle
    m_VertexInActiveList.pop_back();
    //m_Velocity = vec2(rand() % 10 + 1, rand() % 10 + 1);

}

Particle_Emitter::~Particle_Emitter()
{
    delete m_Particle;
    m_VertexInActiveList.clear();
    m_VertexActiveList.clear();
    delete m_PR;
}

void Particle_Emitter::Update(float DeltaTime)
{
    m_Timer += DeltaTime;

    for (int i = 0; i < 30; i++)
    {
        // make sure some particles exist in InActive list
        if (!m_VertexInActiveList.empty())
        {
            //Active last particle
            m_VertexActiveList.push_back(m_VertexInActiveList.back());

            // Deactivate the last particle
            m_VertexInActiveList.pop_back();
        }

    }

    //After every 5 seconds, activate and deactivate some particles
    //if (m_Timer > 1.0f)
    {
        // exchange 3 particles between active and inactive list for now 
        //for (int i = 0; i < 20; i++)
        //{
        //    if (!m_VertexInActiveList.empty())
        //    {
        //         //Active last particle
        //        m_VertexActiveList.push_back(m_VertexInActiveList.back());

        //        // Deactivate the last particle
        //        m_VertexInActiveList.pop_back();
        //    }

        //}

         // Get the world width and height.
        float worldWidth = Game::Game_WORLD_SIZE_X;
        float worldHeight = Game::Game_WORLD_SIZE_Y;

        for (auto activeParticle : m_VertexActiveList)
        {
            // Vertical bounds check
            if (activeParticle->m_Pos.y > worldHeight)
            {
                m_VertexActiveList.erase(m_VertexActiveList.begin());
            }
            else if (activeParticle->m_Pos.y < 0.0f)
            {
                m_VertexActiveList.erase(m_VertexActiveList.begin());
            }

            // Horizontal bounds check.
            if (activeParticle->m_Pos.x < 0.0f)
            {
                m_VertexActiveList.erase(m_VertexActiveList.begin());
            }
            else if (activeParticle->m_Pos.x > worldWidth)
            {
                m_VertexActiveList.erase(m_VertexActiveList.begin());
            }


        }



        m_Timer = 0;
    }

    // if (m_flag)
    {

        // Give those particles base values such as position and velocity, color, size, etc
        for (auto value : m_VertexActiveList)
        {
            value->Update(DeltaTime);
            //value->m_Pos += value->m_Velocity*DeltaTime;
            //value->m_Pos.y += 2.0f * DeltaTime;
            // store the vertex world position and pass it to the renderer
            //m_PR->SetupParticleProperties(value->m_Pos, value->m_Size, value->m_Color);
            m_PR->SetupParticleProperties(vec2(0, 0), value->m_Size, value->m_Color);

            // call addParticle for each active particle
            m_PR->AddParticle();

            m_PR->m_NumParticles = 1;
        }


    }

    // based on some reason, deactivate them
    //m_PR->m_NumParticles = 0;



}

void Particle_Emitter::Draw(vec2 camPos, vec2 projScale)
{

    for (auto value : m_VertexActiveList)
    {
        m_PR->Draw(value->m_Pos, 0.0f, value->m_Size, camPos, projScale, 0, vec2(0, 0), vec2(0, 0));
    }

}

bool Particle_Emitter::GetDrawFlag()
{
    return m_drawFlag;
}

void Particle_Emitter::SetDrawFlag(bool flag)
{
    m_drawFlag = flag;
}

