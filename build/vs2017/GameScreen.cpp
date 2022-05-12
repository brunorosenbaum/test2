#include <graphics/sprite_renderer.h>
#include <SceneManager.h>
#include "GameScreen.h"
#include <maths/math_utils.h>


GameScreen::GameScreen(gef::Platform& platform, gef::Renderer3D* renderer3D, gef::SpriteRenderer* sprite_renderer, gef::InputManager* input_manager, PrimitiveBuilder* primitive_builder_) :
	BaseScene(platform, renderer3D, sprite_renderer, input_manager, primitive_builder_), 
	world_(NULL)
{
	//
}

void GameScreen::Init()
{
	//Initialize gravity
	b2Vec2 gravity(0.0f, -9.81f);
	world_ = new b2World(gravity);

	//Initialize objects

	//Player
	obj_mesh_loader.Load("player/player.obj", platform_, mesh_map);
	gef::Mesh* player_mesh = mesh_map["player"];
	player_.initialize(world_, player_mesh);

	//Enemy
	enemy_.initialize(primitive_builder_, world_);


	txrTest = gef::Texture::CreateCheckerTexture(platform_.width(), 32, platform_);
	ground_.setMtl(txrTest);
	ground_.initialize(primitive_builder_, world_, GAME_OBJECT_TYPE::LEVEL);
	
	/*obj_mesh_loader.Load("level/level.obj", platform_, mesh_map);
	gef::Mesh* level_mesh = mesh_map["Cube"];
	level_.set_mesh(level_mesh);*/
	///*gef::Mesh* level_bg_mesh = mesh_map["Plane"];
	//level_background.set_mesh(level_mesh);*/
	//level_.initLevel(world_);


	
}

void GameScreen::Update(float frame_time)
{
	float timeStep = 1.0f / 60.0f;
	world_->Step(timeStep, velocityIterations, positionIterations);

	checkInput(); //Make sure input is being checked every frame

	//Update game objects
	player_.UpdateFromSimulation(); // update object visuals from simulation data
	enemy_.UpdateFromSimulation();

	processCollisions();
	
	//Check if player's HP is <=0 to change gamestates
	if (player_.getHP() <= 0) {
		//SceneManager::getSceneManager()->Swap(GAME_STATES::SPLASH);
	}

	enemy_.chasePlayer(&player_);
}

void GameScreen::Render()
{
	// projection
	float fov = gef::DegToRad(45.0f);
	float aspect_ratio = (float)platform_.width() / (float)platform_.height();
	gef::Matrix44 projection_matrix;
	projection_matrix = platform_.PerspectiveProjectionFov(fov, aspect_ratio, 0.1f, 100.0f);
	renderer_3d_->set_projection_matrix(projection_matrix);

	// view
	gef::Vector4 camera_eye(player_.transform().GetTranslation().x()-10, player_.transform().GetTranslation().y()+5, 20.0f);
	gef::Vector4 camera_lookat(player_.transform().GetTranslation().x(), player_.transform().GetTranslation().y(), 0.0f);
	gef::Vector4 camera_up(0.0f, 1.0f, 0.0f);
	gef::Matrix44 view_matrix;
	view_matrix.LookAt(camera_eye, camera_lookat, camera_up);
	renderer_3d_->set_view_matrix(view_matrix);

	


	renderer_3d_->Begin();
	ground_.draw(renderer_3d_, primitive_builder_);
	renderer_3d_->DrawMesh(player_);
	enemy_.draw(renderer_3d_, primitive_builder_);
	/*renderer_3d_->DrawMesh(level_);
	renderer_3d_->DrawMesh(level_background);*/

	renderer_3d_->End();

	//sprite_renderer_->Begin(false);
	//// here goes the 2d ui sprites
	//sprite_renderer_->End();


}

void GameScreen::Cleanup()
{
	delete world_;
	world_ = NULL;

}


////////////////////////////////////////////////////////////////////////////Private functions

void GameScreen::checkInput()
{
	//Checks user input during the game screen of the app - during actual gameplay
	player_.checkInput(input_manager_); 

}

void GameScreen::processCollisions()
{

	b2Contact* contact = world_->GetContactList();
	int contact_count = world_->GetContactCount();
	for (int contact_num = 0; contact_num < contact_count; ++contact_num) {

		if (contact->IsTouching()) {

			b2Body* bodyA = contact->GetFixtureA()->GetBody(); //Idk which one of these is the body or the ground. 
			b2Body* bodyB = contact->GetFixtureB()->GetBody(); //We just know 2 bodies collide and there are 2 contacts.

			GameObject* gameObjectA = (GameObject*)bodyA->GetUserData().pointer; //What you do know is that youve set the user data to be of type GameObject.
			//We cast the b2Body ptr to a GameObject ptr. We then assign the ptr to the user data of the body A to a pointer to the GameObject class: gameObjectA. 
			GameObject* gameObjectB = (GameObject*)bodyB->GetUserData().pointer;
			//We still don't know which is each (A or B could be player or ground or the other way around)

			Player* player_ptr = dynamic_cast<Player*>(gameObjectA); //If there is inheritance between the class I passed into gameObjectA and the one I'm casting to
			//and there is polymorphism in the sense of a virtual function being overriden, this cast will work. 
			//Tldr telling us if we can convert gameObjectA to a pointer to the Player class. 
			//So we can do stuff like
			if (player_ptr) {

				gameObjectA->collision_Response(gameObjectB->getObjectType(), input_manager_);
			}


		}
		// Get next contact point
		contact = contact->GetNext();
	}
}
//testest