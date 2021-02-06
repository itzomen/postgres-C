#include <iostream>
#include <fstream>
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
        "CREATE TABLE BOOKS(" \
        "ID INT PRIMARY KEY     NOT NULL," \
        "TITLE         CHAR(50)," \
        "AUTHOR      CHAR(50) );"
        
        );

        W.commit();
        cout << "Table created successfully" << endl;
        C.disconnect ();
    } catch (const std::exception &e) {
        string log;
        // open file for writing
        ofstream writeToLibrary;
        writeToLibrary.open("logs.dat", ios::app);
        log = to_string(e.what());
        // write
        writeToLibrary << log << endl;
        // close the opened file.
        writeToLibrary.close();
    }
}

void SaveToDb(string count, string title, string author) {
    try {
      connection C("dbname = mydatabase user = eufresia password = password hostaddr = 127.0.0.1 port = 5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
      }


      /* Create a transactional object. */
      work W(C);

      /* SQL query */
      string sql = "INSERT INTO BOOKS (ID,TITLE,AUTHOR)" \
        "VALUES ('" + count + "', '" + title + "', '" + author+ "');";

      /* Execute SQL query */
      W.exec( sql );

      W.commit();
      cout << "Records created successfully" << endl;
      C.disconnect ();
    } catch (const std::exception &e) {
        string log;
        // open file for writing
        ofstream writeToLibrary;
        writeToLibrary.open("logs.dat", ios::app);
        log = to_string(e.what());
        // write
        writeToLibrary << log << endl;
        // close the opened file.
        writeToLibrary.close();
    }

}

void updateDb(string count, string title, string author) {
    
    try {
        connection C("dbname = mydatabase user = eufresia password = password hostaddr = 127.0.0.1 port = 5432");
        if (C.is_open()) {
            cout << "Opened database successfully: " << C.dbname() << endl;
        } else {
            cout << "Can't open database" << endl;
        }
        
        /* Create a transactional object. */
        work W(C);

        /* SQL query */
        string sql = "UPDATE BOOKS set TITLE = '" + title + "', AUTHOR = '" + author+ "' where ID=" + count + " ";

      
        
        /* Execute SQL query */
        W.exec( sql );
        W.commit();
        cout << "Records updated successfully" << endl;
        

        /* Create a non-transactional object. */
        nontransaction N(C);
        
        cout << "Operation done successfully" << endl;
        C.disconnect ();
    } catch (const std::exception &e) {
        string log;
        // open file for writing
        ofstream writeToLibrary;
        writeToLibrary.open("logs.dat", ios::app);
        log = to_string(e.what());
        // write
        writeToLibrary << log << endl;
        // close the opened file.
        writeToLibrary.close();
    }
}

void Delete(string count) {
    
    try {
        connection C("dbname = mydatabase user = eufresia password = password hostaddr = 127.0.0.1 port = 5432");
        if (C.is_open()) {
            cout << "Opened database successfully: " << C.dbname() << endl;
        } else {
            cout << "Can't open database" << endl;
        }
        
        /* Create a transactional object. */
        work W(C);

        /* SQL query */
        string sql = "DELETE from BOOKS where ID=" + count + " ";

      
        
        /* Execute SQL query */
        W.exec( sql );
        W.commit();
        cout << "Records updated successfully" << endl;
        

        /* Create a non-transactional object. */
        nontransaction N(C);
        
        cout << "Operation done successfully" << endl;
        C.disconnect ();
    } catch (const std::exception &e) {
        cerr << e.what() << std::endl;
    }
}

void showBook() {
        try {
            connection C("dbname = mydatabase user = eufresia password = password hostaddr = 127.0.0.1 port = 5432");
            if (C.is_open()) {
                cout << "Opened database successfully: " << C.dbname() << endl;
            } else {
                cout << "Can't open database" << endl;
            }


            /* Create a non-transactional object. */
            nontransaction N(C);
            
            /* Execute SQL query */
            result R( N.exec( "SELECT * from BOOKS"));
            
            /* List down all the records */
            for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
                cout << "ID = " << c[0].as<int>() << endl;
                cout << "Title = " << c[1].as<string>() << endl;
                cout << "Author = " << c[2].as<string>() << endl;
            }
            cout << "Operation done successfully" << endl;
            C.disconnect ();
        } catch (const std::exception &e) {
            string log;
            // open file for writing
            ofstream writeToLibrary;
            writeToLibrary.open("logs.dat", ios::app);
            log = to_string(e.what());
            // write
            writeToLibrary << log << endl;
            // close the opened file.
            writeToLibrary.close();
        }
}