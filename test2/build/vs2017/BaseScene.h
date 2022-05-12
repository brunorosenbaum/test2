#pragma once
#include <primitive_builder.h>
#include <system/platform.h>
#include "graphics/scene.h"

//You could have all the includes here or use forward declaration (easier)
namespace gef { //This is like saying "inside the namespace gef there are these class types" 
	//And once we initialize and pass the actual pointers to these classes, BaseScene will recognize them
	class Renderer3D;
	class SpriteRenderer;
	class InputManager;
	
}

//This header file is a class from where other classes will inherit from. 
//It will represent the basic scene: all my classes will need access to the input manager, renderer 3d...etc 
//Likewise, some other classes might not need access to the box2d physics (like the loading screen)

class BaseScene 
{
public:
	BaseScene(gef::Platform& platform, gef::Renderer3D* renderer3D, gef::SpriteRenderer* sprite_renderer, gef::InputManager* input_manager, PrimitiveBuilder* primitive_builder) :platform_(platform)
	{	
		renderer_3d_ = renderer3D;
		sprite_renderer_ = sprite_renderer;
		input_manager_ = input_manager; 
		primitive_builder_ = primitive_builder;
	}

	//You can also create virtual functions to override later
	virtual void Init() = 0; 
	virtual void Update(float frame_time) = 0; 
	virtual void Render() = 0; 
	virtual void Cleanup() = 0; 

protected:

	gef::Platform& platform_; 
	gef::Renderer3D* renderer_3d_;
	gef::SpriteRenderer* sprite_renderer_;
	gef::InputManager* input_manager_; 
	PrimitiveBuilder* primitive_builder_;

};