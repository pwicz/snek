/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include <random>
#include "MainWindow.h"
#include "Game.h"
#include "Colors.h"


Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	xDist(2, brd.GetGridWidth() - 3),
	yDist(2, brd.GetGridHeight() - 3),
	snake({ brd.GetGridWidth()/2, brd.GetGridHeight()/2 })
{
	brd.InitObstacles(rng);

	for (int i = 0; i < pointsCount; i++) {
		points[i].Respawn({ xDist(rng), yDist(rng) });
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (isStarted) {
		if (!gameOver) {
			if (wnd.kbd.KeyIsPressed('W')) {
				snake.ChangeNextMove({ 0, -1 });
			}
			if (wnd.kbd.KeyIsPressed('D')) {
				snake.ChangeNextMove({ 1, 0 });
			}
			if (wnd.kbd.KeyIsPressed('S')) {
				snake.ChangeNextMove({ 0, 1 });
			}
			if (wnd.kbd.KeyIsPressed('A')) {
				snake.ChangeNextMove({ -1, 0 });
			}

			if (timer == gameSpeed) {
				if (brd.DoesColideWithBorder(snake.GetNextHeadLocation()) || snake.DoesHeadColideWithBody() || brd.DoesColideWithObstacle(snake.GetNextHeadLocation())) {
					gameOver = true;
				}
				else {
					snake.MoveBy();
					timer = 0;
				}
			}
			else
				timer++;

			for (int i = 0; i < pointsCount; i++) {
				if (snake.DoesColideWithHead(points[i].GetLocation())) {
					snake.ChangeBodyColor(rng);
					snake.Grow();

					int snakeEatenPoints = snake.GetEatenPoints();
					if (snakeEatenPoints <= 5) {
						NewObstacleCreation();
					}
					else if (snakeEatenPoints <= 15) {
						for (int i = 0; i < 2; i++) {
							NewObstacleCreation();
						}
					}
					else if (snakeEatenPoints <= 35) {
						for (int i = 0; i < 3; i++) {
							NewObstacleCreation();
						}
					}
					else {
						for (int i = 0; i < 4; i++) {
							NewObstacleCreation();
						}
					}

					do {
						points[i].Respawn({ xDist(rng), yDist(rng) });
					} while (snake.DoesColide(points[i].GetLocation()) || brd.DoesColideWithObstacle(points[i].GetLocation()));

					if (snakeEatenPoints == speedPoints[actualSpeedPoint]) {
						if (actualSpeedPoint < 13)
							actualSpeedPoint++;

						if (gameSpeed > 8)
							gameSpeed -= 2;
						else if (gameSpeed > 1) {
							gameSpeed--;
						}
					}
				}
			}
		}
	}
	else {
		if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
			isStarted = true;
		}
	}
}

void Game::NewObstacleCreation()
{
	Location loc;
	bool colide = false;
	do {
		loc = brd.CreateNewObstacle(rng);
		for (int j = 0; j < pointsCount; j++) {
			colide = points[j].GetLocation() == loc;
		}
	} while (snake.DoesColideWithHead(loc) || colide);
}

void Game::ComposeFrame()
{
	if (isStarted) {
		// draw border
		brd.DrawBorder(Colors::Cyan);
		// draw obstacles
		brd.DrawObstacles(Colors::Gray);
		// draw point
		for (int i = 0; i < pointsCount; i++) {
			points[i].Draw(brd, Colors::Red);
		}
		// draw every segment
		snake.Draw(brd);

		if (gameOver) {
			sc.DrawGameOver(200, 200, gfx);
		}
	}
	else {
		sc.DrawTitle(300, 200, gfx);
	}
	
}
