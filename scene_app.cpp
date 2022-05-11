#include "scene_app.h"
#include <system/platform.h>
#include <graphics/sprite_renderer.h>
#include <graphics/font.h>
#include <system/debug_log.h>
#include <graphics/renderer_3d.h>
#include <maths/math_utils.h>
#include <obj_mesh_loader.h>

#include <graphics/mesh.h>
#include <graphics/sprite.h>

#include <input/input_manager.h>
#include <input/touch_input_manager.h>
#include <input/keyboard.h>




SceneApp::SceneApp(gef::Platform& platform) :
	Application(platform),
	sprite_renderer_(NULL),
	renderer_3d_(NULL),
	primitive_builder_(NULL),
	font_(NULL),
	world_(NULL),
	input_manager_(NULL),
	touch_manager_(NULL)
{
}

void SceneApp::Init()
{
	//What you do here is initialize the nullptrs creating instances of each class within the platform. 
	sprite_renderer_ = gef::SpriteRenderer::Create(platform_);

	//Input manager
	input_manager_ = gef::InputManager::Create(platform_);

	// 3D Renderer
	renderer_3d_ = gef::Renderer3D::Create(platform_);

	// Primitive builder to make create some 3D geometry easier
	primitive_builder_ = new PrimitiveBuilder(platform_);

	//Pass the correct parameters into the scene manager
	SceneManager::Create(platform_, renderer_3d_, sprite_renderer_, input_manager_, primitive_builder_);


	InitFont();
	SetupLights();

	// initialise the physics world
	b2Vec2 gravity(0.0f, -9.81f);
	world_ = new b2World(gravity);

	//const char* playerMesh = "penguin_child.scn";
	//player_Mesh_asset_ = LoadSceneAssets(platform_, playerMesh);

	//player_.initialize(primitive_builder_, world_, GetMeshFromSceneAssets(player_Mesh_asset_));
	//ground_.initialize(primitive_builder_, world_, GAME_OBJECT_TYPE::LEVEL);

	/*Create the obj loader*/
	/*OBJMeshLoader obj_loader;
	MeshMap mesh_map;*/

	//if (player_Mesh_asset_)
	//{
	//	//
	//	
	//}
	//else
	//{
	//	gef::DebugOut("Scene file %s failed to load\n", playerMesh);
	//}


}

void SceneApp::CleanUp()
{

	CleanUpFont();

	delete world_;
	world_ = NULL;

	delete primitive_builder_;
	primitive_builder_ = NULL;

	delete renderer_3d_;
	renderer_3d_ = NULL;

	delete sprite_renderer_;
	sprite_renderer_ = NULL;

	delete input_manager_;
	input_manager_ = NULL;

	delete touch_manager_;
	touch_manager_ = NULL;

}

bool SceneApp::Update(float frame_time)
{
	fps_ = 1.0f / frame_time;

	// update physics world
	float timeStep = 1.0f / 60.0f;
	world_->Step(timeStep, velocityIterations, positionIterations);
	
	
	checkInput(); //THIS IS ONLY FOR THE MOUSE POSITION
	if (input_manager_->keyboard()->IsKeyPressed(gef::Keyboard::KC_ESCAPE)) { //Close the app when escape is pressed
		return false;
	}
	//If the current scene gets updated, it'll call the private class functions inside the update() public function of each scene
	SceneManager::getSceneManager()->Update(frame_time);

	return true;
}

void SceneApp::Render()
{
	//Render gamestate app is in
	SceneManager::getSceneManager()->Render();
	
	// setup camera

	// start drawing sprites, but don't clear the frame buffer
	sprite_renderer_->Begin(false);
	DrawHUD();
	sprite_renderer_->End();
}


void SceneApp::checkInput()
{
	input_manager_->Update();

	if (input_manager_->touch_manager()) {
		mousePosition = input_manager_->touch_manager()->mouse_position();
	}

}


void SceneApp::InitFont()
{
	font_ = new gef::Font(platform_);
	font_->Load("comic_sans");
}

void SceneApp::CleanUpFont()
{
	delete font_;
	font_ = NULL;
}

void SceneApp::DrawHUD()
{
	if(font_)
	{
		// display frame rate
		font_->RenderText(sprite_renderer_, gef::Vector4(850.0f, 510.0f, -0.9f), 1.0f, 0xffffffff, gef::TJ_LEFT, "FPS: %.1f", fps_);

		font_->RenderText(
			sprite_renderer_,						// sprite renderer to draw the letters
			gef::Vector4(650.0f, 510.0f, -0.9f),	// position on screen
			1.0f,									// scale
			0xffffffff,								// colour ABGR
			gef::TJ_LEFT,							// justification
			"Mouse pos: %f %f",
			mousePosition.x, mousePosition.y);
	}
}

void SceneApp::SetupLights()
{
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = renderer_3d_->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.25f, 0.25f, 0.25f, 1.0f));

	// add a point light that is almost white, but with a blue tinge
	// the position of the light is set far away so it acts light a directional light
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-500.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(default_point_light);
}

gef::Scene* SceneApp::LoadSceneAssets(gef::Platform& platform, const char* filename)
{
	gef::Scene* scene = new gef::Scene();

	if (scene->ReadSceneFromFile(platform, filename))
	{
		// if scene file loads successful
		// create material and mesh resources from the scene data
		scene->CreateMaterials(platform);
		scene->CreateMeshes(platform);
	}
	else
	{
		delete scene;
		scene = NULL;
	}

	return scene;
}

gef::Mesh* SceneApp::GetMeshFromSceneAssets(gef::Scene* scene)
{
	gef::Mesh* mesh = NULL;

	// if the scene data contains at least one mesh
	// return the first mesh
	if (scene && scene->meshes.size() > 0)
		mesh = scene->meshes.front();

	return mesh;
}

