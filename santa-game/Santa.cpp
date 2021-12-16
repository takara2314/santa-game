#include "Common.hpp"
#include "Santa.hpp"


///////////////////////////////////
//  コンストラクタ
///////////////////////////////////
Santa::Santa() {}


///////////////////////////////////
//  移動処理
///////////////////////////////////
void Santa::move(int direction, double quantity, Collision collisions, int angle)
{
	Vec3 position = m_position;

	// 向きを更新
	m_direction = direction;

	// 移動量をフレーム経過依存に
	quantity *= Scene::DeltaTime();

	// アングル1の時の位置操作
	if (angle == 1)
	{
		switch (direction)
		{
		case 0:
			position.z -= quantity;
			break;
		case 1:
			position.x -= quantity;
			break;
		case 2:
			position.x += quantity;
			break;
		case 3:
			position.z += quantity;
			break;
		}
	}

	// アングル2の時の位置操作
	if (angle == 2)
	{
		switch (direction)
		{
		case 0:
			position.x -= quantity;
			break;
		case 1:
			position.z -= quantity;
			break;
		case 2:
			position.z += quantity;
			break;
		case 3:
			position.x += quantity;
			break;
		}
	}

	// 不の方向に行かないようにする
	position.x = Max(position.x, 0.0);
	position.y = Max(position.y, 0.0);
	position.z = Max(position.z, 0.0);

	// 限界座標-1より大きい移動であればキャンセル
	if (position.x > MAX_X - 1 || position.y > MAX_Y - 1 || position.z > MAX_Z - 1)
	{
		return;
	}

	Print << Unicode::Widen(format("({:5.2f}, {:5.2f}, {:5.2f})", position.x, position.y, position.z));

	// 当たり判定があればキャンセル
	bool collision = collisions
		[static_cast<size_t>(position.x)]
		[static_cast<size_t>(position.y)]
		[static_cast<size_t>(position.z)];

	if (collision)
	{
		return;
	}

	// 適応
	m_position = position;
}


///////////////////////////////////
//  ジャンプ
///////////////////////////////////
void Santa::jump(Collision collisions)
{
	Vec3 position = m_position;

	if (m_is_ground && !m_is_jump)
	{
		m_is_jump = true;
		m_y_speed = jump_speed * 0.05;
		position.y += m_y_speed;
		Print << U"ジャンプ開始";
	}

	// 高度調整
	position.y = Min(position.y, static_cast<double>(MAX_Y) - 1);
	position.y = Max(position.y, 0.0);

	Print << U"(F)変更します！ " << position.y;

	// 適応
	m_position = position;
}


///////////////////////////////////
//  ジャンプ・落下
///////////////////////////////////
void Santa::move_y(Collision collisions)
{
	Vec3 position = m_position;

	if (m_is_jump)
	{
		m_y_speed -= Scene::DeltaTime() * m_y_acceleration * 0.05;

		if (m_y_speed <= 0)
		{
			m_is_jump = false;
		}

		position.y += m_y_speed;
	}

	if (!m_is_jump && !m_is_ground)
	{
		m_y_speed -= Scene::DeltaTime() * m_y_acceleration * 0.05;
		position.y += m_y_speed;
	}
	else if (!m_is_jump)
	{
		m_y_speed = 0.0;
	}

	// 高度調整
	position.y = Min(position.y, static_cast<double>(MAX_Y) - 1);
	position.y = Max(position.y, 0.0);

	Print << U"(S)変更します！ " << position.y << (m_is_jump ? U"はい" : U"いいえ");

	// 適応
	m_position = position;
}


///////////////////////////////////
//  向きを変更
///////////////////////////////////
void Santa::change_angle(int from, int to)
{
	if (from == 1 && to == 2 && m_direction == 0)
	{
		m_direction = 1;
	}
	else if (from == 1 && to == 2 && m_direction == 1)
	{
		m_direction = 3;
	}
	else if (from == 1 && to == 2 && m_direction == 2)
	{
		m_direction = 0;
	}
	else if (from == 1 && to == 2 && m_direction == 3)
	{
		m_direction = 2;
	}
	else if (from == 2 && to == 1 && m_direction == 0)
	{
		m_direction = 2;
	}
	else if (from == 2 && to == 1 && m_direction == 1)
	{
		m_direction = 0;
	}
	else if (from == 2 && to == 1 && m_direction == 2)
	{
		m_direction = 3;
	}
	else if (from == 2 && to == 1 && m_direction == 3)
	{
		m_direction = 1;
	}
}


///////////////////////////////////
//  接地判定
///////////////////////////////////
void Santa::check_ground(Collision collisions)
{
	// ジャンプ中は非対象
	if (m_is_jump)
	{
		return;
	}

	// 0は絶対ある
	if (m_position.y == 0)
	{
		m_is_ground = true;
		return;
	}

	// 下まで当たり判定があるかどうかをチェック
	for (int i = m_position.y; 0 <= i; --i)
	{
		//Print << static_cast<size_t>(m_position.x);
		//Print << static_cast<size_t>(m_position.y);
		//Print << static_cast<size_t>(m_position.z);

		// 当たり判定があればキャンセル
		bool collision = collisions
			[static_cast<size_t>(m_position.x)]
			[static_cast<size_t>(m_position.y)]
			[static_cast<size_t>(m_position.z)];

		if (collision)
		{
			m_is_ground = true;
			return;
		}

	}
	m_is_ground = false;
}


///////////////////////////////////
//  描画処理
///////////////////////////////////
void Santa::draw(int angle)
{
	ScopedRenderStates2D renderState(SamplerState::ClampNearest);

	// デバッグ線
	for (int i = 0; i < MAX_X; ++i)
	{
		for (int j = 0; j < MAX_Y; ++j)
		{
			for (int k = 0; k < MAX_Z; ++k)
			{
				if (angle == 1)
				{
					Rect{
						i * ONE_PIXEL,
						j * ONE_PIXEL,
						ONE_PIXEL,
						ONE_PIXEL
					}
					.drawFrame(3, Color(255, 0, 0));
				}
				else
				{
					Rect{
						k * ONE_PIXEL,
						j * ONE_PIXEL,
						ONE_PIXEL,
						ONE_PIXEL
					}
					.drawFrame(3, Color(255, 0, 0));
				}
			}
		}
	}

	// 描画座標
	Vec2 draw_pos{};

	switch (angle)
	{
	case 1:
		draw_pos = Vec2{ m_position.x, MAX_Y - m_position.y };
		break;
	case 2:
		draw_pos = Vec2{ m_position.z, MAX_Y - m_position.y };
		break;
	}

	// 両足の状態
	size_t walk_progress;
	if ((m_direction == 0 || m_direction == 3) && angle == 1)
	{
		walk_progress = static_cast<size_t>((m_position.z - static_cast<int>(m_position.z)) * 3);
	}
	else if ((m_direction == 1 || m_direction == 2) && angle == 1)
	{
		walk_progress = static_cast<size_t>((m_position.x - static_cast<int>(m_position.x)) * 3);
	}
	else if ((m_direction == 0 || m_direction == 3) && angle == 2)
	{
		walk_progress = static_cast<size_t>((m_position.x - static_cast<int>(m_position.x)) * 3);
	}
	else
	{
		walk_progress = static_cast<size_t>((m_position.z - static_cast<int>(m_position.z)) * 3);
	}

	// サンタを描画
	m_skin(
		Vec2{ 32 * walk_progress, 32 * m_direction },
		32,
		32
	)
		.scaled(2.5)
		.drawAt(
			(draw_pos * ONE_PIXEL)
				.movedBy(Vec2{ ONE_PIXEL / 2, -36 })
		);
}
