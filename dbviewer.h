#ifndef DBVIEWER_H
#define DBVIEWER_H

#include <QWidget>

namespace Ui {
class DBViewer;
}

class DBViewer : public QWidget
{
    Q_OBJECT

public:
    explicit DBViewer(QWidget *parent = nullptr,QString dbName="");
    ~DBViewer();

private slots:
    void on_openTableBtn_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_addBtn_clicked();

    void on_removeBtn_clicked();

    void on_cancelBtn_clicked();

    void on_saveBtn_clicked();

    void on_searchBtn_clicked();

private:
    Ui::DBViewer *ui;
};

#endif // DBVIEWER_H
