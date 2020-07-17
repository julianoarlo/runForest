#ifndef OBJECT_H
#define OBJECT_H

class Object
{
public:

	Object(int, int, int);

	virtual ~Object();

	//Accessors
	int getX() const;
	int getY() const;
	int getHp() const;
	int getAddedWidth() const;

	//Setters
	void setHp(int);
	bool setPosition(int, int);
	void setAddedWidth(int);


	// every object moves differently (items move down, play moves horizontally)
	virtual bool move(int) = 0;

private:
	int m_hp;
	int m_x;
	int m_y;
	int m_addedWidth;
};

#endif // !OBJECT_H
