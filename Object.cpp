#include "Object.h"
#include "Globals.h"

using namespace std;

Object::Object(int hp, int x, int y)
	   :m_hp(hp),
	    m_x(x),
	    m_y(y),
	    m_addedWidth(0) { }

Object::~Object() { }

// Pre-condition: 
// Post-condition: 
int Object::getX() const
{ return m_x; }

// Pre-condition: 
// Post-condition: 
int Object::getY() const
{ return m_y; }

// Pre-condition: 
// Post-condition: 
int Object::getHp() const
{ return m_hp; }


int Object::getAddedWidth() const
{ return m_addedWidth; }

// Pre-condition: 
// Post-condition: 
void Object::setHp(int newHp)
{
	m_hp = newHp;
}

// Pre-condition: 
// Post-condition: 
bool Object::setPosition(int newX, int newY)
{
	if (newX < 0) {
		m_x = 0;
		m_y = newY;
		return false;
	}
	else if (newX > WIDTH + m_addedWidth - 1) {
		m_x = WIDTH + m_addedWidth - 1;
		m_y = newY;
		return false;
	}
	else {
		m_x = newX;
		m_y = newY;
		return true;
	}
}

void Object::setAddedWidth(int add)
{
	m_addedWidth = add;
}