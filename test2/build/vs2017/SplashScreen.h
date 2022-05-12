#pragma once

#include <graphics/sprite.h>
#include <graphics/texture.h>
#include "BaseScene.h"

class SplashScreen : public BaseScene //This way I'll have access to all of the functions and protected member variable
{
public: //Now I can expand on the things i want to
	SplashScreen(gef::Platform& platform, gef::Renderer3D* renderer3D, gef::SpriteRenderer* sprite_renderer, gef::InputManager* input_manager, PrimitiveBuilder* primitive_builder_);
	virtual void Init() override;
	virtual void Update(float frame_time) override;
	virtual void Render() override;
	virtual void Cleanup() override;

private:
	//Have everything related to the splashscreen here
	//Stuff like sprites, the textures, your timer, etc
	gef::Sprite splash_screen_sprite;
	gef::Texture* splash_texture;
	float timer;
};

