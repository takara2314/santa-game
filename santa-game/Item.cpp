#include "Item.hpp"


///////////////////////////////////
//  コンストラクタ
///////////////////////////////////
Item::Item() {
	name = U"空気";
}

Item::Item(String init_name)
{
	name = init_name;
}

Item::Item(String init_name, String texture_path, String touch_sound_path, String walk_sound_path)
{
	name = init_name;
	skin = Texture{ texture_path };
	touch_sound = Audio{ Audio::Stream, touch_sound_path };
	walk_sound = Audio{ Audio::Stream, walk_sound_path };
}
