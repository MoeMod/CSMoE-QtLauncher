#include "QtGuiApplication1.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
#if defined(Q_OS_LINUX) || defined(Q_OS_WIN)
#if (QT_VERSION >= QT_VERSION_CHECK(5,9,0))
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
#endif
	QApplication a(argc, argv);
	QtGuiApplication1 w;
	w.show();
	return a.exec();
}
