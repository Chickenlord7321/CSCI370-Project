# Author: Caleb Bronn
# Last Update: 10 Apr 2025

GXX = g++ -std=c++11
CFLAGS = -Wall -Wextra

go: main.o
	$(GXX) -o ../go main.o app.o server.o
	@echo "Ready to go!"

main.o: main.cpp app.o server.o
	$(GXX) -c $(CFLAGS) main.cpp -o main.o

app.o: app.cpp server.o
	$(GXX) -c $(CFLAGS) app.cpp -o app.o

server.o: server.cpp
	$(GXX) -c $(CFLAGS) server.cpp -o server.o

clean:
	rm -f *.o go*
