﻿#pragma once
#include "Common.hpp"
#include "World.hpp"
#include "Santa.hpp"


///////////////////////////////////
//  ゲームシーン
///////////////////////////////////
class Game : public SantaGame::Scene
{
private:

	//// ブロックのサイズ
	//static constexpr Size blockSize = Size(40, 20);

	//// ボールの速さ
	//static constexpr double speed = 480.0;

	//// ブロックの配列
	//Array<Rect> m_blocks;

	//// ボールの速度
	//Vec2 m_ballVelocity = Vec2(0, -speed);

	//// ボール
	//Circle m_ball = Circle(400, 400, 8);

	//// パドル
	//Rect m_paddle = Rect(Arg::center(Cursor::Pos().x, 500), 60, 10);

	//// スコア
	//int32 m_score = 0;

	// ワールド
	World m_world = World{MAX_X, MAX_Y, MAX_Z};
	Collision m_collisions = m_world.collisions;

	// サンタ
	Santa m_santa = Santa{};

	// アングル
	int m_angle = 1;

	void m_angle1() const;

	void m_angle2() const;

	const Font m_font{50};

public:

	Game(const InitData& init);

	void update() override;

	void draw() const override;
};
