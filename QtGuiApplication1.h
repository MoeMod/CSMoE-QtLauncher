#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_QtGuiApplication1.h"

class GameSettings;

class QtGuiApplication1 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication1(QWidget *parent = Q_NULLPTR);
	~QtGuiApplication1();
	
signals:
	void updateStatusBar(QString str);
	void GameDirChanged(QString path);

public slots:
	void updateMapList();

private:
	void onActionAbout();
	void onActionBrowseGameDir();
	void onActionLaunchGame();

private:
	// controllers
	void initNewGameData();
	void initGameModeList();
	void readGameSettings();
	void saveGameSettings();
	void setGameDir(QString str);

private:
	Ui::QtGuiApplication1Class ui;
	std::shared_ptr<GameSettings> gamesettings;
};
