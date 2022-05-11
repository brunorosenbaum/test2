#pragma once

#include <graphics/sprite.h>
#include <graphics/texture.h>
#include <graphics/mesh.h>

#include <maths/vector2.h>
#include <box2d/Box2D.h>

#include <graphics/sprite.h>

#include "BaseScene.h"
#include "GameObject.h"
#include "player.h"
#include "Level.h"
#include "enemy.h"

class GameScreen : public BaseScene
{
public: //Now I can expand on the things i want to
	GameScreen(gef::Platform& platform, gef::Renderer3D* renderer3D, gef::SpriteRenderer* sprite_renderer, gef::InputManager* input_manager, PrimitiveBuilder* primitive_builder_);
	virtual void Init() override;
	virtual void Update(float frame_time) override;
	virtual void Render() override;
	virtual void Cleanup() override;
	

private:
	//Private functions that can only be accessed from inside the class
	void checkInput();
	void processCollisions();
	//Have everything related to the gamescreen here
	//Stuff like sprites, the textures, your timer, etc
	gef::Sprite game_screen_sprite;
	gef::Texture* gameScreen_Txr;
	OBJMeshLoader obj_mesh_loader;
	MeshMap mesh_map; 
	

	Player player_; 
	Enemy enemy_; 
	//Level level_;
	//GameObject level_background;
	GameObject ground_; 


	b2World* world_;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	gef::Sprite testSprite; 
	gef::Texture* txrTest; 
};

