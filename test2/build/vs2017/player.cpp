#include "player.h"


Player::Player() //Sets attributes for player
{
	setHP(100);
}

void Player::initialize(b2World* world_, gef::Mesh* player_mesh)
{
	setObjectType(GAME_OBJECT_TYPE::PLAYER); //Better to set their object type once at object creation
	this->set_mesh(player_mesh);

	//Set up the user data. We dp this in order to link the physics body to the gameobject. 
	b2BodyUserData user_data;
	user_data.pointer = (uintptr_t) & *this;

	//Create a physics body
	b2BodyDef body_def_;
	body_def_.type = b2_dynamicBody;
	body_def_.position = b2Vec2(0.0f, 0.0f);
	body_def_.userData = user_data;

	//Link body definition data to b2body instance in physics world
	Body_ = world_->CreateBody(&body_def_);
	
	/*Create player shape*/

	b2Vec2 vertices[4];
	vertices[0].Set(-1.5, 4);
	vertices[1].Set(-1.5, 0);
	vertices[2].Set(1.5, 0);
	vertices[3].Set(1.5, 4);

	b2PolygonShape shape;

	shape.Set(vertices, 4);
	
	
	//b2AABB is a struct needed for the shape.computeAABB function. Lowe and upperbound are b2Vec2 structs. 
	//Mesh() has a method that gets the aabb of the mesh itself, and returns the minimum and maximum vertices, but the data type is Vector4.
	//The problem here was how to turn that Vector4 into b2Vec2? 
	//Turns out you can use the Set() method of the b2vec2 struct, which takes in 2 floats (x and y) to initialize the b2vec2
	//And by getting the mesh' vertices x() and y(), which are floats, these can be stored in b2vec2's.
	//b2AABB player_boundingBox;
	//player_boundingBox.lowerBound.Set(this->mesh()->aabb().min_vtx().x(), this->mesh()->aabb().min_vtx().y());
	//player_boundingBox.upperBound.Set(this->mesh()->aabb().max_vtx().x(), this->mesh()->aabb().max_vtx().y());

	//b2PolygonShape shape;
	//shape.Set(vertices, vertCount);
	//shape.SetAsBox(0.5, 0.5); 
	/*
	shape.ComputeAABB(&player_boundingBox, this->Body_->GetTransform(), 1);*/
	//shape.Set(vertices, vertCount);
	
	//Create fixtures of physics body
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.f;
	//Create fixture on rigid body
	Body_->CreateFixture(&fixture);
	
	//Update visuals from simulation data
	this->UpdateFromSimulation();

}

void Player::collision_Response(GAME_OBJECT_TYPE collider, gef::InputManager* input)
{
	//Player's response to collision
	switch (collider) {
	case GAME_OBJECT_TYPE::ENEMY:
		//Player's collision response to an enemy
		enemyResponse(); 
		break;
	case GAME_OBJECT_TYPE::LEVEL:
		//Player's collision response to the ground
		break;
	}
}


void Player::UpdateFromSimulation()
{
	if (Body_)
	{
		//
		// setup object rotation
		gef::Matrix44 object_rotation;
		object_rotation.RotationZ(Body_->GetAngle());
		
		// setup the object translation
		gef::Vector4 object_translation(Body_->GetPosition().x, Body_->GetPosition().y, 0.0f);

		// build object transformation matrix
		gef::Matrix44 object_transform = object_rotation;
		object_transform.Scale(gef::Vector4(0.1f, 0.1f, 0.1f));
		object_transform.SetTranslation(object_translation);
		set_transform(object_transform);
		
	}

	
}

void Player::checkInput(gef::InputManager* input)
{

	if (input->keyboard()->IsKeyPressed(gef::Keyboard::KC_X)) {

		/*this->Body_->ApplyAngularImpulse(10.0f, true);*/
		this->Body_->ApplyLinearImpulse(b2Vec2(100, 0), Body_->GetWorldCenter(), true);
	}
	if (input->keyboard()->IsKeyPressed(gef::Keyboard::KC_SPACE)) {

		/*this->Body_->ApplyAngularImpulse(10.0f, true);*/
		this->Body_->ApplyLinearImpulse(b2Vec2(0, 200), Body_->GetWorldCenter(), true);
	}
	if (input->keyboard()->IsKeyPressed(gef::Keyboard::KC_Z)) {

		/*this->Body_->ApplyAngularImpulse(10.0f, true);*/
		this->Body_->ApplyLinearImpulse(b2Vec2(-100, 0), Body_->GetWorldCenter(), true);
	}

}


void Player::enemyResponse()
{
	setHP(getHP() - 10); 
}
