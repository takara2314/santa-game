#pragma once
#include "Item.hpp"


///////////////////////////////////
//  サンタクラス
///////////////////////////////////
class Santa
{
private:

	Texture m_skin{ U"santa.png" };
	Vec3 m_position{ 3.0, 3.0, 3.0 };
	int m_direction = 0;
	Array<Item> m_inventory;

public:

	Santa();

	void move(int direction, double quantity, Array<Grid<bool>> collisions);

	void draw();
};
