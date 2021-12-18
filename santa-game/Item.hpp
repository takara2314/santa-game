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

	Item();

	Item(String init_name);

	Item(String init_name, String texture_path);

};
