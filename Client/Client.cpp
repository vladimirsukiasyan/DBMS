//
// Created by Vladimir Sukiasyan on 20.05.2018.
//

#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <fstream>
#include "Client.h"
#include "../DatabaseManager/DatabaseManager.h"
#include "../Table/Table.h"
#include "../TableManager/TablesManager.h"
#include "../UserLog/UserLog.h"

void Client::run() {
    DatabaseManager databaseManager;
    TablesManager* tablesManager;

    //======================//
    UserLog::Instance().getUser();
    //======================//
    int command;
    printCommands();
    while(true){
        cout<<">>";
        cin>>command;
        switch (command){
            case 1: {
                string dbName;
                cout<<"Enter the name of database: ";
                cin>>dbName;
                databaseManager.createDatabase(dbName);
                break;
            }
            case 2: {
                string dbName;
                cout<<"Enter the name of database: ";
                cin>>dbName;
                databaseManager.deleteDatabase(dbName);
                break;
            }
            case 3: {
                databaseManager.printDatabases();
                break;
            }
            case 4: {
                string dbName;
                cout<<"Enter the name of database: ";
                cin>>dbName;
                tablesManager=databaseManager.useDatabase(dbName);
                break;
            }
            case 5:{
                system("..\\UserLog.txt");
                break;
            }
            case 6:{
                printCommands();
                break;
            }
            case 7:{//просто сохранение
                databaseManager.saveDatabase();
                break;
            }

            case 8:{ //выход из проги с сохранением
                databaseManager.saveDatabase();
                return;
            }
            case 9:{
                tablesManager->printTables();
                break;
            }
            case 10:{
                tablesManager->createTable();
                break;
            }
            case 11:{
                string tableName;
                cout<<"Enter name of table: ";
                cin>>tableName;
                if(tableName==tablesManager->tableCurrentName) {
                    cout<<"You can't delete the table that you are using!";
                    break;
                }
                tablesManager->deleteTable(tableName);
                break;
            }
            case 12:{
                string tableName;
                cout<<"Enter name of table: ";
                cin>>tableName;
                tablesManager->useTable(tableName);
                break;
            }
            case 13:{
                tablesManager->printCurrentTable();
                break;
            }
            case 14:{
                tablesManager->insertRow();
                break;
            }
            case 15:{
                tablesManager->clearTable();
                break;
            }
            case 16:{
                tablesManager->printColumns();
                break;
            }
            case 17:{
                tablesManager->deleteRowsConditions();
                break;
            }
            case 18:{
                tablesManager->selectWhere();
                break;
            }
            default: cout<<"Unknown command!";
        }
        cout<<endl;
    }


}

void Client::printCommands() {
    cout << setfill(' ') << setw(51) << "Commands for working with DBMS:" << endl << endl;
    cout << '+' << setfill('-') << setw(82) << '+' << endl;
    cout << '|' << " Working with DB: " << setfill(' ') << setw(4) << '|' << " Work inside DB: " << setw(11) << '|' << " Work inside the table: " << setw(8) << '|' << endl;
    cout << '+' << setfill('-') << setw(82) << '+' << endl;
    cout << '|' << " Create DB - 1 " << setfill(' ') << setw(7) << '|' << " List of tables - 9 " << setfill(' ') << setw(8) << '|' << " The output table - 13 " << setfill(' ') << setw(9) << '|' << endl;
    cout << '+' << setfill('-') << setw(82) << '+' << endl;
    cout << '|' << " Delete DB - 2 " << setfill(' ') << setw(7) << '|' << " Create the table - 10 " << setfill(' ') << setw(5) << '|' << setfill(' ') << setw(7) << " Insert a record - 14 " << setfill(' ') << setw(10) << '|' << endl;
    cout << '+' << setfill('-') << setw(82) << '+' << endl;
    cout << '|' << " DB list - 3 " << setfill(' ') << setw(9) << '|' << " Delete the table - 11 " << setfill(' ') << setw(5) << '|' << " Clear the table - 15 " << setfill(' ') << setw(10) << '|' << endl;
    cout << '+' << setfill('-') << setw(82) << '+' << endl;
    cout << '|' << " Use the DB - 4 " << setfill(' ') << setw(6) << '|' << " Use the table - 12 " << setfill(' ') << setw(8) << '|' << " Column output - 16 " << setfill(' ') << setw(12) << '|' << endl;
    cout << '+' << setfill('-') << setw(82) << '+' << endl;
    cout << '|' << " Open logs - 5 " << setfill(' ') << setw(7) << '|' << ' ' << setfill(' ') << setw(26) << ' ' << '|' << " Delete a record - 17 " << setfill(' ') << setw(10) << '|' << endl;
    cout << '+' << setfill('-') << setw(82) << '+' << endl;
    cout << '|' << " Print commands - 6 " << setfill(' ') << setw(2) << '|' << ' ' << setfill(' ') << setw(26) << ' ' << '|' << " Find records(conditions) - 18 " << '|' << endl;
    cout << '+' << setfill('-') << setw(82) << '+' << endl;
    cout << '|' << " Save DB - 7 " << setfill(' ') << setw(8) << ' ' << '|' << ' ' << setfill(' ') << setw(26) << ' ' << '|' << ' '  << setfill(' ') << setw(31) << '|' << endl;
    cout << '+' << setfill('-') << setw(82) << '+' << endl;
    cout << '|' << " Exit - 8" << setfill(' ') << setw(12) << ' ' << '|' << ' ' << setfill(' ') << setw(26) << ' ' << '|' << ' '  << setfill(' ') << setw(31) << '|' << endl;
    cout << '+' << setfill('-') << setw(82) << '+' << endl;
}

