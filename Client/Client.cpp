//
// Created by Vladimir Sukiasyan on 20.05.2018.
//

#include <iostream>
#include "Client.h"
#include "../DatabaseManager/DatabaseManager.h"

void Client::run() {
    DatabaseManager databaseManager;
    //читаем все бд
    databaseManager.printDatabases();
    databaseManager.createDatabase("testDB1");
    databaseManager.useDatabase("testDB");
    databaseManager.printTables();
    databaseManager.createTable("Teachers");
    databaseManager.useTable("Students");

    cout<<databaseManager.databaseName<<"."<<databaseManager.tableName;
}
