#ifndef GAME_H
#define GAME_H

class Stage;

class Game
{
public:
	// difficulty dertermined by starting HP
	Game();
	~Game();

	void menu();

	// start the game and loop
	void play();


private:
	Stage *stage;
};
	
#endif // !GAME_H
