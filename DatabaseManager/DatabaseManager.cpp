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

string DatabaseManager::currentDirectory="..\\Databases\\";
string DatabaseManager::defaultDirectory="..\\Databases\\";

void DatabaseManager::printDatabases() {
    fstream metaDatabases("..\\Databases\\metafile.txt");
    if(!metaDatabases.is_open()){
        cout << "Can't open the metafile!"<<endl;
        return;
    }
    string dbName;
    cout<<"Databases:"<<endl;
    while(getline(metaDatabases, dbName)) cout<<dbName<<endl;
    cout<<endl;
    metaDatabases.close();
}

TablesManager DatabaseManager::useDatabase(const char *dbName) {
    string databasePath=currentDirectory+dbName;

    fstream database(databasePath+"\\metafile.txt");
    if(!database.is_open()){
        cout<<"This database is not exist!";
        return TablesManager();
    }
    database.close();
    this->databaseName=dbName;
    currentDirectory+=dbName;

    //загрузка всех таблиц данной бд в память
    TablesManager tablesManager;
    tablesManager.readAllTables();
    return tablesManager;
}

void DatabaseManager::createDatabase(const char *dbName) {
    string databasePath=currentDirectory+dbName;
    fstream database(databasePath+"\\metafile.txt");
    if(!database.is_open()){
        mkdir(databasePath.c_str());
        database.open(databasePath+"\\metafile.txt", fstream::in|fstream::out|fstream::trunc);
        fstream metafile(currentDirectory+"\\metafile.txt",fstream::app);
        metafile<<endl<<dbName;
    }

//    addInfoToMetafile(database);
    database.close();
}
void DatabaseManager::addInfoToMetafile(fstream& fstream) {

}

