#include "Game.h"
#include "Stage.h"
#include "UserInterface.h"
#include "Globals.h"

using namespace std;

Game::Game()
	 :stage(new Stage) { }

Game::~Game()
{ delete stage; }

void Game::menu() {
	stage->startMenu();
}

void Game::play()
{
	bool playOn = true;
	char input = ARROW_LEFT;
	unsigned long int elapser = 30000;
	bool cont = true;
	int counter = 0;
	while (playOn) {
		if (!cont) {
			elapser = 30000;
			stage->resets();
			stage->startMenu();
			cont = true;
		}
        Timer timer;

		while (timer.elapsed() < elapser / 100) {
			if (getCharIfAny(input)) {
				switch (input) {
				case ARROW_LEFT:
					stage->moveForest(0);
					break;
				case ARROW_RIGHT:
					stage->moveForest(1);
					break;
				case 'q':
					stage->clear();
					playOn = false;
					break;
				default:
					break;
				}
			}
		}

		if (playOn) {
			stage->moveItemsDown();
			if (stage->isForestDead()) {
				cont = false;
				stage->gameover();
				stage->clear();
			}
			if (stage->getLineCount() >= 52) {
				cont = false;
				stage->won();
				stage->clear();
			}
			else {
				counter++;
				if ((counter + 1) % 10 == 0)
					stage->generateBlocks();
				if ((counter + 6) % 20 == 0) {
					if (rand() % 3 == 0) {
						if (rand() % 3 == 0) {
							stage->generateHeals(5);
						}
						else
							stage->generateHeals(1);
					}
				}
			}
			elapser -= 35;
		}
	}
}
