//#pragma once
//#ifndef _DBTableTxt_
//#include "DBDate.h"
//#include <vector>
//#include <unordered_map>
//#include <fstream>
//#include <iostream>
//using namespace std;
//
//enum DBType {
//	NoType,
//	Int32,
//	Double,
//	String,
//	Date
//};
//struct Columns {
//	string columnName;
//	DBType colType;
//	int colLength;
//};
//typedef vector<void*> Row;
//typedef vector<Columns> TableHeader;
//class DBTableTxt {
//	string tableName;
//	string primaryKey;
//	string tablePath;
//	vector<Row> data;
//	TableHeader tableHeader;
//
//	void getTableInfo(fstream &file);
//	void getHeaderInfo(fstream &file);
//	void getDataInfo(fstream &file);
//	void* setValue(char*, DBType dbType);
//	DBType getType(string token);
//	string setType(DBType dbType);
//public:
//	void readDBTable(string tablePath);
//	void printDBTable();
//	void writeDBTable();
//	Row operator[](int index);
//	void setPrimaryKey(string primKey);
//	int getSize();
//	void setFileName(string path);
//	void setTableName(string tName);
//	string getFileName();
//	string getTableName();
//	string getPrimaryKey();
//	TableHeader getHeader();
//	void setHeader(TableHeader& hdr);
//	void addRow();
//	Row getRow(int index);
//	Row createRow();
//	void deleteRow(int index);
//};
//#endif // !_DBTableTxt_