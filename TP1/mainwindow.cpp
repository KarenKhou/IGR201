#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTextEdit>
#include <QToolBar>
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    QAction * openAction = new QAction(QIcon(":open.png"),tr("Open"),this);
    QAction * saveAction = new QAction(QIcon(":save.png"),tr("Save"),this);
    QAction * quitAction = new QAction(QIcon(":quit.png"),tr("Quit"),this);

    openAction->setShortcut(tr("Ctrl+O"));
    openAction->setToolTip(tr("Open File"));
    openAction->setStatusTip(tr("Open File"));

    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setToolTip(tr("Save File"));
    saveAction->setStatusTip(tr("Save File"));


    quitAction->setShortcut(tr("Ctrl+Q"));
    quitAction->setToolTip(tr("Quit File"));
    quitAction->setStatusTip(tr("Quit File"));


    QMenuBar * menubar = this->menuBar();
    QMenu * fileMenu = menubar->addMenu(tr("&File"));

    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(quitAction);

    QToolBar * toolbar = this->addToolBar(tr("File"));
    toolbar->addAction(openAction);
    toolbar->addAction(saveAction);
    toolbar->addAction(quitAction);

    this->statusBar();

}

MainWindow::~MainWindow()
{
    delete ui;
}
