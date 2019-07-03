
target = test_json
all: $(target)

$(target): cJSON.o test.o
	gcc -o $(target) cJSON.o test.o -lm
cJSON.o: cJSON.c cJSON.h test.c
	gcc -c -o cJSON.o cJSON.c
test.o: test.c cJSON.h
	gcc -c -o test.o test.c
clean:
	rm -rf $(target) *.o
