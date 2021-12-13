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

	Collision collisions;

	World(int x, int y, int z);

	void draw();
};
