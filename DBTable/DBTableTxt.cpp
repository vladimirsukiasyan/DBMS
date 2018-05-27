//#include "DBTableTxt.h"
//using namespace std;
//
//void DBTableTxt::getTableInfo(fstream &file) {
//	char *next_token, *token, *delims = "|";
//	string str;
//	getline(file, str); //÷òåíèå çàãîëîâêà òàáëèöû
//	next_token = (char*)str.c_str();
//	//öèêë ïî ñëîâàì (ëåêñåìàì) â ñòðîêå
//	if ((token = strtok_s(next_token, delims, &next_token)) != NULL) {
//		tableName = token;
//	}
//	else cout << "\nÎøèáêà ÷òåíèÿ èìåíè òàáëèöû!";
//	if ((token = strtok_s(next_token, delims, &next_token)) != NULL) {
//		primaryKey = token;
//	}
//	else cout << "\nÎøèáêà ÷òåíèÿ êëþ÷à òàáëèöû!";
//}
//void DBTableTxt::getHeaderInfo(fstream &file) {
//	tableHeader.clear(); //î÷èñòêà çàãîëîâêà òàáëèöû äëÿ íîâîé òàáëèöû
//	char *next_token, *token, *delims = "|";
//	string str;
//	Columns column;
//	getline(file, str); //÷òåíèå çàãîëîâêà òàáëèöû
//	next_token = (char*)str.c_str();
//	//öèêë ïî ñëîâàì (ëåêñåìàì) â ñòðîêå
//	while ((token = strtok_s(next_token, delims, &next_token)) != NULL) {
//		column.columnName = token;
//		token = strtok_s(next_token, delims, &next_token);
//		column.colType = getType(token);
//		token = strtok_s(next_token, delims, &next_token);
//		column.colLength = atoi(token);
//		tableHeader.push_back(column);
//	}
//}
//void DBTableTxt::getDataInfo(fstream &file) {
//	data.clear();
//	char *next_token, *token, *delims = "|";
//	string str;
//	while (!file.eof()) {
//		int i = 0;
//		Row row;
//		getline(file, str); //÷òåíèå çàãîëîâêà òàáëèöû
//		next_token = (char*)str.c_str();
//		//öèêë ïî ñëîâàì (ëåêñåìàì) â ñòðîêå
//		while ((token = strtok_s(next_token, delims, &next_token)) != NULL) {
//			row.push_back(setValue(token, tableHeader[i].colType));
//			i++;
//		}
//		data.push_back(row);
//	}
//}
//void DBTableTxt::readDBTable(string path) {
//	tablePath=path;
//	fstream file(tablePath);
//	if (!file.is_open()) {
//		cout << "Can't open the file!";
//		system("pause");
//		exit(-1);
//	}
//	getTableInfo(file);
//	getHeaderInfo(file);
//	getDataInfo(file);
//	file.close();
//}
//void DBTableTxt::printDBTable() {
//	for (auto item: data) {
//		int i = 0;
//		for (auto itemCol : item) { //data[i]-ïîëó÷åíèÿ îáúåêòà Row
//			switch (tableHeader[i].colType) {
//				case DBType(String): cout << *(string*)itemCol; break;
//				case DBType(Int32): cout << *(int*)itemCol; break;
//				case DBType(Double): cout << *(double*)itemCol; break;
//				case DBType(Date): cout << *(DBDate*)itemCol; break;
//				default: cout << "Cant't defind the type of value!";
//			}
//			if (i++!=item.size()-1) cout << "|";
//		}
//		cout << endl;
//	}
//	cout << endl;
//}
//void DBTableTxt::writeDBTable() {
//	setlocale(LC_ALL, "rus");
//	fstream file;
//	file.open(tablePath);
//	file << tableName << "|" << primaryKey << endl;
//	int i = 0;
//	for (auto item: tableHeader) {
//		file << item.columnName << "|" << setType(item.colType) << "|" << item.colLength;
//		if (i++!= tableHeader.size()-1) file << "|";
//	}
//	i = 0;
//	file << endl;
//	for (auto item: data) {
//		int j = 0;
//		for (auto value: item) {
//			switch (tableHeader[j].colType) {
//				case DBType(String): file << *(string*)value; break;
//				case DBType(Int32): file << *(int*)value; break;
//				case DBType(Double): file << *(double*)value; break;
//				case DBType(Date): file << *(DBDate*)value; break;
//			}
//			if (j++!=item.size()-1) file << "|";
//		}
//		if(i++!=data.size()-1) file << endl;
//	}
//	file.close();
//}
//void* DBTableTxt::setValue(char* value, DBType dbType) {
//	switch (dbType) {
//	case DBType(Int32): return new int(atoi(value)); break;
//	case DBType(Double): return new double(atof(value)); break;
//	case DBType(String): return new string(value); break;
//	case DBType(Date): return new DBDate(value); break;
//	default: return new string();
//	}
//}
//Row DBTableTxt::operator[](int index) {
//	return data[index];
//}
//DBType DBTableTxt::getType(string token) {
//	if (token == "NoType") return DBType(NoType);
//	else if (token == "Int32") return DBType(Int32);
//	else if (token == "Double") return DBType(Double);
//	else if (token == "String") return DBType(String);
//	else return DBType(Date);
//}
//string DBTableTxt::setType(DBType dbType) {
//	switch (dbType) {
//	case DBType(String): return "String"; break;
//	case DBType(Int32): return "Int32"; break;
//	case DBType(Double): return "Double"; break;
//	case DBType(Date): return "Date"; break;
//	}
//}
//Row DBTableTxt::createRow() {
//	Row row;
//	for (auto item : tableHeader) {
//		cout << "Ââåäèòå " << item.columnName << ": ";
//		char* inValue = new char[100];
//		void* writeValue;
//		cin >> inValue;
//		switch (item.colType) {
//			case DBType(String): writeValue = new string(inValue); break;
//			case DBType(Int32): writeValue = new int(atoi(inValue)); break;
//			case DBType(Double): writeValue = new double(atof(inValue)); break;
//			case DBType(Date): writeValue = new DBDate(inValue); break;
//		}
//		row.push_back(writeValue);
//	}
//	return row;
//}
//void DBTableTxt::addRow() {
//	data.push_back(createRow());
//}
//void DBTableTxt::deleteRow(int index) {
//	data.erase(data.begin()+index-1);
//}
//int DBTableTxt::getSize() { return data.size(); }
//void DBTableTxt::setFileName(string path) { tablePath = path; }
//void DBTableTxt::setTableName(string tName) { tableName = tName; }
//void DBTableTxt::setPrimaryKey(string key) { primaryKey = key; }
//string DBTableTxt::getFileName() { return tablePath; }
//string DBTableTxt::getTableName() { return tableName; }
//string DBTableTxt::getPrimaryKey() { return primaryKey; }
//TableHeader DBTableTxt::getHeader() { return tableHeader; }
//void DBTableTxt::setHeader(TableHeader& hdr) { tableHeader = hdr; }
//Row DBTableTxt::getRow(int index) { return data[index]; }