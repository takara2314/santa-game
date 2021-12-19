#pragma once
#include <Siv3D.hpp>
#include "Item.hpp"

using namespace std;

// シーンの名前
enum class State
{
	Title,
	Game
};

// ゲームデータ
struct GameData
{
	// ハイスコア
	int32 highScore = 0;
};

// シーン型
using SantaGame = SceneManager<State, GameData>;

// ワールドの最大幅
const int MAX_X = 12;
const int MAX_Y = 12;
const int MAX_Z = 4;

// 1ブロックピクセル
const int ONE_PIXEL = 48;

// 当たり判定型
using Collision = vector<vector<vector<bool>>>;

// ワールドデータ型
using WorldData = vector<vector<vector<Item>>>;
