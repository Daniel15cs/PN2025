#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnPcCompany_clicked();

    void on_btnRecycle_clicked();

    void on_btnShips_clicked();

    void authForm(QString dbName);
    void on_btnAirport_clicked();

private:
    Ui::MainWindow *ui;
        QStackedWidget *stack;

};
#endif // MAINWINDOW_H
