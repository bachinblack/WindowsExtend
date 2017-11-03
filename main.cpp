#include <QApplication>
#include <QMessageBox>
#include "mainwindow.h"

bool createMessage(const char *title, const char *body)
{
    QMessageBox msgBox;

    (void)title;
    msgBox.setText(body);
    msgBox.exec();
    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    if (!QSystemTrayIcon::isSystemTrayAvailable())
            QMessageBox::critical(0, QObject::tr("Systray"), QObject::tr("I couldn't detect any system tray on this system."));
    w.show();
    return a.exec();
}
