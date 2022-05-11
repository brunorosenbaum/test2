#pragma once
#include "GameObject.h"
class Egg :
    public GameObject
{
	void initialize(PrimitiveBuilder*, b2World*);
	virtual void collision_Response(GAME_OBJECT_TYPE, gef::InputManager*) override;
	virtual void UpdateFromSimulation() override;
};

