#include "World.hpp"


///////////////////////////////////
//  コンストラクタ
///////////////////////////////////
World::World(int x, int y, int z) {
	Collision tmp;
	Grid<bool> surface{ static_cast<uint64>(x), static_cast<uint64>(z), false };
	for (int i = 0; i < y; ++i)
	{
		tmp << surface;
	}

	collisions = tmp;
}


///////////////////////////////////
//  描画処理
///////////////////////////////////
void World::draw()
{
	
}
