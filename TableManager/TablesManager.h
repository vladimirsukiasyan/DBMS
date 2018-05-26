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

    TablesManager();

    void printTables();

    void useTable(const char *tableName);

    void createTable(const char *tableName);

    void readAllTables();

    TablesManager& operator=(const TablesManager& tablesManager);

    void printCurrentTable();
};


#endif //DBMS_TABLESMANAGER_H