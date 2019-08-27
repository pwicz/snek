/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include <random>
#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Snake.h"
#include "SpriteCodex.h"
#include "Point.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	void NewObstacleCreation();
	/********************************/
	/*  User Variables              */
	SpriteCodex sc;
	Board brd;
	std::mt19937 rng;
	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> yDist;
	Snake snake;
	static constexpr int pointsCount = 2;
	Point points[pointsCount];
	bool isPressed = false;
	bool gameOver = false;
	bool isStarted = false;
	int timer = 0;
	int gameSpeed = 20;
	int speedPoints[13] = {2, 4, 6, 8, 10, 15, 20, 25, 30, 35, 45, 55, 70};
	int actualSpeedPoint = 0;
	/********************************/
};