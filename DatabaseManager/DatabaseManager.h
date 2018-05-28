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

    TablesManager *useDatabase(string dbName);

    void createDatabase(string basicString);

    void addInfoToMetafile(fstream &fstream);

    void saveDatabase();

    void deleteDatabase(string basicString);
};


#endif //DBMS_DATABASEMANAGER_H