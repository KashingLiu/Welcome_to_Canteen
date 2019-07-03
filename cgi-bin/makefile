all: target

target: cJSON.o h_identify.o
	gcc -o h_identify.cgi cJSON.o h_identify.o -lm
cJSON.o: cJSON.c cJSON.h
	gcc -c -o cJSON.o cJSON.c
h_identify.o: h_identify.c cJSON.h
	gcc -c -o h_identify.o h_identify.c
clean:
	rm -rf h_identify *.o

refresh: clean target