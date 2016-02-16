/*
 * PacGame.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: TheAsianGuy
 */
#include "PacBoard.h"
#include "PacMan.h"
#include "Ghost.h"
#include "Windows.h"
#include "conio.h"
#include <iostream>

int endType;

bool gameEnd;

char ghostIcon;
char readyMessage[6] = {'R', 'E', 'A', 'D', 'Y', '!'};

void startGame(PacBoard* board)
{
	board->buildMaze();

	int readyIndex = 0;
	for (int i = 11; i <= 16; i++)
	{
		board->setMazeAt(i, 17, readyMessage[readyIndex]);
		readyIndex++;
	}

	board->showMaze();
	Sleep(5000);

	for (int j = 11; j <= 16; j++)
	{
		board->setMazeAt(j, 17, ' ');
	}
}

int main()
{
	ghostIcon = 234;
	endType = 0;
	gameEnd = false;
	PacBoard* board = new PacBoard();
	PacMan* player = new PacMan(board);
	Ghost* ghost1 = new Ghost(13, 12, ghostIcon, board, player);
	Ghost* ghost2 = new Ghost(14, 12, ghostIcon, board, player);
	Ghost* ghost3 = new Ghost(13, 13, ghostIcon, board, player);
	Ghost* ghost4 = new Ghost(14, 13, ghostIcon, board, player);
	startGame(board);

	/*
	//sample ghost declaration and removal
	Ghost* mg = new Ghost(4,5);
	delete mg;
	mg = new Ghost(5,4);
	*/

	while (!gameEnd)
	{
		if (kbhit())
			player->arrowKeyInput();
		board->incrementTurn();
		//system("cls");
		player->movePacMan();
		ghost1->moveGhost();
		ghost2->moveGhost();
		ghost3->moveGhost();
		ghost4->moveGhost();
		board->showMaze();
		//std::cout << "frontOfGhost: " << (char)ghost1->getFrontOfGhost() << "\n";
		//std::cout << "Pacdots: " << board->getPacDots() << "\n";
		//std::cout << "dotType: " << ghost1->getDotType() << "\n";
		//std::cout << "frontOfGhost: " << ghost1->getFrontOfGhost() << "\n";
		//std::cout << "atGhost: " << ghost1->getAtGhost() << "\n";
		//std::cout << "behindGhost: " << ghost1->getBehindGhost() << "\n";		//TODO: Set up behindGhost var in Ghost.cpp
		Sleep(100);
		if (kbhit())
			player->arrowKeyInput();
		if (board->getPacDots() == 0 || (ghost1->collideWithPlayer())) //|| ghost2->collideWithPlayer() || ghost3->collideWithPlayer() || ghost4->collideWithPlayer()))
		{
			if (board->getPacDots() == 0)
				endType = 1;
			gameEnd = true;
		}
	}

	if (endType == 1)
		std::cout << "You win!";
	else
		std::cout << "You got eaten!";

	delete board;
	delete player;
	delete ghost1;
	delete ghost2;
	delete ghost3;
	delete ghost4;

	std::cin.ignore();
	return 0;
}
