#ifndef FORMAUTH_H
#define FORMAUTH_H

#include <QWidget>

namespace Ui {
class FormAuth;
}

class FormAuth : public QWidget
{
    Q_OBJECT

public:
    explicit FormAuth(QWidget *parent = nullptr,QString dbName="Airport");
    ~FormAuth();

private slots:
    void on_loginBtn_clicked();

    void on_cancelBtn_clicked();

private:
    Ui::FormAuth *ui;
};

#endif // FORMAUTH_H
