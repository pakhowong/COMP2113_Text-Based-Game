#include <iostream>

using namespace std;

//commands 
void InputHandler::handleInput()
{
	if (isPressed(BUTTON_W)) up(); 
	else if (isPressed(BUTTON_A)) left(); 
	else if (isPressed(BUTTON_S)) down(); 
	else if (isPressed(BUTTON_D)) right(); 
}

class Command 
{
public: 
	virtual ~Command() {}
	virtual void execute() = 0; 
}; 


int main() {
	//loop for command 
	while (!done) 
	{
		char* command = readCommand(); 
		handleCommand(command); 
	}
}
