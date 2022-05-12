#ifndef _SCENE_APP_H
#define _SCENE_APP_H

#include <system/application.h>
#include <maths/vector2.h>
#include "primitive_builder.h"
#include <box2d/Box2D.h>

#include <graphics/mesh_instance.h>
#include <graphics/scene.h>

#include <GameObject.h>
#include <player.h>

#include "SceneManager.h"
#include "BaseScene.h"

// FRAMEWORK FORWARD DECLARATIONS
namespace gef
{
	class Platform;
	class SpriteRenderer;
	class Font;
	class InputManager;
	class TouchManager; 
	class Renderer3D;
}

class SceneApp : public gef::Application
{
public:
	SceneApp(gef::Platform& platform);
	void Init();
	void CleanUp();
	bool Update(float frame_time);
	void Render();
	void checkInput(); 

private:
	void InitFont();
	void CleanUpFont();
	void DrawHUD();
	void SetupLights();

	gef::Scene* LoadSceneAssets(gef::Platform& platform, const char* filename);
	gef::Mesh* GetMeshFromSceneAssets(gef::Scene* scene);

	gef::SpriteRenderer* sprite_renderer_;
	gef::Font* font_;
	gef::Renderer3D* renderer_3d_;
	PrimitiveBuilder* primitive_builder_;
	gef::InputManager* input_manager_; 
	gef::TouchManager* touch_manager_;


	gef::Vector2 mousePosition;

	//Game states
	//Create an instance of the enumerator 
	GAME_STATES game_state; //This way you can access this anywhere in the class to see which state we're currently in

	//Ptr to the physics world
	b2World* world_;
	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	float fps_;
	float timer_;

};

#endif // _SCENE_APP_H
