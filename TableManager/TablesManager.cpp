//
// Created by Vladimir Sukiasyan on 26.05.2018.
//

#include <iostream>
#include <fstream>
#include "TablesManager.h"
#include "../DatabaseManager/DatabaseManager.h"

TablesManager::TablesManager(){}

TablesManager& TablesManager::operator=(const TablesManager& tablesManager){
    this->tables=tablesManager.tables;
    this->tableCurrentName=tablesManager.tableCurrentName;
    return *this;
}

void TablesManager::printTables() {
    fstream metafile(DatabaseManager::currentDirectory+"metafile.txt");
    if(!metafile.is_open()){
        cout<<"Can't open the metafile!"<<endl;
        return;
    }
    string tableName;
    while(getline(metafile,tableName)) cout<<tableName<<endl;
    cout<<endl;
    metafile.close();
}

void TablesManager::useTable(const char *tableName) {
    string tablePath=DatabaseManager::currentDirectory+tableName+".csv";

    fstream table(tablePath);
    if(!table.is_open()){
        cout<<"This table is not exist!";
        return;
    }
    this->tableCurrentName=tableName;
    this->curTable=&tables.at(tableName);
    table.close();
    return;

}

void TablesManager::createTable(const char *tableName) {
    string tablePath=DatabaseManager::currentDirectory+tableName+".csv";
    fstream table(tablePath, fstream::in|fstream::out|fstream::trunc);
    table.close();
    fstream metafile(DatabaseManager::currentDirectory+"metafile.txt");
    metafile<<endl<<tableName;
}

void TablesManager::readAllTables() {
    fstream metafile(DatabaseManager::currentDirectory+"metafile.txt");
    string tableName;
    while(getline(metafile,tableName)){
        Table table(tableName);
        table.readTable();
        tables.insert(pair<string,Table>(tableName,table));
    }
}

void TablesManager::printCurrentTable() {
    if(curTable!= nullptr) curTable->printTable();
}

void TablesManager::insertRow() {
    curTable->insertRow();
}

void TablesManager::deleteRow(int index) {
    curTable->deleteRow(index);
}

void TablesManager::saveTables() {
    for(auto it=tables.begin();it!=tables.end();it++){
        it->second.writeDBTable();
    }
}

void TablesManager::selectWhere() {
    cout<<"Enter name of Column:";
    string column,value;
    cin>>column;
    cout<<"Enter value:";
    cin>>value;

//    curTable->getRowsWhere();
}


