//
// Created by 小白白 on 2018-12-14.
//

#include "QtGuiApplication1.h"

#include "Model/GameModeList.h"

void QtGuiApplication1::initGameModeList()
{
	QComboBox *b = ui.comboBox_gamemode;
	b->clear();
	for(auto &&gm : GameModeList())
	{
		b->addItem(gm.second, gm.first);
	}
}