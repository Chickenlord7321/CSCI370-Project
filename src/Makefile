# Author: Caleb Bronn
# Last Update: 10 Apr 2025

GXX = g++-4.9 -std=c++11	# allows us to use C++11 methods like Regex
CFLAGS = -I/usr/local/lib/Oracle/instantclient_11_2/sdk/include
LFLAGS = -L/usr/local/lib/Oracle/instantclient_11_2 -locci -lociei

go: main.o
	$(GXX) $(LFLAGS) -o ../go main.o app.o server.o
	@echo "Ready to go!"

main.o: main.cpp app.o server.o
	$(GXX) -c $(CFLAGS) main.cpp -o main.o

app.o: app.cpp server.o
	$(GXX) -c $(CFLAGS) app.cpp -o app.o

server.o: server.cpp
	$(GXX) -c $(CFLAGS) server.cpp -o server.o

clean:
	rm -f *.o go*
