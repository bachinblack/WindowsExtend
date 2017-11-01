#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include "inputs.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool disabled;

private:
    void closeEvent(QCloseEvent *event);
    Input   in;

    /* UI */
private:
    Ui::MainWindow *ui;
    void createUIInt(void);

public slots:
    void clickInput(void);
    void clickShortcut(void);

    /* TrayIcon */
private:
    void createTrayIcon(void);
    void createActions(void);
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    /* Actions */
private:
    QAction *openAction;
    QAction *disableAction;
    QAction *quitAction;

private slots:
    void showWindow(void);
    void Disable(void);
};

#endif // MAINWINDOW_H