#pragma once
#include "GameObject.h"
#include <array>
//Making a Level class just to initialize it and tidy up things
class Level :
    public GameObject
{
public:
    void initLevel(b2World*);
	virtual void UpdateFromSimulation() override;


private:
	
	std::array<GameObject, 21> boundaries;
	std::array<b2Body*, 21> boundaries_body; 
	std::array<gef::Vector2, 84> level_bounds
	{
		//Plane 1
		gef::Vector2(-1, -16),
		gef::Vector2(-1, 12),
		gef::Vector2(-15, 12),
		gef::Vector2(-15, -16),
		//Plane 2
		gef::Vector2(5, -16),
		gef::Vector2(5, 0),
		gef::Vector2(-1, 0),
		gef::Vector2(-1, -16),
		//Plane 3
		gef::Vector2(4, 8),
		gef::Vector2(4, 12),
		gef::Vector2(-1, 12),
		gef::Vector2(-1, 8),
		//Plane 4
		gef::Vector2(17, 10),
		gef::Vector2(17, 12),
		gef::Vector2(4, 12),
		gef::Vector2(4, 10),
		//Plane 5
		gef::Vector2(21, 7),
		gef::Vector2(21, 12),
		gef::Vector2(17, 12),
		gef::Vector2(17, 7),
		//Plane 6
		gef::Vector2(44, 10),
		gef::Vector2(44, 12),
		gef::Vector2(33, 12),
		gef::Vector2(33, 10),
		//Plane 7
		gef::Vector2(33, 9),
		gef::Vector2(33, 12),
		gef::Vector2(21, 12),
		gef::Vector2(21, 9),
		//Plane 8
		gef::Vector2(48, 7),
		gef::Vector2(48, 12),
		gef::Vector2(44, 12),
		gef::Vector2(44, 7),
		//Plane 9
		gef::Vector2(54, 9),
		gef::Vector2(54, 12),
		gef::Vector2(48, 12),
		gef::Vector2(48, 9),
		//Plane 10
		gef::Vector2(69, -17),
		gef::Vector2(69, 12),
		gef::Vector2(54, 12),
		gef::Vector2(54, -17),
		//Plane 11
		gef::Vector2(15, -16),
		gef::Vector2(15, 0),
		gef::Vector2(9, 0),
		gef::Vector2(9, -16),
		//Plane 12
		gef::Vector2(23, -16),
		gef::Vector2(23, 0),
		gef::Vector2(18, 0),
		gef::Vector2(18, -16),
		//Plane 13
		gef::Vector2(38.32, -16),
		gef::Vector2(38.32, 4),
		gef::Vector2(35.32, 4),
		gef::Vector2(35.32, -16),
		//Plane 14
		gef::Vector2(44.32, -16),
		gef::Vector2(44.32, 2),
		gef::Vector2(38.32, 2),
		gef::Vector2(38.32, -16),
		//Plane 15
		gef::Vector2(27, -16),
		gef::Vector2(27, 2),
		gef::Vector2(23, 2),
		gef::Vector2(23, -16),
		//Plane 16
		gef::Vector2(30, -16),
		gef::Vector2(30, 4),
		gef::Vector2(27, 4),
		gef::Vector2(27, -16),
		//Plane 17 
		gef::Vector2(9, -16),
		gef::Vector2(9, 2),
		gef::Vector2(5, 2),
		gef::Vector2(5, -16),
		//Plane 18
		gef::Vector2(54, -17),
		gef::Vector2(54, 2),
		gef::Vector2(49, 2),
		gef::Vector2(49, -17),
		//Plane 19
		gef::Vector2(49, -17),
		gef::Vector2(49, 3),
		gef::Vector2(48, 3),
		gef::Vector2(48, -17),
		//Plane 20
		gef::Vector2(14.15, 2.59),
		gef::Vector2(14.15, 3.44),
		gef::Vector2(10.66, 3.44),
		gef::Vector2(10.66, 2.59),
		//Plane 21
		gef::Vector2(33.89, 1.74),
		gef::Vector2(33.89, 2.62),
		gef::Vector2(30.89, 2.62),
		gef::Vector2(30.89, 1.74),
	};
};

