﻿#include "Game.hpp"
#include "Santa.hpp"


///////////////////////////////////
//  コンストラクタ
///////////////////////////////////
Game::Game(const InitData& init)
	: IScene(init)
{
	// ウィンドウの幅
	Window::Resize(MAX_X * ONE_PIXEL, MAX_Y * ONE_PIXEL);

	//// 横 (Scene::Width() / blockSize.x) 個、縦 5 個のブロックを配列に追加する
	//for (auto p : step(Size((Scene::Width() / blockSize.x), 5)))
	//{
	//	m_blocks << Rect(p.x * blockSize.x, 60 + p.y * blockSize.y, blockSize);
	//}
}


///////////////////////////////////
//  繰り返しされる処理
///////////////////////////////////
void Game::update()
{
	// プレイヤーの操作
	if (KeyDown.pressed())
	{
		m_santa.move(0, 4.0, m_collisions, m_angle);
	}
	if (KeyLeft.pressed())
	{
		m_santa.move(1, 4.0, m_collisions, m_angle);
	}
	if (KeyRight.pressed())
	{
		m_santa.move(2, 4.0, m_collisions, m_angle);
	}
	if (KeyUp.pressed())
	{
		m_santa.move(3, 4.0, m_collisions, m_angle);
	}

	// アングル変更
	if (KeyLBracket.pressed())
	{
		m_angle = 1;
	}
	if (KeyRBracket.pressed())
	{
		m_angle = 2;
	}

	//// パドルを操作
	//m_paddle = Rect(Arg::center(Cursor::Pos().x, 500), 60, 10);

	//// ボールを移動
	//m_ball.moveBy(m_ballVelocity * Scene::DeltaTime());

	//// ブロックを順にチェック
	//for (auto it = m_blocks.begin(); it != m_blocks.end(); ++it)
	//{
	//	// ボールとブロックが交差していたら
	//	if (it->intersects(m_ball))
	//	{
	//		// ボールの向きを反転する
	//		(it->bottom().intersects(m_ball) || it->top().intersects(m_ball) ? m_ballVelocity.y : m_ballVelocity.x) *= -1;

	//		// ブロックを配列から削除（イテレータが無効になるので注意）
	//		m_blocks.erase(it);

	//		// スコアを加算
	//		++m_score;

	//		// これ以上チェックしない  
	//		break;
	//	}
	//}

	//// 天井にぶつかったらはね返る
	//if (m_ball.y < 0 && m_ballVelocity.y < 0)
	//{
	//	m_ballVelocity.y *= -1;
	//}

	//if (m_ball.y > Scene::Height())
	//{
	//	changeScene(State::Title);
	//	getData().highScore = Max(getData().highScore, m_score);
	//}

	//// 左右の壁にぶつかったらはね返る
	//if ((m_ball.x < 0 && m_ballVelocity.x < 0) || (Scene::Width() < m_ball.x && m_ballVelocity.x > 0))
	//{
	//	m_ballVelocity.x *= -1;
	//}

	//// パドルにあたったらはね返る
	//if (m_ballVelocity.y > 0 && m_paddle.intersects(m_ball))
	//{
	//	// パドルの中心からの距離に応じてはね返る向きを変える
	//	m_ballVelocity = Vec2((m_ball.x - m_paddle.center().x) * 10, -m_ballVelocity.y).setLength(speed);
	//}
}


///////////////////////////////////
//  描画処理
///////////////////////////////////
void Game::draw() const
{
//	FontAsset(U"Score")(m_score).drawAt(Scene::Center().x, 30);
//
//	// すべてのブロックを描画する
//	for (const auto& block : m_blocks)
//	{
//		block.stretched(-1).draw(HSV(block.y - 40));
//	}
//
//	// ボールを描く
//	m_ball.draw();
//
//	// パドルを描く
//	m_paddle.draw();

	switch (m_angle)
	{
	case 1:
		m_angle1();
		break;
	case 2:
		m_angle2();
		break;
	}
}


// アングル1
void Game::m_angle1() const
{
	Santa santa = m_santa;
	// サンタ
	santa.draw(1);

	m_font(U"アングル1").draw(Vec2{50, 50});
}


// アングル2
void Game::m_angle2() const
{
	Santa santa = m_santa;
	// サンタ
	santa.draw(2);

	m_font(U"アングル2").draw(Vec2{ 50, 50 });
}

