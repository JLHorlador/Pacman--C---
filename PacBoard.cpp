/*
 * PacBoard.cpp
 *
 *  Created on: Jan 28, 2016
 *      Author: TheAsianGuy
 */

#include "PacBoard.h"
#include "windows.h"
#include <iostream>
#include <string>

PacBoard::PacBoard()
{
	maze = 0;
	mazeString = "";
	pacDots = 245;	//includes powerpellets
	gameTurn = 0;
}

void PacBoard::buildMaze()
{
	maze = new int*[28];
	for (int i = 0; i < 28; i++)
		maze[i] = new int[31];

	for (int y = 0; y < 31; y++)
	{
		for (int x = 0; x < 28; x++)
		{
			if (y == 0 || y == 30)	//top and bottom walls
				maze[x][y] = 'W';
			else if ((x == 0 || x == 27) && y < 10)		//top half side walls
				maze[x][y] = 'W';
			else if ((x == 13 || x == 14) && y < 5)		//middle walls from top wall
				maze[x][y] = 'W';
			else if (((x >= 2 && x <= 5)		//1st row obstacles
					|| (x >= 7 && x <= 11)
					|| (x >= 16 && x <= 20)
					|| (x >= 22 && x <= 25)) && (y >= 2 && y <= 4))
				maze[x][y] = 'W';
			else if (((x >= 2 && x <= 5)		//2nd row obstacles
					|| x == 7 || x == 8
					|| (x >= 10 && x <= 17)
					|| x == 19 || x == 20
					|| (x >= 22 && x <= 25)) && (y == 6 || y == 7))
				maze[x][y] = 'W';
			else if ((x == 7 || x == 8 || x == 13 || x == 14 || x == 19 || x == 20) && y == 8)	//3rd row obstacles
				maze[x][y] = 'W';
			else if ((x <= 5 || (x >= 7 && x <= 11)	//top-middle obstacles
					|| x == 13 || x == 14
					|| (x >= 16 && x <= 20)
					|| x >= 22) && y == 9)
				maze[x][y] = 'W';
			else if (((x >= 7 && x <= 11)
					|| x == 13 || x == 14
					|| (x >= 16 && x <= 20)) && y == 10)
				maze[x][y] = 'W';
			else if ((x >= 9 && x <= 18) && ((y == 11 || y == 17)))
				maze[x][y] = ' ';
			else if ((x == 9 || x == 18) && (y >= 12 && y <= 19))
				maze[x][y] = ' ';
			else if ((x >= 11 && x <= 16) && (y >= 13 && y <= 15))
				maze[x][y] = ' ';
			else if ((x == 12 || x == 15) && (y == 9 || y == 10))
				maze[x][y] = ' ';
			else if (((x >= 0 && x <= 5)
					|| (x >= 22 && x <= 27)
					|| x == 7 || x == 8
					|| x == 19 || x == 20) && y == 14)
				maze[x][y] = ' ';
			else if ((x >= 10 && x <= 17) && (y == 12 || y == 16))
				maze[x][y] = 'W';
			else if ((x == 10 || x == 17) && (y > 12 && y < 16))
				maze[x][y] = 'W';
			else if (((x >= 0 && x < 5) || (x > 22 && x <= 27)) && ((y >= 10 && y <= 12) || (y >= 16 && y <= 18)))
				maze[x][y] = ' ';
			else if ((x <= 5 || x >= 22) && (y == 13 || y == 15))
				maze[x][y] = 'W';
			else if ((x == 7 || x == 8 || x == 19 || x == 20) && ((y > 10 && y <= 13) || (y >= 15 && y <= 19)))
				maze[x][y] = 'W';
			else if ((x >= 10 && x <= 17) && (y == 18 || y == 19))
				maze[x][y] = 'W';
			else if ((x == 13 || x == 14) && (y == 20 || y == 21 || y == 22))
				maze[x][y] = 'W';
			else if (((x > 1 && x <= 5)
					|| (x >= 7 && x <= 11)
					|| (x >= 16 && x <= 20)
					|| (x >= 22 && x < 26)) && (y == 21 || y == 22))
				maze[x][y] = 'W';
			else if ((x == 4 || x == 5 || x == 22 || x == 23) && (y >= 23 && y <= 25))
				maze[x][y] = 'W';
			else if ((x == 1 || x == 2 || x == 7 || x == 8
					|| (x >= 10 && x <= 17)
					|| x == 19 || x == 20 || x == 25 || x == 26) && (y == 24 || y == 25))
				maze[x][y] = 'W';
			else if ((x == 7 || x == 8 || x == 13 || x == 14 || x == 19 || x == 20) && y == 26)
				maze[x][y] = 'W';
			else if (((x >= 2 && x <= 11)
					|| (x == 13 || x == 14)
					|| (x >= 16 && x <= 25)) && (y == 27 || y == 28))
				maze[x][y] = 'W';
			else if ((x == 5 || x == 22) && (y != 14 && (y > 9 && y < 20)))	//inner side walls
				maze[x][y] = 'W';
			else if ((x == 0 || x == 27) && y > 18)	//bottom half side walls
				maze[x][y] = 'W';
			else if ((x <= 5 || x >= 22) && y == 19)	//middle walls from bottom wall
				maze[x][y] = 'W';
			else
				maze[x][y] = '*';
		}
	}

	maze[1][3] = 'O';
	maze[1][23] = 'O';
	maze[26][3] = 'O';
	maze[26][23] = 'O';

	maze[13][12] = 234;
	maze[14][12] = 234;
	maze[13][13] = 234;
	maze[14][13] = 234;

	maze[14][23] = 'C';

	//maze[ghostX][ghostY] = ghostChar;
}

char PacBoard::getMazeAt(int x, int y)
{
	return maze[x][y];
}

void PacBoard::setMazeAt(int x, int y, char c)
{
	maze[x][y] = c;
}

void PacBoard::incrementTurn()
{
	gameTurn++;
}

void PacBoard::decrementDots()
{
	pacDots--;
}

int PacBoard::getGameTurn()
{
	return gameTurn;
}

int PacBoard::getPacDots()
{
	return pacDots;
}

void PacBoard::showMaze()
{
	mazeString = "";

	for (int y = 0; y < 31; y++)
	{
		for (int x = 0; x < 28; x++)
		{
			if (maze[x][y] != 'B')
				mazeString += maze[x][y];
			else
				mazeString += " ";
			mazeString += " ";
		}
		mazeString += "\n";
	}

	COORD coord = {0, 0};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	std::cout << mazeString;

	/*
	for (int y = 0; y < 31; y++)
	{
		for (int x = 0; x < 28; x++)
		{
			if (maze[x][y] == 'W')
				cout << "W";
			else if (maze[x][y] == ' ')
				cout << " ";
			else if (maze[x][y] == 'G')
				cout << "G";
			else if (maze[x][y] == 'C')
				cout << "C";
			else
				cout << "*";
			cout << " ";
		}
		cout << "\n";
	}
	*/
}
