# Author: Caleb Bronn
# Last Update: 13 Mar 2025

GXX = g++
CFLAGS = -Wall -Wextra
CROWFLAGS = -lpthread


go: main.o
	$(GXX) -o go main.o
	@echo "Ready to go!"

main.o: main.cpp
	$(GXX) -c $(CFLAGS) $(CROWFLAGS) main.cpp main.o

clean:
	rm -f *.o go
