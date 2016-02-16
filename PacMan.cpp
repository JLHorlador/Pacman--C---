/*
 * PacMan.cpp
 *
 *  Created on: Jan 7, 2016
 *      Author: TheAsianGuy
 */

#include "Conio.h"
#include "PacMan.h"
#include <iostream>

#define UpArrow 72
#define DownArrow 80
#define RightArrow 77
#define LeftArrow 75

PacMan::PacMan(PacBoard* mb)
{
	myBoard = mb;
	keyInput = 0;
	pacX = 14;
	pacY = 23;
	pacTeleport = false;
	pacMovement[0] = "LEFT";
	pacMovement[1] = "LEFT";
}

void PacMan::teleport()
{
	pacTeleport = false;
	if (pacTeleport == false && pacY == 14 && (pacX == 0 || pacX == 27))
	{
		if (pacX == 0)
			pacX = 27;
		else
			pacX = 0;
		pacTeleport = true;
	}
}

void PacMan::movePacMan()
{
	myBoard->setMazeAt(pacX, pacY, ' ');

	int tempX = pacX;
	int tempY = pacY;

	if (pacMovement[0] == "UP")
		pacY = pacY-1;
	else if (pacMovement[0] == "DOWN")
		pacY = pacY+1;
	else if (pacMovement[0] == "RIGHT")
		pacX = pacX+1;
	else if (pacMovement[0] == "LEFT")
		pacX = pacX-1;

	teleport();

	if (pacTeleport == true && (myBoard->getMazeAt(1, 14) == 'C' || myBoard->getMazeAt(26, 14) == 'C'))
		pacTeleport = false;

	if (myBoard->getMazeAt(pacX, pacY) != 'W')
	{
		if (myBoard->getMazeAt(pacX, pacY) == '*' || myBoard->getMazeAt(pacX, pacY) == 'O')
			myBoard->decrementDots();
		pacMovement[1] = pacMovement[0];
		myBoard->setMazeAt(pacX, pacY, 'C');
	}
	else
	{
		pacX = tempX;
		pacY = tempY;
		myBoard->setMazeAt(pacX, pacY, 'C');
		pacMovement[0] = pacMovement[1];
	}
}

void PacMan::arrowKeyInput()
{
	keyInput = getch();

	if (keyInput == 0 || keyInput == 224)
	{
		switch (keyInput = getch())
		{
		case UpArrow:
			pacMovement[0] = "UP";
			//cout << "Up\n";
			break;
		case DownArrow:
			pacMovement[0] = "DOWN";
			//cout << "Down\n";
			break;
		case RightArrow:
			pacMovement[0] = "RIGHT";
			//cout << "Right\n";
			break;
		case LeftArrow:
			pacMovement[0] = "LEFT";
			//cout << "Left\n";
			break;
		default:
			std::cout << "Invalid key";
			break;
		}
	}
}

int PacMan::getPacX()
{
	return pacX;
}

int PacMan::getPacY()
{
	return pacY;
}
