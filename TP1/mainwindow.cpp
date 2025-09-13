#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QTextEdit>
#include <QToolBar>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>

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

    text = new QTextEdit(this);
    this->setCentralWidget(text);

    connect(openAction,SIGNAL(triggered()),this,SLOT(openSlot()));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(saveSlot()));
    connect(quitAction,SIGNAL(triggered()),this,SLOT(quitSlot()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openSlot(){
    std::cout<<"Open Clicked"<<std::endl;
    QString fileName= QFileDialog::getOpenFileName(this,"Open Text File","text.txt","Text Files(*.txt)");
    std::cout<< qPrintable(fileName) << std::endl;
    qDebug()<<fileName;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString content = in.readAll();
    text->setPlainText(content);
    }
}

void MainWindow::saveSlot(){
    std::cout<<"Save Clicked"<<std::endl;
    QString fileName= QFileDialog::getSaveFileName(this,"Save Text File","text.txt","Text Files(*.txt)");
    std::cout<< qPrintable(fileName) << std::endl;
    qDebug()<<fileName;
    QFile file(fileName);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        out<< text->toPlainText();
        text->close();
    }
}

void MainWindow::quitSlot(){
    std::cout<<"Quit Clicked"<<std::endl;
    QMessageBox * messageBox = new QMessageBox(this);
    messageBox->setWindowTitle("Confirm Action");
    messageBox->setText("Do you want to continue?");
    messageBox->setIcon(QMessageBox::Question);
    messageBox->setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    messageBox->setDefaultButton(QMessageBox::No);
    int ret = messageBox->exec();
    if (ret == QMessageBox::Yes) {
        this->close();
        qDebug() << "User clicked YES";
    } else {
        qDebug() << "User clicked NO";
    }
}

void MainWindow::closeEvent(QCloseEvent *event){
    MainWindow::quitSlot();
}
