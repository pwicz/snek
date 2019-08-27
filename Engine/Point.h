#pragma once

#include "Location.h"
#include "Board.h"

class Point
{
public:
	void Respawn(Location in_loc);
	void Draw(Board& brd, Color c);
	Location GetLocation() const;
private:
	Location loc = { 10,10 };
};