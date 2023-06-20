#include <iostream>
#include <vector>
#include <Student.h>
#include <database.h>

void displayMenu() {
    std::cout << "\nWelcome to the School Management System!\n";
    std::cout << "Please select an option:\n";
    std::cout << "1. Add a student\n";
    std::cout << "2. View all students\n";
    std::cout << "3. Update a student\n";
    std::cout << "4. Delete a student\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    int choice = 0;
    std::vector<Student> students;
    Database database;

    // Connect to the database
    if (database.connect()) {
        std::cout << "Connected to the database successfully!\n";
        // Create the students table if it doesn't exist
        // database.createTable();
    } else {
        std::cout << "Failed to connect to the database.\n";
        return 1;
    }

    while (choice != 5) {
        displayMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string name, grade;
                int age;
                std::cout << "Enter student name: ";
                std::cin.ignore();
                std::getline(std::cin, name);
                std::cout << "Enter student age: ";
                std::cin >> age;
                std::cout << "Enter student grade: ";
                std::cin.ignore();
                std::getline(std::cin, grade);

                // Create a new Student object
                int newId = database.getNextId();
                Student newStudent(newId, name, age, grade);

                // Insert the student record into the database
                if (database.insertStudent(newId, name, age, grade)) {
                    // Add the student to the vector
                    students.push_back(newStudent);
                    std::cout << "Student added successfully!\n";
                } else {
                    std::cout << "Failed to add student to the database.\n";
                }
                break;
            }
            case 2: {
                // Retrieve all student records from the database
                students = database.getAllStudents();

                if (students.empty()) {
                    std::cout << "No students found.\n";
                } else {
                    std::cout << "\nAll Students:\n";
                    for (const auto& student : students) {
                        std::cout << "Name: " << student.getName() << "\n";
                        std::cout << "Age: " << student.getAge() << "\n";
                        std::cout << "Grade: " << student.getGrade() << "\n\n";
                    }
                }
                break;
            }
            case 3: {
                students = database.getAllStudents();
                if (students.empty()) {
                    std::cout << "No students found. Please add a student first.\n";
                    break;
                }

                int updateId;
                std::cout << "Enter the ID of the student to update: ";
                std::cin >> updateId;

                // Find the student in the vector
                auto it = std::find_if(students.begin(), students.end(), [updateId](const Student& student) {
                    return student.getId() == updateId;
                });

                if (it != students.end()) {
                    std::string newName, newGrade;
                    int newAge;
                    std::cout << "Enter new name: ";
                    std::cin.ignore();
                    std::getline(std::cin, newName);
                    std::cout << "Enter new age: ";
                    std::cin >> newAge;
                    std::cout << "Enter new grade: ";
                    std::cin.ignore();
                    std::getline(std::cin, newGrade);

                    // Update the student record in the database
                    if (database.updateStudent(updateId, newName, newAge, newGrade)) {
                        // Update the student in the vector
                        it->setName(newName);
                        it->setAge(newAge);
                        it->setGrade(newGrade);
                        std::cout << "Student updated successfully!\n";
                    } else {
                        std::cout << "Failed to update student.\n";
                    }
                } else {
                    std::cout << "Student not found.\n";
                }
                break;
            }
            case 4: {
                if (students.empty()) {
                    std::cout << "No students found. Please add a student first.\n";
                    break;
                }

                int deleteId;
                std::cout << "Enter the ID of the student to delete: ";
                std::cin >> deleteId;

                // Find the student in the vector
                auto it = std::find_if(students.begin(), students.end(), [deleteId](const Student& student) {
                    return student.getId() == deleteId;
                });

                if (it != students.end()) {
                    // Delete the student record from the database
                    if (database.deleteStudent(deleteId)) {
                        // Remove the student from the vector
                        students.erase(it);
                        std::cout << "Student deleted successfully!\n";
                    } else {
                        std::cout << "Failed to delete student.\n";
                    }
                } else {
                    std::cout << "Student not found.\n";
                }
                break;
            }
            case 5:
                std::cout << "Exiting the program. Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }

    // Disconnect from the database
    database.disconnect();

    return 0;
}
