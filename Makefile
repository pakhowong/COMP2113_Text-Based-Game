main.o : main.cpp 
	g++ -c -o main.o main.cpp 

run:
	chmod 755 main.o
	./main.o
