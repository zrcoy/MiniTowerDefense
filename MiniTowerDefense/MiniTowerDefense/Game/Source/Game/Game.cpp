#include "GamePCH.h"
#include <vector>
#include "Game/Game.h"
#include "Mesh/Mesh.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Player.h"
#include "GameObjects/Ball.h"
#include "GameObjects/PlayerController.h"
#include "GameObjects/Boss/Boss.h"
#include "SpriteSheet/SpriteSheet.h"
#include "GameObjects/Cursor.h"
#include "GameObjects/Tower.h"
#include "Tilemap/Tilemap.h"
#include "Score/Score.h"
#include "Particle System/Particle Emitter.h"
#include "GameObjects/HealthBar.h"

typedef float(*MathOp)(float value1, float value2);

float Add(float value1, float value2)
{
    return value1 + value2;
}
float Sub(float value1, float value2)
{
    return value1 - value2;
}

Game::Game(Framework* pFramework)
    : GameCore(pFramework, new EventManager())
{
    //char* str;

    //// Create JSON stuff
    //{
    //    cJSON* root = cJSON_CreateObject();

    //    cJSON* gameobject = cJSON_CreateObject();
    //    cJSON_AddItemToObject(root, "GameObject", gameobject);

    //    cJSON_AddNumberToObject(gameobject, "x", 10.5f);
    //    cJSON_AddNumberToObject(gameobject, "y", -2.9f);

    //    str = cJSON_Print(root);

    //    cJSON_Delete(root);
    //}

    //// Load JSON stuff
    //{
    //    cJSON* root = cJSON_Parse(str);

    //    cJSON* gameobject = cJSON_GetObjectItem(root, "GameObject");

    //    float x= (float)cJSON_GetObjectItem(gameobject, "x")->valuedouble;
    //    float y = (float)cJSON_GetObjectItem(gameobject, "y")->valuedouble;

    //    cJSON_Delete(root);
    //}

    //free(str);

    MathOp pMathFunc = &Sub;

    float result = pMathFunc(1, 2);

    OutputMessage("The result is: %0.1f\n", result);

    int bp = 0;
    m_Score = 0;

    m_pShader = 0;
    m_pMeshTriangle = 0;
    m_pMeshDiamond = 0;
    m_pMeshRect = 0;
    m_pMeshTileRect = 0;
    m_pMeshHealthBar = 0;

    m_pSpriteSheet = 0;

    m_pPlayer = 0;
    m_pBall = 0;
    m_pBoss = 0;
    m_pCursor = 0;
    m_pTower = 0;
    m_pTilemap = 0;
    m_pScore = 0;
    m_pHealthBar = 0;
    m_pMeshCurrentHealthBar = 0;

    m_pPlayerController = 0;

    m_TextureHandle = 0;

    m_DrawTowerOrNot = false;

    m_pParticle_Emitter = 0;

    m_TotalHealthForEnemy = 0;

    m_WinFlag = false;

    m_Timer_RespawnProjectile = 0;
    m_FireRate = 1.5f;

    m_RespawnTimerFlag = false;
    // m_DrawProjectileOrNot = false;
}

Game::~Game()
{
    delete m_pPlayerController;

    delete m_pPlayer;
    delete m_pBall;
    delete m_pBoss;
    delete m_pCursor;
    delete m_pTower;
    delete m_pTilemap;
    delete m_pScore;
    delete m_pHealthBar;
    delete m_pMeshCurrentHealthBar;

    m_pTowersVector.clear();
    //m_pScoreVector.clear();
    m_pBallVector.clear();
    m_pBossVector.clear();
    m_HealthBarVector.clear();
    m_ParticleEmitVector.clear();

    delete m_pMeshTriangle;
    delete m_pMeshDiamond;
    delete m_pMeshRect;
    delete m_pMeshTileRect;
    delete m_pMeshHealthBar;

    delete m_pParticle_Emitter;

    m_pSpriteSheet->m_SpriteInfoVector.clear();
    delete m_pSpriteSheet;

    delete m_pShader;

}

void Game::OnSurfaceChanged(unsigned int width, unsigned int height)
{
    // Set OpenGL to draw to the entire window.
    glViewport(0, 0, width, height);
}

void Game::LoadContent()
{
#if WIN32
    // Turn on v-sync.
    wglSwapInterval(1);
#endif

    // Turn on depth buffer testing.
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Turn on alpha blending.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Create our shaders.
    m_pShader = new ShaderProgram("Data/Shaders/Moving.vert", "Data/Shaders/Moving.frag");
    m_pColorShader = new ShaderProgram("Data/Shaders/Color.vert", "Data/Shaders/Color.frag");

    // Create out meshes.
    m_pMeshTriangle = new Mesh();
    m_pMeshTriangle->SetShader(m_pShader);
    m_pMeshTriangle->GenerateTriangle();

    m_pMeshDiamond = new Mesh();
    m_pMeshDiamond->SetShader(m_pShader);
    m_pMeshDiamond->GenerateDiamond();

    m_pMeshRect = new Mesh();
    m_pMeshRect->SetShader(m_pShader);
    m_pMeshRect->GenerateRect();

    m_pMeshTileRect = new Mesh();
    m_pMeshTileRect->SetShader(m_pShader);
    m_pMeshTileRect->GenerateTileRect();

    m_pMeshHealthBar = new Mesh();
    m_pMeshHealthBar->SetShader(m_pColorShader);
    m_pMeshHealthBar->GenerateHealthBar();

    m_pMeshCurrentHealthBar = new Mesh();
    m_pMeshCurrentHealthBar->SetShader(m_pColorShader);
    m_pMeshCurrentHealthBar->GenerateCurrentHealthBar();

    // Load SpriteSheet
    m_pSpriteSheet = new SpriteSheet();

    m_TextureHandle = LoadTexture("Data/TowerDefense.png");
    //m_pSpriteSheet->CreateJSON_Info();
    //m_pSpriteSheet->LoadJSON_Info();

    // Create Tilemap
    m_pTilemap = new Tilemap();
    m_pTilemap->SetSpriteSheet(m_pSpriteSheet);
    m_pTilemap->SetMesh(m_pMeshTileRect);
    m_pTilemap->Create();
    m_pTilemap->SetTexture(m_TextureHandle);



    // Create Score
    //m_pScore = new Score(this,m_pMeshTileRect,m_pSpriteSheet,digit,);
    //m_pScore->SetTexture(m_TextureHandle);
    m_pScore = new Score(this, m_pMeshTileRect, m_pSpriteSheet, m_Score, m_TextureHandle);

    // Create our GameObjects.
    m_pPlayer = new Player(this, m_pMeshRect, m_pSpriteSheet);
    m_pPlayer->SetTexture(m_TextureHandle);
    m_pPlayer->setTilemap(m_pTilemap);

    for (int i = 0; i < NumOfParticleEmitter; i++)
    {
        m_pParticle_Emitter = new Particle_Emitter(m_pColorShader);
        m_ParticleEmitVector.push_back(m_pParticle_Emitter);
    }

    for (int i = 0; i < ENEMY_AMOUNT; i++)
    {
        m_pBoss = new Boss(this, m_pMeshRect, m_pSpriteSheet);
        m_pBoss->SetTexture(m_TextureHandle);
        m_pBoss->SetTilemap(m_pTilemap);
        m_pBoss->SetupPath();
        m_pBossVector.push_back(m_pBoss);

        // Generate a health bar relative a boss
        m_pHealthBar = new HealthBar(this, m_pMeshHealthBar, m_pSpriteSheet, m_pBoss, m_pMeshCurrentHealthBar);
        m_HealthBarVector.push_back(m_pHealthBar);
    }


    //m_pHealthBar = new HealthBar(this, m_pMeshHealthBar, m_pSpriteSheet, m_pBoss, m_pMeshCurrentHealthBar);

    m_pCursor = new Cursor(this, m_pMeshRect, m_pSpriteSheet);
    m_pCursor->SetPlayer(m_pPlayer);
    m_pCursor->SetTexture(m_TextureHandle);

    /* m_pTower = new Tower(this, m_pMeshRect, m_pSpriteSheet);
     m_pTower->SetCurrentTower(m_pCursor->GetCurrentTower());*/

     // Assign our controllers.
    m_pPlayerController = new PlayerController();
    m_pPlayer->SetPlayerController(m_pPlayerController);
    m_pCursor->SetPlayerController(m_pPlayerController);

    // load particle emitter
   // m_pParticle_Emitter = new Particle_Emitter(m_pColorShader);

    CheckForGLErrors();
}

void Game::OnEvent(Event* pEvent)
{
    m_pPlayerController->OnEvent(pEvent);
}

void Game::Update(float deltatime)
{
    m_pPlayer->Update(deltatime);

    for (auto boss : m_pBossVector)
    {
        boss->Update(deltatime);
    }
    //m_pBoss->Update(deltatime);
    for (auto healthBar : m_HealthBarVector)
    {
        healthBar->Update(deltatime);
    }

    //m_pHealthBar->Update(deltatime);


    m_pCursor->Update(deltatime);

    //Handle mouse press that spawn a tower
    if (m_pPlayerController)
    {
        if (m_pPlayerController->IsMousePressed())
        {
            m_DrawTowerOrNot = true;
            m_pTower = new Tower(this, m_pMeshRect, m_pSpriteSheet);
            m_pTower->SetTexture(m_TextureHandle);
            m_pTower->SetSprite(m_pCursor->GetSprite());
            m_pTower->ExtractInfoFromSprite(m_pTower->GetSprite());
            m_pTower->SetPosition(m_pCursor->GetPosition());
            m_pTowersVector.push_back(m_pTower);


            // the last number in the ball constructor is the kind of projectile
            int kindOfBall = 0;
            if (m_pTower->GetSprite() == m_pSpriteSheet->GetSpriteInfo("TD_Tower_1.png"))
            {
                kindOfBall = 0;
            }
            else if (m_pTower->GetSprite() == m_pSpriteSheet->GetSpriteInfo("TD_Tower_2.png"))
            {
                kindOfBall = 1;
            }
            else if (m_pTower->GetSprite() == m_pSpriteSheet->GetSpriteInfo("TD_Tower_3.png"))
            {
                kindOfBall = 2;
            }
            else if (m_pTower->GetSprite() == m_pSpriteSheet->GetSpriteInfo("TD_Tower_4.png"))
            {
                kindOfBall = 3;
            }
            // need to initialize each projectile with each tower's position, if enemy is close to certain range, launch the ball
            m_pBall = new Ball(this, m_pMeshRect, m_pSpriteSheet, m_pTower, kindOfBall);
            m_pBall->SetTexture(m_TextureHandle);
            m_pBall->SetBallDrawBool(true);
            m_pBallVector.push_back(m_pBall);
        }

        // Handle save JSON file
        if (m_pPlayerController->IsSaveJSONPressed())
        {
            m_pSpriteSheet->SaveBinaryData();
        }

    }
    for (auto value : m_pBallVector)
    {
        if (value->GetBallDrawBool() == true)
        {
            value->Update(deltatime);
        }
    }

    for (auto boss : m_pBossVector)
    {
        m_TotalHealthForEnemy += (int)boss->GetCurrentHealth();
    }

    // win flag check
    if (m_Score==ENEMY_AMOUNT)
    {
        m_WinFlag = true;
    }

    if (m_WinFlag)
    {
        for (auto particle : m_ParticleEmitVector)
        {
            particle->Update(deltatime);
        }

    }

    //Update Particle emitter
    //m_pParticle_Emitter->Update(deltatime);

    //Update Score 
    m_pScore->SetScore(m_Score);


    CheckForCollisions(deltatime);
}

void Game::Draw()
{
    // Setup the values we will clear to, then actually clear the color and depth buffers.
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f); // dark blue
#if WIN32
    glClearDepth(1); // 1 is maximum depth
#endif
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    vec2 halfWorldSize = vec2(Game_WORLD_SIZE_X / 2.0f, Game_WORLD_SIZE_Y / 2.0f);


    // Actual game world projection scale for the viewport
    glViewport(0, 0, 600, 600);

    vec2 projection = vec2(1 / 20.0f, 1 / 20.0f);

    // Draw tile map
    m_pTilemap->Draw(m_pPlayer->GetPosition(), projection);

    // Draw our game objects.

    //m_pScore->Draw(m_pPlayer->GetPosition(), projection);

    m_pPlayer->Draw(m_pPlayer->GetPosition(), projection);


    for (auto boss : m_pBossVector)
    {
        if (boss->GetDrawable())
        {
            //m_pHealthBar->Draw(m_pPlayer->GetPosition(), projection);
            boss->Draw(m_pPlayer->GetPosition(), projection);
        }
    }

    for (auto healthBar : m_HealthBarVector)
    {
        if (healthBar->GetRelativeBoss()->GetDrawable())
        {
            healthBar->Draw(m_pPlayer->GetPosition(), projection);
            //boss->Draw(m_pPlayer->GetPosition(), projection);
        }
    }

    m_pCursor->Draw(m_pPlayer->GetPosition(), projection);

    for (auto tower : m_pTowersVector)
    {
        tower->Draw(m_pPlayer->GetPosition(), projection);
    }

    /*for (auto score : m_pScoreVector)
    {
        score->Draw(m_pPlayer->GetPosition(), projection);
    }*/
    m_pScore->Draw(m_pPlayer->GetPosition(), projection);


    for (auto projectile : m_pBallVector)
    {
        if (projectile->GetBallDrawBool() == true)
        {
            projectile->Draw(m_pPlayer->GetPosition(), projection);
        }
    }
    if (m_WinFlag)
    {
        for (auto particleEmit : m_ParticleEmitVector)
        {
            particleEmit->Draw(m_pPlayer->GetPosition(), projection);
        }

    }
   // m_pParticle_Emitter->Draw(m_pPlayer->GetPosition(), projection);


    // mini map
    glViewport(0, 0, 150, 150);
    m_pPlayer->Draw(halfWorldSize, 1 / halfWorldSize);
    //m_pBall->Draw(halfWorldSize, 1 / halfWorldSize);
    m_pBoss->Draw(halfWorldSize, 1 / halfWorldSize);

    for (auto tower : m_pTowersVector)
    {
        tower->Draw(halfWorldSize, 1 / halfWorldSize);
    }

    CheckForGLErrors();
}

void Game::CheckForCollisions(float DeltaTime)
{
    if (m_RespawnTimerFlag)
    {
        m_Timer_RespawnProjectile += DeltaTime;
    }

    m_pPlayer->OnCollision(m_pTower);

    if (!m_pBallVector.empty())
        Ball* pBall = m_pBallVector.back();

    for (auto projectile : m_pBallVector)
    {
        if (projectile->GetBallDrawBool() == true)
        {
            // loop for each boss
            for (auto boss : m_pBossVector)
            {
                // if the boss is stepping into the range of shooting
                if (projectile->IsInRangeOfShooting(boss))
                {
                    // shoot the boss
                    projectile->OnCollision(boss);
                }

                //if projectile hit the boss
                if (projectile->IsColliding(boss))
                {
                    // don't draw this projectile
                    projectile->SetBallDrawBool(false);

                    projectile->Destroy();

                    //m_RespawnTimerFlag = true;
                    //if (m_Timer_RespawnProjectile >= m_FireRate)
                    //{
                    //    projectile->SetBallDrawBool(true);
                    //    projectile->Respawn();
                    //    projectile->OnCollision(boss);
                    //    m_Timer_RespawnProjectile = 0;
                    //    //m_RespawnTimerFlag = false;
                    //}
                    projectile->GetRelativeTower()->Destroy();

                    if (boss->GetCurrentHealth() > 0)
                    {

                        boss->DecreaseHealth();
                    }

                    if (boss->GetCurrentHealth() <= 0)
                    {
                        boss->Destroy();
                        m_Score += 1;
                    }
                }
            }

        }
    }

}
