//
// Created by Vladimir Sukiasyan on 20.05.2018.
//

#include <iostream>
#include <iomanip>
#include <Windows.h>
#include "Client.h"
#include "../DatabaseManager/DatabaseManager.h"
#include "../Table/Table.h"
#include "../TableManager/TablesManager.h"

void Client::run() {

    cout << setfill(' ') << setw(51) << "Команды для работы с СУБД:" << endl << endl;
    cout << ' ' << setfill('-') << setw(78) << ' ' << endl;
    cout << '|' << " Работа с БД: " << setfill(' ') << setw(9) << '|' << " Работа внутри БД: " << setw(9) << '|' << " Работа внутри таблицы: " << setw(3) << '|' << endl;
    cout << ' ' << setfill('-') << setw(78) << ' ' << endl;
    cout << '|' << " Создать БД - 1 " << setfill(' ') << setw(7) << '|' << " Список таблиц - 7 " << setfill(' ') << setw(9) << '|' << " Вывод таблицы - 11 " << setfill(' ') << setw(7) << '|' << endl;
    cout << ' ' << setfill('-') << setw(78) << ' ' << endl;
    cout << '|' << " Удалить БД - 2 " << setfill(' ') << setw(7) << '|' << " Создать таблицу - 8 " << setfill(' ') << setw(7) << '|' << setfill(' ') << setw(7) << " Вставить запись - 12 " << setfill(' ') << setw(5) << '|' << endl;
    cout << ' ' << setfill('-') << setw(78) << ' ' << endl;
    cout << '|' << " Список БД - 3 " << setfill(' ') << setw(8) << '|' << " Удалить таблицу - 9 " << setfill(' ') << setw(7) << '|' << " Очистить таблицу - 13 " << setfill(' ') << setw(4) << '|' << endl;
    cout << ' ' << setfill('-') << setw(78) << ' ' << endl;
    cout << '|' << " Использовать БД - 4 " << setfill(' ') << setw(2) << '|' << " Использовать таблицу - 11 " << '|' << " Вывод столбцов - 10 " << setfill(' ') << setw(6) << '|' << endl;
    cout << ' ' << setfill('-') << setw(78) << ' ' << endl;
    cout << '|' << " Открыть логи - 5 " << setfill(' ') << setw(5) << '|' << ' ' << setfill(' ') << setw(26) << ' ' << '|' << " Удалить запись - 14 " << setfill(' ') << setw(6) << '|' << endl;
    cout << ' ' << setfill('-') << setw(78) << ' ' << endl;
    cout << '|' << " Выход - 6 " << setfill(' ') << setw(12) << '|' << ' ' << setfill(' ') << setw(26) << ' ' << '|' << " Доб. столб. в конец - 15 " << '|' << endl;
    cout << ' ' << setfill('-') << setw(78) << ' ' << endl;
    cout << '|' << ' ' << setfill(' ') << setw(21) << ' ' << '|' << ' ' << setfill(' ') << setw(26) << ' ' << '|' << " Найти запись - 16 " << setfill(' ') << setw(8) << '|' << endl;
    cout << ' ' << setfill('-') << setw(78) << ' ' << endl;

//    DatabaseManager databaseManager;
//
//    //читаем все бд
//    databaseManager.printDatabases();
//    databaseManager.createDatabase("testDB1");
//
//    TablesManager* tablesManager=databaseManager.useDatabase("testDB"); //получаем указатель на tableManager(поле DatabaseManager) со всеми таблицами бд
//
//    tablesManager->printTables();
//
//    tablesManager->useTable("Books");
//    tablesManager->useTable("Abonements");
//    tablesManager->useTable("Students");
//    tablesManager->createTable();
//
//    tablesManager->printTables();
//    tablesManager->useTable("Teachers");
//    tablesManager->printCurrentTable();
//
//    cout<<">>Insert Row:"<<endl;
//    tablesManager->insertRow();
//    tablesManager->printCurrentTable();
//    cout<<">>Select Row:"<<endl;
//    tablesManager->selectWhere();
//    cout<<">>Delete rows with conditions:"<<endl;
//    tablesManager->deleteRowsConditions();
//    tablesManager->printCurrentTable();

//    cout<<">>clearColumnFromAllRows():"<<endl;
//    tablesManager->clearColumnFromAllRows();
//    tablesManager->printCurrentTable();

//    cout<<">>clearTable():"<<endl;
//    tablesManager->clearTable();
//    tablesManager->printCurrentTable();


//    databaseManager.useDatabase("testDB1");

}
