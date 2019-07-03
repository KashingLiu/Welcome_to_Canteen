#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <typeinfo>

#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include "cJSON.h"
using namespace std;
using namespace cgicc;

cJSON *category,*tmp,*array;
vector<int> category_vector;

cJSON *items, *item, *classs, *tmpp;

static int category_item(void *data, int argc, char **argv, char **azColName){
    int i;
    size_t pos;
    tmp = cJSON_CreateObject();
    for(i=0; i<argc; i++){

        if (strcmp(azColName[i], "id") == 0) {
            int d;
            sscanf( argv[i], "%d", &d);
            cJSON_AddNumberToObject(tmp, azColName[i], d);
            category_vector.push_back(d);
        } else {
            cJSON_AddStringToObject(tmp, azColName[i], argv[i]);
        }
    }
    cJSON_AddItemToArray(array, tmp);
    return 0;
}

static int test(void *data, int argc, char **argv, char **azColName){
    int i;
    classs = cJSON_CreateObject();
    for(i=0; i<argc; i++){
        if (strcmp(azColName[i], "price") == 0) {
            double d;
            sscanf( argv[i], "%lf", &d);
            cJSON_AddNumberToObject(classs, azColName[i], d);
        } else {
            cJSON_AddStringToObject(classs, azColName[i], argv[i]);
        }
    }
    cJSON_AddItemToArray(item, classs);
//    printf("\n");
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

    category = cJSON_CreateObject();
    array = cJSON_CreateArray();
    sql = "SELECT * FROM dish_category";
    rc = sqlite3_exec(db, sql, category_item, (void*)data, &zErrMsg);

    cJSON_AddItemToObject(category, "category", array);


    items = cJSON_CreateObject();
    tmpp = cJSON_CreateObject();
    vector<int>::iterator it;
    for(it = category_vector.begin();it!=category_vector.end();it++) {
        string tmp = "SELECT name,price,img,detail FROM dish_item WHERE category = ";
        string num = to_string(*it);
        tmp = tmp + num;
        const char * res = tmp.c_str();


        item = cJSON_CreateArray();
        rc = sqlite3_exec(db, res, test, (void*)data, &zErrMsg);
        cJSON_AddItemToObject(tmpp, num.c_str(), item);
    }

    cJSON_AddItemToObject(category, "items", tmpp);
    sqlite3_close(db);

   	Cgicc formData;
	cout << "Content-type:text/html;charset=utf-8\n\n";	// !REQUIRED!
	// prepare response json
	char *out;
	out=cJSON_Print(category);	cJSON_Delete(category);	printf("%s\n",out);	free(out);	/* Print to text, Delete the cJSON, print it, release the string. */

   return 0;
}