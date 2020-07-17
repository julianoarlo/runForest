#include "Stage.h"
#include "Actor.h"
#include "Item.h"
#include "Globals.h"
#include "UserInterface.h"
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <fstream>
#include <iostream>

using namespace std;


Stage::Stage()
	  :forest(new Actor(20, (int)(WIDTH / 2), HEIGHT - 1)),
	   scr(new Screen(90, 90)),
	   lineCount(0),
	   addedWidth(0)
{

}


void Stage::generateBlocks()
{
	srand(time(0));
	Block* tempBlock = new Block[WIDTH + addedWidth];
	for (int i = 0; i < WIDTH + addedWidth; ++i) {
		tempBlock[i].setAddedWidth(addedWidth);
		tempBlock[i].setHp(rand() % 5);
		tempBlock[i].setPosition(i, 0);
	}
	items.push_back(tempBlock);
}

void Stage::generateHeals(int healValue){
	srand(time(0));
	Gatorade* tempGato = new Gatorade(healValue, rand()%(WIDTH + addedWidth), 0);
	heals.push_back(tempGato);
}

Stage::~Stage()
{
	delete forest;
	Item* temp;
	for (list<Item*>::iterator it = items.begin(); it != items.end(); ++it) {
		temp = *it;
		delete [] temp;
	}
	items.clear();
	for (list<Item*>::iterator it = heals.begin(); it != heals.end(); ++it) {
		temp = *it;
		delete temp;
	}
	heals.clear();
}


bool Stage::isForestDead()
{
	return forest->getHp() == 0;
}


void Stage::display()
{
	scr->gotoXY(WIDTH + addedWidth + 7, 7);
	scr->printString("Player HP: " + to_string(forest->getHp()));

	scr->gotoXY(WIDTH + addedWidth + 7, 9);
	scr->printStringClearLine("Lines: " + to_string(lineCount));

	scr->gotoXY(forest->getX() + 1, forest->getY() + 1);
	scr->printChar('@');

	for (list<Item*>::iterator it = items.begin(); it != items.end(); ++it) {
		for (int i = 0; i < WIDTH + addedWidth; ++i) {
			scr->gotoXY((*it)[i].getX() + 1, (*it)[i].getY() + 1);
			if ((*it)[i].getHp() == 0)
				scr->printChar(' ');
			else
				scr->printChar((*it)[i].getHp() + 48);
		}
	}

	for (list<Item*>::iterator it = heals.begin(); it != heals.end(); ++it) {
		scr->gotoXY((*it)->getX() + 1, (*it)->getY() + 1);
		if ((*it)->getHp() == 0)
			scr->printChar(' ');
		else if ((*it)->getHp() == 1)
			scr->printChar('G');
		else
			scr->printChar('F');
	}
}


void Stage::moveItemsDown()
{
	bool isValidBlock = false;
	bool isValidHeal  = false;
	for (int i = 0; i < WIDTH + addedWidth; ++i)
	{
		if ((*items.begin())[i].getY() == HEIGHT - 1)
		{
			isValidBlock = true;
			break;
		}
		if (!(heals.empty())) {
			if ((*heals.begin())[i].getY() == HEIGHT - 1)
			{
				isValidHeal = true;
				break;
			}
		}
	}

	if (isValidBlock) {
		items.pop_front();
		for (int i = 0; i < WIDTH + addedWidth; ++i) {
			if (forest->getX() != i) {
				scr->gotoXY(i + 1, HEIGHT);
				scr->printChar(' ');
			}
		}
		++lineCount;
		scr->gotoXY(WIDTH + addedWidth + 7, 9);
		scr->printStringClearLine("Lines: " + to_string(lineCount));
	}

	if (isValidHeal) {
		scr->gotoXY((*heals.begin())->getX() + 1, (*heals.begin())->getY() + 1);
		scr->printChar(' ');
		heals.pop_front();
	}


	for (list<Item*>::iterator it = items.begin(); it != items.end(); ++it) {
		for (int i = 0; i < WIDTH + addedWidth; ++i) {
			if (willCollide(&((*it)[i]))) {
				(*it)[i].handleCollision(forest);
				scr->gotoXY((*it)[i].getX() + 1, (*it)[i].getY() + 1);
				scr->printChar(' ');
				scr->gotoXY(WIDTH + addedWidth + 7, 7);
				scr->printStringClearLine("Player HP:" + to_string(forest->getHp()));
			}
			else {
				scr->gotoXY((*it)[i].getX() + 1, (*it)[i].getY() + 1);
				scr->printChar(' ');
				(*it)[i].setPosition((*it)[i].getX(), (*it)[i].getY() + 1);
				scr->gotoXY((*it)[i].getX() + 1, (*it)[i].getY() + 1);
				if ((*it)[i].getHp() == 0)
					scr->printChar(' ');
				else
					scr->printChar((*it)[i].getHp() + 48);
			}
		}
	}

	for (list<Item*>::iterator it = heals.begin(); it != heals.end(); ++it) {
		if (it == heals.begin() && willCollide(*it)) {
			(*it)->handleCollision(forest);
			scr->gotoXY((*it)->getX() + 1, (*it)->getY() + 1);
			scr->printChar(' ');
			scr->gotoXY(WIDTH + addedWidth + 7, 7);
			scr->printStringClearLine("Player HP:" + to_string(forest->getHp()));
		}
		else {
			scr->gotoXY((*it)->getX() + 1, (*it)->getY() + 1);
			scr->printChar(' ');
			(*it)->setPosition((*it)->getX(), (*it)->getY() + 1);
			scr->gotoXY((*it)->getX() + 1, (*it)->getY() + 1);
			if ((*it)->getHp() == 0)
				scr->printChar(' ');
			else if ((*it)->getHp() == 1)
				scr->printChar('G');
			else
				scr->printChar('F');
		}
	}	
}

void Stage::moveForest(int direction)
{
	int step;
	switch (direction) {
	case LEFT:
		step = -1;
		break;
	case RIGHT:
		step = 1;
		break;
	default:
		step = 0;
		break;
	}

	Item* someObject = getObjectAt(forest->getX() + step, forest->getY());
	if (someObject == nullptr || someObject->getHp() == 0) {
		if (forest->move(direction)) {
			scr->gotoXY(forest->getX() - step + 1, HEIGHT);
			scr->printChar(' ');
			scr->gotoXY(forest->getX() + 1, HEIGHT);
			scr->printChar('@');
			if (isHeals()) {
				scr->gotoXY(WIDTH + addedWidth + 7, 7);
				scr->printStringClearLine("Player HP:" + to_string(forest->getHp()));
			}
		}
	}
}



Item* Stage::getObjectAt(int x, int y)
{
	for (list<Item*>::iterator it = items.begin(); it != items.end(); ++it) {
		if ((*it)[x].getY() == y)
			return &((*it)[x]);
	}

	return nullptr;
}

bool Stage::isHeals()
{
	if (!heals.empty()) {
		if (forest->getX() == (*heals.begin())->getX() &&
			forest->getY() == (*heals.begin())->getY()) {
			(*heals.begin())->handleCollision(forest);
			heals.pop_front();
			return true;
		}
	}
	return false;
}


bool Stage::willCollide(Item* item) const
{
	if (item->getX() == forest->getX() &&
		item->getY() + 1 == forest->getY())
		return true;
	else
		return false;
}

void Stage::clear()
{
	scr->clear();
}

void Stage::gameover()
{
	scr->clear();
	ifstream my_file("gameover.txt");
	string temp;
	int yAxis;
	
    yAxis = 0;
    if (my_file.is_open()) {
    	while(getline(my_file, temp)) {
    		scr->gotoXY(0, yAxis);
    		scr->printString(temp);
    		++yAxis;
    	}
    }
	my_file.close();
	waitForEnter();
}

void Stage::won()
{
	scr->clear();
	ifstream my_file("won.txt");
	string temp;
	int yAxis = 0;
    if (my_file.is_open()) {
    	while(getline(my_file, temp)) {
    		scr->gotoXY(0, yAxis);
    		scr->printString(temp);
    		++yAxis;
    	}
    }

	my_file.close();
	scr->gotoXY(30, 26);
	scr->printString("GOOD JOB!");
	scr->gotoXY(30, 28);
	scr->printString("YOU BROKE THE WALL!");

	waitForEnter();
}

void Stage::startMenu() 
{
	scr->clear();
	ifstream my_file("start.txt");
	string temp;
	int yAxis = 0;
	if (my_file.is_open()) {
		while(getline(my_file, temp)) {
			scr->gotoXY(0, yAxis++);
			scr->printString(temp);
		}
	}
	my_file.close();
	scr->gotoXY(10, yAxis + 3);
	scr->printString("--Select Options--");
	scr->gotoXY(10, yAxis + 5);
	scr->printString("[1] EASY Mode (11 blocks) ..ARE YOU A BABY?");
	scr->gotoXY(10, yAxis + 7);
	scr->printString("[2] OKAY Mode (15 blocks) ..DECENT \"Gamer\"");
	scr->gotoXY(10, yAxis + 9);
	scr->printString("[3] HARD Mode (27 blocks) ..MUST BE UCLA STUDENT");
	scr->gotoXY(10, yAxis + 11);
	scr->printString("[4] NOPE Mode (53 blocks) ..DONT DO IT");

	char selection = '\0';
	bool selected = false;
	while (selection == '\0') {
		if (getCharIfAny(selection)) {
			switch (selection) {
			case '1':
				addedWidth = 2;
				break;
			case '2':
				addedWidth = 6;
				break;
			case '3':
				addedWidth = 18;
				break;
			case '4':
				addedWidth = 44;
				break;
			default:
				break;
			}
		}
	}
	//waitForEnter();
	forest->setAddedWidth(addedWidth);
	forest->setPosition((WIDTH + addedWidth) / 2, HEIGHT - 1);


	scr->clear();
	srand(static_cast<unsigned int>(time(NULL)));
	for (int i = 0; i < HEIGHT + 2; ++i) {
		scr->gotoXY(0, i);
		scr->printChar('#');
		scr->gotoXY(WIDTH + addedWidth + 1, i);
		scr->printChar('#');
	}
	for (int i = 0; i < WIDTH + addedWidth + 2; ++i) {
		scr->gotoXY(i, 0);
		scr->printChar('#');
		scr->gotoXY(i, HEIGHT + 1);
		scr->printChar('#');
	}


	Block* tempBlock = new Block[WIDTH + addedWidth];
	for (int i = 0; i < WIDTH + addedWidth; ++i) {
		tempBlock[i].setAddedWidth(addedWidth);
		tempBlock[i].setHp(rand() % 5);
		tempBlock[i].setPosition(i, 0);
	}
	items.push_back(tempBlock);

	scr->gotoXY(WIDTH + addedWidth + 7, 7);
	scr->printString("Player HP: " + to_string(forest->getHp()));

	scr->gotoXY(WIDTH + addedWidth + 7, 9);
	scr->printStringClearLine("Lines: " + to_string(lineCount));

	scr->gotoXY(forest->getX() + 1, forest->getY() + 1);
	scr->printChar('@');

    //display();

}

int Stage::getLineCount() const
{ return lineCount; }

void Stage::resets()
{
	lineCount = 0;
	addedWidth = 0;
	if (!items.empty())
		items.clear();
	if (!heals.empty())
		heals.clear();
	forest->setHp(20);
	forest->setPosition((WIDTH)/2, HEIGHT - 1);
}