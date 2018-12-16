//
// Created by 小白白 on 2018-12-14.
//

#include "QtGuiApplication1.h"
#include "Model/GameDir.h"
#include "Model/GameSettings.h"

#include <QProcess>
#include <QMessageBox>
#include <QFileInfo>

#include <algorithm>

#if defined(Q_OS_MAC)
constexpr const char *GameExe()
{
	return "csmoe_macos";
}
#elif defined(Q_OS_LINUX)
constexpr const char *GameExe()
{
	return "csmoe_linux";
}
#elif defined(Q_OS_WIN)
constexpr const char *GameExe()
{
	return "csmoe_win32.exe";
}
#endif

static inline QString AdjustMapName(const QString &str)
{
	if(str.size() <= 4)
		return str;
	if(str.endsWith(".bsp"))
		return str.left(str.size() - 4);
	return str;
}

void QtGuiApplication1::onActionLaunchGame()
{
	// find exec
	std::string exec;
	if(!QFileInfo(QString::fromStdString(exec = GameDir().get() + "/" + GameExe())).exists())
		if (!QFileInfo(QString::fromStdString(exec = GameDir().get() + "/xash3d")).exists())
		{
			QMessageBox::critical(this, "Error: ", QString() + (GameExe()) + " not found");
			return;
		}

	// save config
	saveGameSettings();

	QStringList parm {
		"+game csmoe",
		"+deathmatch 1",
		"+maxplayers " + QString::fromStdString(gamesettings->Read("maxplayers")),
		"+map " + AdjustMapName(ui.comboBox_map->currentText())
	};

	if(!QProcess::startDetached(QString::fromStdString(exec), parm, QString::fromStdString(GameDir().get())))
		QMessageBox::critical(this, "Error: Cannot execute ", QString::fromStdString(exec));
}