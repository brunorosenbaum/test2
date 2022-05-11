#include "GameObject.h"

//Getsetters
GAME_OBJECT_TYPE GameObject::getObjectType()
{
	return object_type;
}

void GameObject::setObjectType(GAME_OBJECT_TYPE newObjectType)
{
	object_type = newObjectType;

}

//Function to access the body of a game object from other class, to determine distance for example between game objects
b2Body* GameObject::getBody()
{
	return Body_;
}




void GameObject::initialize(PrimitiveBuilder* primitive_builder_, b2World* world_, GAME_OBJECT_TYPE type)
{
	//This code is gonna be temporarily for static objects, especially the ground for now. I'll see whether to make my own static body game objects class if needed. 
	setObjectType(type); //Set object type (for now it'll be for the ground)
	
	//Mesh
	gef::Vector4 ground_dimensions(100.0f, 0.5f, 5.0f);
	this->set_mesh(primitive_builder_->CreateBoxMesh(ground_dimensions));
	
	//User data
	b2BodyUserData data;
	data.pointer = (uintptr_t) & *this;

	//Physics body
	b2BodyDef body_def;
	body_def.type = b2_staticBody;
	body_def.position = b2Vec2(0.0f, -1.0f);
	body_def.userData = data; 

	Body_ = world_->CreateBody(&body_def);

	//Shape
	b2PolygonShape shape;
	shape.SetAsBox(ground_dimensions.x(), ground_dimensions.y());

	//Fixture
	b2FixtureDef fixture_def; 
	fixture_def.shape = &shape; 

	Body_->CreateFixture(&fixture_def);

	this->UpdateFromSimulation();
	
}

void GameObject::collision_Response(GAME_OBJECT_TYPE collider, gef::InputManager* input)
{
	//
}

void GameObject::draw(gef::Renderer3D* renderer_3d_, PrimitiveBuilder* primitive_builder_)
{
	renderer_3d_->set_override_material(&testMtl_);
	renderer_3d_->DrawMesh(*this);
	renderer_3d_->set_override_material(NULL);
}

// Update the transform of this object from a physics rigid body
void GameObject::UpdateFromSimulation()
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
		object_transform.SetTranslation(object_translation);
		set_transform(object_transform);
	}
}



