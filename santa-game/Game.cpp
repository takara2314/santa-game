#include "Game.hpp"
#include "Santa.hpp"


///////////////////////////////////
//  コンストラクタ
///////////////////////////////////
Game::Game(const InitData& init)
	: IScene(init)
{
	// ウィンドウの幅
	Window::Resize(MAX_X * ONE_PIXEL, MAX_Y * ONE_PIXEL + ONE_PIXEL);
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
	if (KeySpace.pressed())
	{
		Print << U"ジャンプします！";
		m_santa.jump(m_collisions);
	}

	// アングル変更
	if (KeyLBracket.pressed())
	{
		m_santa.change_angle(m_angle, 1);
		m_angle = 1;
	}
	if (KeyRBracket.pressed())
	{
		m_santa.change_angle(m_angle, 2);
		m_angle = 2;
	}

	// 接地判定
	m_santa.check_ground(m_collisions);

	// 接地していなかったら落下
	m_santa.move_y(m_collisions);
}


///////////////////////////////////
//  描画処理
///////////////////////////////////
void Game::draw() const
{
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

