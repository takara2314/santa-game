#pragma once
#include "Common.hpp"
#include "World.hpp"
#include "Santa.hpp"
#include "Item.hpp"


///////////////////////////////////
//  ゲームシーン
///////////////////////////////////
class Game : public SantaGame::Scene
{
private:
	// アイテム情報
	vector<Item> m_items = {
		Item{ U"土ブロック", U"items/dirt.png" },
		Item{ U"草ブロック", U"items/grass.png" },
		Item{ U"レンガブロック", U"items/brick.png" },
	};

	// ワールド
	World m_world = World{MAX_X, MAX_Y, MAX_Z, m_items};
	Collision m_collisions = m_world.collisions;
	const double m_gravity = m_world.gravity;

	// サンタ
	Santa m_santa = Santa{ m_world.gravity };

	// アングル
	int m_angle = 1;

	void m_angle1() const;

	void m_angle2() const;

	// クリック位置補正
	Point m_correct_click_pos(Point pos);

	const Font m_font{50};

public:

	Game(const InitData& init);

	void update() override;

	void draw() const override;
};
