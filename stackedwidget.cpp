#include "stackedwidget.h"
#include "ui_stackedwidget.h"
#include "mainwindow.h"


StackedWidget::StackedWidget(QWidget *parent)
    : QStackedWidget(parent)
    , ui(new Ui::StackedWidget){
    MainWindow* main = new MainWindow(this);
    addWidget(main);
    ui->setupUi(this);

}

StackedWidget::~StackedWidget()
{
    delete ui;
}
