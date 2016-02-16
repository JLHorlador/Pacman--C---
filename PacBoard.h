/*
 * PacBoard.h
 *
 *  Created on: Jan 28, 2016
 *      Author: TheAsianGuy
 */
#ifndef PACBOARD_H
#define PACBOARD_H

#include <string>

class PacMan;
class Ghost;

class PacBoard
{
private:
	int** maze;
	int pacDots;
	int gameTurn;

	std::string mazeString;
public:
	PacBoard();
	char getMazeAt(int x, int y);
	void setMazeAt(int x, int y, char c);
	void showMaze();
	void buildMaze();
	void incrementTurn();
	void decrementDots();
	int getPacDots();
	int getGameTurn();
};

#endif
