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

	// 接地しているか
	bool m_is_ground = true;

	// ジャンプしているか
	bool m_is_jump = false;

	// ジャンプ初速度
	const double jump_speed = 2.0;
	// 縦方向の加速度
	const double m_y_acceleration = 9.8;
	// 縦方向の速度
	double m_y_speed = 0.0;

	// インベントリ
	Array<Item> m_inventory;

public:

	Santa();

	void move(int direction, double quantity, Collision collisions, int angle);

	void jump(Collision collisions);

	void move_y(Collision collisions);

	void change_angle(int from, int to);

	void check_ground(Collision collisions);

	void draw(int angle);
};
