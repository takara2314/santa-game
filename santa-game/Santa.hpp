#pragma once
#include "Common.hpp"
#include "Item.hpp"
#include "Human.hpp"


///////////////////////////////////
//  サンタクラス
///////////////////////////////////
class Santa : public Human
{
private:

	// 接地しているか
	bool m_is_ground = true;
	// ジャンプしているか
	bool m_is_jump = false;

	// ジャンプ初速度
	const double jump_speed = 2.8;
	// 縦方向の加速度
	double m_y_acceleration = 9.8;
	// 縦方向の速度
	double m_y_speed = 0.0;

	// 扱えるアイテム一覧
	vector<Item> m_items;
	// インベントリ
	Inventory m_inventory;

public:

	Santa(Texture skin, double y_acceleration, vector<Item> items);

	void move(int direction, double quantity, Collision collisions, WorldData world_data, Audio& init_walk_sound, int angle);

	void jump(Collision collisions);

	void move_y(Collision collisions);

	void check_ground(Collision collisions);

	Inventory get_inventory();

	void give_item(int selection, Item& item, int quantity);

	void remove_item(int selection, int quantity);

	int inventory_selection = 0;
};
