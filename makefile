all: main.cpp tsp.o solution.o cities.o
	g++ -O3 -std=c++11 main.cpp tsp.o solution.o cities.o -o main

tsp.o: tsp.cpp
	g++ -c -O3 -std=c++11 tsp.cpp

solution.o: solution.cpp
	g++ -c -O3 -std=c++11 solution.cpp

cities.o: cities.cpp
	g++ -c -O3 -std=c++11 cities.cpp

clean:
	rm -rf *.out *.o *.gch
	rm main
