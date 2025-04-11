all:
	g++ -std=c++17 main.cpp poly.cpp tests/* -o run
	./run

valcheck:
	g++ -std=c++17 main.cpp poly.cpp tests/* -o run
	valgrind --leak-check=full --track-origins=yes ./run

