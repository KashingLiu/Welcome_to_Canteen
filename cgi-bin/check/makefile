ROOT_DIR=../
CJSON_DIR=$(ROOT_DIR)cJSON/
test = h_check
all: target
target: cJSON.o $(test).o
	g++ -o $(test).cgi $(CJSON_DIR)cJSON.o $(test).o -lcgicc -lm -lwiringPi
cJSON.o: $(CJSON_DIR)cJSON.c $(CJSON_DIR)cJSON.h
	gcc -c -o cJSON.o $(CJSON_DIR)cJSON.c
$(test).o: $(test).cpp
	g++ -c -o $(test).o $(test).cpp -I$(CJSON_DIR) 
clean:
	rm -rf $(test).cgi *.o
refresh: clean target

