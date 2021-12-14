#pragma once
#include "Common.hpp"
#include "Item.hpp"


///////////////////////////////////
//  サンタクラス
///////////////////////////////////
class Santa
{
private:

	Texture m_skin{ U"santa.png" };
	Vec3 m_position{ 3.0, 5.0, 2.0 };
	int m_direction = 0;
	Array<Item> m_inventory;

public:

	Santa();

	void move(int direction, double quantity, Collision collisions);

	void draw();
};
