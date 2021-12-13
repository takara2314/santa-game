#pragma once


///////////////////////////////////
//  アイテム
///////////////////////////////////
class Item
{
private:

	String m_name;
	Texture m_skin{ U"present.png" };

public:

	Item();

	void draw();
};
