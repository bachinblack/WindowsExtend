#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    in = new Input();
    sc = in->getSC();
    disabled = false;
    setWindowTitle(tr("WinEx settings"));
    createActions();
    createTrayIcon();
    trayIcon->show();
    ui->setupUi(this);
    createUIInt();
    setupShortcut();
}

MainWindow::~MainWindow()
{
    delete sc;
    delete in;
    delete ui;
    delete trayIcon;
    delete trayIconMenu;
    delete openAction;
    delete disableAction;
    delete quitAction;
}

/* UI */

void MainWindow::createUIInt(void)
{
    ui->sKb->setID(EnActive::CONV);
    ui->sDis->setID(EnActive::ALL);
    ui->sInf->setID(EnActive::EXTS);
    ui->sInvX->setID(EnActive::INVX);
    ui->sInvY->setID(EnActive::INVY);
    ui->sSC->setID(EnActive::SC);
    connect(ui->sDis, SIGNAL(released()),this, SLOT(Disable()));
}

/*   TrayIcon   */

void MainWindow::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(openAction);
    trayIconMenu->addAction(disableAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    trayIcon->setContextMenu(trayIconMenu);
    trayIcon->setIcon(QIcon(":/images/resources/Luma.ico"));

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(tryShow(QSystemTrayIcon::ActivationReason)));
}

void MainWindow::tryShow(const QSystemTrayIcon::ActivationReason& r)
{
    if (r == QSystemTrayIcon::Trigger)
        {
            if (!this->isVisible()) {
                this->show();
            } else {
                this->hide();
            }
        }
}

/* Actions */

void MainWindow::createActions(void)
{
    openAction = new QAction(tr("Open settings"), this);
    connect(openAction, SIGNAL(triggered()), this, SLOT(showWindow()));

    disableAction = new QAction(tr("Disable/Enable"), this);
    connect(disableAction, SIGNAL(triggered()), this, SLOT(Disable()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}

/* Slots */

void MainWindow::showWindow(void) { if (!this->isVisible()) { this->show(); } }

void MainWindow::Disable(void)
{
    if (!disabled) {
        disabled = true;
        in->Disable();
        trayIcon->setIcon(QIcon(":/images/resources/RedLuma.ico"));
    } else {
        disabled = false;
        in->Enable();
        trayIcon->setIcon(QIcon(":/images/resources/Luma.ico"));
    }
    setActive(EnActive::ALL, disabled);
}

/* Shortcuts */

void MainWindow::setupShortcut(void)
{
    QStringListModel *model = sc->getSCList();

    ui->liSC->setModel(model);
    //ui->bDel->setEnabled(false);
}

/* window handling */

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        this->hide();
        event->ignore();
    }
}
