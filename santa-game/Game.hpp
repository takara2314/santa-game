#pragma once
#include "Common.hpp"
#include "World.hpp"
#include "Santa.hpp"
#include "Child.hpp"
#include "Item.hpp"


///////////////////////////////////
//  ゲームシーン
///////////////////////////////////
class Game : public SantaGame::Scene
{
private:

	// アイテム情報
	vector<Item> m_items = {
		Item{ U"空気" },
		Item{ U"土ブロック", U"items/dirt.png", U"se/touch_to_grass.mp3", U"se/walk_on_grass.mp3" },
		Item{ U"草ブロック", U"items/grass.png", U"se/touch_to_grass.mp3", U"se/walk_on_grass.mp3" },
		Item{ U"レンガブロック", U"items/brick.png", U"se/touch_to_stone.mp3", U"se/walk_on_brick.mp3" },
		Item{ U"ベッド", U"items/bed.png", U"se/touch_to_grass.mp3", U"se/walk_on_grass.mp3" },
		Item{ U"プレゼントボックス", U"items/present.png", U"se/touch_to_present.mp3", U"se/walk_on_grass.mp3" }
	};

	// BGM
	const Audio m_bgm = Audio{ Audio::Stream, U"bgm.mp3", Loop::Yes };

	// ワールド
	World m_world = World{MAX_X, MAX_Y, MAX_Z, m_items};
	Collision m_collisions = m_world.collisions;
	WorldData m_world_data = m_world.world_data;
	const double m_gravity = m_world.gravity;

	// サンタ
	Santa m_santa = Santa{ Texture{ U"santa.png" }, m_world.gravity, m_items };
	// 子供
	Child m_child = Child{ Texture{ U"child.png" } };

	// アングル
	int m_angle = 1;

	void m_angle1() const;

	void m_angle2() const;

	void m_draw_inventory(Inventory& inventory, int selection) const;

	// クリック位置補正
	Point m_correct_click_pos(Point pos);

	const Font m_font{ 50 };

	const Font m_item_font{ 16 };

	// 前回の視点変更
	double m_changed_direction_time = 0.0;

public:

	Game(const InitData& init);

	void update() override;

	void draw() const override;
};
