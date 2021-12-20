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


///////////////////////////////////
//  サンタ検知
///////////////////////////////////
bool Child::detect_santa(Vec3 player_position, Collision collisions)
{
	struct LocalFunc
	{
		static bool detect_collison(int i, int axis, Vec3 child_position, Collision collisions)
		{
			int y = static_cast<size_t>(child_position.y);
			i = Max(0, i);
			i = axis == 0 ? Min(i, MAX_X - 1) : Min(i, MAX_Z - 1);

			switch (axis)
			{
			case 0:
				if (collisions[i][y][static_cast<size_t>(child_position.z + 0.5)])
				{
					return true;
				}
				break;
			case 1:
				if (collisions[static_cast<size_t>(child_position.x + 0.5)][y][i])
				{
					return true;
				}
				break;
			}

			return false;
		}

		static bool detected_event(Vec3 child_position, Vec3 player_position, double detect_height, int i, int axis)
		{
			for (int j = child_position.y - detect_height; j < child_position.y + detect_height; ++j)
			{
				j = Max(0, j);
				j = Min(j, MAX_Y - 1);
				i = Max(0, i);
				i = axis == 0 ? Min(i, MAX_X - 1) : Min(i, MAX_Z - 1);

				size_t x = static_cast<size_t>(player_position.x + 0.5);
				size_t y = static_cast<size_t>(player_position.y);
				size_t z = static_cast<size_t>(player_position.z + 0.5);

				size_t x_child = static_cast<size_t>(child_position.x + 0.5);
				size_t z_child = static_cast<size_t>(child_position.z + 0.5);

				switch (axis)
				{
				case 0:
					if (x == i && y == j && z == z_child)
					{
						// Print << U"いた！0";
						return true;
					}
					// Print << U"0: (" << i << U", " << j << U", " << child_position.z << U")";
					// Print << U"player: (" << player_position.x << U", " << player_position.y << U", " << player_position.z << U")";
					break;

				case 1:
					if (z == i && y == j && x == x_child)
					{
						// Print << U"いた！1";
						return true;
					}
					// Print << U"1: (" << child_position.x << U", " << i << U", " << j << U")";
					// Print << U"player: (" << player_position.x << U", " << player_position.y << U", " << player_position.z << U")";
					break;
				}

				return false;
			}
		}
	};

	switch (Human::direction)
	{
	case 0:
		// Print << U"前方";
		for (int i = Human::position.z - 1; i > Human::position.z - m_detect_length; --i)
		{
			if (LocalFunc::detected_event(Human::position, player_position, m_detect_height, i, 1))
			{
				// Print << U"ぺぺぺ";
				return true;
			}
			if (LocalFunc::detect_collison(i, 0, Human::position, collisions))
			{
				break;
			}
		}
		break;

	case 1:
		// Print << U"右";
		for (int i = Human::position.x - 1; i > Human::position.x - m_detect_length; --i)
		{
			if (LocalFunc::detected_event(Human::position, player_position, m_detect_height, i, 0))
			{
				// Print << U"あああ";
				return true;
			}
			if (LocalFunc::detect_collison(i, 1, Human::position, collisions))
			{
				break;
			}
		}
		break;

	case 2:
		// Print << U"左";
		for (int i = Human::position.x + 1; i < Human::position.x + m_detect_length; ++i)
		{
			if (LocalFunc::detected_event(Human::position, player_position, m_detect_height, i, 0))
			{
				// Print << U"いいい";
				return true;
			}
			if (LocalFunc::detect_collison(i, 1, Human::position, collisions))
			{
				break;
			}
		}
		break;

	case 3:
		// Print << U"後方";
		for (int i = Human::position.z + 1; i < Human::position.z + m_detect_length; ++i)
		{
			if (LocalFunc::detected_event(Human::position, player_position, m_detect_height, i, 1))
			{
				// Print << U"ううう";
				return true;
			}
			if (LocalFunc::detect_collison(i, 0, Human::position, collisions))
			{
				break;
			}
		}
		break;
	}

	return false;
}
