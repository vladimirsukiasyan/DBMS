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
    fstream tableFile(DatabaseManager::currentDirectory+tableName+".csv");
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
		row.push_back(setValueToVoid(line,tableHeader[i].colType));
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
void Table::insertRow() {
	Row row;
	for (auto item : tableHeader) {
		cout << "Enter " << item.columnName << ": ";
		string enterValue;
		cin >> enterValue;
		void* writeValue;
		switch (item.colType) {
			case DBType(String): writeValue = new string(enterValue); break;
			case DBType(Int32): writeValue = new int(stoi(enterValue)); break;
			case DBType(Double): writeValue = new double(stof(enterValue)); break;
			case DBType(Date): writeValue = new DBDate(enterValue); break;
		}
		row.push_back(writeValue);
	}
	data.push_back(row);
	cout<<endl;
}
void Table::deleteRow(int index) {
	data.erase(data.begin()+index-1);
}
void Table::writeDBTable() {
	setlocale(LC_ALL, "rus");
	fstream table;
	table.open(DatabaseManager::currentDirectory+tableName+".csv");
	table << primaryKey << endl;
	int i = 0;
	for (auto item: tableHeader) {
		table << item.columnName << "|" << setType(item.colType);
		if (i++!= tableHeader.size()-1) table << "|";
	}
	i = 0;
	table << endl;
	for (auto item: data) {
		int j = 0;
		for (auto value: item) {
			switch (tableHeader[j].colType) {
				case DBType(String): table << *reinterpret_cast<string*>(value); break;
				case DBType(Int32): table << *reinterpret_cast<int*>(value); break;
				case DBType(Double): table << *reinterpret_cast<double*>(value); break;
				case DBType(Date): table << *reinterpret_cast<DBDate*>(value); break;
			}
			if (j++!=item.size()-1) table << "|";
		}
		if(i++!=data.size()-1) table << endl;
	}
	table.close();
}

void Table::getRowsWhere(string column,string value) {
//	for(auto item: data){
//		item.
//	}

}
