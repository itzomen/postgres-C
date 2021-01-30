#include <iostream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

int main(int argc, char* argv[]) {
   char * sql;
   
   try {
      connection C("dbname = mydatabase user = eufresia password = password hostaddr = 127.0.0.1 port = 5432");
      if (C.is_open()) {
         cout << "Opened database successfully: " << C.dbname() << endl;
      } else {
         cout << "Can't open database" << endl;
         return 1;
      }


      /* Create a transactional object. */
      work W(C);
      
      /* Execute SQL query */
      W.exec( 
          /* Create SQL statement */
        "INSERT INTO BOOK (ID,NAME,AUTHOR,PUB_NAME) "  \
        "VALUES (1, 'Mystery', 'Mendes', 'Book'); " \
        "INSERT INTO BOOK (ID,NAME,AUTHOR,PUB_NAME) "  \
        "VALUES (2, 'Round Dis', 'Hungary', 'Deny'); "     \
        "INSERT INTO BOOK (ID,NAME,AUTHOR,PUB_NAME)" \
        "VALUES (3, 'Jump High', 'Sharon', 'Love Lies');" \
        "INSERT INTO BOOK (ID,NAME,AUTHOR,PUB_NAME)" \
        "VALUES (4, 'Mystery', 'Mendes', 'Book');"

       );
      W.commit();
      cout << "Records created successfully" << endl;
      C.disconnect ();
   } catch (const std::exception &e) {
      cerr << e.what() << std::endl;
      return 1;
   }

   return 0;
}