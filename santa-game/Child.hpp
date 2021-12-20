#pragma once
#include "Common.hpp"
#include "Item.hpp"
#include "Human.hpp"


///////////////////////////////////
//  子供クラス
///////////////////////////////////
class Child : public Human
{
private:

	// 検知する縦幅
	const double m_detect_height = 1.0;
	// 検知する横幅の長さ
	const double m_detect_length = 4.0;

public:

	Child(Texture skin);

	void change_direction_random();

	void draw(int angle, Vec3 player_position);

	bool detect_santa(Vec3 player_position, Collision collisions);
};
