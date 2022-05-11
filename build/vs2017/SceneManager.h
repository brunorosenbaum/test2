#pragma once
#include "BaseScene.h"
#include "SplashScreen.h"
#include "GameScreen.h"

typedef SplashScreen;
typedef GameScreen;
enum GAME_STATES { SPLASH, GAME };

class SceneManager 
{
	//A class to manage which game state you're in. It will update and render according to that. 
public:
	SceneManager(gef::Platform& platform, gef::Renderer3D* renderer3D, gef::SpriteRenderer* sprite_renderer, gef::InputManager* input_manager, PrimitiveBuilder* primitive_builder_);
	void Update(float frame_time);
	void Render();
	void Swap(GAME_STATES new_scene);
	static SceneManager* getSceneManager();
	static void Create(gef::Platform& platform, gef::Renderer3D* renderer3D, gef::SpriteRenderer* sprite_renderer, gef::InputManager* input_manager, PrimitiveBuilder* primitive_builder_);

private: 
	BaseScene* current_scene; //This is a ptr to whatever scene/state the game is in. 
	SplashScreen* splashScreen_scene; 
	GameScreen* gameScreen_scene; 

};