cmake_minimum_required(VERSION 3.10)
project(DBMS)

set(CMAKE_CXX_STANDARD 11)

add_executable(DBMS main.cpp DatabaseManager/DatabaseManager.cpp DatabaseManager/DatabaseManager.h Client/Client.cpp Client/Client.h CRUDManager/CRUDManager.cpp CRUDManager/CRUDManager.h DBDate/DBDate.cpp DBDate/DBDate.h Table/Table.cpp Table/Table.h TableManager/TablesManager.cpp TableManager/TablesManager.h)