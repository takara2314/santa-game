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
	m_direction = direction;
	Vec3 position = m_position;

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

	if (collision) {
		return;
	}

	m_position = position;
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
				.movedBy(Vec2{ ONE_PIXEL / 2, ONE_PIXEL - 36 })
		);
}
