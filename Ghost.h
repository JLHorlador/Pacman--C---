/*
 * Ghost.h
 *
 *  Created on: Jan 28, 2016
 *      Author: TheAsianGuy
 */
#ifndef GHOST_H
#define GHOST_H

#include <string>
#include "PacBoard.h"
#include "PacMan.h"

class PacBoard;
class PacMan;

class Ghost
{
private:
	PacBoard* myBoard;
	PacMan* player;
	int turn;
	int pacX;
	int pacY;
	int ghostX;
	int ghostY;
	int tempX;
	int tempY;
	int ghostDotX;
	int ghostDotY;
	int ghostDirections;
	int randomNumber;

	char dotType;
	char ghostChar;
	char atGhost;
	char frontOfGhost;
	char behindGhost;

	bool ghostTeleported;
	bool ghostPassDot;

	std::string ghostMovement;
	std::string ghostTurnable[3];
	std::string foo;

public:
	Ghost(int xStart, int yStart, char ghostSymbol, PacBoard* mb, PacMan* pl);
	int getGhostX();
	int getGhostY();
	char getAtGhost();
	char getFrontOfGhost();
	char getBehindGhost();
	char getDotType();
	std::string ghostTurn();
	void moveGhost();
	void ghostTeleport();
	void checkForDots();
	bool collideWithPlayer();
};

#endif
