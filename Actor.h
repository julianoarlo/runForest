#ifndef ACTOR_H
#define ACTOR_H

#include "Object.h"

// class Stage;

class Actor : public Object
{
public:
	Actor(int, int, int);

	virtual ~Actor();

	// moving left or right
	bool move(int direction); 

	//return true if the actor's hp is 0
	bool isDead() const;

//private:
//	bool m_isDead;

	// to access getObjectAt(int x, int y)
	// Stage* m_stage;
};

#endif // !1

