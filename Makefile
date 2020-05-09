main.out: main.cpp
	g++ -g main.cpp -o main.out

run:
	chmod 755 main.out
	./main.out
