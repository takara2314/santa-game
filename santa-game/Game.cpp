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

	// 背景色を設定
	Scene::SetBackground(Color(189, 247, 255));

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

	// ゲームオーバーまたはゲームクリアしたら操作できないように
	if (!(m_gameovered || m_gamecleared))
	{
		// プレイヤーの操作
		if (KeyDown.pressed() || KeyS.pressed())
		{
			m_santa.move(0, 4.0, m_collisions, m_world_data, m_items[3].walk_sound, m_angle);
		}
		if (KeyLeft.pressed() || KeyA.pressed())
		{
			m_santa.move(1, 4.0, m_collisions, m_world_data, m_items[3].walk_sound, m_angle);
		}
		if (KeyRight.pressed() || KeyD.pressed())
		{
			m_santa.move(2, 4.0, m_collisions, m_world_data, m_items[3].walk_sound, m_angle);
		}
		if (KeyUp.pressed() || KeyW.pressed())
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

			// 現在選択しているアイテム
			Item item = m_santa.get_inventory()[m_santa.inventory_selection].item;
			// 置けたらアイテムを減らす
			bool result = m_world.set_block(pos.x, pos.y, m_santa.get_position(), item);
			if (result)
			{
				m_santa.remove_item(m_santa.inventory_selection, 1);
			}
		}
		if (MouseL.pressed())
		{
			Point pos = m_correct_click_pos(Cursor::Pos());

			// 消せたらそのアイテムを付与する
			auto [result, item] = m_world.remove_block(pos.x, pos.y, m_santa.get_position());
			if (result)
			{
				m_santa.give_item(m_santa.inventory_selection, item, 1);
			}
		}

		// インベントリ操作
		if (Key1.pressed())
		{
			m_santa.inventory_selection = 0;
		}
		if (Key2.pressed())
		{
			m_santa.inventory_selection = 1;
		}
		if (Key3.pressed())
		{
			m_santa.inventory_selection = 2;
		}
		if (Key4.pressed())
		{
			m_santa.inventory_selection = 3;
		}
		if (Key5.pressed())
		{
			m_santa.inventory_selection = 4;
		}

		// 1秒～6秒ごとに視点変更
		if (Scene::Time() - m_changed_direction_time >= Random(1.0, 6.0))
		{
			m_changed_direction_time = Scene::Time();
			m_child.change_direction_random();
		}

		// サンタ検知
		if (m_child.detect_santa(m_santa.get_position(), m_world.collisions))
		{
			m_gameovered = Scene::Time();
			m_is_gameovered = true;
			m_bgm.stop();
		}

		// プレゼント検知
		if (m_child.detect_present(m_world.collisions, m_world.world_data))
		{
			m_gamecleared = Scene::Time();
			m_is_gamecleared = true;
		}
	}

	// ゲームオーバーして一定時間経ったら
	if (m_is_gameovered && m_gameovered + m_gameovered_wait <= Scene::Time())
	{
		changeScene(State::Title);
	}

	// ゲームクリアして一定時間経ったら
	if (m_is_gamecleared && m_is_gamecleared + m_gamecleared_wait <= Scene::Time())
	{
		m_bgm.stop();
		changeScene(State::Title);
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

	// ゲームオーバーして、一定時間経過するまでメッセージを表示
	if (m_is_gameovered && m_gameovered + m_gameovered_wait > Scene::Time())
	{
		int opacity = 255 * (Scene::Time() - m_gameovered) / m_gameovered_wait;
		opacity = Min(255, opacity);

		Rect{ 0, 0, Scene::Width(), Scene::Height()}
			.draw(Color(255, 0, 0, opacity));

		m_result_font(U"失敗…").drawAt(
			Scene::Center().x,
			Scene::Center().x - 100
		);
	}

	// ゲームクリアして、一定時間経過するまでメッセージを表示
	if (m_is_gamecleared && m_gamecleared + m_gamecleared_wait > Scene::Time())
	{
		int opacity = 255 * (Scene::Time() - m_gamecleared) / m_gamecleared_wait;
		opacity = Min(255, opacity);

		Rect{ 0, 0, Scene::Width(), Scene::Height() }
		.draw(Color(0, 255, 0, opacity));

		m_result_font(U"成功！").drawAt(
			Scene::Center().x,
			Scene::Center().x - 100
		);
	}
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

	m_angle_font(U"XYカメラ").drawAt(
		Vec2{
			Scene::Width() - 60,
			200
		},
		Color(128, 128, 128)
	);
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

	m_angle_font(U"ZYカメラ").drawAt(
		Vec2{
			Scene::Width() - 60,
			200,
		},
		Color(128, 128, 128)
	);
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
		Slot slot = inventory[i];

		if (slot.item.name != U"空気")
		{
			// アイテムスキン
			slot.item.skin
				.scaled(0.4)
				.draw(
					start.movedBy(10, 10 + i * 30)
				);

			// アイテム数
			m_item_font(slot.quantity)
				.draw(
					start.movedBy(35, 9 + i * 30)
				);
		}
	}

	// 選択しているところを囲む
	Vec2 pos = start.movedBy(0, selection * 31);
	RoundRect{
		static_cast<int>(pos.x),
		static_cast<int>(pos.y),
		60,
		35,
		10
	}
		.drawFrame(3, 0, Color(200, 200, 200));
}
