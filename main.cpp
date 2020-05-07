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

class upCommand : public Command
{
public: 
	virtual void execute() { up(); }
};

class leftCommand : public Command
{
public: 
	virtual void execute() { left(); }
};

class downCommand : public Command
{
public: 
	virtual void execute() { down(); }
};

class rightCommand : public Command
{
public: 
	virtual void execute() { right(); }
};

class InputHandler
{
	
int main() {
	//loop for command 
	while (!done) 
	{
		char* command = readCommand(); 
		handleCommand(command); 
	}
}
