#include "World.hpp"
#include "Item.hpp"


///////////////////////////////////
//  コンストラクタ
///////////////////////////////////
World::World(int x, int y, int z, vector<Item> items)
{
	m_items = items;

	// 当たり判定メンバを初期化
	collisions = Collision(x, vector<vector<bool>>(y, vector<bool>(z)));
	// ワールドデータメンバを初期化
	world_data = WorldData(x, vector<vector<Item>>(y, vector<Item>(z)));

	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			for (int k = 0; k < z; ++k)
			{
				collisions[i][j][k] = false;
			}
		}
	}
}


///////////////////////////////////
//  アングル変更
///////////////////////////////////
void World::change_angle(int angle)
{
	m_angle = angle;
}


///////////////////////////////////
//  描画処理
///////////////////////////////////
void World::draw(Vec3 player_pos)
{
	// デバッグ線
	for (int i = 0; i < MAX_X; ++i)
	{
		for (int j = 0; j < MAX_Y; ++j)
		{
			for (int k = 0; k < MAX_Z; ++k)
			{
				if (m_angle == 1)
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

	// 当たり判定
	if (m_angle == 1)
	{
		for (int i = 0; i < MAX_Y; ++i)
		{
			for (int j = 0; j < MAX_X; ++j)
			{
				int z = static_cast<int>(player_pos.z + 0.5);
				for (int k = z; k < MAX_Z; ++k)
				{
					Item item = world_data[j][i][k];

					if (item.name != U"空気")
					{
						item.skin.draw(
							j * ONE_PIXEL,
							ONE_PIXEL * (MAX_Y - 1 - i),
							// 遠くなっていくほど薄くなる
							ColorF(1.0, Max(1.0 - (k - z) * 0.3, 0.0))
						);

						break;
					}
				}

				// デバッグ用
				/*if (collision)
				{
					Rect{
						j * ONE_PIXEL,
						ONE_PIXEL * (MAX_Y - 1 - i),
						ONE_PIXEL,
						ONE_PIXEL
					}
						.draw(Color(0, 255, 0, 128));
				}*/
			}
		}
	}
	else
	{
		for (int i = 0; i < MAX_Y; ++i)
		{
			for (int j = 0; j < MAX_Z; ++j)
			{
				int x = static_cast<int>(player_pos.x + 0.5);
				for (int k = x; k >= 0; --k)
				{
					Item item = world_data[k][i][j];

					if (item.name != U"空気")
					{
						item.skin.draw(
							j * ONE_PIXEL,
							ONE_PIXEL * (MAX_Y - 1 - i),
							// 遠くなっていくほど薄くなる
							ColorF(1.0, Max(1.0 - (x - k) * 0.3, 0.0))
						);

						break;
					}
				}

				// デバッグ用
				/*if (collision)
				{
					Rect{
						j * ONE_PIXEL,
						ONE_PIXEL * (MAX_Y - 1 - i),
						ONE_PIXEL,
						ONE_PIXEL
					}
						.draw(Color(0, 255, 0, 128));
				}*/
			}
		}
	}
}


///////////////////////////////////
//  ブロックの設置
///////////////////////////////////
void World::set_block(int mouse_x, int mouse_y, Vec3 player_pos, Item& block)
{
	size_t x, y, z;
	if (m_angle == 1)
	{
		x = static_cast<size_t>(mouse_x / ONE_PIXEL);
		y = static_cast<size_t>((MAX_Y * ONE_PIXEL - mouse_y) / ONE_PIXEL);
		z = static_cast<size_t>(player_pos.z + 0.5);
	}
	else
	{
		x = static_cast<size_t>(player_pos.x + 0.5);
		y = static_cast<size_t>((MAX_Y * ONE_PIXEL - mouse_y) / ONE_PIXEL);
		z = static_cast<size_t>(mouse_x / ONE_PIXEL);
	}

	// プレイヤーの位置には設置できない
	if (
		x == static_cast<size_t>(player_pos.x + 0.5)
		&& y == static_cast<size_t>(player_pos.y)
		&& z == static_cast<size_t>(player_pos.z + 0.5))
	{
		return;
	}

	// Print << U"click " << mouse_x << U" " << mouse_y;
	Print << U"設置 " << x << U" " << y << U" " << z;

	world_data[x][y][z] = block;
	collisions[x][y][z] = true;
}


///////////////////////////////////
//  ブロックを破壊
///////////////////////////////////
void World::remove_block(int mouse_x, int mouse_y, Vec3 player_pos)
{
	size_t x, y, z;
	if (m_angle == 1)
	{
		x = static_cast<size_t>(mouse_x / ONE_PIXEL);
		y = static_cast<size_t>((MAX_Y * ONE_PIXEL - mouse_y) / ONE_PIXEL);
		z = static_cast<size_t>(player_pos.z + 0.5);
	}
	else
	{
		x = static_cast<size_t>(player_pos.x + 0.5);
		y = static_cast<size_t>((MAX_Y * ONE_PIXEL - mouse_y) / ONE_PIXEL);
		z = static_cast<size_t>(mouse_x / ONE_PIXEL);
	}

	world_data[x][y][z] = Item{};
	collisions[x][y][z] = false;
}
