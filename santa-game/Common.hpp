#pragma once
#include <Siv3D.hpp>

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
const int MAX_Y = 10;
const int MAX_Z = 4;

// 1ブロックピクセル
const int ONE_PIXEL = 48;

// 当たり判定型
using Collision = array<array<array<bool, MAX_Z>, MAX_Y>, MAX_X > ;
