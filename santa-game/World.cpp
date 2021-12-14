#include "World.hpp"


///////////////////////////////////
//  コンストラクタ
///////////////////////////////////
World::World(int x, int y, int z) {
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			for (int k = 0; k < z; ++k)
			{
				collisions[i][j][k] = false;
			}
		}
	}
}


///////////////////////////////////
//  描画処理
///////////////////////////////////
void World::draw()
{
	
}
