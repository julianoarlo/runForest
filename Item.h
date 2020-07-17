#ifndef ITEM_H
#define ITEM_H

#include "Object.h"

class Actor;
class Item : public Object
{
public:
	Item(int, int, int);

	virtual ~Item();

	//move down
	bool move(int direction);

	//does nothing if no collision, else handle collision
	virtual void handleCollision(Actor*) = 0  ;
};

class Gatorade : public Item
{
public:
	Gatorade(int, int, int);

	virtual ~Gatorade();

	//give hp
	void handleCollision(Actor*);
};

class Block : public Item
{
public:
	Block();
	Block(int, int, int);

	virtual ~Block();

	//take away hp
	void handleCollision(Actor*);
};

class FirstAid : public Item
{
public:
	FirstAid(int, int, int);

	virtual ~FirstAid();

	void handleCollision(Actor*);
};


class Bomb : public Item
{
public:
	Bomb(int, int, int);
	virtual ~Bomb();

	void handleCollision(Actor*);
};


#endif // !BOX_H

