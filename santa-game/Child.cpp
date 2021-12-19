#include "Common.hpp"
#include "Child.hpp"
#include "Human.hpp"


///////////////////////////////////
//  コンストラクタ
///////////////////////////////////
Child::Child(Texture skin)
{
	Human::skin = skin;
	Human::position = Vec3{ 4.0, 4.0, 1.0 };
}


///////////////////////////////////
//  ランダムで視点変更
///////////////////////////////////
void Child::change_direction_random()
{
	for (;;)
	{
		int direction = Random(3);
		if (Human::direction != direction)
		{
			Human::direction = direction;
			break;
		}
	}
};


///////////////////////////////////
//  描画
///////////////////////////////////
void Child::draw(int angle, Vec3 player_position)
{
	ScopedRenderStates2D renderState(SamplerState::ClampNearest);

	// 描画座標
	Vec2 draw_pos{};
	// 透明度
	double opacity = 0.0;

	switch (angle)
	{
	case 1:
		draw_pos = Vec2{ Human::position.x, MAX_Y - Human::position.y };
		if (player_position.z <= Human::position.z)
		{
			opacity = Max(1.0 - (Human::position.z - player_position.z) * 0.3, 0.0);
		}
		break;
	case 2:
		draw_pos = Vec2{ Human::position.z, MAX_Y - Human::position.y };
		if (player_position.x >= Human::position.x)
		{
			opacity = Max(1.0 - (player_position.x - Human::position.x) * 0.3, 0.0);
		}
		break;
	}

	// 人間を描画
	skin(
		Vec2{ 32, 32 * direction },
		32,
		32
	)
		.scaled(2.5)
		.drawAt(
			(draw_pos * ONE_PIXEL)
				.movedBy(Vec2{ ONE_PIXEL / 2, -40 }),
			ColorF(1.0, opacity)
		);
}
