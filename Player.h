#pragma once
#include "Transform2D.h"
#include "Object2D.h"
#include "components/simple_scene.h"

#define PLAYER_SIZE 4.2f
#define PLAYER_SPEED 80.f
#define BULLET_SIZE 3.5f
#define BULLET_RANGE 100.f
#define BULLET_SPEED 200.f
#define PLAYER_FIRE_RATE 0.5f
#define BONUS_RATE 4.f

struct Bullet {
	glm::vec2 position;
	float ang, range, speed;

	Bullet(glm::vec2 position, float ang);
	bool Move(float deltaTimeSeconds); // DE imbunatatit sa fac aici miscarea sa fie cat mai POO! returnez true daca nu a depasit rangeul
};

class Player {
	int points;
	int health;
	float fireRate; // Time between 2 possible shots
	std::vector<Mesh*> meshes;
	std::vector<glm::mat3> matrices;

public:
	float size;
	glm::vec3 position;
	glm::vec2 nexPosition;
	Mesh* bulletMesh;
	std::vector<Bullet*> bullets;

	Player(glm::vec3 position = glm::vec3(50, 50, 0), float size = PLAYER_SIZE);

	bool playerColision(glm::vec2* posObstacles, glm::vec2* sizeObstacles, char* meshType, int nr);	// determina daca se ciocneste de ceva
	bool isAlive() const; // Cheks if the player is alive

	void updateFireRate(float deltaTimeSeconds); // Update the fire rate
	void Shoot(glm::vec2 position, float ang);	// Shoot a bullet
	void addPoints(int); // add points
	void modHealth(uint8_t); //	 Modify Health (first bit used for mode and the last for ammount so maximum 2^7-1 = 127)
							 // Returns true if is still alive, false if is dead
	void bulletsHitObstacles(glm::vec2*, glm::vec2*, char*, int); // Colision of bullets with obstacles: checks which one get collided
														   // with obstacles and destroy them (just the bullets)
	int getPoints() const; // Returns player's points
	int getHealth() const; // Returns player's health

	std::vector<Mesh*> getMeshes() const; // Returns a vector of meshes
	std::vector<glm::mat3> getMatrices() const; // Returns a vector of transformation matrices
};