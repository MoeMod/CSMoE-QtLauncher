//
// Created by 小白白 on 2018-12-14.
//

#include "QtGuiApplication1.h"

#include "Model/GameDir.h"
#include <QFileSystemModel>
#include <QFileInfo>

static inline bool isValidMapDir(const std::string &path)
{
	return QFileInfo(QString::fromStdString(path)).isDir();
}

void QtGuiApplication1::updateMapList()
{
	ui.comboBox_map->clear();
	QFileSystemModel *model = dynamic_cast<QFileSystemModel *>(ui.comboBox_map->model());
	if(!model)
		ui.comboBox_map->setModel(model = new QFileSystemModel(this));

	// find map dir
	std::string mapdir = GameDir().get() + "/csmoe/maps";
	if(!isValidMapDir(mapdir))
		mapdir = GameDir().get() + "/cstrike/maps";

	if(!isValidMapDir(mapdir))
		return;

	QModelIndex index = model->setRootPath(QString::fromStdString(mapdir));

	model->setNameFilters({"*.bsp"});
	model->setNameFilterDisables(false);

	// apply
	ui.comboBox_map->setModelColumn(0);
	ui.comboBox_map->setRootModelIndex(index);
}