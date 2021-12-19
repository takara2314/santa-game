#include "Common.hpp"
#include "Human.hpp"


///////////////////////////////////
//  コンストラクタ
///////////////////////////////////
Human::Human() {}


///////////////////////////////////
//  座標を受け取る
///////////////////////////////////
Vec3 Human::get_position()
{
	return position;
}


// 小数部分だけ取り出す
double Human::pick_decimal(double num)
{
	return num - static_cast<int>(num);
}



///////////////////////////////////
//  向きを変更
///////////////////////////////////
void Human::change_angle(int from, int to)
{
	if (from == 1 && to == 2 && direction == 0)
	{
		direction = 1;
	}
	else if (from == 1 && to == 2 && direction == 1)
	{
		direction = 3;
	}
	else if (from == 1 && to == 2 && direction == 2)
	{
		direction = 0;
	}
	else if (from == 1 && to == 2 && direction == 3)
	{
		direction = 2;
	}
	else if (from == 2 && to == 1 && direction == 0)
	{
		direction = 2;
	}
	else if (from == 2 && to == 1 && direction == 1)
	{
		direction = 0;
	}
	else if (from == 2 && to == 1 && direction == 2)
	{
		direction = 3;
	}
	else if (from == 2 && to == 1 && direction == 3)
	{
		direction = 1;
	}
}


///////////////////////////////////
//  描画処理
///////////////////////////////////
void Human::draw(int angle)
{
	ScopedRenderStates2D renderState(SamplerState::ClampNearest);

	// 描画座標
	Vec2 draw_pos{};

	switch (angle)
	{
	case 1:
		draw_pos = Vec2{ position.x, MAX_Y - position.y };
		break;
	case 2:
		draw_pos = Vec2{ position.z, MAX_Y - position.y };
		break;
	}

	// 両足の状態
	size_t walk_progress;
	if ((direction == 0 || direction == 3) && angle == 1)
	{
		walk_progress = static_cast<size_t>((position.z - static_cast<int>(position.z)) * 3);
	}
	else if ((direction == 1 || direction == 2) && angle == 1)
	{
		walk_progress = static_cast<size_t>((position.x - static_cast<int>(position.x)) * 3);
	}
	else if ((direction == 0 || direction == 3) && angle == 2)
	{
		walk_progress = static_cast<size_t>((position.x - static_cast<int>(position.x)) * 3);
	}
	else
	{
		walk_progress = static_cast<size_t>((position.z - static_cast<int>(position.z)) * 3);
	}

	// 人間を描画
	skin(
		Vec2{ 32 * walk_progress, 32 * direction },
		32,
		32
	)
		.scaled(2.5)
		.drawAt(
			(draw_pos * ONE_PIXEL)
				.movedBy(Vec2{ ONE_PIXEL / 2, -40 })
		);
}
