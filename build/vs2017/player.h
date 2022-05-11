#pragma once
#include "GameObject.h"
class Player :
    public GameObject
{
public:
	//Accessible from outside
	Player::Player(); 
	void initialize(b2World*, gef::Mesh*);
	virtual void UpdateFromSimulation() override;
	void checkInput(gef::InputManager*);
	int getHP() { return HP; }

private:
	//Accessible within the class
	virtual void collision_Response(GAME_OBJECT_TYPE, gef::InputManager*) override;

	//HP functions

	void enemyResponse();
	void setHP(int HP_) { HP = HP_; }

	//Attributes
	int HP;
};

