#include "Actor.h"
#include "Globals.h"

using namespace std;


Actor::Actor(int hp, int x, int y)
	  :Object(hp, x, y) { }

Actor::~Actor() { }


bool Actor::move(int direction) {
	switch (direction) {
	case LEFT:
		return setPosition(getX() - 1, getY());
		break;
	case RIGHT:
		return setPosition(getX() + 1, getY());
		break;
	default:
		return false;
		break;
	}
}


bool Actor::isDead() const
{ return getHp() == 0; }