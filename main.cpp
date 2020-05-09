#include <iostream>

using namespace std;

//commands 
class Command 
{
public: 
	virtual ~Command() {}
	virtual void execute(players) = 0; 
}; 

class upCommand : public Command
{
public: 
	virtual void execute(players) 
	{ 
	players.up(); 
	}
};

class leftCommand : public Command
{
public: 
	virtual void execute(players) 
	{ 
	players.left(); 
	}
};

class downCommand : public Command
{
public: 
	virtual void execute(players) 
	{
	players.down(); 
	}
};

class rightCommand : public Command
{
public: 
	virtual void execute(players) 
	{
	players.right(); 
	}
};

class InputHandler
{
public: 
	void handleInput(); 

   //Methods to bind commnands 
private:
	Command* buttonW_; 
	Command* buttonA_; 
	Command* buttonS_; 
	Command* buttonD_; 
};

Command* InputHandler::handleInput()
{
	if (isPressed(BUTTON_W)) return buttonW_();
	if (isPressed(BUTTON_A)) return buttonA_(); 
	if (isPressed(BUTTON_S)) return buttonS_(); 
	if (isPressed(BUTTON_D)) return buttonD_();
	
	//nothing pressed, do nothing 
	return NULL;
}

//takes command & runs it on the players 
Command* command = inputHandler.handlerInput(); 
if (command) 
{
	command->execute(players); 
}
	
int main() {
	//loop for command 
	while (!done) 
	{
		char* command = readCommand(); 
		handleCommand(command); 
	}
}
