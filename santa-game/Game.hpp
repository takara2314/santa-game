#pragma once
#include "Common.hpp"
#include "World.hpp"
#include "Santa.hpp"


///////////////////////////////////
//  ゲームシーン
///////////////////////////////////
class Game : public SantaGame::Scene
{
private:

	// ブロックのサイズ
	static constexpr Size blockSize = Size(40, 20);

	// ボールの速さ
	static constexpr double speed = 480.0;

	// ブロックの配列
	Array<Rect> m_blocks;

	// ボールの速度
	Vec2 m_ballVelocity = Vec2(0, -speed);

	// ボール
	Circle m_ball = Circle(400, 400, 8);

	// パドル
	Rect m_paddle = Rect(Arg::center(Cursor::Pos().x, 500), 60, 10);

	// スコア
	int32 m_score = 0;

	// ワールド
	World m_world = {10, 10, 10};
	Collision m_collisions = m_world.collisions;

	// サンタ
	Santa m_santa = Santa{};

public:

	Game(const InitData& init);

	void update() override;

	void draw() const override;
};
