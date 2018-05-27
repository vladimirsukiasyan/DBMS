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

    tablesManager->createTable();

    tablesManager->useTable("Books");
    tablesManager->useTable("Abonements");
    tablesManager->useTable("Students");
    tablesManager->printCurrentTable();

    cout<<">>Insert Row:"<<endl;
    tablesManager->insertRow();
    tablesManager->printCurrentTable();
    cout<<">>Select Row:"<<endl;
    tablesManager->selectWhere();
    cout<<">>Delete rows with conditions:"<<endl;
    tablesManager->deleteRowsConditions();
    tablesManager->printCurrentTable();

//    cout<<">>clearColumnFromAllRows():"<<endl;
//    tablesManager->clearColumnFromAllRows();
//    tablesManager->printCurrentTable();

//    cout<<">>clearTable():"<<endl;
//    tablesManager->clearTable();
//    tablesManager->printCurrentTable();


    databaseManager.useDatabase("testDB1");

}
