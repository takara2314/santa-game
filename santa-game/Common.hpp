#pragma once
#include <Siv3D.hpp>

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

// 当たり判定型
using Collision = Array<Grid<bool>>;
