#include "QtGuiApplication1.h"

#include <QFileDialog>
#include <QMessageBox>

#ifdef Q_OS_MACOS
#include <QtMacExtras/QMacToolBar>
#include <QWindow>
#include "Platform/TouchBar.h"
#endif

#include <memory>

#include "Model/GameModeList.h"


QtGuiApplication1::QtGuiApplication1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.actionAbout, &QAction::triggered, this, &QtGuiApplication1::onActionAbout);
	connect(ui.actionBrowseGameDir, &QAction::triggered, this, &QtGuiApplication1::onActionBrowseGameDir);
	connect(ui.actionLaunchGame, &QAction::triggered, this, &QtGuiApplication1::onActionLaunchGame);

	connect(ui.pushButton_Advanced, &QPushButton::clicked, [=](){ui.stackedWidget_NewGame->setCurrentIndex(ui.stackedWidget_NewGame->currentIndex() + 1);});
	connect(ui.buttonBox_NewGameAdvanced, &QDialogButtonBox::rejected, [=](){ui.stackedWidget_NewGame->setCurrentIndex(0);});

	connect(ui.verticalStackedWidget_Options, &QStackedWidget::currentChanged, [=](int _1){ui.buttonBox_Options->setVisible(_1!=0);});
	connect(ui.toolButton_Audio, &QToolButton::clicked, [=]{ui.verticalStackedWidget_Options->setCurrentWidget(ui.OptionsSubAudio);});
	connect(ui.toolButton_Video, &QToolButton::clicked, [=]{ui.verticalStackedWidget_Options->setCurrentWidget(ui.OptionsSubVideo);});
	connect(ui.toolButton_Voice, &QToolButton::clicked, [=]{ui.verticalStackedWidget_Options->setCurrentWidget(ui.OptionsSubVoice);});
	connect(ui.toolButton_Keyboard, &QToolButton::clicked, [=]{ui.verticalStackedWidget_Options->setCurrentWidget(ui.OptionsSubKeyboard);});
	connect(ui.toolButton_Multiplay, &QToolButton::clicked, [=]{ui.verticalStackedWidget_Options->setCurrentWidget(ui.OptionsSubMultiplay);});
	connect(ui.toolButton_GamePad, &QToolButton::clicked, [=]{ui.verticalStackedWidget_Options->setCurrentWidget(ui.OptionsSubGamepad);});
	connect(ui.toolButton_Mouse, &QToolButton::clicked, [=]{ui.verticalStackedWidget_Options->setCurrentWidget(ui.OptionsSubMouse);});
	connect(ui.toolButton_Touch, &QToolButton::clicked, [=]{ui.verticalStackedWidget_Options->setCurrentWidget(ui.OptionsSubTouch);});
	connect(ui.buttonBox_Options, &QDialogButtonBox::rejected, [=]{ui.verticalStackedWidget_Options->setCurrentIndex(0);});
	ui.verticalStackedWidget_Options->setCurrentIndex((0));
	ui.buttonBox_Options->setVisible(false);

	setWindowTitle("Counter-Strike Mobile-oriented Edition");
	updateStatusBar("CSMoE Launcher (Qt-based) by MoeMod");

	initNewGameData();

	//this->setWindowFlag(Qt::WindowStaysOnTopHint, true);

#ifdef Q_OS_MACOS
	// Mac specific

	QMacToolBar *toolBar = new QMacToolBar(this);

	// pages
	toolBar->addStandardItem(QMacToolBarItem::FlexibleSpace);
	//toolBar->addSeparator();
	for(int i=0;i<ui.centralWidget->count();++i)
	{

		QMacToolBarItem *item = toolBar->addItem(ui.centralWidget->tabIcon(i), ui.centralWidget->tabText(i));
		item->setSelectable(true);
		connect(
				item,
				&QMacToolBarItem::activated,
				[=](){ui.centralWidget->setCurrentWidget(ui.centralWidget->widget(i));}
				);

	}
	//toolBar->addSeparator();
	toolBar->addStandardItem(QMacToolBarItem::FlexibleSpace);
	InstallTouchBar(toolBar);

#if 0
	QMacToolBarItem *item = toolBar->addItem(this->windowIcon(), QString());
	item->setSelectable(false);
	connect(
			item,
			&QMacToolBarItem::activated,
			[=](){ onActionAbout(); }
	);
#endif


	this->window()->windowHandle()->handle();
	this->window()->winId(); // create window->windowhandle()
	toolBar->attachToWindow(this->window()->windowHandle());

	ui.centralWidget->tabBar()->setVisible(false);
	ui.statusBar->setVisible(false);

#endif

}

QtGuiApplication1::~QtGuiApplication1() = default;

void QtGuiApplication1::initNewGameData()
{
	initGameModeList();
	setGameDir(QApplication::applicationDirPath());
}

void QtGuiApplication1::onActionAbout()
{
	QMessageBox::about(this, "About", "I am a simple Qt template. \n Made by MoeMod in Fall 2018.");
}
