#include <iostream>

using namespace std;

//commands 
class Command 
{
public: 
	virtual ~Command() {}
	virtual void execute(player) = 0; 
}; 

class upCommand : public Command
{
public:
	virtual void execute(player) 
	{ 
	player.up();
	}
};

class leftCommand : public Command
{
public: 
	virtual void execute(player) 
	{ 
	player.left(); 
	}
};

class downCommand : public Command
{
public: 
	virtual void execute(player) 
	{
	player.down(); 
	}
};

class rightCommand : public Command
{
public: 
	virtual void execute(player) 
	{
	player.right(); 
	}
};

class quitCommand : public Command
{
public: 
	virtual void execute(player)
	{
	player.quit();
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
	Command* buttonQ_; 
};

Command* InputHandler::handleInput()
{
	if (isPressed(BUTTON_W)) return buttonW_();
	if (isPressed(BUTTON_A)) return buttonA_(); 
	if (isPressed(BUTTON_S)) return buttonS_(); 
	if (isPressed(BUTTON_D)) return buttonD_();
	if (isPressed(BUTTON_Q)) return buttonQ_(); 
	
	//nothing pressed, do nothing 
	return NULL;
}

//takes command & runs it on the players 
Command* command = inputHandler.handlerInput(); 
if (command) 
{
	command->execute(player); 
}

void players_movement()
{
	int x, y;
	char command; 
	
	x = player.x; //0
	y = player.y; //0 
	
	switch(command) 
	{
		case 'W': 
		//Move up 
			if (y - 1 >= 0) 
			{
				if ((stage[y - 1][x] == '.') || (stage[y - 1][x] == 'P')) 
				{
					stage[y][x] = '.';
					stage[y - 1][x] = 'm';
					player.y--;
				}
			}
			break;
		case 'A':
		//move left 
			if (x - 1 >= 0) 
			{
				if ((stage[y][x - 1] == '.') || (stage[y][x - 1] == 'P')) 
				{
					stage[y][x] = '.';
					stage[y][x - 1] = 'm';
					player.x--;
				}
			}
			break;	
		case 'S':
		//move down 
			if (y + 1 >= 0) 
			{
				if ((stage[y + 1][x] == '.') || (stage[y + 1][x] == 'P')) 
				{
					stage[y][x] = '.';
					stage[y + 1][x] = 'm';
					player.y++;
				}
			}
			break;
		case 'D':
		//move right 
			if (x + 1 >= 0) 
			{
				if ((stage[y][x + 1] == '.') || (stage[y][x + 1] == 'P')) 
				{
					stage[y][x] = '.';
					stage[y][x + 1] = 'm';
					player.x++;
				}
			}
			break;
		case 'Q':
		//quit 
			if(isGameover == true) 
			{
				return;
			}
			break; 
	}
}

int main() {
	//loop for command 
	while (!done) 
	{
		char* command = readCommand(); 
		handleCommand(command); 
	}
}

//save and load 
if ("exit") 
{
	cout << "Want to quit? (Y/N)" << endl; 
	string quit; 
	cin >> quit; 
	if (quit == "Y") 
	{
		cout << "Do you want to save your status? (Y/N)" << endl; 
		string save; 
		cin >> save; 
		if (save == "Y") 
		{
			currentMap.saveMap(); 
			currentMap.saveObjects(); 
			currentPlayer.savePlayer(); 
			currentPlayer.getMonsters().saveMonsters(); 
			currentPlayer.getBlood().saveBlood(); 
		}
		else if (save == "N") 
		{
			currentPlayer.setHealth(0); 
		}
	}
}

