# Author: Caleb Bronn
# Last Update: 6 Apr 2025
# This makefile is for testing httplib_test.cpp
# It's intended to be an alternative way to compile the code in order to see what is going wrong with it.

GXX = g++
CFLAGS = -Wall -Wextra -v
CROWFLAGS = -lpthread

goTest: test.o
	$(GXX) -o goHttp test.o

test.o: httplib_test.cpp http.o json.o
	$(GXX) -c $(CFLAGS) httplib_test.cpp -o test.o

json.o: ../include/nlohmann/json.hpp
	$(GXX) -c $(CFLAGS) ../include/nlohmann/json.hpp -o json.o

http.o: ../include/httplib.h
	$(GXX) -c $(CFLAGS) ../include/httplib.h -o http.o

#go: main.o
#	$(GXX) -o go main.o
#	@echo "Ready to go!"

#main.o: main.cpp
#	$(GXX) -c $(CFLAGS) $(CROWFLAGS) main.cpp main.o

clean:
	rm -f *.o go*
