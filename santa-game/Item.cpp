#include "Item.hpp"


///////////////////////////////////
//  コンストラクタ
///////////////////////////////////
Item::Item() {}

Item::Item(String name)
{
	m_name = name;
}

Item::Item(String name, String texture_path)
{
	m_name = name;
	m_skin = Texture{ texture_path };
}


///////////////////////////////////
//  描画処理
///////////////////////////////////
void Item::draw() {}
