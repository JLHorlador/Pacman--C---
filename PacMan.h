/*
 * PacMan.h
 *
 *  Created on: Jan 7, 2016
 *      Author: TheAsianGuy
 */
#ifndef PACMAN_H
#define PACMAN_H

#include <string>
#include "PacBoard.h"

class PacBoard;

class PacMan
{
private:
	PacBoard* myBoard;

	int keyInput;
	int pacX;
	int pacY;

	bool pacTeleport;

	std::string pacMovement[2];
public:
	PacMan(PacBoard* mb);
	int getPacX();
	int getPacY();
	void arrowKeyInput();
	void movePacMan();
	void teleport();
};

#endif
