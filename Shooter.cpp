#include "lab_m1/Shooter/Shooter.h"


using namespace std;
using namespace shooter;

Shooter::Shooter(): enemies(ENEMY_SIZE), bonusRate(BONUS_RATE) {}
Shooter::~Shooter() {}
void Shooter::FrameEnd() {}
void Shooter::OnKeyPress(int key, int mods) {}
void Shooter::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void Shooter::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

void Shooter::Init()
{
    auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    logicSpace.x = 0;       // logic x
    logicSpace.y = 0;       // logic y
    logicSpace.width = 100;   // logic width
    logicSpace.height = 100;  // logic height

    spawnTime = 0;

    player.nexPosition.x = player.position.x;
    player.nexPosition.y = player.position.y;
    ang = 0;

    // IDEE de incarcat doar 3 meshrui si in enemy si player salvez doar translatiile


    // Create the MAP
    {
        // Add primitives
        AddMeshToList(object2D::CreateCircle("circle", glm::vec3(0), 1.f, glm::vec3(1, 0, 0), true));
        AddMeshToList(object2D::CreateTriangle("triangle", glm::vec3(0), 1.f, glm::vec3(1.f, 1.f, 1.f), true));
        AddMeshToList(object2D::CreateSquare("square", glm::vec3(-0.5f, -0.5f, 0.f), 1.f, OBJECTS_COLOR, true));
        
        uint16_t nr = 30;

        // First 4 are the walls
        char* meshType = new char[] {'s', 's', 's', 's', 's', 's', 'c', 'c', 'c', 'c',
                                     'c', 's', 's', 's', 's', 'c', 's', 'c', 's', 's',
                                     'c', 's', 's', 'c', 'c', 'c', 's', 's', 's', 'c'};

        /*
        float* angObstacles = new float[] {0.f, 0.f, 0.f, 0.f, 10.f, 4.f, 9.f, 9.f, 11.f, 8.f,
                                           4.f, 7.f, 6.f, 11.f, 10.f, 11.f, 6.f, 7.f, 3.f, 8.f,
                                           4.f, 9.f, 9.f, 11.f, 11.f, 4.f, 8.f, 3.f, 2.f, 0.f};
        */
        float* angObstacles = new float[] {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f,
            0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};

        glm::vec2* posObstacles = new glm::vec2[]{ {-200.f, 0.f}, {200.f, 0.f}, {0.f, 200.f}, {0.f, -200.f}, {-2.f, 38.f},
                                                   {-10.f, 139.f}, {-178.f, -179.f}, {22.f, 132.f}, {57.f, 19.f}, {-66.f, -71.f},
                                                   {-105.f, -35.f}, {-100.f, -128.f}, {106.f, 48.f}, {74.f, 9.f}, {135.f, 111.f},
                                                   {38.f, -65}, {-8.f, -184.f}, {-88.f, 110.f}, {-8.f, 181.f}, {-42.f, -46.f},
                                                   {-110.f, 135.f}, {70.f, -7.f}, {53.f, -171.f}, {176.f, 84.f}, {-83.f, 102.f},
                                                   {-166.f, 119.f}, {-197.f, -105.f}, {-110.f, 137.f}, {-32.f, 111.f}, {70.f, 22.f} };

        /*
        glm::vec2* sizeObstacles = new glm::vec2[]{ {10.f, 400.f}, {10.f, 400.f}, {410.f, 10.f}, {410.f, 10.f}, {16.f, 17.f}, 
                                                    {5.f, 14.f}, {14.f, 13.f}, {6.f, 17.f}, {8.f, 20.f}, {4.f, 4.f}, 
                                                    {18.f, 17.f}, {4.f, 40.f}, {18.f, 7.f}, {1.f, 19.f}, {13.f, 15.f},
                                                    {12.f, 20.f}, {3.f, 12.f}, {4.f, 18.f}, {16.f, 8.f}, {13.f, 14.f},
                                                    {14.f, 3.f}, {17.f, 12.f}, {4.f, 2.f}, {6.f, 15.f}, {8.f, 11.f},
                                                    {16.f, 8.f}, {14.f, 6.f}, {9.f, 12.f}, {3.f, 8.f}, {20.f, 12.f} };
        */

        glm::vec2* sizeObstacles = new glm::vec2[]{ {10.f, 400.f}, {10.f, 400.f}, {410.f, 10.f}, {410.f, 10.f}, {10.f, 10.f},
                                                    {10.f, 10.f}, {10.f, 10.f}, {10.f, 10.f}, {10.f, 10.f}, {10.f, 10.f},
                                                    {10.f, 10.f}, {10.f, 10.f}, {10.f, 10.f}, {10.f, 10.f}, {10.f, 10.f},
                                                    {10.f, 10.f}, {10.f, 10.f}, {10.f, 10.f}, {10.f, 10.f}, {10.f, 10.f},
                                                    {10.f, 10.f}, {10.f, 10.f}, {10.f, 10.f}, {10.f, 10.f}, {10.f, 10.f},
                                                    {10.f, 10.f}, {10.f, 10.f}, {10.f, 10.f}, {10.f, 10.f}, {10.f, 10.f} };

        obstacles.createObstacles(posObstacles, sizeObstacles, angObstacles, meshType, nr);
    }


    enemies.createEnemy(glm::vec2(player.position.x, player.position.y));
    AddMeshToList(player.bulletMesh);
    
    {
        AddMeshToList(object2D::CreateSquare("healthBar1", glm::vec3(-0.5f, -0.5f, 0.f), 1.f, glm::vec3(0, 0, 0), true));
        AddMeshToList(object2D::CreateSquare("healthBar2", glm::vec3(-0.5f, -0.5f, 0.f), 1.f, glm::vec3(1, 0, 0), true));
    }
}

glm::mat3 Shooter::VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty, smin;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    if (sx < sy)
        smin = sx;
    else
        smin = sy;
    tx = viewSpace.x - smin * logicSpace.x + (viewSpace.width - smin * logicSpace.width) / 2;
    ty = viewSpace.y - smin * logicSpace.y + (viewSpace.height - smin * logicSpace.height) / 2;

    return glm::transpose(glm::mat3(
        smin, 0.0f, tx,
        0.0f, smin, ty,
        0.0f, 0.0f, 1.0f));
}

glm::mat3 Shooter::VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace)
{
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
        sx, 0.0f, tx,
        0.0f, sy, ty,
        0.0f, 0.0f, 1.0f));
}

void Shooter::SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor, bool clear)
{
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width), (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}

void Shooter::Update(float deltaTimeSeconds)
{
    if (!player.isAlive()) {
        cout << "\n\n\n\n\t\t\t=================GAME OVER!=================     SCORE: " << player.getPoints() << "\n\n" << endl;
        //clear();
        exit(EXIT_SUCCESS);
    }
    resolution = window->GetResolution();

    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0.3f, 0.2f, 1.f), true);

    visMatrix = glm::mat3(1);
    logicSpace.x = player.position.x -logicSpace.width / 2;
    logicSpace.y = player.position.y -logicSpace.height / 2;
    visMatrix *= VisualizationTransf2DUnif(logicSpace, viewSpace);


    for (std::vector<Bullet*>::iterator i = player.bullets.begin(); i != player.bullets.end();) {
        if (!((*i)->Move(deltaTimeSeconds)))
            i = player.bullets.erase(i);
        else
            ++i;
    }

    spawnTime -= deltaTimeSeconds;
    if (spawnTime <= 0) {
        enemies.createEnemy(glm::vec2(player.position.x, player.position.y));
        spawnTime = ENEMY_SPAWN_TIME;
    }

    player.updateFireRate(deltaTimeSeconds);

    if (enemies.touchPlayer(glm::vec2(player.position.x, player.position.y), player.size))
        player.modHealth(0x01);
    
    // Tests if player get bonus health
    {
        for (std::vector<glm::vec2> ::iterator it = bonus.positions.begin();
            it != bonus.positions.end();) {
            if ((player.position.x - it->x) * (player.position.x - it->x)
                + (player.position.y - it->y) * (player.position.y - it->y)
                <= (player.size + ENEMY_SIZE * 0.8f) * (player.size + ENEMY_SIZE * 0.8f)) {
                player.modHealth(0x81);
                it = bonus.positions.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    player.bulletsHitObstacles(obstacles.positions, obstacles.sizes, obstacles.meshType, obstacles.nrObstacles);

    DrawScene(visMatrix, deltaTimeSeconds);
    player.addPoints(enemies.getHit(player.bullets));

    if (bonusRate <= 0.f) {
        bonus.createBonus();
        bonusRate = BONUS_RATE;
    }
    else
        bonusRate -= deltaTimeSeconds;
}

void Shooter::DrawScene(glm::mat3 visMatrix, float deltaTimeSeconds)
{
    // Draw HealthBar
    {
        glm::vec2 healthBarSize = { 50.f, 5.f };
        glm::mat3 matrix = VisualizationTransf2D(logicSpace, viewSpace);

        // Red healthBars
        int playerHealth = player.getHealth();
        for (int i = 0; i < playerHealth; ++i)
            RenderMesh2D(meshes["healthBar2"], shaders["VertexColor"], matrix
                * transform2D::Translate(player.position.x - logicSpace.width / 2.f + ((0.5f + i) * healthBarSize.x / 10.f),
                                                player.position.y + logicSpace.height / 2.f - healthBarSize.y / 2.f)
                * transform2D::Scale(healthBarSize.x / 10.f, healthBarSize.y));

        // Black healthBar
        RenderMesh2D(meshes["healthBar1"], shaders["VertexColor"], matrix 
            * transform2D::Translate(player.position.x - logicSpace.width / 2.f + healthBarSize.x / 2.f,
                                     player.position.y + logicSpace.height / 2.f - healthBarSize.y / 2.f)
            * transform2D::Scale(healthBarSize.x, healthBarSize.y));
    }

    // Draw bonuses
    {
        {
            for (std::vector<glm::vec2> ::iterator it = bonus.positions.begin();
                    it != bonus.positions.end(); ++it) {
                RenderMesh2D(meshes["triangle"], shaders["VertexColor"], visMatrix * transform2D::Translate(it->x, it->y)
                    * transform2D::Scale(ENEMY_SIZE * 1.2f, ENEMY_SIZE * 1.2f)
                    * transform2D::Rotate(PI / 2.f));
                RenderMesh2D(meshes["circle"], shaders["VertexColor"], visMatrix * transform2D::Translate(it->x, it->y)
                    * transform2D::Scale(ENEMY_SIZE * 0.8f, ENEMY_SIZE * 0.8f));
            }
        }
    }

    // Draw Map
    {
        for (int i = 0; i < obstacles.nrObstacles; ++i) {
            switch (obstacles.meshType[i]) {
            case 'c':
                RenderMesh2D(meshes["circle"], shaders["VertexColor"], visMatrix * obstacles.getMatrix(i));
                break;
            case 's':
                RenderMesh2D(meshes["square"], shaders["VertexColor"], visMatrix * obstacles.getMatrix(i));
                break;
            case 't':
                RenderMesh2D(meshes["triangle"], shaders["VertexColor"], visMatrix * obstacles.getMatrix(i));
                break;
            }
        }
    }


    std::vector<Mesh*> meshesVec;
    for (int index = 0; index < enemies.getNumber(); index++) {
        meshesVec = enemies.getMeshes();
        for (auto i : meshesVec)
            RenderMesh2D(i, shaders["VertexColor"], visMatrix * enemies.getMatrix(glm::vec2(player.position.x,
                player.position.y), index, deltaTimeSeconds));
    }

    meshesVec = player.getMeshes();
    std::vector<glm::mat3> matrices = player.getMatrices();
    for (int i = 0; i < meshesVec.size(); ++i) {
        RenderMesh2D(meshesVec[i], shaders["VertexColor"], visMatrix * transform2D::Translate(player.position.x, player.position.y)
            * transform2D::Rotate(ang) * matrices[i]);
    }

    for (int index = 0; index < obstacles.nrObstacles; ++index) {
        RenderMesh2D(meshes["obstacles"], shaders["VertexColor"], visMatrix * obstacles.getMatrix(index));
    }

    for (auto& i : player.bullets) {
        glm::mat3 matrix = glm::mat3(1) * transform2D::Translate(i->position.x, i->position.y)
            *transform2D::Rotate(i->ang);
        RenderMesh2D(meshes["bulletMesh"], shaders["VertexColor"], visMatrix * matrix);
    }

}

void Shooter::OnInputUpdate(float deltaTime, int mods)
{
    
        if (window->KeyHold(GLFW_KEY_W)) {
            //y = player.position.y;
            //player.position.y += PLAYER_SPEED * deltaTime;
            player.nexPosition.y += PLAYER_SPEED * deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_S)) {
            //y = player.position.y;
            //player.position.y -= PLAYER_SPEED * deltaTime;
            player.nexPosition.y -= PLAYER_SPEED * deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_D)) {
            //x = player.position.x;
            //player.position.x += PLAYER_SPEED * deltaTime;
            player.nexPosition.x += PLAYER_SPEED * deltaTime;
        }
        if (window->KeyHold(GLFW_KEY_A)) {
            //x = player.position.x;
            //player.position.x -= PLAYER_SPEED * deltaTime;
            player.nexPosition.x -= PLAYER_SPEED * deltaTime;
        }
    

    if (!player.playerColision(obstacles.positions, obstacles.sizes, obstacles.meshType, obstacles.nrObstacles)) {
        player.position.x = player.nexPosition.x;
        player.position.y = player.nexPosition.y;
    }
    else {
        player.nexPosition.x = player.position.x;
        player.nexPosition.y = player.position.y;
    }

}

void Shooter::OnKeyRelease(int key, int mods)
{
    // Add key release event
}

void Shooter::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    
    float Dx = (float)mouseX - resolution.x / 2;
    float Dy = (resolution.y - (float)mouseY) - resolution.y / 2;
    ang = calculateAngle(Dx, Dy);
}

void Shooter::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    if (button == 1)
        player.Shoot(glm::vec2(player.position.x, player.position.y), ang);
}

void Shooter::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    std::cout << "Health: " << player.getHealth() << "\nPoints: " << player.getPoints() << "\n" << endl;
}

Shooter::Obstacle::Obstacle(): nrObstacles(0) {}

void Shooter::Obstacle::createObstacles(glm::vec2* posObstacles, glm::vec2* sizeObstacles, float* ang, char* meshType, int nr) {
    positions = posObstacles;
    sizes = sizeObstacles;
    this->ang = ang;
    this->meshType = meshType;
    nrObstacles = nr;
}

glm::mat3 Shooter::Obstacle::getMatrix(int index) {
    return transform2D::Translate(positions[index].x, positions[index].y) * transform2D::Scale(sizes[index].x, sizes[index].y) * transform2D::Rotate(ang[index]);
}

float shooter::calculateAngle(float Dx, float Dy) {
    if (Dx == 0)
        return ((Dy > 0) ? 0.5f * PI : -0.5f * PI);
    else {
        if (Dx > 0)
            return (float)atan(Dy / Dx);
        else
            return ((float)atan(Dy / Dx) + PI);
    }
}

void Shooter::Bonus::createBonus() {
    positions.push_back(glm::vec2((rand() % 380) - 200, (rand() % 380) - 200));
}