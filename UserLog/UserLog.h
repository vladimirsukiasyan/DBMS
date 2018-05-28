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
    map<string, string> UserStat;
    fstream logs;

public:
    static UserLog &Instance() {
        // согласно стандарту, этот код ленивый и потокобезопасный
        static UserLog userLog;
        return userLog;
    }

    fstream& getStream(){
        logs.open("../UserLog.txt",fstream::out|fstream::trunc);
        logs.seekp(0, ios::end);
        return logs;
    }

    void getUser() {
        string name;
        cout << "Enter your name, User: ";
        getline(cin, name);
        logs<<endl << "User: " <<name;
        UserName = name;

        time_t t = time(nullptr);
        tm* timeinfo = localtime(&t);
        logs<< endl << "Time: " << asctime(timeinfo);
        logs.close();
    }

    string outUser() {
        return UserName;
    }

    map<string, string>::iterator iter;

    void tOpened(string TableName) {
        UserStat.insert(pair<string, string>(TableName, "Opened"));
    }

    void tUpdated(string TableName) {
        UserStat.insert(pair<string, string>(TableName, "Updated"));
    }

    void tCleared(string TableName) {
        UserStat.insert(pair<string, string>(TableName, "Cleared"));
    }

    void tDeleted(string TableName) {
        UserStat.insert(pair<string, string>(TableName, "Deleted"));
    }

    void tCreated(string TableName) {
        UserStat.insert(pair<string, string>(TableName, "Created"));
    }

    void outUserStat() {
        fstream fileout("../UserLog.txt");
        fileout.seekp(0, ios::end);
        for (iter = UserStat.begin(); iter != UserStat.end(); iter++)
            fileout << "Table: " << (iter->first) << " | Status: " << (iter->second) << endl;
        fileout.close();
    }
};


#endif //DBMS_USERLOG_H
