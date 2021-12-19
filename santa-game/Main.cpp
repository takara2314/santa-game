#include "Common.hpp"
#include "Title.hpp"
#include "Game.hpp"


void Main()
{
	// Esc キーで終了しない
	System::SetTerminationTriggers(UserAction::CloseButtonClicked);

	// タイトルを設定
	Window::SetTitle(U"サンタさんのおしごと");

	// 使用するフォントアセットを登録
	FontAsset::Register(U"Title", 60, U"001Shirokuma-Regular.otf");
	FontAsset::Register(U"Menu", 30, Typeface::Regular);
	FontAsset::Register(U"Score", 36, Typeface::Bold);

	// シーンと遷移時の色を設定
	SantaGame manager;
	manager
		.add<Title>(State::Title)
		.add<Game>(State::Game)
		.setFadeColor(ColorF(1.0));

	while (System::Update())
	{
		if (!manager.update())
		{
			break;
		}
	}
}
