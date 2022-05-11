#include "SceneManager.h"

//Create a global ptr of SceneManager.
SceneManager* fsm_manager = NULL;

SceneManager::SceneManager(gef::Platform& platform, gef::Renderer3D* renderer3D, gef::SpriteRenderer* sprite_renderer, gef::InputManager* input_manager, PrimitiveBuilder* primitive_builder_)
{
	//Create ALL the different screens and pass the necessary arguments into them, as well as initialize them
	splashScreen_scene = new SplashScreen(platform, renderer3D, sprite_renderer, input_manager, primitive_builder_); 
	splashScreen_scene->Init();

	gameScreen_scene = new GameScreen(platform, renderer3D, sprite_renderer, input_manager, primitive_builder_);
	

	//Now you should create loading, meny, settings, credits...

	//Now what this here does is set the ptr of the current screen to be a splashscreen the moment the scene manager is constructed. 
	//Hence, the first screen that 'current_scene' will be pointing to, and thus rendering the information, will be the splashcreen. 
	current_scene = splashScreen_scene; 
}

void SceneManager::Update(float frame_time)
{
	//Since we are overriding the baseScene's class functions, 
	//the function we call using current_scene will be the one from the class (splashscreen, gamescreen..etc) it points to
	//So if current_scene in this moment is set to splashcreen, it'll call the Update() function from the splashcreen class. 
	//Likewise, if in another moment it's set to gamescreen, it'll call the Update() function from the gamescreen class. 
	//Koby del futuro me vas a agradecer haber escrito esto como papilla para dartelo masticao me oyes
	current_scene->Update(frame_time); 
}

void SceneManager::Render()
{
	current_scene->Render(); 
}

void SceneManager::Swap(GAME_STATES new_scene)
{
	//We gotta give each scene class access to the manager to tell it to swap to a new type. This function is for that. 
	switch (new_scene) {
	case GAME_STATES::SPLASH:
		//Cleanup the previous scene and initalize the next one
		current_scene->Cleanup();
		current_scene = splashScreen_scene;
		current_scene->Init();
		break;
	case GAME_STATES::GAME:
		current_scene->Cleanup();
		current_scene = gameScreen_scene;
		current_scene->Init();
		break;
		//Yadda yadda the same for the rest
	}
}

SceneManager* SceneManager::getSceneManager()
{
	//This is a singleton: there's basically one version of SceneManager that I can access. 
	//It means that I can call create() in scene_app and give it the necessary arguments. 
	//If I try to access scenemanager, i can use the getSceneManager() method to access the ptr we made for this class, that is only initialized using the variables we passed in scene app. 
	return fsm_manager;
}

void SceneManager::Create(gef::Platform& platform, gef::Renderer3D* renderer3D, gef::SpriteRenderer* sprite_renderer, gef::InputManager* input_manager, PrimitiveBuilder* primitive_builder_)
{
	fsm_manager = new SceneManager(platform, renderer3D, sprite_renderer, input_manager, primitive_builder_);
}
