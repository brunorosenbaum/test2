#include "SplashScreen.h"
#include <graphics/sprite_renderer.h>
#include <SceneManager.h>

SplashScreen::SplashScreen(gef::Platform& platform, gef::Renderer3D* renderer3D, gef::SpriteRenderer* sprite_renderer, gef::InputManager* input_manager, PrimitiveBuilder* primitive_builder_)
	: BaseScene(platform, renderer3D, sprite_renderer, input_manager, primitive_builder_), //Also calls the basescene constructor and get the member variables from there
	timer(2.f) //You can directly initialize it here
{
	//
}

void SplashScreen::Init()
{
	//Create sprites, set width, etc
	splash_texture = gef::Texture::CreateCheckerTexture(platform_.width(), 32, platform_);
	splash_screen_sprite.set_texture(splash_texture);
	splash_screen_sprite.set_height(platform_.height());
	splash_screen_sprite.set_width(platform_.width());
	splash_screen_sprite.set_position(gef::Vector4(platform_.width() / 2, platform_.height() / 2, 0)); 

}

void SplashScreen::Update(float frame_time)
{
	if (timer > 0.f) {
		timer -= frame_time;
	}
	else {
		//This way, since it's a static function, we can access the singleton of this class by calling it here (including the header in the cpp), 
		//and we avoid circular dependency as well ass nullptrs. 
		SceneManager::getSceneManager()->Swap(GAME_STATES::GAME); 
	}

}

void SplashScreen::Render()
{
	sprite_renderer_->Begin();
	sprite_renderer_->DrawSprite(splash_screen_sprite);
	sprite_renderer_->End(); 
}

void SplashScreen::Cleanup()
{
	//Txr cleanup maybe
	//You dont need to cleanup the stuff from the constructor cause theyre being taken from somewhere else via pointers

}
