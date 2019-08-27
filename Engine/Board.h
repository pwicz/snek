#pragma once

#include "Graphics.h"
#include "Location.h"
#include <random>

class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c);
	void DrawBorder(Color c);
	void InitObstacles(std::mt19937& rng);
	const Location& CreateNewObstacle(std::mt19937& rng);
	void DrawObstacles(Color c);
	bool DoesColideWithBorder(const Location& loc);
	bool DoesColideWithObstacle(const Location& loc);
	int GetGridWidth();
	int GetGridHeight();
private:
	static constexpr int dimension = 17;
	static constexpr int width = 46;
	static constexpr int height = 34;
	static constexpr int centerX = (Graphics::ScreenWidth - (width * dimension)) / 2;
	static constexpr int centerY = (Graphics::ScreenHeight - (height * dimension)) / 2;
	static constexpr int padding = 1 ;
	static constexpr int borderThickness = 7;
	int nObstacles = 5;
	Location obstacles[500];
	Graphics& gfx;
};