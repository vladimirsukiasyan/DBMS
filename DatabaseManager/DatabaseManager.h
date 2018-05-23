//
// Created by Vladimir Sukiasyan on 20.05.2018.
//

#ifndef DBMS_DATABASEMANAGER_H
#define DBMS_DATABASEMANAGER_H

#include "string"
using namespace std;

class DatabaseManager {
public:
    string databaseName;
    string tableName;
    string currentDirectory="..\\Databases\\";
    string defaultDirectory="..\\Databases\\";
    void printDatabases();

    void useDatabase(const char *dbName);

    void createDatabase(const char *path);

    void printTables();

    void useTable(const char *tableName);

    void createTable(const char *tableName);

    void addInfoToMetafile(fstream& fstream);
};


#endif //DBMS_DATABASEMANAGER_H
