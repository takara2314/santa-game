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

Item::Item(String init_name, String texture_path)
{
	name = init_name;
	skin = Texture{ texture_path };
}
