#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

void Board::DrawCell(const Location& loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);

	gfx.DrawRectDim(centerX + loc.x * dimension + padding, centerY + loc.y * dimension + padding, dimension-padding*2, dimension-padding*2, c);
}

void Board::DrawBorder(Color c)
{
	// lewa kreska alternartywa
	//gfx.DrawRect(centerX - padding - borderThickness,
	//	centerY - padding,
	//	centerX - padding, centerY + height * dimension, c);

	// lewa kreska
	gfx.DrawRectDim(centerX - borderThickness,
		centerY,
		borderThickness,
		height*dimension,
		c);

	//// (x - 5 jako gruboœæ), (y musi pokryæ padding górnej kreski)
	//// dolna kreska
	gfx.DrawRectDim(centerX - borderThickness,
		centerY + height * dimension,
		width*dimension+borderThickness,
		borderThickness,
		c);
	//// (x tak samo jak wy¿ej), (y to d³ugoœæ planszy + centerY), (width musi pokryæ gruboœæ 5 i padding 3 aby kreski siê ³¹czy³y)
	//// prawa kreska
	gfx.DrawRectDim(centerX + width * dimension,
		centerY,
		borderThickness,
		height * dimension+borderThickness,
		c);
	//// (x to koniec planszy), (y to centerY), (), (d³ugoœæ musi dodatkowo pogryæ gruboœæ dolnej kreski czyli 5) 
	//// górna kreska
	gfx.DrawRectDim(centerX - borderThickness,
		centerY-borderThickness,
		width*dimension+borderThickness*2,
		borderThickness,
		c);
	// (x - 3 jako padding - 5 jako gruboœæ), (y musi pokryæ gruboœæ 5 i padding 3), (d³ugoœæ musi zape³niæ gruboœæ prawej i lewej kreski), ()
}

void Board::InitObstacles(std::mt19937& rng)
{
	std::uniform_int_distribution<int> xDist(1, GetGridWidth() - 2);
	std::uniform_int_distribution<int> yDist(1, GetGridHeight() - 2);

	for (int i = 0; i < nObstacles; i++) {
		
		do {
			obstacles[i] = { xDist(rng), yDist(rng) };
		} while ((obstacles[i].x == (GetGridWidth() / 2)) && (obstacles[i].y == (GetGridHeight() / 2)));
	}
}

const Location& Board::CreateNewObstacle(std::mt19937& rng)
{
	std::uniform_int_distribution<int> xDist(1, GetGridWidth() - 2);
	std::uniform_int_distribution<int> yDist(1, GetGridHeight() - 2);

	obstacles[nObstacles] = { xDist(rng), yDist(rng) };
	nObstacles++;

	return obstacles[nObstacles - 1];
}

void Board::DrawObstacles(Color c)
{
	for (int i = 0; i < nObstacles; i++) {
		DrawCell(obstacles[i], c);
	}
}

bool Board::DoesColideWithBorder(const Location& loc)
{
	if (loc.x < 0 || loc.x >= width)
		return true;
	if (loc.y < 0 || loc.y >= height)
		return true;

	return false;
}

bool Board::DoesColideWithObstacle(const Location& loc)
{
	for (int i = 0; i < nObstacles; i++) {
		if (loc == obstacles[i]) {
			return true;
		}
	}
	return false;
}

int Board::GetGridWidth()
{
	return width;
}

int Board::GetGridHeight()
{
	return height;
}
