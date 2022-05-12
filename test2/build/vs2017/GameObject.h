
#ifndef _GAME_OBJECT_H
#define _GAME_OBJECT_H
#include <graphics/renderer_3d.h>
#include "primitive_builder.h"
#include <input/input_manager.h> //Having includes in the .cpp is better for compilation time
#include <input/touch_input_manager.h>
#include <input/keyboard.h>
#include <graphics/mesh_instance.h>
#include <box2d/Box2D.h>
#include <obj_mesh_loader.h>
#include <graphics/mesh.h>
#include <graphics/texture.h>
#include <graphics/material.h>


	//A very good way to separate differentiate collision bodies is with the use of enumerators.
	//That way, depending on the int ID each enum class element has, you can use switch statements to fire 
	// a different collision response based on the enum type of the collider.
	enum class GAME_OBJECT_TYPE {
		PLAYER, LEVEL, ENEMY
	};

	//This is the GameObject class. Thanks to polymorphism, the classes derived from it will be able to override its virtual functions. 
	//It also inherits from MeshInstance, so it has all its functions. Thus, in concept, a Game Object doesn't stop being a mesh.
	class GameObject : public gef::MeshInstance
	{
	public:
		virtual void UpdateFromSimulation();
		void initialize(PrimitiveBuilder*, b2World*, GAME_OBJECT_TYPE);
		virtual void collision_Response(GAME_OBJECT_TYPE, gef::InputManager*);
		virtual void draw(gef::Renderer3D*, PrimitiveBuilder*);
		void setMtl(gef::Texture* txr) { 
			testMtl_.set_texture(txr);
		}

		GAME_OBJECT_TYPE getObjectType();
		void setObjectType(GAME_OBJECT_TYPE); 

		b2Body* getBody(); 

	protected:
		GAME_OBJECT_TYPE object_type; 
		b2Body* Body_; 

	private:
		gef::Material testMtl_; 
		
		//Ideally we should have it so we can only set up the GAME OBJECT TYPE enum in the construction of each game object. 
	};

#endif // _GAME_OBJECT_H

