#include <iostream>

using namespace std;

//commands 
void InputHandler::handleInput()
{
	if (isPressed(BUTTON_W)) up()-> execute(); 
	else if (isPressed(BUTTON_A)) left()-> execute(); 
	else if (isPressed(BUTTON_S)) down()-> execute(); 
	else if (isPressed(BUTTON_D)) right()-> execute(); 
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
public: 
	void handleInput(); 
private:
	Command* buttonX_; 
	Command* buttonY_; 
	Command* buttonA_; 
	Command* buttonB_; 
};

void 
	
int main() {
	//loop for command 
	while (!done) 
	{
		char* command = readCommand(); 
		handleCommand(command); 
	}
}
