//
// Created by 小白白 on 2018-12-14.
//

#include "QtGuiApplication1.h"

#include "Model/GameSettings.h"
#include "Model/GameDir.h"
#include "Model/GameModeList.h"
#include <memory>
#include <string>

void QtGuiApplication1::readGameSettings()
{
	gamesettings = std::make_shared<GameSettings>(GameDir().get());
	const GameModeList gml;

	auto iter = std::find_if(gml.begin(), gml.end(), [target = gamesettings->Read("mp_gamemode")](auto _1) { return target == _1.first; });
	if(iter != gml.end())
	{
		ui.comboBox_gamemode->setCurrentIndex(std::distance(gml.begin(), iter));

	}

	try
	{
		ui.comboBox_botDifficulty->setCurrentIndex(std::stoi(gamesettings->Read("bot_difficulty")));
		ui.spinBox_botQuota->setValue(std::stoi(gamesettings->Read("bot_quota")));
		ui.checkBox_EnableBOT->setChecked(ui.spinBox_botQuota->value() != 0);
	} catch(const std::invalid_argument &e)
	{
		// error format
	}

}

void QtGuiApplication1::saveGameSettings()
{
	gamesettings->Write("mp_gamemode", ui.comboBox_gamemode->currentData().toString().toStdString());
	gamesettings->Write("bot_difficulty", std::to_string(ui.comboBox_botDifficulty->currentIndex()));
	gamesettings->Write("bot_quota", ui.checkBox_EnableBOT->isChecked() ? std::to_string(ui.spinBox_botQuota->value()) : "0");

	gamesettings->Save(GameDir().get());
}