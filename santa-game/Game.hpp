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

	// ワールド
	World m_world = World{MAX_X, MAX_Y, MAX_Z};
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

	// アイテム情報
	Item m_dirt{ U"土ブロック", U"items/dirt.png" };
	Item m_grass{ U"草ブロック", U"items/grass.png" };
	Item m_brick{ U"レンガブロック", U"items/brick.png" };

public:

	Game(const InitData& init);

	void update() override;

	void draw() const override;
};
