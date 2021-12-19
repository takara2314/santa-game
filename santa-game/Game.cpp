#include "Game.hpp"
#include "Santa.hpp"


///////////////////////////////////
//  コンストラクタ
///////////////////////////////////
Game::Game(const InitData& init)
	: IScene(init)
{
	// ウィンドウの幅
	Window::Resize(MAX_X * ONE_PIXEL, MAX_Y * ONE_PIXEL);

	// BGMを再生
	m_bgm.setVolume(0.8);
	m_bgm.play();
}


///////////////////////////////////
//  繰り返しされる処理
///////////////////////////////////
void Game::update()
{
	// 当たり判定を更新
	m_collisions = m_world.collisions;
	// ワールドデータを更新
	m_world_data = m_world.world_data;

	// プレイヤーの操作
	if (KeyDown.pressed())
	{
		m_santa.move(0, 4.0, m_collisions, m_world_data, m_items[3].walk_sound, m_angle);
	}
	if (KeyLeft.pressed())
	{
		m_santa.move(1, 4.0, m_collisions, m_world_data, m_items[3].walk_sound, m_angle);
	}
	if (KeyRight.pressed())
	{
		m_santa.move(2, 4.0, m_collisions, m_world_data, m_items[3].walk_sound, m_angle);
	}
	if (KeyUp.pressed())
	{
		m_santa.move(3, 4.0, m_collisions, m_world_data, m_items[3].walk_sound, m_angle);
	}
	if (KeySpace.pressed())
	{
		m_santa.jump(m_collisions);
	}

	// アングル変更
	if (KeyLBracket.pressed())
	{
		m_santa.change_angle(m_angle, 1);
		m_world.change_angle(1);
		m_angle = 1;
	}
	if (KeyRBracket.pressed())
	{
		m_santa.change_angle(m_angle, 2);
		m_world.change_angle(2);
		m_angle = 2;
	}

	// 接地判定
	m_santa.check_ground(m_collisions);

	// 接地していなかったら落下
	m_santa.move_y(m_collisions);

	// ブロック操作
	if (MouseR.pressed())
	{
		Point pos = m_correct_click_pos(Cursor::Pos());
		m_world.set_block(pos.x, pos.y, m_santa.get_position(), m_items[1]);
	}
	if (MouseL.pressed())
	{
		Point pos = m_correct_click_pos(Cursor::Pos());
		m_world.remove_block(pos.x, pos.y, m_santa.get_position());
	}
}


///////////////////////////////////
//  クリック位置補正
///////////////////////////////////
Point Game::m_correct_click_pos(Point pos)
{
	// ワールド外にマウスが行っているときは補正
	if (pos.x <= 0)
	{
		pos.x = 1;
	}
	if (pos.y <= 0)
	{
		pos.y = 1;
	}
	if (pos.x >= MAX_X * ONE_PIXEL && m_angle == 1)
	{
		pos.x = MAX_X * ONE_PIXEL - 1;
	}
	if (pos.x >= MAX_Z * ONE_PIXEL && m_angle == 2)
	{
		pos.x = MAX_Z * ONE_PIXEL - 1;
	}
	if (pos.y >= MAX_Y * ONE_PIXEL)
	{
		pos.y = MAX_Y * ONE_PIXEL - 1;
	}

	return pos;
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
	World world = m_world;
	Santa santa = m_santa;

	// ワールド
	world.draw(santa.get_position());

	// サンタ
	santa.draw(1);

	m_font(U"アングル1").draw(Vec2{50, 50});
}


// アングル2
void Game::m_angle2() const
{
	World world = m_world;
	Santa santa = m_santa;

	// ワールド
	world.draw(santa.get_position());

	// サンタ
	santa.draw(2);

	m_font(U"アングル2").draw(Vec2{ 50, 50 });
}
