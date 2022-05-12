#include "Level.h"

void Level::initLevel(b2World* world_)
{
    setObjectType(GAME_OBJECT_TYPE::LEVEL); //Better to set their object type once at object creation
 
    int j = 0;
    for (int i = 0; i < boundaries.size(); ++i)
    {
        b2BodyUserData level_data;
        level_data.pointer = (uintptr_t)&boundaries;

        // create a physics body
        b2BodyDef body_def;
        body_def.type = b2_staticBody;
        body_def.position = b2Vec2(0.0f, 0.0f);
        body_def.userData = level_data;

        boundaries_body[i] = world_->CreateBody(&body_def);

        // create the shape
        b2Vec2 vs[4];
        vs[0].Set(level_bounds[j].x, level_bounds[j].y);
        vs[1].Set(level_bounds[j + 1].x, level_bounds[j + 1].y);
        vs[2].Set(level_bounds[j + 2].x, level_bounds[j + 2].y);
        vs[3].Set(level_bounds[j + 3].x, level_bounds[j + 3].y);

        b2ChainShape shape;
        shape.CreateLoop(vs, 4);

        j += 4;

        // create the fixture
        b2FixtureDef fixture_def;
        fixture_def.shape = &shape;

        // create the fixture on the rigid body
        boundaries_body[i]->CreateFixture(&fixture_def);
    }
    UpdateFromSimulation();
}

void Level::UpdateFromSimulation()
{
    //if (Body_)
    //{
    //    //
    //    // setup object rotation
    //   /* gef::Matrix44 object_rotation;
    //    object_rotation.RotationZ(Body_->GetAngle());*/

    //    // setup the object translation
    //    //gef::Vector4 object_translation(Body_->GetPosition().x, Body_->GetPosition().y, 0.0f);

    //    // build object transformation matrix
    //    gef::Matrix44 object_transform;
    //    object_transform.Scale(gef::Vector4(2.0f, 2.0f, 2.0f));
    //    //object_transform.SetTranslation(object_translation);
    //    set_transform(object_transform);

    //}
}

