#pragma once
#include "Common.hpp"
#include "Item.hpp"


///////////////////////////////////
//  ワールドクラス
///////////////////////////////////
class World
{
private:

public:

	const double gravity = 9.8;

	Collision collisions;

	World(int x, int y, int z);

	void draw();
};
