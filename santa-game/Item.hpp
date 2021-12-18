#pragma once


///////////////////////////////////
//  アイテム
///////////////////////////////////
class Item
{
private:

	String m_name = U"空気";
	Texture m_skin;

public:

	Item();

	Item(String name);

	Item(String name, String texture_path);

	void draw();
};
