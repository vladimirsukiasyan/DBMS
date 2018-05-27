//
// Created by Vladimir Sukiasyan on 26.05.2018.
//

#ifndef DBMS_TABLESMANAGER_H
#define DBMS_TABLESMANAGER_H


#include <map>
#include "../Table/Table.h"

class TablesManager {
public:
    map<string,Table> tables;
    string tableCurrentName;
    Table* curTable= nullptr;

    TablesManager();

    void printTables();

    void useTable(const char *tableName);

    void createTable();

    void readAllTables();

    TablesManager& operator=(const TablesManager& tablesManager);

    void printCurrentTable();

    void insertRow();

    void saveTables();

    void selectWhere();

    void clearTable();

    void deleteRowsConditions();

    void clearColumnFromAllRows();
};


#endif //DBMS_TABLESMANAGER_H
