#include "Common.hpp"
#include "Santa.hpp"
#include "Human.hpp"


///////////////////////////////////
//  コンストラクタ
///////////////////////////////////
Santa::Santa(Texture skin, double y_acceleration)
{
	m_y_acceleration = y_acceleration;
	Human::skin = skin;
}


///////////////////////////////////
//  移動処理
///////////////////////////////////
void Santa::move(int direction, double quantity, Collision collisions, WorldData world_data, Audio& init_walk_sound, int angle)
{
	Vec3 position = Human::position;

	// 向きを更新
	Human::direction = direction;

	// 移動量をフレーム経過依存に
	quantity *= Scene::DeltaTime();

	// アングル1の時の位置操作
	if (angle == 1)
	{
		switch (Human::direction)
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
		switch (Human::direction)
		{
		case 0:
			position.x += quantity;
			break;
		case 1:
			position.z -= quantity;
			break;
		case 2:
			position.z += quantity;
			break;
		case 3:
			position.x -= quantity;
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

	Print << U"現在座標: " << Unicode::Widen(format("({:5.2f}, {:5.2f}, {:5.2f})", position.x, position.y, position.z));

	size_t x = static_cast<size_t>(position.x + 0.5);
	size_t y = static_cast<size_t>(position.y);
	size_t z = static_cast<size_t>(position.z + 0.5);

	// yの小数部分が0.9~1.0ならインクリメントして考える
	if (Human::pick_decimal(position.y) >= 0.9 && Human::pick_decimal(position.y) < 1.0)
	{
		y++;
	}

	// 足元か頭上に当たり判定があればキャンセル
	if (angle == 1)
	{
		if (Human::direction == 1)
		{
			double temp = position.x + 0.5 - Human::width / 2;
			x = static_cast<size_t>(temp < 0 ? 0 : temp);
		}
		else if (Human::direction == 2)
		{
			x = Min(static_cast<size_t>(position.x + 0.5 + Human::width / 2), static_cast<size_t>(MAX_X - 1));
		}
	}
	else
	{
		if (Human::direction == 1)
		{
			double temp = position.z + 0.5 - Human::width / 2;
			z = static_cast<size_t>(temp < 0 ? 0 : temp);
		}
		else if (Human::direction == 2)
		{
			z = Min(static_cast<size_t>(position.z + 0.5 + Human::width / 2), static_cast<size_t>(MAX_Z - 1));
		}
	}


	bool collision_underfoot = collisions[x][y][z];

	size_t y_overhead = Min(static_cast<size_t>(position.y + Human::height), static_cast<size_t>(MAX_Y - 1));
	// Print << U"移動先: " << Unicode::Widen(format("({:d}, {:d}, {:d})", static_cast<int>(x), static_cast<int>(y), static_cast<int>(z)));

	bool collision_overhead = collisions[x][y_overhead][z];

	if (collision_underfoot || collision_overhead)
	{
		return;
	}

	// Print << U"";

	// 歩行音
	if (y > 0 && world_data[x][y - 1][z].name != U"空気")
	{
		world_data[x][y - 1][z].walk_sound.play();
	}
	else
	{
		init_walk_sound.play();
	}

	// 適応
	Human::position = position;
}


///////////////////////////////////
//  ジャンプ
///////////////////////////////////
void Santa::jump(Collision collisions)
{
	Vec3 position = Human::position;

	if (m_is_ground && !m_is_jump)
	{
		m_is_jump = true;
		m_is_ground = false;
		m_y_speed = jump_speed * 0.05;
		position.y += m_y_speed;
	}

	// 高度調整
	position.y = Min(position.y, static_cast<double>(MAX_Y - 1));
	position.y = Max(position.y, 0.0);

	// 適応
	Human::position = position;
}


///////////////////////////////////
//  y座標位置変更
///////////////////////////////////
void Santa::move_y(Collision collisions)
{
	Vec3 position = Human::position;

	// ジャンプ中
	if (m_is_jump)
	{
		m_y_speed -= Scene::DeltaTime() * m_y_acceleration * 0.05;

		if (m_y_speed <= 0)
		{
			m_is_jump = false;
		}

		// <身長>ブロック上にブロックがあればキャンセル
		size_t x = static_cast<size_t>(position.x + 0.5);
		size_t y = Min(static_cast<size_t>(position.y + Human::height), static_cast<size_t>(MAX_Y - 1));
		size_t z = static_cast<size_t>(position.z + 0.5);

		bool collision = collisions[x][y][z];

		if (collision)
		{
			m_is_jump = false;
			m_y_speed = 0.0;
		}

		position.y += m_y_speed;
	}

	// ジャンプ落下中
	if (!m_is_jump && !m_is_ground)
	{
		m_y_speed -= Scene::DeltaTime() * m_y_acceleration * 0.05;
		position.y += m_y_speed;
	}

	// 落下して地面についた
	else if (!m_is_jump)
	{
		m_y_speed = 0.0;
		if (Human::pick_decimal(position.y) >= 0.5)
		{
			position.y = static_cast<int>(position.y) + 1.0;
		}
	}

	// 高度調整
	position.y = Min(position.y, static_cast<double>(MAX_Y) - 1);
	position.y = Max(position.y, 0.0);

	// 適応
	Human::position = position;
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
	if (position.y == 0)
	{
		m_is_ground = true;
		return;
	}

	// その位置に当たり判定があれば
	bool collision = collisions
		[static_cast<size_t>(position.x + 0.5)]
		[static_cast<size_t>(position.y)]
		[static_cast<size_t>(position.z + 0.5)];

	if (collision)
	{
		m_is_ground = true;
		return;
	}

	m_is_ground = false;
}
