#include "dbviewer.h"
#include "ui_dbviewer.h"
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlQuery>
#include <QInputDialog>
#include <QDebug>
struct MyQuery{
    QString name, sql, description,db;
};

int tableIndex;
int perms;
int selectedSql=-1;
QSqlTableModel* model;
QList<MyQuery> queries = {
    {"laptop.Price>1000",
        "select pc.model, pc.ram,pc.screen,pc.price "
        " from laptop as pc"
        " where pc.price > 1000;"
        ,"Displays laptops that are more expensive than 1000"
        ,"PcCompany"
    },
    {"laptop.hd>10",
        "select * from product as p"
        " join laptop as l on p.model=l.model"
        " where l.hd>10;"
        ,"Displays the manufacturer of those laptops that have a disk larger than 10gb"
        ,"PcCompany"
    },
    {"maker.laptops>=750",
        "select maker from product "
        " join pc on product.model = pc.model"
        " where maker != all("
        " select maker from product "
        " join laptop as l on product.model = l.model);"
        ,"Displays the manufacturer of those laptops that have 750Hz and more"
        ,"PcCompany"
    },
    {"income.date format",
        "select code, point, format(date, 'yyyy.MM.dd') as date, inc from income;"
        ,"Displays income.date in yyyy.MM.dd format"
        ,"RecycleCompany"
    }
    ,{"ships.name like %o",
        "select * from ships "
        " where ships.name like '%o' and not ships.name like '%go';"
        ,"Displays ships ending in 'o' in the name"
        ,"Ships"
    },
};
int getQueryIdByName(QString name){
    for(int i=0;i<queries.size();i++){
        if (queries[i].name==name)
            return i;
    }
    return -1;
}
DBViewer::DBViewer(QWidget *parent,QString dbName,int perms)
    : QWidget(parent), ui(new Ui::DBViewer){

    ui->setupUi(this);
    model = new QSqlTableModel(this);

    QSqlQuery query("SELECT TABLE_NAME FROM "+ dbName+".INFORMATION_SCHEMA.TABLES WHERE TABLE_TYPE='BASE TABLE';");
    while(query.next()){
        QVariant name = query.value(0);
        ui->comboBox->addItem(name.toString());
    }
    ui->comboBox->setCurrentIndex(0);
    if(perms==0){
        ui->saveBtn->setEnabled(false);
        ui->cancelBtn->setEnabled(false);
        ui->removeBtn->setEnabled(false);
        ui->addBtn->setEnabled(false);
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
    ui->queryList->clear();
    for(int i=0;i<queries.size();i++){
        MyQuery q = queries[i];
        if(q.db!=dbName)continue;
        ui->queryList->addItem(q.name);
    }
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
    QString filter = QInputDialog::getText(nullptr,"Search filter","Write a search filter with SQL WHERE syntax",QLineEdit::Normal);
    model->setFilter(filter);
    model->select();
}

void DBViewer::on_queryList_itemDoubleClicked(QListWidgetItem *item){
    selectedSql = getQueryIdByName(item->text());
    MyQuery q = queries[selectedSql];
    ui->queryDesc->setText(q.description+"\n\nSql Query:\n"+q.sql);
}
void DBViewer::on_startQueryBtn_clicked(){
    if(selectedSql==-1)return;
    MyQuery q = queries[selectedSql];
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery(q.sql);

    ui->queryTable->setModel(model);
    ui->queryTable->show();
}

