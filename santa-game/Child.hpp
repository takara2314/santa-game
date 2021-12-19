#pragma once
#include "Common.hpp"
#include "Item.hpp"
#include "Human.hpp"


///////////////////////////////////
//  子供クラス
///////////////////////////////////
class Child : public Human
{
public:

	Child(Texture skin);

	void change_direction_random();

	void draw(int angle, Vec3 player_position);
};
