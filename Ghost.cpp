/*
 * Ghost.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: TheAsianGuy
 */

#include "Ghost.h"
#include <cstdlib>
#include <iostream>


#define ghostLocation myBoard->getMazeAt(ghostX, ghostY)
#define aboveGhost myBoard->getMazeAt(ghostX, ghostY - 1)
#define belowGhost myBoard->getMazeAt(ghostX, ghostY + 1)
#define leftGhost myBoard->getMazeAt(ghostX - 1, ghostY)
#define rightGhost myBoard->getMazeAt(ghostX + 1, ghostY)

Ghost::Ghost(int xStart, int yStart, char ghostSymbol, PacBoard* mb, PacMan* pl)
{
	myBoard = mb;
	player = pl;
	ghostChar = ghostSymbol;
	turn = 0;
	pacX = 0;
	pacY = 0;
	ghostX = xStart;
	ghostY = yStart;
	tempX = 0;
	tempY = 0;
	ghostDotX = 0;
	ghostDotY = 0;
	ghostDirections = 0;
	randomNumber = 0;
	ghostTeleported = false;
	ghostPassDot = false;
	ghostMovement = "UP";
	foo = "";
	dotType = ' ';
	atGhost = ' ';
	frontOfGhost = ' ';
	behindGhost = ' ';
}

void Ghost::moveGhost()
{
	myBoard->setMazeAt(ghostX, ghostY, dotType);

	tempX = ghostX;
	tempY = ghostY;

	checkForDots();

	ghostTeleport();

	behindGhost = atGhost;

	if (ghostTeleported == true && (myBoard->getMazeAt(1, 14) == 'G' || myBoard->getMazeAt(26, 14) == 'G'))
		ghostTeleported = false;

	if (ghostMovement == "UP")
	{
		atGhost = aboveGhost;
		ghostY = ghostY-1;
		frontOfGhost = aboveGhost;
	}
	else if (ghostMovement == "RIGHT")
	{
		atGhost = rightGhost;
		ghostX = ghostX+1;
		frontOfGhost = rightGhost;
	}
	else if (ghostMovement == "DOWN")
	{
		atGhost = belowGhost;
		ghostY = ghostY+1;
		frontOfGhost = belowGhost;
	}
	else if (ghostMovement == "LEFT")
	{
		atGhost = leftGhost;
		ghostX = ghostX-1;
		frontOfGhost = leftGhost;
	}

	if (myBoard->getMazeAt(ghostX, ghostY) != 'W')
		myBoard->setMazeAt(ghostX, ghostY, ghostChar);
	else
	{
		ghostX = tempX;
		ghostY = tempY;
		myBoard->setMazeAt(ghostX, ghostY, ghostChar);
	}

	if (ghostPassDot == true && (ghostX != ghostDotX || ghostY != ghostDotY))
	{
		myBoard->setMazeAt(ghostDotX, ghostDotY, dotType);
		ghostPassDot = false;
	}

	myBoard->setMazeAt(tempX, tempY, dotType);

	if (atGhost == ' ' && (behindGhost == '*' || behindGhost == 'O'))
	{
		if (behindGhost == 'O')
		{
			if (ghostMovement == "UP")
				myBoard->setMazeAt(ghostX, ghostY + 1, 'O');
			else if (ghostMovement == "DOWN")
				myBoard->setMazeAt(ghostX, ghostY - 1, 'O');
			else if (ghostMovement == "RIGHT")
				myBoard->setMazeAt(ghostX - 1, ghostY, 'O');
			else if (ghostMovement == "LEFT")
				myBoard->setMazeAt(ghostX + 1, ghostY, 'O');
		}
		else
		{
			if (ghostMovement == "UP")
				myBoard->setMazeAt(ghostX, ghostY + 1, '*');
			else if (ghostMovement == "DOWN")
				myBoard->setMazeAt(ghostX, ghostY - 1, '*');
			else if (ghostMovement == "RIGHT")
				myBoard->setMazeAt(ghostX - 1, ghostY, '*');
			else if (ghostMovement == "LEFT")
				myBoard->setMazeAt(ghostX + 1, ghostY, '*');
		}
		//std::cout << "TRUE" << "\n";
	}
}

std::string Ghost::ghostTurn()
{
	ghostDirections = 0;
	ghostTurnable[0] = "";
	ghostTurnable[1] = "";
	ghostTurnable[2] = "";
	randomNumber = 0;

	if (aboveGhost != 'W' && ghostMovement != "DOWN")
	{
		ghostTurnable[ghostDirections] = "UP";
		ghostDirections++;
	}
	if (rightGhost != 'W' && ghostMovement != "LEFT")
	{
		ghostTurnable[ghostDirections] = "RIGHT";
		ghostDirections++;
	}
	if (belowGhost != 'W' && belowGhost != 'B' && ghostMovement != "UP")
	{
		ghostTurnable[ghostDirections] = "DOWN";
		ghostDirections++;
	}
	if (leftGhost != 'W' && ghostMovement != "RIGHT")
	{
		ghostTurnable[ghostDirections] = "LEFT";
		ghostDirections++;
	}

	randomNumber = rand() % ghostDirections;
	return ghostTurnable[randomNumber];
}

void Ghost::ghostTeleport()
{
	ghostTeleported = false;
	if ((ghostX == 1 || ghostX == 26) && ghostY == 14 && ghostTeleported == false)
	{
		if (ghostX == 1)
		{
			ghostMovement = "LEFT";
			ghostX = 26;
		}
		else
		{
			ghostMovement = "RIGHT";
			ghostX = 1;
		}
		ghostTeleported = true;
	}
}

void Ghost::checkForDots()
{
	dotType = ' ';
	ghostPassDot = false;
	ghostMovement = ghostTurn();
	if (ghostPassDot == false && ((ghostMovement == "UP" && (aboveGhost == '*' || aboveGhost == 'O'))
			|| (ghostMovement == "RIGHT" && (rightGhost == '*' || rightGhost == 'O'))
			|| (ghostMovement == "DOWN" && (belowGhost == '*' || belowGhost == 'O'))
			|| (ghostMovement == "LEFT" && (leftGhost == '*' || leftGhost == 'O'))))
	{
		if (atGhost != ' ')
		{
			ghostDotX = ghostX;
			ghostDotY = ghostY;
			if (atGhost == 'O')
				dotType = 'O';
			else
				dotType = '*';
			ghostPassDot = true;
		}
	}
	/*
	else
	{
		if (ghostMovement == "UP")
		{
			myBoard->setMazeAt(ghostX, ghostY + 1, '*');
		}
		else if (ghostMovement == "RIGHT")
		{
			myBoard->setMazeAt(ghostX - 1, ghostY, '*');
		}
		else if (ghostMovement == "DOWN")
		{
			myBoard->setMazeAt(ghostX, ghostY - 1, '*');
		}
		else
			myBoard->setMazeAt(ghostX + 1, ghostY, '*');
	}
	*/
}

int Ghost::getGhostX()
{
	return ghostX;
}

int Ghost::getGhostY()
{
	return ghostY;
}

char Ghost::getAtGhost()
{
	return atGhost;
}

char Ghost::getFrontOfGhost()
{
	return frontOfGhost;
}

char Ghost::getBehindGhost()
{
	return behindGhost;
}

char Ghost::getDotType()
{
	return dotType;
}

bool Ghost::collideWithPlayer()
{
	pacX = player->getPacX();
	pacY = player->getPacY();
	if (ghostX == pacX && ghostY == pacY)
		return true;
	return false;
}
