#include "Common.hpp"
#include "Santa.hpp"


///////////////////////////////////
//  コンストラクタ
///////////////////////////////////
Santa::Santa() {}


///////////////////////////////////
//  移動処理
///////////////////////////////////
void Santa::move(int direction, double quantity, Collision collisions)
{
	m_direction = direction;
	Vec3 position = m_position;

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
void Santa::draw()
{
	ScopedRenderStates2D renderState(SamplerState::ClampNearest);

	// デバッグ線
	for (int i = 0; i < MAX_X; ++i)
	{
		for (int j = 0; j < MAX_Y; ++j)
		{
			for (int k = 0; k < MAX_Z; ++k)
			{
				Rect{
					i * ONE_PIXEL,
					j * ONE_PIXEL,
					ONE_PIXEL,
					ONE_PIXEL
				}
				.drawFrame(3, Color(255, 0, 0));
			}
		}
	}

	// サンタを描画
	m_skin(
		Vec2{ 32, 32 * m_direction },
		32,
		32
	)
		.scaled(2.5)
		.drawAt(
			(Vec2{ m_position.x, MAX_Y - m_position.y } * ONE_PIXEL)
				.movedBy(Vec2{ ONE_PIXEL / 2, ONE_PIXEL - 36 })
		);
}
