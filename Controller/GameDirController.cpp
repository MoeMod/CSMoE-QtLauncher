//
// Created by 小白白 on 2018-12-14.
//

#include "QtGuiApplication1.h"

#include "Model/GameDir.h"

#include <QFileDialog>
#include <QMessageBox>

void QtGuiApplication1::onActionBrowseGameDir()
{
	QString path = QFileDialog::getExistingDirectory(this);
	if(!path.isEmpty())
	{
		setGameDir(path);
	}
}

void QtGuiApplication1::setGameDir(QString path)
{
	try
	{
		GameDir().set(path.toStdString());
		ui.PathEdit->setText(path);
		readGameSettings();
		updateMapList();

		emit GameDirChanged(path);
	}
	catch (const std::exception &e)
	{
		QMessageBox::warning(this, "Error", e.what());
	}
}