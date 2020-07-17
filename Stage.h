#ifndef STAGE_H
#define STAGE_H
#include <iostream>
#include <vector>
#include <list>

class Actor;
class Item;
class Screen;

class Stage
{
private:
	Actor *forest;
	std::list<Item*> items;
	std::list<Item*> heals;
	Screen *scr;
	int lineCount;
	int addedWidth;

public:
	Stage();

	void generateBlocks();

	void generateHeals(int);

	virtual ~Stage();

	bool isForestDead();

	// Displays current stage to the screen
	void display();

	// At every timestep, move all items down
	void moveItemsDown();

	// If we get user input, move forest unless collision with wall.
	void moveForest(int direction);

	// Return an item at X,Y or nullptr if nothing
	Item* getObjectAt(int, int);

	bool isHeals();

	bool willCollide(Item*) const;
	
	//char getCharAt(int x, int y);

	void clear();

	void gameover();

	void won();

	void startMenu();

	int getLineCount() const;

	void resets();

};
#endif

