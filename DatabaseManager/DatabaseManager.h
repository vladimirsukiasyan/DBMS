//
// Created by Vladimir Sukiasyan on 20.05.2018.
//

#ifndef DBMS_DATABASEMANAGER_H
#define DBMS_DATABASEMANAGER_H

#include "string"
#include "../Table/Table.h"
#include "../TableManager/TablesManager.h"

using namespace std;

class DatabaseManager {
public:
    string databaseName;
    TablesManager tablesManager;
    static string currentDirectory;
    static string defaultDirectory;

    void printDatabases();

    TablesManager* useDatabase(const char *dbName);

    void createDatabase(const char *path);

    void addInfoToMetafile(fstream& fstream);

    void saveDatabase();
};


#endif //DBMS_DATABASEMANAGER_H