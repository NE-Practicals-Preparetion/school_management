#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include <mysql_driver.h>
#include <Student.h>

class Database {
public:
    Database();
    ~Database();

    bool connect();
    void disconnect();

    bool insertStudent(int id,const std::string& name, int age, const std::string& grade);
    bool updateStudent(int id, const std::string& name, int age, const std::string& grade);
    bool deleteStudent(int id);
    std::vector<Student> getAllStudents();
    int getNextId();

private:
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* connection;
};

#endif // DATABASE_H
