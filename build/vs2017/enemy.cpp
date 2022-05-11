#include "enemy.h"

void Enemy::initialize(PrimitiveBuilder* primitive_builder_, b2World* world_/*, gef::Mesh* enemy_mesh*/)
{
	setObjectType(GAME_OBJECT_TYPE::ENEMY);

	//Set up the mesh for the enemy
	this->set_mesh(primitive_builder_->GetDefaultCubeMesh());
	/*this->set_mesh(enemy_mesh);*/

	//Set up the user data. We dp this in order to link the physics body to the gameobject. 
	b2BodyUserData user_data;
	user_data.pointer = (uintptr_t) & *this;

	//Create a physics body
	b2BodyDef body_def_;
	body_def_.type = b2_dynamicBody;
	body_def_.position = b2Vec2(4.0f, 6.0f);
	body_def_.userData = user_data;

	//Link body definition data to b2body instance in physics world
	Body_ = world_->CreateBody(&body_def_);

	//Create player shape

	b2PolygonShape shape;
	shape.SetAsBox(0.5, 0.5);

	//shape.SetAsBox(0.5f, 0.5f);

	//Create fixtures of physics body
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;

	//Create fixture on rigid body
	Body_->CreateFixture(&fixture);

	//Update visuals from simulation data
	

}

void Enemy::collision_Response(GAME_OBJECT_TYPE collider, gef::InputManager* input)
{
	//Enemy's response to collision
	switch (collider) {
	case GAME_OBJECT_TYPE::PLAYER:
		//Enemy's collision response to player
		break;
	case GAME_OBJECT_TYPE::LEVEL:
		//Enemy's collision response to the ground
		break;
	}
}

void Enemy::draw(gef::Renderer3D* renderer_3d_, PrimitiveBuilder* primitive_builder_)
{
	renderer_3d_->set_override_material(&primitive_builder_->green_material());
	renderer_3d_->DrawMesh(*this);
	renderer_3d_->set_override_material(NULL);
}

void Enemy::chasePlayer(Player* player)
{
	//Use pythagoras
	float x = abs(Body_->GetPosition().x - player->getBody()->GetPosition().x);
	float y = abs(Body_->GetPosition().y - player->getBody()->GetPosition().y);

	float distance = sqrt(pow(x, 2) + pow(y, 2));
	if (distance <= 50) {
		if (player->getBody()->GetPosition().x < Body_->GetPosition().x && player->getBody()->GetPosition().y < Body_->GetPosition().y) {
			Body_->SetLinearVelocity(b2Vec2(-(float)cos(Body_->GetAngle()), -(float)sin(Body_->GetAngle())));
		}
		else if (player->getBody()->GetPosition().x > Body_->GetPosition().x && player->getBody()->GetPosition().y < Body_->GetPosition().y) {
			Body_->SetLinearVelocity(b2Vec2((float)cos(Body_->GetAngle()), -(float)sin(Body_->GetAngle())));
		}
		else if (player->getBody()->GetPosition().x < Body_->GetPosition().x && player->getBody()->GetPosition().y > Body_->GetPosition().y) {
			Body_->SetLinearVelocity(b2Vec2(-(float)cos(Body_->GetAngle()), (float)sin(Body_->GetAngle())));
		}
		else if (player->getBody()->GetPosition().x > Body_->GetPosition().x && player->getBody()->GetPosition().y > Body_->GetPosition().y) {
			Body_->SetLinearVelocity(b2Vec2((float)cos(Body_->GetAngle()), (float)sin(Body_->GetAngle())));
		}
	}
}
