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
	case 1:
		position.x -= quantity;
	case 2:
		position.x += quantity;
	case 3:
		position.z += quantity;
	}

	// 当たり判定があればキャンセル
	bool collision = collisions
		[static_cast<size_t>(position.y)]
		[static_cast<size_t>(position.x)]
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
	m_skin(
		Vec2{32, 0},
		32,
		32
	)
		.drawAt(Scene::Center());
}
