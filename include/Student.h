#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student
{
public:
    Student(int id, const std::string &name, int age, const std::string &grade);
    ~Student();

    int getId() const;
    std::string getName() const;
    int getAge() const;
    std::string getGrade() const;
    void setName(std::string name);
    void setGrade(std::string grade);
    void setAge(int age);

private:
    int id;
    std::string name;
    int age;
    std::string grade;
};

#endif // STUDENT_H
