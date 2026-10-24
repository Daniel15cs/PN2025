#ifndef DBVIEWER_H
#define DBVIEWER_H

#include <QListWidgetItem>
#include <QWidget>

namespace Ui {
class DBViewer;
}

class DBViewer : public QWidget
{
    Q_OBJECT

public:
    explicit DBViewer(QWidget *parent = nullptr,QString dbName="",int perms=0);
    ~DBViewer();

private slots:
    void on_openTableBtn_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void on_addBtn_clicked();

    void on_removeBtn_clicked();

    void on_cancelBtn_clicked();

    void on_saveBtn_clicked();

    void on_searchBtn_clicked();

    void on_queryList_itemDoubleClicked(QListWidgetItem *item);

    void on_startQueryBtn_clicked();

private:
    Ui::DBViewer *ui;
};

#endif // DBVIEWER_H
