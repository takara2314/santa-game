﻿#include "World.hpp"
#include "Item.hpp"


///////////////////////////////////
//  コンストラクタ
///////////////////////////////////
World::World(int x, int y, int z, vector<Item> items)
{
	m_items = items;

	// ワールドデータ読み込み
	m_load_world_data(x, y, z);
}


///////////////////////////////////
//  ワールドデータ読み込み
///////////////////////////////////
void World::m_load_world_data(int x, int y, int z)
{
	// 当たり判定メンバを初期化
	collisions = Collision(x, vector<vector<bool>>(y, vector<bool>(z)));
	// ワールドデータメンバを初期化
	world_data = WorldData(x, vector<vector<Item>>(y, vector<Item>(z)));

	// ワールドファイル読み込み
	for (int i = 0; i < z; ++i)
	{
		CSV data{ Unicode::Widen(format("world/{:d}.csv", i)) };

		for (int j = 0; j < data.rows(); ++j)
		{
			for (int k = 0; k < data[j].size(); ++k)
			{
				size_t item_id = Parse<size_t>(data[j][k]);

				// そのアイテムを設置
				world_data[k][MAX_Y - 1 - j][i] = m_items[item_id];
				if (item_id != 0)
				{
					// 空気以外なら当たり判定
					collisions[k][MAX_Y - 1 - j][i] = true;
				}
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

	// 既にブロックが設置されているならキャンセル
	if (world_data[x][y][z].name != U"空気")
	{
		return;
	}

	// Print << U"click " << mouse_x << U" " << mouse_y;
	Print << U"設置 " << x << U" " << y << U" " << z;

	// 設置音
	block.touch_sound.play();

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

	// 破壊音
	if (world_data[x][y][z].name != U"空気")
	{
		world_data[x][y][z].touch_sound.play();
	}

	world_data[x][y][z] = Item{};
	collisions[x][y][z] = false;
}
