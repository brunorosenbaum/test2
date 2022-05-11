#pragma once
#include "GameObject.h"
#include "player.h"
class Enemy :
    public GameObject
{
public:
	void initialize(PrimitiveBuilder*, b2World*);
	virtual void collision_Response(GAME_OBJECT_TYPE, gef::InputManager*) override;
	virtual void draw(gef::Renderer3D*, PrimitiveBuilder*) override;
	void chasePlayer(Player*);
private:
	float speed = 2.f; 

};

