#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

// web
#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include "cJSON.h"
// "cJSON.h"应该放在
#include <time.h>

using namespace std;
using namespace cgicc;

int main ()
{
	clock_t start_t, end_t;
	double total_t;
	start_t = clock();
	while(1){
		end_t = clock();
		total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
//		printf("now : %f\n", total_t);
		if(total_t>5.0) {
			break;
		}
	}
   	Cgicc formData;
	cout << "Content-type:text/html;charset=utf-8\n\n";	// !REQUIRED!
	// prepare response json
	cJSON *root,*fmt;
	// 创建一个cJSON对象
	root=cJSON_CreateObject();
	cJSON_AddItemToObject(root, "name", cJSON_CreateString("wxc"));
	cJSON_AddItemToObject(root, "format", fmt=cJSON_CreateObject());
	cJSON_AddStringToObject(fmt,"type",		"rect");
	cJSON_AddNumberToObject(fmt,"width",		1920);
	cJSON_AddNumberToObject(fmt,"height",		1080);

	form_iterator fi = formData.getElement("msg");
	if( !fi->isEmpty() && fi != (*formData).end()) {
//	      cout << "Text Content: " << **fi << endl;
		cJSON_AddItemToObject(root, "msg", cJSON_CreateString((**fi).c_str()));
	}else{
//	      cout << "No text entered" << endl;
		cJSON_AddItemToObject(root, "msg", cJSON_CreateString("no message"));
	}


//   	fi = formData.getElement("myjsn");
//	if( !fi->isEmpty() && fi != (*formData).end()) {
//	 cout << "Text Content: " << **fi << endl;
//	char *out;
//	cJSON *json;
//	char str[1024];
//	int len = (**fi).length();
//	(**fi).copy(str, len,0);
//	*(str + len)='\0';
//	cout << str << endl;
//	json=cJSON_Parse(str);
//	if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
//	else
//	{
//		out=cJSON_Print(json);
//	//			child = cJSON_GetObjectItem(json, "name");
//	//			out=cJSON_Print(child);
//		cJSON_Delete(json);
//	//		printf("***************:%s\n",out);
//	//		printf("\n");
//		fprintf(stdout,"get json is %s", out);
//		fprintf(stdout,"\n");
//		free(out);
//	}
//	}else{
//	 cout << "No text entered" << endl;
//	}


	char *out;
	out=cJSON_Print(root);	cJSON_Delete(root);	printf("%s\n",out);	free(out);	/* Print to text, Delete the cJSON, print it, release the string. */

   return 0;
}
