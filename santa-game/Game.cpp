#include "Game.hpp"
#include "Santa.hpp"
#include "Child.hpp"


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

	// インベントリ操作
	if (Key1.pressed())
	{
		m_santa.inventory_selection = 1;
	}
	if (Key2.pressed())
	{
		m_santa.inventory_selection = 2;
	}
	if (Key3.pressed())
	{
		m_santa.inventory_selection = 3;
	}
	if (Key4.pressed())
	{
		m_santa.inventory_selection = 4;
	}
	if (Key5.pressed())
	{
		m_santa.inventory_selection = 5;
	}

	// 1秒～6秒ごとに視点変更
	if (Scene::Time() - m_changed_direction_time >= Random(1.0, 6.0))
	{
		m_changed_direction_time = Scene::Time();
		m_child.change_direction_random();
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

	Santa santa = m_santa;

	// インベントリの描画
	Inventory inventory = santa.get_inventory();
	m_draw_inventory(inventory, santa.inventory_selection);
}


// アングル1
void Game::m_angle1() const
{
	World world = m_world;
	Santa santa = m_santa;
	Child child = m_child;

	// ワールド
	world.draw(santa.get_position());

	// 子供
	child.draw(1, santa.get_position());
	// サンタ
	santa.draw(1);

	m_font(U"アングル1").draw(Vec2{50, 50});
}


// アングル2
void Game::m_angle2() const
{
	World world = m_world;
	Santa santa = m_santa;
	Child child = m_child;

	// ワールド
	world.draw(santa.get_position());

	// 子供
	child.draw(2, santa.get_position());
	// サンタ
	santa.draw(2);

	m_font(U"アングル2").draw(Vec2{ 50, 50 });
}


// インベントリを描画
void Game::m_draw_inventory(Inventory& inventory, int selection) const
{
	// 始点座標
	Vec2 start = { Scene::Width() - 90, 20 };

	RoundRect{ start, 60, 160, 10 }
		.draw(Color(0, 0, 0, 50));

	for (int i = 0; i < inventory.size(); ++i)
	{
		auto [item, num] = inventory[i];

		if (item.name != U"空気")
		{
			// アイテムスキン
			item.skin
				.scaled(0.4)
				.draw(
					start.movedBy(10, 10 + i * 30)
				);

			// アイテム数
			m_item_font(num)
				.draw(
					start.movedBy(35, 9 + i * 30)
				);
		}
	}

	// 選択しているところを囲む
	Vec2 pos = start.movedBy(0, (selection - 1) * 31);
	RoundRect{
		static_cast<int>(pos.x),
		static_cast<int>(pos.y),
		60,
		35,
		10
	}
		.drawFrame(3, 0, Color(175, 175, 175));
}
