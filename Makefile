battle.o : battle.cpp 
	g++ -c -o battle.o battle.cpp 

map.o : map.cpp 
	g++ -c -o map.o map.cpp 

commandMovement.o : commandMovement.cpp
	g++ -c -o commandMovement.o commandMovement.cpp 

enemy_items.o : enemy_ items.cpp 
	g++ -c -o enemy_items.o enemy_items.cpp 

gameover_victory.o : gameover_victory.cpp 
	g++ -c -o gameover_victory.o gameover_victory.cpp 

save_load_start_refresh.o : save_load_start_refresh.cpp
	g++ -c -o save_load_start_refresh.o save_load_start_refresh.cpp

stages.o : stages.cpp 
	g++ -c -o stages.o stages.cpp 

main.o : main.cpp 
	g++ -c -o main.o main.cpp 

battle.out : battle.o map.o commandMovement.o enemy_items.o gameover_victory.o save_load_start_refresh.o stages.o main.o 
	g++ -o battle.out battle.o map.o commandMovement.o enemy_items.o gameover_victory.o save_load_start_refresh.o stages.o main.o 

clean:
	rm *.o  
