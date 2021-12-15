#pragma once
#include "Common.hpp"
#include "Item.hpp"


///////////////////////////////////
//  サンタクラス
///////////////////////////////////
class Santa
{
private:

	// テクスチャ画像
	Texture m_skin{ U"santa.png" };

	// 位置
	Vec3 m_position{ 3.0, 5.0, 2.0 };

	// 向き
	int m_direction = 0;

	// インベントリ
	Array<Item> m_inventory;

public:

	Santa();

	void move(int direction, double quantity, Collision collisions, int angle);

	void draw(int angle);
};
