#include "dbviewer.h"
#include "ui_dbviewer.h"
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QInputDialog>
struct MyQuery{
    QString name, sql, description;
};

int tableIndex;
QSqlTableModel* model;
QList<MyQuery> queries = {
{"asd","asdasd","asda"}
};
DBViewer::DBViewer(QWidget *parent,QString dbName)
    : QWidget(parent)
    , ui(new Ui::DBViewer){

    ui->setupUi(this);
    model = new QSqlTableModel(this);

    QSqlQuery query("SELECT TABLE_NAME FROM "+ dbName+".INFORMATION_SCHEMA.TABLES WHERE TABLE_TYPE='BASE TABLE';");
    while(query.next()){
        QVariant name = query.value(0);
        ui->comboBox->addItem(name.toString());
    }
    ui->comboBox->setCurrentIndex(0);
    // ui->tableView->setModel(model);
}
DBViewer::~DBViewer(){
    delete ui;
}
void DBViewer::on_openTableBtn_clicked(){
    QString selectedTable = ui->comboBox->itemText(tableIndex);

    model->setTable(selectedTable);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->show();

}
void DBViewer::on_comboBox_currentIndexChanged(int index){
    tableIndex=index;
}
void DBViewer::on_addBtn_clicked(){
    model->insertRow(model->rowCount());
}
void DBViewer::on_removeBtn_clicked(){
    QModelIndexList rows = ui->tableView->selectionModel()->selectedRows();
    if(rows.isEmpty()){
        QMessageBox::warning(this,"Delete","There is no selected rows for removing");
        return;
    }
    int beginRowIndex = rows.first().row();
    int endRowIndex = rows.last().row();
    if(endRowIndex>1){
        for(int i=endRowIndex;i>=beginRowIndex; --i){
            model->removeRow(i);
        }
    }else if(rows.size()==1){
        model->removeRow(beginRowIndex);
    }
}
void DBViewer::on_cancelBtn_clicked(){
    model->revertAll();
}
void DBViewer::on_saveBtn_clicked(){
    model->submitAll();
    // TODO: errors handling
}
void DBViewer::on_searchBtn_clicked(){
    QString filter = QInputDialog::getText(nullptr,"get string","Write a search filter with SQL WHERE syntax",QLineEdit::Normal);
    model->setFilter(filter);
    model->select();

}
