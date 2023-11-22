bank.exe: bank.o
	g++ -std=c++11 -g -Wall bank.o -o bank.exe

bank.o: bank.cpp
	g++ -std=c++11 -g -Wall -c bank.cpp

clean:
	rm *.o bank.exe
