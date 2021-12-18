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

	// 身長
	const double m_height = 1.65;

	// 横幅
	const double m_width = 1.0;
		
	// 向き
	int m_direction = 0;

	// 接地しているか
	bool m_is_ground = true;

	// ジャンプしているか
	bool m_is_jump = false;

	// ジャンプ初速度
	const double jump_speed = 3.25;
	// 縦方向の加速度
	double m_y_acceleration = 9.8;
	// 縦方向の速度
	double m_y_speed = 0.0;

	// インベントリ
	Array<Item> m_inventory;

	// 小数部分だけ取り出す
	double m_pick_decimal(double num);

public:

	Santa(double y_acceleration);

	Vec3 get_position();

	void move(int direction, double quantity, Collision collisions, int angle);

	void jump(Collision collisions);

	void move_y(Collision collisions);

	void change_angle(int from, int to);

	void check_ground(Collision collisions);

	void draw(int angle);
};
