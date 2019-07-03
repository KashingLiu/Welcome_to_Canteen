#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include "cJSON.h"
using namespace std;
using namespace cgicc;

static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main ()
{
    sqlite3 *db;
    char *zErrMsg = 0;
    char *sql;
    int rc;
    const char* data = "Callback function called";
    rc = sqlite3_open("/home/pi/nfs/canteen.db", &db);
    if (rc) {
        cout << "cannot open db" << sqlite3_errmsg(db);
    }

    sql = "SELECT * FROM dish_category";
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }else{
        fprintf(stdout, "Operation done successfully\n");
    }
    sqlite3_close(db);

//   	Cgicc formData;
//	cout << "Content-type:text/html;charset=utf-8\n\n";	// !REQUIRED!
//	// prepare response json
//	cJSON *products,*detail,*array;
//	cJSON *fmt,*root;
//
//	int id[4] = {1,2,3,4};
//	int quantity[4] = {1,0,5,2};
//	char * string[4] = {"compass", "jacket", "hiking", "test"};
//	// 创建一个cJSON对象
//	products=cJSON_CreateObject();
//
//	array = cJSON_CreateArray();
//	for ( int i = 0; i < 4; i++) {
//	    cJSON * ArrayItem = cJSON_CreateObject();
//	    cJSON_AddNumberToObject(ArrayItem, "id", id[i]);
//	    cJSON_AddNumberToObject(ArrayItem, "quantity", quantity[i]);
//	    cJSON_AddStringToObject(ArrayItem, "name", string[i]);
//	    cJSON_AddItemToArray(array, ArrayItem);
//	}
//
//	cJSON_AddItemToObject(products, "products", array);



//	char *out;
//	out=cJSON_Print(products);	cJSON_Delete(products);	printf("%s\n",out);	free(out);	/* Print to text, Delete the cJSON, print it, release the string. */

   return 0;
}