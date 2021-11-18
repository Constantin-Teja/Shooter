#include "Player.h"

Player::Player(glm::vec3 position, float size) : size(PLAYER_SIZE), position(position), points(0), health(10), fireRate(0.f) {
    bulletMesh = object2D::CreateSquare("bulletMesh", glm::vec3(-BULLET_SIZE / 2, -BULLET_SIZE / 2, 0), BULLET_SIZE, glm::vec3(0, 0, 0), true);

    //hatch
    meshes.push_back(object2D::CreateSquare("hatch3", glm::vec3(-1.f, -1.f, 0), 2.f, glm::vec3(0.f, 0.f, 0.f), true));
    matrices.push_back(transform2D::Translate(1.8f * size, 0.f) * transform2D::Scale(0.3 * size, 0.27f * size));

    //hatch
    meshes.push_back(object2D::CreateSquare("hatch2", glm::vec3(-1.f, -1.f, 0), 2.f, glm::vec3(0.75f, 0.f, 0.f), true));
    matrices.push_back(transform2D::Translate(size, 0.f) * transform2D::Scale(size, 0.13f * size));

    //hatch
    meshes.push_back(object2D::CreateCircle("hatch1", glm::vec3(0), 2.f, glm::vec3(0.75f, 0.f, 0.f), true));
    matrices.push_back(transform2D::Scale(size * 0.33f, 0.23 * size));

    //triangle body up
    meshes.push_back(object2D::CreateTriangle("playerBody2", glm::vec3(0), 2.f, glm::vec3(0.f, 0.3f, 0.f), true));
    matrices.push_back(transform2D::Translate(size * 1.22f, 0.f) * transform2D::Scale(size * 0.22f, size / 1.3f));

    //rectangle body
    meshes.push_back(object2D::CreateSquare("playerBody1", glm::vec3(-1.f, -1.f, 0), 2.f, glm::vec3(0.f, 0.3f, 0.f), true));
    matrices.push_back(transform2D::Scale(size, size / 1.3f));

    //tracks
    meshes.push_back(object2D::CreateSquare("playerTracks", glm::vec3(-1.f, -1.f, 0), 2.f, glm::vec3(0.f, 0.f, 0.f), true));
    matrices.push_back(transform2D::Scale(size * 0.8, size));
}

bool Player::playerColision(glm::vec2* posObstacles, glm::vec2* sizeObstacles, char* meshType, int nr) {
    for (int index = 0; index < nr; ++index) {
        if (meshType[index] == 's') {
            if ((abs(nexPosition.x - posObstacles[index].x) < 1.2f * size + sizeObstacles[index].x / 2)
                && (abs(nexPosition.y - posObstacles[index].y) < 1.2f * size + sizeObstacles[index].y / 2))
                return true;
        }
        else
            if ((nexPosition.x - posObstacles[index].x) * (nexPosition.x - posObstacles[index].x)
                + (nexPosition.y - posObstacles[index].y) * (nexPosition.y - posObstacles[index].y)
                <= (size + sizeObstacles[index].y) * (size + sizeObstacles[index].y))
                return true;
    }
    return false;
}

Bullet::Bullet(glm::vec2 position, float ang): position(position), ang(ang), range(BULLET_RANGE) {}

void Player::Shoot(glm::vec2 position, float ang) {
    if (fireRate <= 0) {
        bullets.push_back(new Bullet(position + glm::vec2(2.f * size * (float)cos(ang), 2.f * size * (float)sin(ang)), ang));
        fireRate = PLAYER_FIRE_RATE;
    }
}

void Player::addPoints(int points) {
    this->points += points;
}

int Player::getPoints() const {
    return points;
}

void Player::bulletsHitObstacles(glm::vec2* posObstacles, glm::vec2* sizeObstacles, char* meshType, int nrObstacles) {
    for (std::vector<Bullet*>::iterator bullet = bullets.begin(); bullet != bullets.end(); ) {
        for (int i = 0; i < nrObstacles; ++i) {
            if(meshType[i] == 's') {
                if (abs(posObstacles[i].x - bullet[0]->position.x) <= sizeObstacles[i].x / 2.f + BULLET_SIZE / 2.2f
                 && abs(posObstacles[i].y - bullet[0]->position.y) <= sizeObstacles[i].y / 2.f + BULLET_SIZE / 2.2f) {
                    delete bullet[0];
                    bullet = bullets.erase(bullet);
                    if (bullet == bullets.end())
                        return;
                }
            }
            else {
                if ((posObstacles[i].x - bullet[0]->position.x) * (posObstacles[i].x - bullet[0]->position.x)
                  + (posObstacles[i].y - bullet[0]->position.y) * (posObstacles[i].y - bullet[0]->position.y) 
                 <= (sizeObstacles[i].x + BULLET_SIZE / 2.f) * (sizeObstacles[i].x + BULLET_SIZE / 2.f)) {
                    delete bullet[0];
                    bullet = bullets.erase(bullet);
                    if (bullet == bullets.end())
                        return;
                }
            }
        }
        ++bullet;
    }
}

std::vector<Mesh*> Player::getMeshes() const {
    return meshes;
}

void Player::modHealth(uint8_t mod) {
    if (mod & 0x80) // ADD
        health += mod & 0x7F;
    else {
        health -= mod;
        if (health == 0)
            meshes.clear();
    }
}

int Player::getHealth() const {
    return health;
}

bool Player::isAlive() const {
    if (health > 0)
        return true;
    return false;
}

bool Bullet::Move(float deltaTimeSeconds) {
    position.x += BULLET_SPEED * deltaTimeSeconds * (float)cos(ang);
    position.y += BULLET_SPEED * deltaTimeSeconds * (float)sin(ang);

    range -= BULLET_SPEED * deltaTimeSeconds;
    if (range > 0)
        return true;
    else
        return false;
}

void Player::updateFireRate(float deltaTimeSeconds) {
    fireRate -= deltaTimeSeconds;
}

std::vector<glm::mat3> Player::getMatrices() const {
    return matrices;
}