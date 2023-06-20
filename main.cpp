// MYSQL DRIVERS HEADER FILES
#include <mysql_driver.h>
// #include <mysql_connection.h>
// INPUT OUTPUT HEADER FILE
#include <iostream>

using namespace std;

int main() {
  sql::mysql::MySQL_Driver *driver;
  sql::Connection *con;

  // Create a MySQL Connector/C++ driver object
  driver = sql::mysql::get_mysql_driver_instance();

  // Create a connection to the MySQL database
  con = driver->connect("tcp://localhost:3306", "root", "password");
  if(con){
    cout<<"Connected"<<endl;
  }else{
    cout<<"Connection failed"<<endl;
  }

  // Select the database to use
  con->setSchema("cpp");

  // Perform database operations
  // Close the connection
  delete con;

  return 0;
}
