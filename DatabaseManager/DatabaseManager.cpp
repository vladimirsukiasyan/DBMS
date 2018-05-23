//
// Created by vova_ on 20.05.2018.
//
#include <fstream>
#include <iostream>
#include <cstring>
#include "DatabaseManager.h"
#include <direct.h>
using namespace std;

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

void DatabaseManager::useDatabase(const char *dbName) {
    string databasePath=currentDirectory+dbName;

    fstream database(databasePath+"\\metafile.txt");
    if(!database.is_open()){
        cout<<"This database is not exist!";
        return;
    }
    this->databaseName=dbName;
    currentDirectory+=dbName;

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

void DatabaseManager::printTables() {
    fstream metafile(currentDirectory+"\\metafile.txt");
    if(!metafile.is_open()){
        cout<<"Can't open the metafile!"<<endl;
        return;
    }
    string tableName;
    while(getline(metafile,tableName)) cout<<tableName<<endl;
    cout<<endl;
    metafile.close();
}

void DatabaseManager::useTable(const char *tableName) {
    string tablePath=currentDirectory+"\\"+tableName+".csv";

    fstream table(tablePath);
    if(!table.is_open()){
        cout<<"This database is not exist!";
        return;
    }
    this->tableName=tableName;
    currentDirectory+="\\";
    currentDirectory+=tableName;
}

void DatabaseManager::createTable(const char *tableName) {
    string tablePath=currentDirectory+"\\"+tableName+".csv";
    fstream table(tablePath, fstream::in|fstream::out|fstream::trunc);
}

void DatabaseManager::addInfoToMetafile(fstream& fstream) {

}

