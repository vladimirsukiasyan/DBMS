//
// Created by Vladimir Sukiasyan on 25.05.2018.
//

#include <fstream>
#include <iostream>
#include <cstring>
#include "Table.h"
#include "../DBDate/DBDate.h"
#include "../DatabaseManager/DatabaseManager.h"


Table::Table(string name) {
    tableName = name;
}

Table::Table() {}
//Table& Table::operator=(const Table &tableManager) {
//    this->tableName=tableManager.tableName;
//    this->tablePath=tableManager.tablePath;
//}

void Table::readTable() {
    fstream tableFile(DatabaseManager::currentDirectory + tableName + ".csv");
    if (!tableFile.is_open()) {
        cout << "Can't open the table!";
        return;
    }
    getTableTitle(tableFile);
    getHeaderInfo(tableFile);
    getDataInfo(tableFile);
    tableFile.close();
}

void Table::getTableTitle(fstream &file) {
    getline(file, primaryKey);
}

void Table::getHeaderInfo(fstream &file) {
    string token;
    string line;
    string delim = "|";
    Columns column;
    getline(file, line);
    size_t pos = 0;
    while ((pos = line.find(delim)) != string::npos) {
        column.columnName = line.substr(0, pos);
        line.erase(0, pos + delim.length());
        pos = line.find(delim);
        column.colType = getType(line.substr(0, pos));
        line.erase(0, pos + delim.length());
        tableHeader.push_back(column);
    }
}

void Table::getDataInfo(fstream &file) {
    data.clear();
    string token;
    string line;
    string delim = "|";
    size_t pos = 0;
    while (!file.eof()) {
        Row row;
        getline(file, line);
        int i = 0;
        while ((pos = line.find(delim)) != string::npos) {
            token = line.substr(0, pos);
            line.erase(0, pos + delim.length());
            row.push_back(setValueToVoid(token, tableHeader[i].colType));
            ++i;
        }
        row.push_back(setValueToVoid(line, tableHeader[i].colType));
        data.push_back(row);
    }
}

DBType Table::getType(string token) {
    if (token == "NoType") return DBType::NoType;
    else if (token == "Int") return DBType::Int;
    else if (token == "Double") return DBType::Double;
    else if (token == "String") return DBType::String;
    else return DBType(Date);
}

string Table::setType(DBType dbType) {
    switch (dbType) {
        case DBType::String:
            return "String";
        case DBType::Int:
            return "Int";
        case DBType::Double:
            return "Double";
        case DBType::Date:
            return "Date";
    }
}

void *Table::setValueToVoid(string value, DBType dbType) {
    switch (dbType) {
        case DBType::Int:
            return new int(stoi(value));
        case DBType::Double:
            return new double(stof(value));
        case DBType::String:
            return new string(value);
        case DBType::Date:
            return new DBDate(value);
        default:
            return new string();
    }
}

void Table::printTable(vector<Row> table) {
    cout << "\n";
    for (auto item: table) {
        int i = 0;
        cout << "|";
        for (auto itemCol : item) {
            switch (tableHeader[i].colType) {

                case DBType::String: {
                    int y = sizeof(*reinterpret_cast<string *>(itemCol));
                    int z = (*reinterpret_cast<string *>(itemCol)).length();
                    int x = (y - z) / 2;
                    for (int i = 0; i < x; ++i) cout << ' ';
                    cout << *reinterpret_cast<string *>(itemCol);
                    if (z % 2 != 0) {
                        for (int i = 0; i < x+1; ++i) cout << ' ';
                    } else for (int i = 0; i < x; ++i) cout << ' ';
                    break;
                }

                case DBType::Int:{
                    int c = *reinterpret_cast<int *>(itemCol);
                    int z = 0;
                    while(c != 0) {
                        z++;
                        c /= 10;
                    }
                    int x = (16 - z) / 2;
                    for (int i = 0; i < x; ++i) cout << ' ';
                    cout << *reinterpret_cast<int *>(itemCol);
                    if (z % 2 == 0) {
                        for (int i = 0; i < x-1; ++i) cout << ' ';
                    } else for (int i = 0; i < x; ++i) cout << ' ';
                    break;
                }

                case DBType::Double: {
                    ostringstream c;
                    c << *reinterpret_cast<double *>(itemCol);
                    string str = c.str();
                    int z = str.length();
                    int x = (14 - z) / 2;
                    for (int i = 0; i < x; ++i) cout << ' ';
                    cout << *reinterpret_cast<double *>(itemCol);
                    if (z % 2 != 0) {
                        for (int i = 0; i < x+1; ++i) cout << ' ';
                    } else for (int i = 0; i < x; ++i) cout << ' ';
                    break;
                }
                case DBType::Date: {
                    for (int i = 0; i < 3; ++i) cout << ' ';
                    cout << *reinterpret_cast<DBDate *>(itemCol);
                    for (int i = 0; i < 3; ++i) cout << ' ';
                    break;
                }
                default:
                    cout << "Cant't defind the type of value!";
            }
            if (i++!=item.size()-1) {
                cout << "|";
            }
        }
        cout << "|";
        cout << endl;
    }
    cout << endl;
}

void Table::printTable() {
    printTable(data);
}

void Table::insertRow() {
    Row row;
    for (auto item : tableHeader) {
        cout << "Enter " << item.columnName << ": ";
        string enterValue;
        cin >> enterValue;
        void *writeValue;
        writeValue = setValueToVoid(enterValue, item.colType);
        row.push_back(writeValue);
    }
    data.push_back(row);
    cout << endl;
}

void Table::deleteRow(int index) {
    data.erase(data.begin() + index - 1);
}

void Table::writeDBTable() {
    setlocale(LC_ALL, "rus");
    fstream table;
    table.open(DatabaseManager::currentDirectory + tableName + ".csv", fstream::out); //Народ, всгда указывайте флаги! Я тут блин кучу времени потерял.
    table << primaryKey << endl;
    int i = 0;
    for (auto item: tableHeader) {
        table << item.columnName << "|" << setType(item.colType);
        if (i++ != tableHeader.size() - 1) {
            table << "|";
        }
    }
    i = 0;
    if (data.empty()) {
        table.close();
        return;
    }
    table << endl;
    for (auto item: data) {
        int j = 0;
        for (auto value: item) {
            switch (tableHeader[j].colType) {
                case DBType::String:
                    table << *reinterpret_cast<string *>(value);
                    break;
                case DBType::Int:
                    table << *reinterpret_cast<int *>(value);
                    break;
                case DBType::Double:
                    table << *reinterpret_cast<double *>(value);
                    break;
                case DBType::Date:
                    table << *reinterpret_cast<DBDate *>(value);
                    break;
            }
            if (j++ != item.size() - 1) {
                table << "|";
            }
        }
        if (i++ != data.size() - 1) {
            table << endl;
        }
    }
    table.close();
}

vector<Row> Table::getRowsWhere(string column, string value) {
    vector<Row> response;
    DBType dbType;
    int indexColumn = -1;
    for (int i = 0; i < tableHeader.size(); ++i)
        if (tableHeader[i].columnName == column) {
        indexColumn = i;
    }
    dbType = tableHeader[indexColumn].colType;
    for (auto record: data) {
        switch (dbType) {
            case DBType(Int): {
                if (*reinterpret_cast<int *>(record[indexColumn]) == stoi(value)) {
                    response.push_back(record);
                }
                break;
            }
            case DBType(Double): {
                if (*reinterpret_cast<double *>(record[indexColumn]) == stof(value)) {
                    response.push_back(record);
                }
                break;
            }
            case DBType(String): {
                if (*reinterpret_cast<string *>(record[indexColumn]) == value) {
                    response.push_back(record);
                }
                break;
            }
            case DBType(Date): {
                DBDate dbDate(value);
                if (*reinterpret_cast<DBDate *>(record[indexColumn]) == dbDate) {
                    response.push_back(record);
                }
                break;
            }
        }
    }
    return response;

}

void Table::deleteAllRows() {
    data.clear();
}

void Table::clearColumn(string columnName, string fillingValue) {
    int indexColumn = -1;
    for (int i = 0; i < tableHeader.size(); ++i) {
        if (tableHeader[i].columnName == columnName) {
            indexColumn = i;
        }
    }
    if(fillingValue=="") {
        switch (tableHeader[indexColumn].colType){
            case DBType::Int:
                fillingValue="0";
                break;
            case DBType::Double:
                fillingValue="0";
                break;
            case DBType::Date:
                fillingValue="0.0.0";
                break;
            case DBType::String:
                break;
        }
    }
    for (int i=0;i<data.size();++i) {
        data[i][indexColumn] = setValueToVoid(fillingValue, tableHeader[indexColumn].colType);
    }
}

void Table::deleteByValue(string columnName, string value) {
    int indexColumn = -1, indexRow = 0;
    for (int i = 0; i < tableHeader.size(); ++i) {
        if (tableHeader[i].columnName == columnName) {
            indexColumn = i;
            break;
        }
    }
    DBType dbType = tableHeader[indexColumn].colType;
    for (auto row = data.begin(); row < data.end(); row++) {
        switch (dbType) {
            case DBType(Int): {
                if (stoi(value) == *reinterpret_cast<int *>((*row)[indexColumn])) {
                    data.erase(data.begin() + indexRow--);
                    row--;
                }
                break;
            }
            case DBType(Double): {
                if (stof(value) == *reinterpret_cast<double *>((*row)[indexColumn])) {
                    data.erase(data.begin() + indexRow--);
                    row--;
                }
                break;
            }
            case DBType(String): {
                if (value == *reinterpret_cast<string *>((*row)[indexColumn])) {
                    data.erase(data.begin() + indexRow--);
                    row--;
                }
                break;
            }
            case DBType(Date): {
                DBDate dbDate(value);
                if (dbDate == *reinterpret_cast<DBDate *>((*row)[indexColumn])) {
                    data.erase(data.begin() + indexRow--);
                    row--;
                }
                break;
            }
        }
        indexRow++;
    }

}

bool Table::isColumnExist(string columnName) {
    for (int i = 0; i < tableHeader.size(); ++i) {
        if (tableHeader[i].columnName == columnName) return true;
    }
    return false;
}

void Table::setTableName(const string &tableName) {
    Table::tableName = tableName;
}

void Table::setPrimaryKey(const string &primaryKey) {
    Table::primaryKey = primaryKey;
}

void Table::setTableHeader(const TableHeader &tableHeader) {
    Table::tableHeader = tableHeader;
}

string Table::getTableName() {
    return tableName;
}

TableHeader& Table::getHeader() {
    return tableHeader;
}
