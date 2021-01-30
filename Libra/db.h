#include <iostream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

void CreateTable (){
    try {
        connection C("dbname = mydatabase user = eufresia password = password hostaddr = 127.0.0.1 port = 5432");
        if (C.is_open()) {
            cout << "Opened database successfully: " << C.dbname() << endl;
        } else {
            cout << "Can't open database" << endl;
        }

        /* Create a transactional object. */
        work W(C);
        
        /* Execute SQL query */
        W.exec( 
        /* Create SQL statement */
        "CREATE TABLE BOOK(" \
        "ID INT PRIMARY KEY     NOT NULL," \
        "TITLE         CHAR(50)," \
        "AUTHOR      CHAR(50) );"
        
        );

        W.commit();
        cout << "Table created successfully" << endl;
        C.disconnect ();
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
    }
}