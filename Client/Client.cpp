//
// Created by Vladimir Sukiasyan on 20.05.2018.
//

#include <iostream>
#include "Client.h"
#include "../DatabaseManager/DatabaseManager.h"
#include "../Table/Table.h"
#include "../TableManager/TablesManager.h"

void Client::run() {
    DatabaseManager databaseManager;

    //читаем все бд
    databaseManager.printDatabases();
    databaseManager.createDatabase("testDB1");

    TablesManager* tablesManager=databaseManager.useDatabase("testDB"); //получаем указатель на tableManager(поле DatabaseManager) со всеми таблицами бд
    tablesManager->printTables();

    tablesManager->useTable("Books");
    tablesManager->useTable("Abonements");
    tablesManager->useTable("Students");
    tablesManager->printCurrentTable();

    tablesManager->insertRow();
    tablesManager->printCurrentTable();
    tablesManager->deleteRow(0);
    tablesManager->printCurrentTable();
//    tablesManager->selectWhere();

    databaseManager.useDatabase("testDB1");

}
