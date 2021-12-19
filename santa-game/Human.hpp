#pragma once
#include "Common.hpp"
#include "Item.hpp"


///////////////////////////////////
//  人間クラス
///////////////////////////////////
class Human
{
protected:

	// テクスチャ画像
	Texture skin{ U"child.png" };

	// 位置
	Vec3 position{ 0.0, 3.0, 0.0 };

	// 身長
	const double height = 1.65;

	// 横幅
	const double width = 1.0;

	// 向き
	int direction = 0;

	// 小数部分だけ取り出す
	double pick_decimal(double num);

public:

	Human();

	Vec3 get_position();

	void change_angle(int from, int to);

	void draw(int angle);
};
