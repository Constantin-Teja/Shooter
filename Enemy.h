#pragma once
#include "Player.h"

#define ENEMY_COLOR glm::vec3(1.f, 0.f, 0.f)
#define ENEMY_SPEED PLAYER_SPEED / 2.f
#define ENEMY_SPAWN_TIME 0.6f
#define ENEMY_SIZE 6.f
#define PI 3.141592f

class Enemy {
	float size;
	int nrEnemies;
	std::vector<Mesh*> meshes;
	std::vector<glm::vec2> positions;

public:
	Enemy(float size = 0);	// Constructor: creates the meshes of enemy
	~Enemy(); // Destructor

	void createEnemy(glm::vec2);	// Creates enemies with random positions
	int getHit(std::vector<Bullet*>&); //	Checks which enemy get hit by bullets and destroy them. Destroy all
										// enemies hit by bullets and the bullets and returns the number of enemies hit
	int getNumber() const;	// Return the number of enemies
	bool touchPlayer(glm::vec2, float);	// Checks if an enemy touch the player
	
	glm::mat3 getMatrix(glm::vec2 target, int index, float deltaTimeSeconds);	// Create the transform matrix	for the enemy
																				// with index index and moves it towards target,
																				// which should be the player
	std::vector<glm::vec2>::iterator destroyEnemy(std::vector<glm::vec2>::iterator); // Destroy the enemy by deleting his position
	std::vector<Mesh*> getMeshes() const; // Returns a vector of meshes
};