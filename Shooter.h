#pragma once

#include <iostream>
#include <vector>

#include "components/simple_scene.h"
#include "Player.h"
#include "Enemy.h"

#define OBJECTS_COLOR glm::vec3(0.5f, 1.f, 0.64f)

namespace shooter
{
    class Shooter : public gfxc::SimpleScene
    {
    public:
        struct ViewportSpace
        {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}
            ViewportSpace(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace
        {
            LogicSpace() : x(0), y(0), width(1), height(1) {}
            LogicSpace(float x, float y, float width, float height)
                : x(x), y(y), width(width), height(height) {}
            float x;
            float y;
            float width;
            float height;
        };

        struct Obstacle
        {
            glm::vec2* positions;
            glm::vec2* sizes;
            float* ang;
            char* meshType;
            int nrObstacles;

            Obstacle();
            void createObstacles(glm::vec2*, glm::vec2*, float*, char*, int nr); // creates obstacles at the given positions
            glm::mat3 getMatrix(int index); // return the transform matrix            
        };

        struct Bonus
        {
            std::vector<glm::vec2> positions;
            void createBonus(); // creates Bonuses
        };

    public:
        Shooter();
        ~Shooter();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void DrawScene(glm::mat3 visMatrix, float deltaTimeSeconds);

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

        // Sets the logic space and view space
        // logicSpace: { x, y, width, height }
        // viewSpace: { x, y, width, height }
        glm::mat3 VisualizationTransf2D(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);
        glm::mat3 VisualizationTransf2DUnif(const LogicSpace& logicSpace, const ViewportSpace& viewSpace);

        void SetViewportArea(const ViewportSpace& viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);

    protected:
        ViewportSpace viewSpace;
        LogicSpace logicSpace;
        glm::mat3 modelMatrix, visMatrix;
        
        Player player;
        Enemy enemies;
        Obstacle obstacles;
        Bonus bonus;

        glm::ivec2 resolution;
        float spawnTime;
        float bonusRate;

        float ang;
    };

    float calculateAngle(float, float); // Calculates angle in radians
}// namespace tema
