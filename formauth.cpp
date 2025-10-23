#include "formauth.h"
#include "ui_formauth.h"
#include "QMainWindow"
#include "mainwindow.h"
#include "dbviewer.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QMessageBox>
#include <QErrorMessage>

QString dbName;
FormAuth::FormAuth(QWidget *parent,QString _dbName)
    : QWidget(parent)
    , ui(new Ui::FormAuth){
    ui->setupUi(this);
    ui->title->setText("Login to database: "+_dbName);
    dbName=_dbName;
    connect(ui->loginEdit,&QLineEdit::returnPressed, ui->loginBtn, &QPushButton::click);
    connect(ui->pwdEdit,&QLineEdit::returnPressed, ui->loginBtn, &QPushButton::click);

}
FormAuth::~FormAuth(){
    delete ui;
}

void FormAuth::on_loginBtn_clicked(){
    QSqlDatabase db;

    QString serverName = "localhost";
    QString user = ui->loginEdit->text();
    QString password = ui->pwdEdit->text();
    // "Resu.0987654321";
    if(user.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Enter username/password");
        return;
    }
    QString connectionString = QString(
        "Driver={ODBC Driver 17 for SQL Server};"
        "Server=%1;" "Database=%2;" "Uid=%3;" "Pwd=%4;"
    ).arg(serverName,dbName, user, password);

    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(connectionString);

    if (!db.open()) {
        qDebug() << "Помилка підключення: " << db.lastError().text();
        // ui->title->setText(db.lastError().text());
        QErrorMessage *msg = new QErrorMessage;
        msg->showMessage("Failed to connect. Error mesage: "+db.lastError().text());
    } else {
        // ui->title->setText("good");
        qDebug() << "Підключення успішне!";
        QMainWindow *mw = qobject_cast<QMainWindow*>(parent());
        QWidget * wid = new DBViewer(mw,dbName);
        wid->show();
        this->close();
    }
}
void FormAuth::on_cancelBtn_clicked(){
    QMainWindow *mw = qobject_cast<QMainWindow*>(parent());
    QWidget * wid = new MainWindow(mw);
    wid->show();
    this->close();
}

