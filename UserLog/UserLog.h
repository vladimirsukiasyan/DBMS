#pragma once
//
// Created by Shysa on 27.05.2018.
//

#ifndef DBMS_USERLOG_H
#define DBMS_USERLOG_H

#include <map>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

//UserLog-класс Singleton!
class UserLog {
private:
    UserLog() {}

    ~UserLog() {}

    UserLog(UserLog const &) = delete;

    UserLog &operator=(UserLog const &) = delete;

    string UserName;
    multimap<string, string> userStateTable,userStateDB;
    fstream logs;

public:
    static UserLog &Instance() {
        // согласно стандарту, этот код ленивый и потокобезопасный
        static UserLog userLog;
        return userLog;
    }

    fstream& openStream(){
        logs.open("../UserLog.txt",fstream::out|fstream::app);
    }

    void getUser() {
        string name;
        cout << "Enter your name, User: ";
        getline(cin, name);
        logs << "User: " <<name;
        UserName = name;

        time_t t = time(nullptr);
        tm* timeinfo = localtime(&t);
        logs<< endl << "Time: " << asctime(timeinfo);
    }

    string outUser() {
        return UserName;
    }

    map<string, string>::iterator iter;

    void dOpened(string databaseName) {
        userStateDB.insert(pair<string, string>(databaseName, "Opened"));
    }

    void dDeleted(string databaseName) {
        userStateDB.insert(pair<string, string>(databaseName, "Deleted"));
    }

    void dCreated(string TableName) {
        userStateDB.insert(pair<string, string>(TableName, "Created"));
    }

    void tOpened(string TableName) {
        userStateTable.insert(pair<string, string>(TableName, "Opened"));
    }

    void tUpdated(string TableName) {
        userStateTable.insert(pair<string, string>(TableName, "Updated"));
    }

    void tCleared(string TableName) {
        userStateTable.insert(pair<string, string>(TableName, "Cleared"));
    }

    void tDeleted(string TableName) {
        userStateTable.insert(pair<string, string>(TableName, "Deleted"));
    }

    void tCreated(string TableName) {
        userStateTable.insert(pair<string, string>(TableName, "Created"));
    }

    void outUserStat() {
        for (auto iter: userStateDB){
            logs <<"--- "<< "Database: " << (iter.first) << " | Status: " << (iter.second) << endl;
        }

        for (auto iter: userStateTable){
            logs <<"--- "<< "Table: " << (iter.first) << " | Status: " << (iter.second) << endl;
        }

        logs<<endl;
        logs.close();
    }
};


#endif //DBMS_USERLOG_H
