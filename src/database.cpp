#include <database.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>
#include <Student.h>

Database::Database() : driver(nullptr), connection(nullptr) {}

Database::~Database()
{
    disconnect();
}

bool Database::connect()
{
    driver = sql::mysql::get_mysql_driver_instance();

    const std::string host = "tcp://localhost:3306";
    const std::string user = "root";
    const std::string password = "password";
    const std::string database = "school_mis";

    try
    {
        connection = driver->connect(host, user, password);
        connection->setSchema(database);
    }
    catch (sql::SQLException &e)
    {
        // Handle error: Failed to connect to MySQL database
        return false;
    }

    return true;
}

void Database::disconnect()
{
    if (connection)
    {
        delete connection;
        connection = nullptr;
    }
}

bool Database::insertStudent(int id, const std::string &name, int age, const std::string &grade)
{
    try
    {
        sql::PreparedStatement *pstmt;
        pstmt = connection->prepareStatement("INSERT INTO students (id,name, age, grade) VALUES (?, ?, ?, ?)");
        pstmt->setInt(1, id);
        pstmt->setString(2, name);
        pstmt->setInt(3, age);
        pstmt->setString(4, grade);
        pstmt->executeUpdate();
        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        // Handle error: Failed to execute the query
        return false;
    }

    return true;
}

bool Database::updateStudent(int id, const std::string &name, int age, const std::string &grade)
{
    try
    {
        sql::PreparedStatement *pstmt;
        pstmt = connection->prepareStatement("UPDATE students SET name = ?, age = ?, grade = ? WHERE id = ?");
        pstmt->setString(1, name);
        pstmt->setInt(2, age);
        pstmt->setString(3, grade);
        pstmt->setInt(4, id);
        pstmt->executeUpdate();
        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        // Handle error: Failed to execute the query
        return false;
    }

    return true;
}

bool Database::deleteStudent(int id)
{
    try
    {
        sql::PreparedStatement *pstmt;
        pstmt = connection->prepareStatement("DELETE FROM students WHERE id = ?");
        pstmt->setInt(1, id);
        pstmt->executeUpdate();
        delete pstmt;
    }
    catch (sql::SQLException &e)
    {
        // Handle error: Failed to execute the query
        return false;
    }

    return true;
}

std::vector<Student> Database::getAllStudents()
{
    std::vector<Student> students;

    try
    {
        sql::Statement *stmt;
        stmt = connection->createStatement();
        sql::ResultSet *res = stmt->executeQuery("SELECT * FROM students");

        while (res->next())
        {
            int id = res->getInt("id");
            std::string name = res->getString("name");
            int age = res->getInt("age");
            std::string grade = res->getString("grade");

            Student student(id,name, age, grade);
            students.push_back(student);
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException &e)
    {
        // Handle error: Failed to execute the query
        return students;
    }

    return students;
}


int Database::getNextId() {
    // Prepare the SQL statement to retrieve the next ID
    sql::PreparedStatement *stmt;
    sql::ResultSet *res;
    int nextId = 0;

    stmt = connection->prepareStatement("SELECT MAX(id) AS max_id FROM students");
    res = stmt->executeQuery();

    // Retrieve the next ID
    if (res->next()) {
        nextId = res->getInt("max_id") + 1;
    }

    // Clean up resources
    delete res;
    delete stmt;

    return nextId;
}
