//
// Created by Vladimir Sukiasyan on 25.05.2018.
//

#ifndef DBMS_Table_H
#define DBMS_Table_H

#include <vector>
#include "string"
using namespace std;

enum DBType {
    NoType,
    Int32,
    Double,
    String,
    Date
};

struct Columns {
    string columnName;
    DBType colType;
//    int colLength;
};

typedef vector<void*> Row;
typedef vector<Columns> TableHeader;

class Table{
    string tableName;
    string primaryKey;
    vector<Row> data;
    TableHeader tableHeader;

public:
    Table(string name);
    Table();
    Table& operator=(const Table &Table);

    void readTable();

    void getHeaderInfo(fstream &file);

    void getDataInfo(fstream &file);

    void getTableTitle(fstream &file);

    DBType getType(string token);

    string setType(DBType dbType);

    void *setValueToVoid(string value, DBType dbType);

    void printTable();

    Row createRow();
};


#endif //DBMS_Table_H