#include "Enemy.h"

Enemy::Enemy(float size): size(size), nrEnemies(0) {
	// Creates the meshes of enemy
	meshes.push_back(object2D::CreateTriangle("enemy3", glm::vec3(0), size, glm::vec3(1, 0, 0), true));
	meshes.push_back(object2D::CreateSquare("enemy2", glm::vec3(-0.5f * size, -0.5f * size, 0.f), size, glm::vec3(0, 1, 0), true));
	meshes.push_back(object2D::CreateCircle("enemy1", glm::vec3(0), size, glm::vec3(0), true));
}

Enemy::~Enemy() {
	positions.clear();
	// std::vector<Mesh*> meshes;
	for (std::vector<Mesh*>::iterator it = meshes.begin(); it != meshes.begin(); ++it) {
		delete *it;
	}
	meshes.clear();
}

void Enemy::createEnemy(glm::vec2 position) {
	glm::vec2 pos(0);
	float aux = (float)(rand() % 60);
	switch ((int)rand() % 4) {
	case 0:
		pos.x = (position.x - 70.f <= -170.f ) ? position.x + 70.f : position.x - 70.f;
		pos.y = (position.y - 70.f + aux <= -170.f) ? position.y + 70.f + aux : position.y - 70.f + aux;
		break;
	case 1:
		pos.x = (position.x - 70.f + aux <= -170.f) ? (position.x + 70.f + aux) : (position.x - 70.f + aux);
		pos.y = (position.y - 70.f <= -170.f) ? (position.y + 70.f) : (position.y - 70.f);
		break;
	case 2:
		pos.x = (position.x + 70.f >= 170.f) ? (position.x - 70.f) : (position.x + 70.f);
		pos.y = (position.y - 70.f + aux <= -170) ? (position.y + 70.f + aux) : (position.y - 70.f + aux);
		break;
	case 3:
		pos.x = (position.x - 70.f + aux <= -170.f) ? (position.x + 70.f + aux) : (position.x - 70.f + aux);
		pos.y = (position.y + 70.f >= 170.f) ? (position.y - 70.f) : (position.y + 70.f);
		break;
	}
	positions.push_back(pos);
	nrEnemies++;
}

glm::mat3 Enemy::getMatrix(glm::vec2 target, int i, float deltaTimeSeconds) {
	float ang;
	float speedEnemy = rand() % (int)(70.f * ENEMY_SPEED / 100.f);
	//  calculez unghiul de rotatie
	float Dx = target.x - positions[i].x;
	float Dy = target.y - positions[i].y;
	if (Dx == 0) {
		ang = (Dy > 0) ? 0.5f * PI : 1.5f * PI;
	}
	else
		ang = (float)atan(Dy / Dx);
	// dupa modific coordonatele
	short int signX = ((Dx>0) ? 1 : -1);
	short int signY = ((ang > 0) ? ((Dy > 0) ? 1 : -1) : ((Dy > 0) ? -1 : 1));

	positions[i].x += signX * speedEnemy * deltaTimeSeconds * (float)cos(ang);
	positions[i].y += signY * speedEnemy * deltaTimeSeconds * (float)sin(ang);
	// fac matricea
	if (Dx < 0) {
		ang += PI;
	}
	return transform2D::Translate(positions[i].x, positions[i].y) * transform2D::Rotate(ang);
}

bool Enemy::touchPlayer(glm::vec2 posPlayer, float playerSize) {
	bool flag = false;
	for (std::vector<glm::vec2>::iterator it = positions.begin(); it != positions.end(); ) {
		if ((it->x - posPlayer.x) * (it->x - posPlayer.x) + (it->y - posPlayer.y) * (it->y - posPlayer.y)
				<= (size + playerSize) * (size + playerSize)) {
			it = destroyEnemy(it);
			flag = true;
		}
		else
			++it;
	}
	return flag;
}

std::vector<glm::vec2>::iterator Enemy::destroyEnemy(std::vector<glm::vec2>::iterator it) {
	nrEnemies--;
	return positions.erase(it);
}

int Enemy::getNumber() const {
	return nrEnemies;
}

int Enemy::getHit(std::vector<Bullet*>& bullets) {
	int nr = 0;
	for (std::vector<Bullet*>::iterator bullet = bullets.begin(); bullet != bullets.end(); ) {
		for (std::vector<glm::vec2>::iterator it = positions.begin(); it != positions.end(); ) {
			//(x-x)^2 + (y-y)^ < (size + size)^2
			if((it->x - bullet[0]->position.x) * (it->x - bullet[0]->position.x)
					+ (it->y - bullet[0]->position.y) * (it->y - bullet[0]->position.y) 
					<= (BULLET_SIZE + ENEMY_SIZE) * (BULLET_SIZE + ENEMY_SIZE)) {

				it = destroyEnemy(it);
				delete bullet[0];
				bullet = bullets.erase(bullet);
				nr++;
				if (bullet == bullets.end())
					return nr;
			}
			else {
				++it;
			}
		}
		++bullet;
	}
	return nr;
}

std::vector<Mesh*> Enemy::getMeshes() const {
	return meshes;
}