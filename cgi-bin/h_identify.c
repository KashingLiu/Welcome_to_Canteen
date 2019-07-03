#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "cJSON.h"

#define MAXLEN 1024

char* getcgidata(FILE* fp, char* requestmethod);

int main(void)
{
//	char cgistr[] = "{\n\"name\": \"Jack (\\\"Bee\\\") Nimble\", \n\"format\": {\"type\":       \"rect\", \n\"width\":      1920, \n\"height\":     1080, \n\"interlace\":  false,\"frame rate\": 24\n}\n}";

    char * cgistr = NULL;
    char * req_method = NULL;
    printf( "Content-type: application/text;charset=utf-8\n\n" );
    req_method = getenv("REQUEST_METHOD");
    cgistr = getcgidata(stdin, req_method);

	printf("input:%s\n", cgistr);
    char *out;cJSON *json;

	json=cJSON_Parse(cgistr);
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

    fprintf(stdout,"you post param is %s",cgistr);
}

char* getcgidata(FILE* fp, char* requestmethod)
{
    char* input;
    int len;
    int size = MAXLEN;
    int i = 0;

    if (!strcmp(requestmethod, "GET")) // for GET method
    {
        input = getenv("QUERY_STRING");
        return input;
    }
    else if (!strcmp(requestmethod, "POST")) // for POST method
    {
        len = atoi(getenv("CONTENT_LENGTH"));
        input = (char*)malloc(sizeof(char)*(size + 1));


        if (len == 0)
        {
            input[0] = '\0';
            return input;
        }

        while(1)
        {
            input[i] = (char)fgetc(fp);
            if (i == size)
        {
            input[i+1] = '\0';
            return input;
        }

        --len;
        if (feof(fp) || (!(len)))
        {
            i++;
            input[i] = '\0';
            return input;
        }
            i++;

        }
    }
    return NULL;
}
