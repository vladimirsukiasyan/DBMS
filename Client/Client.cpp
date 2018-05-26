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

    TablesManager tablesManager=databaseManager.useDatabase("testDB"); //получаем tableManager со всеми таблицами в бд
    tablesManager.printTables();

    tablesManager.useTable("Students");
    tablesManager.useTable("Abonements");
    tablesManager.useTable("Books");
    tablesManager.printCurrentTable();

}
