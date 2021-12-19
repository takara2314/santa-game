#pragma once


///////////////////////////////////
//  アイテム
///////////////////////////////////
class Item
{
private:

public:

	String name = U"空気";
	Texture skin;
	bool is_alpha = false;
	Audio touch_sound;
	Audio walk_sound;

	Item();

	Item(String init_name);

	Item(String init_name, String texture_path, String touch_sound_path, String walk_sound_path);

	Item(String init_name, String texture_path, bool init_is_alpha, String touch_sound_path, String walk_sound_path);

};
