#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <stdlib.h>

#include <cgicc/CgiDefs.h>
#include <cgicc/Cgicc.h>
#include <cgicc/HTTPHTMLHeader.h>
#include <cgicc/HTMLClasses.h>
#include "cJSON.h"
using namespace std;
using namespace cgicc;

int main ()
{
   Cgicc formData;

   cout << "Content-type:text/html;charset=utf-8\n\n";
   cout << "<html>\n";
   cout << "<head>\n";
   cout << "<title>向 CGI 程序传递文本区域数据</title>\n";
   cout << "</head>\n";
   cout << "<body>\n";

   form_iterator fi = formData.getElement("msg");
   if( !fi->isEmpty() && fi != (*formData).end()) {
      cout << "Text Content: " << **fi << endl;
   }else{
      cout << "No text entered" << endl;
   }
   fi = formData.getElement("op");
   if( !fi->isEmpty() && fi != (*formData).end()) {
      cout << "Text Content: " << **fi << endl;
   }else{
      cout << "No text entered" << endl;
   }
   fi = formData.getElement("myjsn");
	  if( !fi->isEmpty() && fi != (*formData).end()) {
		 cout << "Text Content: " << **fi << endl;
		char *out;
		cJSON *json;
		char str[1024];
		int len = (**fi).length();
		(**fi).copy(str, len,0);
		*(str + len)='\0';
		cout << str << endl;
		json=cJSON_Parse(str);
		if (!json) {printf("Error before: [%s]\n",cJSON_GetErrorPtr());}
		else
		{
			out=cJSON_Print(json);
	//			child = cJSON_GetObjectItem(json, "name");
	//			out=cJSON_Print(child);
			cJSON_Delete(json);
	//		printf("***************:%s\n",out);
	//		printf("\n");
			fprintf(stdout,"get json is %s", out);
			fprintf(stdout,"\n");
			free(out);
		}
	  }else{
		 cout << "No text entered" << endl;
	  }
   cout << "<br/>\n";
   cout << "</body>\n";
   cout << "</html>\n";

   return 0;
}