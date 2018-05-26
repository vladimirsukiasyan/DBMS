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
    tableName=name;
}
Table::Table() {}
//Table& Table::operator=(const Table &tableManager) {
//    this->tableName=tableManager.tableName;
//    this->tablePath=tableManager.tablePath;
//}

void Table::readTable() {
    fstream tableFile(DatabaseManager::currentDirectory+"\\"+tableName+".csv");
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
    getline(file,primaryKey);
}
void Table::getHeaderInfo(fstream &file) {
    string token,line,delim="|";
    Columns column;
    getline(file, line);
    size_t pos = 0;
    while ((pos = line.find(delim)) != string::npos) {
        column.columnName=line.substr(0, pos);
        line.erase(0, pos + delim.length());
        pos=line.find(delim);
        column.colType=getType(line.substr(0,pos));
        line.erase(0,pos+delim.length());
        tableHeader.push_back(column);
    }
}
void Table::getDataInfo(fstream &file) {
    data.clear();
    string token,line,delim="|";
    size_t pos=0;
    while (!file.eof()) {
        Row row;
        getline(file, line);
        int i = 0;
        while ((pos=line.find(delim))!=string::npos) {
            token=line.substr(0,pos);
            line.erase(0,pos+delim.length());
            row.push_back(setValueToVoid(token, tableHeader[i].colType));
            i++;
        }
        data.push_back(row);
    }
}
DBType Table::getType(string token) {
	if (token == "NoType") return DBType(NoType);
	else if (token == "Int32") return DBType(Int32);
	else if (token == "Double") return DBType(Double);
	else if (token == "String") return DBType(String);
	else return DBType(Date);
}
string Table::setType(DBType dbType) {
	switch (dbType) {
	case DBType(String): return "String"; break;
	case DBType(Int32): return "Int32"; break;
	case DBType(Double): return "Double"; break;
	case DBType(Date): return "Date"; break;
	}
}
void* Table::setValueToVoid(string value, DBType dbType) {
	switch (dbType) {
	case DBType(Int32): return new int(stoi(value)); break;
	case DBType(Double): return new double(stof(value)); break;
	case DBType(String): return new string(value); break;
	case DBType(Date): return new DBDate(value); break;
	default: return new string();
	}
}

void Table::printTable() {
	for (auto item: data) {
		int i = 0;
		for (auto itemCol : item) {
			switch (tableHeader[i].colType) {
				case DBType(String): cout << *reinterpret_cast<string*>(itemCol); break;
				case DBType(Int32): cout << *reinterpret_cast<int*>(itemCol); break;
				case DBType(Double): cout << *reinterpret_cast<double*>(itemCol); break;
				case DBType(Date): cout << *reinterpret_cast<DBDate*>(itemCol); break;
				default: cout << "Cant't defind the type of value!";
			}
			if (i++!=item.size()-1) cout << "|";
		}
		cout << endl;
	}
	cout << endl;
}
Row Table::createRow() {
	Row row;
	for (auto item : tableHeader) {
		cout << "Enter " << item.columnName << ": ";
		char* inValue = new char[100];
		void* writeValue;
		cin >> inValue;
		switch (item.colType) {
			case DBType(String): writeValue = new string(inValue); break;
			case DBType(Int32): writeValue = new int(atoi(inValue)); break;
			case DBType(Double): writeValue = new double(atof(inValue)); break;
			case DBType(Date): writeValue = new DBDate(inValue); break;
		}
		row.push_back(writeValue);
	}
	return row;
}
void DBTableTxt::addRow() {
	data.push_back(createRow());
}
void DBTableTxt::deleteRow(int index) {
	data.erase(data.begin()+index-1);
}
