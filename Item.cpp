#include "Item.h"
#include "Actor.h"
#include "Globals.h"


using namespace std;


Item::Item(int hp, int x, int y)
	 :Object(hp, x, y) { }


Item::~Item() { }


bool Item::move(int)
{
	return setPosition(getX(), getY() - 1);
}


Gatorade::Gatorade(int hp, int x, int y)
		 :Item(hp, x, y) { }

Gatorade::~Gatorade() { }

void Gatorade::handleCollision(Actor* player)
{
	player->setHp(player->getHp() + this->getHp());
	this->setHp(0);
}

Block::Block()
	:Item(-1, -1, -1) 
{  }

Block::Block(int hp, int x, int y)
	  :Item(hp, x, y) { }

Block::~Block() { } 

void Block::handleCollision(Actor* player)
{
	if (this->getHp() > player->getHp())
		player->setHp(0);
	else
		player->setHp(player->getHp() - this->getHp());
}


FirstAid::FirstAid(int hp, int x, int y)
		 :Item(hp, x, y) { }

FirstAid::~FirstAid() { }


void FirstAid::handleCollision(Actor* player)
{
	player->setHp(player->getHp() + this->getHp());
}

Bomb::Bomb(int hp, int x, int y)
	 :Item(hp, x, y) { }

Bomb::~Bomb() { }

void Bomb::handleCollision(Actor* player)
{
	player->setHp(0);
}