#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formauth.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}
void MainWindow::authForm(QString dbName){
    QMainWindow *mw = qobject_cast<QMainWindow*>(parent());
    QWidget * wid = new FormAuth(mw,dbName);
    wid->show();
    this->close();
    // setCentralWidget(wid);

}
void MainWindow::on_btnPcCompany_clicked(){
    authForm("PcCompany");
}


void MainWindow::on_btnRecycle_clicked(){
    authForm("RecycleCompany");
}


void MainWindow::on_btnShips_clicked(){
    authForm("Ships");
}
void MainWindow::on_btnAirport_clicked(){
    authForm("Airport");
}

