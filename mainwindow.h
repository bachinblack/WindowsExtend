#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QAudio>
#include <QAudioInput>
#include <QModelIndex>
#include "inputs.h"
#include "audioloopback.h"

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
    Input           *in;
    Shortcut        *sc;
    AudioLoopBack   *audio;

    /* UI */
private:
    Ui::MainWindow *ui;
    void createUIInt(void);

public slots:
    void tryShow(const QSystemTrayIcon::ActivationReason &r);

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

    /* Toggle */
private:
    void showSC(void);
    void showMain(void);

    /* Setup */
private:
    void setupShortcut(void);
    void setupAudio(void);

private:
    void removeRow(void);
    void insertRow(const std::string& path, const std::string& sc);
    void insertColumn(const std::string& s);

private slots:
    void showWindow(void);
    void Disable(void);

private slots:
    void chVol(const int &nvol);
    void chDev(const int& ndev);
};

#endif // MAINWINDOW_H
