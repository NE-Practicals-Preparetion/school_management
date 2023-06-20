#include <Student.h>

Student::Student(int id, const std::string &name, int age, const std::string &grade)
    : id(id), name(name), age(age), grade(grade) {}

Student::~Student() {}

int Student::getId() const
{
    return id;
}

std::string Student::getName() const
{
    return name;
}

int Student::getAge() const
{
    return age;
}

std::string Student::getGrade() const
{
    return grade;
}

void Student::setName(std::string name)
{
    this->name = name;
}
void Student::setAge(int age)
{
    this->age = age;
}
void Student::setGrade(std::string grade)
{
    this->grade = grade;
}
