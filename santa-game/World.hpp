#pragma once
#include "Common.hpp"
#include "Item.hpp"


///////////////////////////////////
//  ワールドクラス
///////////////////////////////////
class World
{
private:

	int m_angle = 1;

	const double m_max_place_limit = 1.8;

	vector<Item> m_items;

	void m_load_world_data(int x, int y, int z);

public:

	const double gravity = 9.8;

	Collision collisions;
	WorldData world_data;

	World(int x, int y, int z, vector<Item> items);

	void change_angle(int angle);

	void draw(Vec3 player_pos);

	bool set_block(int mouse_x, int mouse_y, Vec3 player_pos, Item& block);

	tuple<bool, Item> remove_block(int mouse_x, int mouse_y, Vec3 player_pos);
};
