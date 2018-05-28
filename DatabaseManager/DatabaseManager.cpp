//
// Created by vova_ on 20.05.2018.
//
#include <fstream>
#include <iostream>
#include <cstring>
#include "DatabaseManager.h"
#include "../TableManager/TablesManager.h"
#include <direct.h>

using namespace std;

string DatabaseManager::currentDirectory = "..\\Databases\\";
string DatabaseManager::defaultDirectory = "..\\Databases\\";

void DatabaseManager::printDatabases() {
    fstream metaDatabases("..\\Databases\\metafile.txt");
    if (!metaDatabases.is_open()) {
        cout << "Can't open the metafile!" << endl;
        return;
    }
    string dbName;
    cout << "Databases:" << endl;
    while (getline(metaDatabases, dbName)) cout << dbName << endl;
    metaDatabases.close();
}

TablesManager *DatabaseManager::useDatabase(string dbName) {
    saveDatabase();
    currentDirectory = defaultDirectory;

    string databasePath = currentDirectory + dbName;
    fstream database(databasePath + "\\metafile.txt");
    if (!database.is_open()) {
        cout << "This database is not exist!";
        return new TablesManager();
    }
    database.close();
    this->databaseName = dbName;
    currentDirectory += dbName;
    currentDirectory += "\\";

    //очистка tableManager от данных предудущей бд
    tablesManager.tables.clear();
    tablesManager.curTable = nullptr;
    tablesManager.tableCurrentName = "";

    //загрузка всех таблиц данной бд в память
    tablesManager.readAllTables();
    return &tablesManager;
}

void DatabaseManager::createDatabase(string dbName) {
    string databasePath = defaultDirectory+ dbName;

    fstream database(databasePath + "\\metafile.txt");
    if (!database.is_open()) {
        mkdir(databasePath.c_str());
        database.open(databasePath + "\\metafile.txt", fstream::in | fstream::out | fstream::trunc);
        fstream metafile(defaultDirectory + "\\metafile.txt", fstream::app);
        metafile << endl << dbName;
    }

//    addInfoToMetafile(database);
    database.close();
}

void DatabaseManager::addInfoToMetafile(fstream &fstream) {

}

void DatabaseManager::saveDatabase() {
    tablesManager.saveTables();
}

void DatabaseManager::deleteDatabase(string dbName) {
    int result=system(("rd /s "+defaultDirectory+dbName).c_str());
    result==0?cout<<"Database has been deleted!"<<endl:cout<<"Database hasn't been deleted!";

    fstream metafile(defaultDirectory+"metafile.txt",fstream::in);
    string line;
    vector<string> metafileTemp;
    while(getline(metafile,line)) if(line!=dbName) metafileTemp.push_back(line);
    metafile.close();

    metafile.open(defaultDirectory+"metafile.txt",fstream::out|fstream::trunc); //чистим metafile;
    for(string line:metafileTemp) metafile<<line<<endl;
    metafile.close();

}

